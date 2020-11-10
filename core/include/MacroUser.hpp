/*
** EPITECH PROJECT, 2020
** MacroUser
** File description:
** hpp
*/

#ifndef MACROUSER_HPP
#define MACROUSER_HPP

#define TEXT_ASK_NAME "Enter your name:"
#define X_ASK_NAME 100
#define Y_ASK_NAME 100

#define X_USERNAME 100
#define Y_USERNAME 200
#define INIT_USER_NAME " "
#define COLOR_USERNAME_INPUT Color::BLUE

#define LETTER_PER_LINE 10
#define KEYBOARD "qwertyuiopasdfghjklzxcvbnm"
#define X_KEYBOARD 100
#define Y_KEYBOARD 300
#define X_SEPARATION_KEYBOARD 50
#define Y_SEPARATION_KEYBOARD 50

#define X_DELETE 600
#define Y_DELETE 350
#define TEXT_DELETE "[Delete]"

#define X_DONE 250
#define Y_DONE 500
#define TEXT_DONE "[Done]"

#define INIT_KEY_SELECTED 0
#define LAST_CHAR '\n'

#define LAST_CHAR_LINE(keySelected) round(((keySelected/LETTER_PER_LINE)) + 1 ) * LETTER_PER_LINE

#define INDEX_SPACE(nbrKeys) nbrKeys - 1
#define INDEX_LAST_KEY(nbrKeys) nbrKeys - 3
#define INDEX_DELETE(nbrKeys) nbrKeys - 2
#define INDEX_LAST_LINE 20
#define INDEX_LAST_CHAR_FIST_LINE LETTER_PER_LINE - 1
#define INDEX_FIRST_CHAR_FIST_LINE 0

#define INDEX_LINE_UP(keySelected) keySelected - LETTER_PER_LINE
#define INDEX_LINE_DOWN(nbrKeys, keySelected) keySelected + LETTER_PER_LINE > INDEX_LAST_KEY(nbrKeys) ? INDEX_LAST_KEY(nbrKeys) : keySelected + LETTER_PER_LINE
#define INDEX_LEFT_KEY(keySelected) keySelected - 1
#define INDEX_RIGHT_KEY(keySelected) keySelected + 1

#endif /* !MACROUSER_HPP */
