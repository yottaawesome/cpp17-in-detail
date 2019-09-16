// variant_fsm.cpp
// example for "C++17 In Detail"
// by Bartlomiej Filipek
// 2018/2019

#include <iostream>
#include <variant>
#include <cassert>

struct DoorState {
    struct DoorOpened {};
    struct DoorClosed {};
    struct DoorLocked {};

    using State = std::variant<DoorOpened, DoorClosed, DoorLocked>;
    
    void open() {
        m_state = std::visit(OpenEvent{}, m_state);
    }
    
    void close() {
        m_state = std::visit(CloseEvent{}, m_state);
    }

    void lock() {
        m_state = std::visit(LockEvent{}, m_state);
    }
    
    void unlock() {
        m_state = std::visit(UnlockEvent{}, m_state);
    }
    
    struct OpenEvent {
        State operator()(const DoorOpened&){ return DoorOpened(); }
        State operator()(const DoorClosed&){ return DoorOpened(); }
        // cannot open locked doors
        State operator()(const DoorLocked&){ return DoorLocked(); } 
    };
    
    struct CloseEvent {
        State operator()(const DoorOpened&){ return DoorClosed(); }
        State operator()(const DoorClosed&){ return DoorClosed(); }
        State operator()(const DoorLocked&){ return DoorLocked(); }
    };
    
    struct LockEvent {
        // cannot lock opened doors
        State operator()(const DoorOpened&){ return DoorOpened(); }
        State operator()(const DoorClosed&){ return DoorLocked(); }
        State operator()(const DoorLocked&){ return DoorLocked(); }
    };
    
    struct UnlockEvent {
        // cannot unlock opened doors
        State operator()(const DoorOpened&){ return DoorOpened(); }
        State operator()(const DoorClosed&){ return DoorClosed(); }
        // unlock
        State operator()(const DoorLocked&){ return DoorClosed(); } 
    };

    State m_state;
};

int main() {
    DoorState s;
    assert(std::holds_alternative<DoorState::DoorOpened>(s.m_state));
    s.lock();
    assert(std::holds_alternative<DoorState::DoorOpened>(s.m_state));
    s.close();
    assert(std::holds_alternative<DoorState::DoorClosed>(s.m_state));
    s.lock();
    assert(std::holds_alternative<DoorState::DoorLocked>(s.m_state));
    s.open();
    assert(std::holds_alternative<DoorState::DoorLocked>(s.m_state));
    
    return 0;
}