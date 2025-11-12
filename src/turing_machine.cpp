#include <stdexcept>
#include "turing_machine.hpp"

std::set<move_direction> move_direction_set = {move_direction::left, move_direction::right, move_direction::stationary};

turing_machine::turing_machine(const int _num_states, const std::set<char>& _input_alphabet, const std::set<char>& _tape_alphabet, const int _initial_state, const char _blank, const std::set<int>& _final_states) :
num_states(_num_states), input_alphabet(_input_alphabet), tape_alphabet(_tape_alphabet), initial_state(_initial_state), blank(_blank), final_states(_final_states), transition_function(num_states), curr_state(initial_state), read_head(0), tape({blank}), has_halted(false){
    if(!tape_alphabet.contains(blank)){
        throw std::runtime_error("Constraint Violation: Blank symbol should belong to the tape alphabet");
    }
    if(initial_state < 0 || initial_state >= num_states){
        throw std::runtime_error("Constraint Violation: Initial state should belong to the set of internal states");
    }
    for(const auto& fstate : final_states){
        if(fstate < 0 || fstate >= num_states){
            throw std::runtime_error("Constraint Violation: Set of final states should be a subset of the set of internal states");
        }
    }
    for(const auto& symbol : input_alphabet){
        if(symbol == blank || !tape_alphabet.contains(symbol)){
            throw std::runtime_error("Constraint Violation: Input alphabet should be a subset of tape alphabet excluding the blank symbol");
        }
    }
}

void turing_machine::add_transition(const int _curr_state, const char _curr_symbol, const int _next_state, const char _new_symbol, const move_direction _direction){
    if(_curr_state < 0 || _curr_state >= num_states){
        throw std::runtime_error("Constraint Violation: Current state should belong to the set of internal states");
    }
    if(!tape_alphabet.contains(_curr_symbol)){
        throw std::runtime_error("Constraint Violation: Current symbol should belong to the tape alphabet");
    }
    if(_next_state < 0 || _next_state >= num_states){
        throw std::runtime_error("Constraint Violation: Next state should belong to the set of internal states");
    }
    if(!tape_alphabet.contains(_new_symbol)){
        throw std::runtime_error("Constraint Violation: New symbol should belong to the tape alphabet");
    }
    if(!move_direction_set.contains(_direction)){
        throw std::runtime_error("Constraint Violation: Move direction should belong to the set {L, R, S}");
    }

    transition_function[_curr_state].emplace(_curr_symbol, std::make_tuple(_next_state, _new_symbol, _direction));
}

void turing_machine::setup(const std::string& _input){
    for(const auto& symbol : _input){
        if(!input_alphabet.contains(symbol)){
            throw std::runtime_error("Constraint Violation: Symbols in the input string should belong to the input alphabet");
        }
    }
    
    curr_state = initial_state;

    tape = std::deque<char>(_input.begin(), _input.end());
    if(tape.empty()) tape.emplace_back(blank);

    read_head = 0;

    has_halted = false;
}

void turing_machine::reset(){
    curr_state = initial_state;

    tape = std::deque<char>({blank});

    read_head = 0;

    has_halted = false;
}

void turing_machine::make_move(){
    if(!transition_function[curr_state].contains(tape[read_head])){
        has_halted = true;
        // throw std::runtime_error("Simulation Error: No transition defined for the current move");

        return;
    }
    const auto& move = transition_function[curr_state].at(tape[read_head]);

    curr_state = std::get<int>(move);

    tape[read_head] = std::get<char>(move);

    move_direction direction = std::get<move_direction>(move);
    if(direction == move_direction::left){
        if(read_head == 0){
            tape.emplace_front(blank);
        }
        else{
            read_head--;
        }
    }
    else if(direction == move_direction::right){
        if(read_head == static_cast<int>(tape.size()) - 1){
            tape.emplace_back(blank);
        }
        read_head++;
    }
    else if(direction == move_direction::stationary){
        // do nothing
    }
}

bool turing_machine::halted() const{
    return has_halted;
}