#include <iostream>
#include <fstream>
#include <string>
#include <SFML/Graphics.hpp>
#include "turing_machine.hpp"
#include "simulator.hpp"
#include "tape_box.hpp"

void simulator::simulate_turing_machine() const{
    // std::ifstream turing_machine_file(TM_FILE_PATH);
    turing_machine tm(5, {'0', '1'}, {'0', '1', 'x', 'y', ' '}, 0, ' ', {4});
    tm.add_transition(0, '0', 1, 'x', move_direction::right);
    tm.add_transition(0, 'y', 3, 'y', move_direction::right);
    tm.add_transition(1, '0', 1, '0', move_direction::right);
    tm.add_transition(1, '1', 2, 'y', move_direction::left);
    tm.add_transition(1, 'y', 1, 'y', move_direction::right);
    tm.add_transition(2, '0', 2, '0', move_direction::left);
    tm.add_transition(2, 'x', 0, 'x', move_direction::right);
    tm.add_transition(2, 'y', 2, 'y', move_direction::left);
    tm.add_transition(3, 'y', 3, 'y', move_direction::right);
    tm.add_transition(3, ' ', 4, ' ', move_direction::stationary);
    // turing_machine tm = get_tm_from_file();
    // turing_machine_file.close();

    std::ifstream input_string_file(INPUT_STRING_FILE_PATH);
    std::string input_string;

    input_string_file >> input_string;

    tm.setup(input_string);

    sf::RenderWindow simulation_window(sf::VideoMode(1400u, 850u), "Turing Machine Simulator");
    simulation_window.setFramerateLimit(60);

    sf::Font tape_font;
    if(!tape_font.loadFromFile("../res/fonts/NotoSans_Regular.ttf")){
        throw std::runtime_error("Failed to load the tape font");
    }

    std::vector<tape_box> tape_boxes;
    float xpos = 300.0f, ypos = 200.0f;
    auto mini_tape_contents = tm.get_mini_tape_contents();
    for(int i = 0; i < MINI_TAPE_SIZE; i++){
        tape_boxes.emplace_back(mini_tape_contents[i], tape_font, xpos, ypos);
        xpos += TAPE_BOX_SIZE;
    }

    long long frame_count = 0ll;

    while(simulation_window.isOpen()){
        frame_count++;

        sf::Event event;
        
        while(simulation_window.pollEvent(event)){
            if(event.type == sf::Event::Closed) simulation_window.close();
        }

        simulation_window.clear();
        for(auto& box : tape_boxes){
            box.draw(simulation_window);
        }
        simulation_window.display();

        if(frame_count % 60 == 0){
            if(!tm.halted()){
                tm.make_move();

                mini_tape_contents = tm.get_mini_tape_contents();
                for(int i = 0; i < MINI_TAPE_SIZE; i++){
                    tape_boxes[i].set_text(mini_tape_contents[i]);
                }
            }
        }
    }

    if(tm.accepting()){
        std::cout << "Accepted" << std::endl;
    }
    else{
        std::cout << "Rejected" << std::endl;
    }

    input_string_file.close();
}