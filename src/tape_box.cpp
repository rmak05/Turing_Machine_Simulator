#include "tape_box.hpp"
#include "constants.hpp"

tape_box::tape_box(){}

tape_box::tape_box(const char _text, const sf::Font& _font, const float _xpos, const float _ypos) :
box(sf::Vector2f(TAPE_BOX_SIZE, TAPE_BOX_SIZE)), text(_text, _font), position(_xpos, _ypos){
    box.setFillColor(sf::Color::Green);
    box.setPosition(position);

    text.setPosition(position);
    text.setFillColor(sf::Color::Red);
}

void tape_box::draw(sf::RenderWindow& _window) const{
    _window.draw(box);
    _window.draw(text);
}

void tape_box::set_text(const char _text){
    text.setString({_text});
}