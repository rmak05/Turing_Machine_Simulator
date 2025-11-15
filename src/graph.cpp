#include "include/turing_machine.hpp"
#include <fstream>
#include <string>

void turing_machine::export_to_graphviz(const std::string& filename) const {
    std::ofstream dot(filename);
    dot << "digraph TuringMachine {\n";
    dot << "  rankdir=LR;\n";
    dot << "  node [shape = circle];\n";

    // Mark final states as doublecircle
    for (auto f : final_states) {
        dot << "  " << f << " [shape=doublecircle];\n";
    }

    // Mark initial state with an arrow
    dot << "  start [shape=point];\n";
    dot << "  start -> " << initial_state << ";\n";

    auto direction_to_string = [](move_direction dir) {
        switch(dir) {
            case move_direction::left: return "L";
            case move_direction::right: return "R";
            case move_direction::stationary: return "S";
            default: return "?";
        }
    };

    // Add transitions
    for (int state = 0; state < num_states; ++state) {
        for (const auto& [read_symbol, trans] : transition_function[state]) {
            int next_state;
            char write_symbol;
            move_direction dir;
            std::tie(next_state, write_symbol, dir) = trans;

            dot << "  " << state << " -> " << next_state
                << " [label=\""
                << read_symbol << " → " << write_symbol << ", "
                << direction_to_string(dir) << "\"];\n";
        }
    }

    dot << "}\n";
}
