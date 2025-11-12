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

int main(){
    demo_window();

    return 0;
}