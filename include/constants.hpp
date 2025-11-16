#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <SFML/Graphics.hpp>

inline constexpr int MINI_TAPE_SIZE = 11;
static_assert(MINI_TAPE_SIZE & 1, "Constraint Violation: MINI_TAPE_SIZE must be odd");

inline constexpr const char *TM_FILE_PATH           = "../input/turing_machine.txt";
inline constexpr const char *INPUT_STRING_FILE_PATH = "../input/input_string.txt";
inline constexpr const char *TAPE_FONT_PATH         = "../res/fonts/NotoSans_Regular.ttf";
inline constexpr const char *DOT_FILE_PATH          = "tm.dot";

inline constexpr float TAPE_BOX_SIZE            = 100.0f;
inline constexpr unsigned TAPE_BOX_TEXT_SIZE    = 75u;

inline const sf::Color BG_COLOR = sf::Color(0x99e6ffff);

#endif /* CONSTANTS_HPP */