#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <SFML/Graphics.hpp>

inline constexpr int MINI_TAPE_SIZE = 11;
static_assert(MINI_TAPE_SIZE & 1, "Constraint Violation: MINI_TAPE_SIZE must be odd");

inline constexpr const char *TM_FILE_PATH               = "../input/turing_machine.txt";
inline constexpr const char *INPUT_STRING_FILE_PATH     = "../input/input_string.txt";
inline constexpr const char *TAPE_FONT_PATH             = "../res/fonts/NotoSans_Regular.ttf";
inline constexpr const char *TAPE_TEXTURE_PATH          = "../res/textures/tape_box_3.png";
inline constexpr const char *TAPE_CENTER_TEXTURE_PATH   = "../res/textures/tape_box_5.png";
inline constexpr const char *READ_HEAD_TEXTURE          = "../res/textures/read_head_0.png";
inline constexpr const char *DOT_FILE_PATH              = "../output/tm.dot";
inline constexpr const char *TM_FA_IMAGE_PATH           = "../output/tm.png";

inline constexpr float TAPE_BOX_SIZE            = 100.0f;
inline constexpr unsigned TAPE_BOX_TEXT_SIZE    = 45u;
inline constexpr char BLANK_SYM                 = ' ';

inline const sf::Color BG_COLOR                 = sf::Color(0x99E6FFFF);
inline const sf::Color TAPE_TEXT_COLOR          = sf::Color(0x442009FF);
inline const sf::Color FA_BOX_OUTLINE_COLOR     = sf::Color(0x111184FF);

#endif /* CONSTANTS_HPP */