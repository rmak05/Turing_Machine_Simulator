#include <iostream>
#include "tape_box.hpp"
#include "constants.hpp"

tape_box::tape_box(){}

tape_box::tape_box(const char _text, const sf::Font& _font, const float _xpos, const float _ypos) :
box(sf::Vector2f(TAPE_BOX_SIZE, TAPE_BOX_SIZE)), text(_text, _font), position(_xpos, _ypos){
    box.setOrigin(box.getSize() / 2.0f);
    box.setFillColor(sf::Color::Green);
    box.setPosition(position);
    box.setOutlineColor(sf::Color::Magenta);
    box.setOutlineThickness(5.0f);
    
    sf::FloatRect text_bounds = text.getLocalBounds();
    text.setOrigin(text_bounds.left + text_bounds.width / 2.0f, text_bounds.top + text_bounds.height / 2.0f);
    text.setPosition(position);
    text.setFillColor(sf::Color::Red);
}

void tape_box::draw(sf::RenderWindow& _window) const{
    _window.draw(box);
    _window.draw(text);
}

void tape_box::set_text(const char _text){
    std::string text_string = {_text};

    if(text_string == text.getString()) return;

    text.setString(text_string);
    sf::FloatRect text_bounds = text.getLocalBounds();
    text.setOrigin(text_bounds.left + text_bounds.width / 2.0f, text_bounds.top + text_bounds.height / 2.0f);
}

void tape_box::set_position(const float _xpos, const float _ypos){
    position.x = _xpos;
    position.y = _ypos;
}

void tape_box::set_velocity(const float _xv, const float _yv){
    velocity.x = _xv;
    velocity.y = _yv;
}

void tape_box::transform(){
    position += velocity;

    box.setPosition(position);
    text.setPosition(position);
}