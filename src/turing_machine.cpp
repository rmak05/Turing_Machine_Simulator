#include <stdexcept>
#include "turing_machine.hpp"

std::set<move_direction> move_direction_set = {move_direction::left, move_direction::right, move_direction::stationary};

turing_machine::turing_machine(const int _num_states, const std::set<char>& _input_alphabet, const std::set<char>& _tape_alphabet, const int _initial_state, const char _blank, const std::set<int>& _final_states) :
num_states(_num_states), input_alphabet(_input_alphabet), tape_alphabet(_tape_alphabet), initial_state(_initial_state), blank(_blank), final_states(_final_states), transition_function(num_states), curr_state(initial_state){
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