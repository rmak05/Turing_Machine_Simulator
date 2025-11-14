#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

inline constexpr int MINI_TAPE_SIZE = 9;
static_assert(MINI_TAPE_SIZE & 1, "Constraint Violation: MINI_TAPE_SIZE must be odd");

inline constexpr const char *TM_FILE_PATH           = "../input/turing_machine.txt";
inline constexpr const char *INPUT_STRING_FILE_PATH = "../input/input_string.txt";
inline constexpr const char *TAPE_FONT_PATH         = "../res/fonts/NotoSans_Regular.ttf";

inline constexpr float TAPE_BOX_SIZE            = 100.0f;
inline constexpr unsigned TAPE_BOX_TEXT_SIZE    = 75u;

#endif /* CONSTANTS_HPP */