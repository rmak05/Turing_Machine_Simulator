#ifndef TAPE_BOX_HPP
#define TAPE_BOX_HPP

#include <SFML/Graphics.hpp>

class tape_box{
private:
    sf::RectangleShape  box;
    sf::Text            text;
    sf::Vector2f        position;

public:
    tape_box();
    tape_box(const char _text, const sf::Font& _font, const float _xpos, const float _ypos);

    void draw(sf::RenderWindow& _window) const;
    void set_text(const char _text);
};

#endif /* TAPE_BOX_HPP */