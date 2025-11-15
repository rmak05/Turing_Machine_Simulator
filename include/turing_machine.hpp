#ifndef TURING_MACHINE_HPP
#define TURING_MACHINE_HPP

#include <array>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <deque>
#include <tuple>
#include "constants.hpp"

enum class move_direction{
    left,
    right,
    stationary
};
extern const std::set<move_direction> move_direction_set;

/*
Turing Machine:
M = (Q, Σ, Γ, δ, q0, □, F)

Legend:
Q   - Set of internal states
Σ   - Input alphabet
Γ   - Tape alphabet
δ   - Transition function
q0  - Initial state
□   - Blank symbol
F   - Set of final states

Constraints:
□ ∈ Γ
q0 ∈ Q
F ⊆ Q
Σ ⊆ Γ - {□}
δ : Q x Γ -> Q x Γ x {L, R, S}
*/ 
class turing_machine{
private:
    int                                 num_states;           // Q = {0, 1, 2, ..., num_states - 1}
    std::set<char>                      input_alphabet;
    std::set<char>                      tape_alphabet;
    std::vector<std::map<char, std::tuple<int, char, move_direction>>> transition_function;
    int                                 initial_state;
    char                                blank;
    std::set<int>                       final_states;

    int                                 curr_state;
    std::deque<char>                    tape;
    int                                 read_head;

    void validate_contraints();

public:
    turing_machine();
    turing_machine(const int _num_states, const std::set<char>& _input_alphabet, const std::set<char>& _tape_alphabet, const int _initial_state, const char _blank, const std::set<int>& _final_states);

    void add_transition(const int _curr_state, const char _curr_symbol, const int _next_state, const char _new_symbol, const move_direction _direction);
    void setup(const std::string& _input);
    void reset();
    bool halted() const;
    bool accepting() const;
    std::tuple<int, char, move_direction> make_move();
    std::array<char, MINI_TAPE_SIZE> get_mini_tape_contents() const;
};

#endif /* TURING_MACHINE_HPP */