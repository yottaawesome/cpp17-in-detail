// any_winapi.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

#include <string>
#include <iostream>
#include <any>
#include <utility>
 
void* operator new(std::size_t count) {
    std::cout << " allocating: " << count << " bytes" << std::endl;
    return malloc(count);
} 
 
void operator delete(void* ptr) noexcept {
    std::puts("global op delete called");
    std::free(ptr);
} 

class Message {
public:
    enum class Type {
        Init,
        Closing,
        ShowWindow,        
        DrawWindow
    };
    
public:
    explicit Message(Type type, std::any param) :
        mType(type),
        mParam(param)
    {   }
    explicit Message(Type type) :
        mType(type)
    {   }
    
    Type mType;
    std::any mParam;
};

class Window {
public:
    virtual void HandleMessage(const Message& msg) = 0;
};
 
class DialogWindow : public Window {
public:
    void HandleMessage(const Message& msg) override {
        try {
            switch (msg.mType) {
                case Message::Type::Init:
                    std::cout << "Init\n";
                    break;
                case Message::Type::Closing:
                    std::cout << "Closing\n";
                    break;
                case Message::Type::ShowWindow: {
                    auto pos = std::any_cast<std::pair<int, int>>(msg.mParam);
                    std::cout << "ShowWidow: "<< pos.first << ", " << pos.second << '\n';
                    break;
                }
                case Message::Type::DrawWindow: {
                    auto col = std::any_cast<uint32_t>(msg.mParam);
                    std::cout << "DrawWindow, color: "<< std::hex << col << '\n';
                    break;
                }
            }
        }
        catch(const std::bad_any_cast& e) {
            std::cout << e.what() << '\n';
        }
    }
};
 
int main() {
    auto a = std::make_any<int>(10);
    
    DialogWindow dlg;
    Message m1(Message::Type::Init);
    dlg.HandleMessage(m1);
    Message m2(Message::Type::ShowWindow, std::make_pair(10, 11));
    dlg.HandleMessage(m2);
    Message m3(Message::Type::DrawWindow, static_cast<uint32_t>(0xFF00FFFF));
    dlg.HandleMessage(m3);
    dlg.HandleMessage(Message{Message::Type::Closing});
}