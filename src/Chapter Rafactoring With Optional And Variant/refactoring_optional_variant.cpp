// refactoring_optional.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

#include <iostream>
#include <tuple>
#include <optional>
#include <variant>
#include <vector>

class ObjSelection {
public:
    bool IsValid() const { return true; }
};

bool CheckSelectionVer1(const ObjSelection &objList, bool *pOutAnyCivilUnits, bool *pOutAnyCombatUnits, int *pOutNumAnimating) {
    if (!objList.IsValid())
        return false;
    
    // local variables:
    int numCivilUnits = 0;
    int numCombat = 0;
    int numAnimating = 0;
    
    // scan...
    
    // set values:
    if (pOutAnyCivilUnits)
        *pOutAnyCivilUnits = numCivilUnits > 0;
        
    if (pOutAnyCombatUnits)
        *pOutAnyCombatUnits = numCombat > 0;
    
    if (pOutNumAnimating)
        *pOutNumAnimating = numAnimating;
    
    return true;
}

std::tuple<bool, bool, bool, int> CheckSelectionVer2(const ObjSelection &objList) {
    if (!objList.IsValid())
        return {false, false, false, 0};
    
    // local variables:
    int numCivilUnits = 0;
    int numCombat = 0;
    int numAnimating = 0;
    
    // scan...
    
    return {true, numCivilUnits > 0, numCombat > 0, numAnimating };
}

struct SelectionData {
    bool anyCivilUnits { false };
    bool anyCombatUnits { false };
    int numAnimating { 0 };
};

std::pair<bool, SelectionData> CheckSelectionVer3(const ObjSelection &objList) {
    SelectionData out;
    
    if (!objList.IsValid())
        return {false, out};

    
    // scan...
    
    return {true, out};
}

std::optional<SelectionData> CheckSelectionVer4(const ObjSelection &objList) {   
    if (!objList.IsValid())
        return std::nullopt;

    SelectionData out;   
    // scan...
    
    return out;
}

enum class [[nodiscard]] ErrorCode {
    InvalidSelection,
    Undefined
};

std::variant<SelectionData, ErrorCode> CheckSelectionVer5(const ObjSelection &objList) {   
    if (!objList.IsValid())
        return ErrorCode::InvalidSelection;

    SelectionData out;   
    // scan...
    
    return out;
}

int main() {
    ObjSelection sel;
    
    bool anyCivilUnits = false;
    bool anyCombatUnits = false;
    int numAnimating = 0;
    if (CheckSelectionVer1(sel, &anyCivilUnits, &anyCombatUnits, &numAnimating))
        std::cout << "ok...\n";
    
    if (auto [ok, anyCivilVer2, anyCombatVer2, numAnimatingVer2] = CheckSelectionVer2(sel); ok)
        std::cout << "ok...\n";
    
    if (auto [ok1, selData] = CheckSelectionVer3(sel); ok1) {
		
	}    
        
    if (auto retV4 = CheckSelectionVer4(sel)) {
        // access via *ret or even ret->
        std::cout << "ok..." << retV4->numAnimating << '\n';
    }
    
    if (auto retV5 = CheckSelectionVer5(sel); std::holds_alternative<SelectionData>(retV5)) {
        std::cout << "ok..." << std::get<SelectionData>(retV5).numAnimating << '\n';
    }
    else {
        switch (std::get<ErrorCode>(retV5)) {
            case ErrorCode::InvalidSelection: std::cerr << "Invalid Selection!\n"; break;
            case ErrorCode::Undefined: std::cerr << "Undefined Error!\n"; break;
        }
    }
}