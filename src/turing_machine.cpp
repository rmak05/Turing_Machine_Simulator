#include <iostream>
#include <fstream>
#include <stdexcept>
#include <fstream>
#include <iostream>
#include <sstream>
#include "turing_machine.hpp"

const std::set<move_direction> move_direction_set = {move_direction::left, move_direction::right, move_direction::stationary};

turing_machine::turing_machine() :
num_states(1), tape_alphabet({' '}), initial_state(0), blank(' '), final_states({0}), transition_function(1), curr_state(0), read_head(0), tape({' '}), extracted_to_dot(false){
    validate_contraints();
}

turing_machine::turing_machine(const int _num_states, const std::set<char>& _input_alphabet, const std::set<char>& _tape_alphabet, const int _initial_state, const char _blank, const std::set<int>& _final_states) :
num_states(_num_states), input_alphabet(_input_alphabet), tape_alphabet(_tape_alphabet), initial_state(_initial_state), blank(_blank), final_states(_final_states), transition_function(_num_states), curr_state(_initial_state), read_head(0), tape({_blank}), extracted_to_dot(false){
    validate_contraints();
}

void turing_machine::validate_contraints(){
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
}

void turing_machine::reset(){
    curr_state = initial_state;

    tape = std::deque<char>({blank});

    read_head = 0;
}

bool turing_machine::halted() const{
    return !transition_function[curr_state].contains(tape[read_head]);
}

bool turing_machine::accepting() const{
    return halted() && final_states.contains(curr_state);
}

std::tuple<int, char, move_direction> turing_machine::make_move(){
    if(halted()){
        return std::make_tuple(-1, blank, move_direction::stationary);
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

    return move;
}

std::array<char, MINI_TAPE_SIZE> turing_machine::get_mini_tape_contents() const{
    std::array<char, MINI_TAPE_SIZE> mini_tape;

    for(int i = 0; i < MINI_TAPE_SIZE; i++){
        mini_tape[i] = blank;
    }

    int tape_size = static_cast<int>(tape.size());
    int index;

    index = MINI_TAPE_SIZE / 2;
    for(int i = read_head; i < tape_size && index < MINI_TAPE_SIZE; i++){
        mini_tape[index] = tape[i];
        index++;
    }
    index = MINI_TAPE_SIZE / 2 - 1;
    for(int i = read_head - 1; i >= 0 && index >= 0; i--){
        mini_tape[index] = tape[i];
        index--;
    }

    return mini_tape;
}

void turing_machine::export_to_graphviz(const std::string& filename){
    if(!extracted_to_dot){
        extracted_to_dot = true;

        std::ofstream dot(filename);
        if (!dot) {
            std::cerr << "ERROR: Cannot open " << filename << " for writing\n";
        }
    
        dot << "digraph TuringMachine {\n";
        dot << "bgcolor=\"lightyellow\";\n";
        dot << "  rankdir=LR;\n";
        dot << "  fontsize=14;\n";
        dot << "  node [shape=circle, fontname=Helvetica];\n";
    
        dot << R"(
    subgraph cluster_legend {
        label="Legend";
        fontsize=15;
        style=dashed;
        margin=8;
        rank=sink;
    
        Lmove [label="L = Move Left", shape=plaintext, fontcolor=red];
        Rmove [label="R = Move Right", shape=plaintext, fontcolor=blue];
        Smove [label="S = Stay", shape=plaintext, fontcolor="#4c525c"];
        Curr [label="Current State", shape=circle, style=filled, fillcolor=lightgreen, fontsize=8];
    
        // Invisible edges for vertical stacking
        Lmove -> Rmove [style=invis];
        Rmove -> Smove [style=invis];
        Smove -> Curr  [style=invis];
    }
    )";
    
        for (int f : final_states) {
            dot << "  " << f << " [shape=doublecircle];\n";
        }
    
        dot << "  start [shape=point];\n";
        dot << "  start -> " << initial_state << ";\n";
    
        // dot << "  " << curr_state << " [style=filled, fillcolor=lightgreen];\n";
    
        auto direction_to_string = [](move_direction dir) {
            switch(dir) {
                case move_direction::left: return "L";
                case move_direction::right: return "R";
                case move_direction::stationary: return "S";
                default: return "?";
            }
        };
    
        for (int state = 0; state < num_states; ++state) {
            for (const auto& [read_symbol, trans] : transition_function[state]) {
                int next_state;
                char write_symbol;
                move_direction dir;
                std::tie(next_state, write_symbol, dir) = trans;
    
                std::string color;
                switch (dir) {
                    case move_direction::left:       color = "red"; break;
                    case move_direction::right:      color = "blue"; break;
                    case move_direction::stationary: color = "\"#4c525c\""; break;
                    default:                         color = "black"; break;
                }

                std::string temp_read_str = {read_symbol};
                std::string temp_write_str = {write_symbol};
                std::string temp_blank_str = "□";
    
                dot << "  " << state << " -> " << next_state
                    << " [label=\""
                    << (read_symbol == blank ? temp_blank_str : temp_read_str) << " → " << (write_symbol == blank ? temp_blank_str : temp_write_str)
                    << "\", color=" << color << "];\n";
            }
        }
    
        dot << "}\n";
        dot.close();
    
        std::string cmd = "dot -Tdot " + filename + " -o " + DOT_POS_FILE_PATH;
        system(cmd.c_str());
        
        // dot.open(filename);
        // dot << "  " << curr_state << " [style=filled, fillcolor=lightgreen];\n";
        // dot.close();
        export_to_graphviz(filename);
        
        // std::string cmd = "dot -Tpng " + filename + " -o " + TM_FA_IMAGE_PATH;
        // system(cmd.c_str());
    }
    else{
        std::ofstream dot(filename);
        std::ifstream dot_pos(DOT_POS_FILE_PATH);

        std::string line;
        while(std::getline(dot_pos, line)){
            if(line == "}"){
                dot << "  " << curr_state << " [style=filled, fillcolor=lightgreen];\n";
            }
            dot << line << "\n";
        }

        dot_pos.close();
        dot.close();

        std::string cmd = "dot -Tpng " + filename + " -o " + TM_FA_IMAGE_PATH;
        system(cmd.c_str());
    }
}

turing_machine read_input_turing_machine(){
    std::ifstream file(TM_FILE_PATH);
    if (!file) {
        throw std::runtime_error("Cannot open turing_machine file");
    }
    int numStates;
    file >> numStates;

    std::set<char> alphabets;
    {
        std::string line;
        getline(file, line); // clear leftover newline
        getline(file, line);
        std::stringstream ss(line);
        char x;
        while (ss >> x) alphabets.insert(x);
    }
    std::set<char> tapeAlphabets;
    {
        std::string line;
        getline(file, line);
        std::stringstream ss(line);
        char x;
        while (ss >> x) tapeAlphabets.insert(x);
    }

    // Adding blank symbol
    tapeAlphabets.insert(BLANK_SYM);

    int initialState;
    file >> initialState;

    std::set<int> finalStates;
    {
        std::string line;
        getline(file, line); // clear leftover newline
        getline(file, line);
        std::stringstream ss(line);
        int x;
        while (ss >> x) finalStates.insert(x);
    }

    turing_machine tm(numStates, alphabets, tapeAlphabets, initialState, (char)BLANK_SYM, finalStates);
    {
        int cs, ns;
        char rs, ws, dir;

        while (file >> cs >> rs >> ns >> ws >> dir) {
            char rs_s = (rs == '_' ? BLANK_SYM : rs);
            char ws_s = (ws == '_' ? BLANK_SYM : ws);

            if(dir == 'L') tm.add_transition(cs, rs_s, ns, ws_s, move_direction::left);
            else if(dir == 'R') tm.add_transition(cs, rs_s, ns, ws_s, move_direction::right);
            else if(dir == 'S') tm.add_transition(cs, rs_s, ns, ws_s, move_direction::stationary);
            else{
                throw std::runtime_error(std::string("Invalid Read Write Head movement direction in transitions. Possible directions are - L: left, R: Right, S: Stationary. Found value: ") + dir);
            }
        }
    }

    file.close();

    return tm;
}