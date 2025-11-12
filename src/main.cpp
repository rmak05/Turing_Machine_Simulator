#include <iostream>
#include <SFML/Graphics.hpp>
#include "turing_machine.hpp"

void demo_window(){
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    window.setFramerateLimit(60);
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    int frames = 0;
    
    while(window.isOpen()){
        frames++;
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed) window.close();
        }
    
        window.clear();
        window.draw(shape);
        window.display();
    
        if(frames >= 60) break;
    }
}

void demo_tm(){
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

    auto print_array = [](const std::array<char, MINI_TAPE_SIZE>& _arr){
        for(auto itr : _arr) std::cout << itr << ' ';
        std::cout << std::endl;
    };

    tm.setup("0011");
    print_array(tm.get_mini_tape_contents());
    while(!tm.halted()){
        tm.make_move();
        print_array(tm.get_mini_tape_contents());
    }
    if(tm.accepting()){
        std::cout << "Accepted" << std::endl;
    }
    else{
        std::cout << "Rejected" << std::endl;
    }
}

int main(){
    try{
        // demo_window();
        demo_tm();
    }
    catch(const std::exception& _e){
        std::cout << _e.what() << std::endl;
    }
    catch(...){
        std::cout << "Unknown exception" << std::endl;
    }

    return 0;
}