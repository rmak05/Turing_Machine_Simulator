#include "turing_machine.hpp"
#include <iostream>
#include <fstream>
#include <string>

void turing_machine::export_to_graphviz(const std::string& filename) const {
    std::ofstream dot(filename);
    if (!dot) {
        std::cerr << "ERROR: Cannot open " << filename << " for writing\n";
    }

    dot << "digraph TuringMachine {\n";
    dot << "  rankdir=LR;\n";
    dot << "  fontsize=14;\n";
    dot << "  node [shape=circle, fontname=Helvetica];\n";

    dot << R"(
  subgraph cluster_legend {
    label="Legend";
    fontsize=9;
    style=dashed;
    margin=8;
    rank=sink;

    Lmove [label="L = Move Left", shape=plaintext, fontcolor=red];
    Rmove [label="R = Move Right", shape=plaintext, fontcolor=blue];
    Smove [label="S = Stay", shape=plaintext, fontcolor=gray];
    Curr [label="Current State", shape=circle, style=filled, fillcolor=lightgreen, fontsize=7];

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

    dot << "  " << curr_state << " [style=filled, fillcolor=lightgreen];\n";

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
                case move_direction::stationary: color = "gray"; break;
                default:                         color = "black"; break;
            }

            dot << "  " << state << " -> " << next_state
                << " [label=\""
                << read_symbol << " → " << write_symbol
                << "\", color=" << color << "];\n";
        }
    }

    dot << "}\n";
    dot.close();

    std::string cmd = "dot -Tpng " + filename + " -o tm.png";
    system(cmd.c_str());
}
