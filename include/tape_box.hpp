#ifndef TAPE_BOX_HPP
#define TAPE_BOX_HPP

#include <SFML/Graphics.hpp>

class tape_box{
private:
    sf::RectangleShape  box;
    sf::Text            text;
    sf::Vector2f        position;
    sf::Vector2f        velocity;

public:
    tape_box();
    tape_box(const char _text, const sf::Font& _font, const float _xpos, const float _ypos);

    void draw(sf::RenderWindow& _window) const;
    void set_text(const char _text);
    void set_position(const float _xpos, const float _ypos);
    void set_velocity(const float _xv, const float _yv);
    void transform();
};

#endif /* TAPE_BOX_HPP */