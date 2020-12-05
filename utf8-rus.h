/**
 * @headerfile  utf8-rus.h
 * @author      MyInk
 * @date        5.12.2020
 */

#ifndef HYPHY_UTF8_RUS_H
#define HYPHY_UTF8_RUS_H

/**
 * @brief           Check symbol for being a russian letter
 * @param u8_str    Symbol for checking
 * @return          1 if symbol is russian letter, 0 otherwise
 */
int is_alpha(char* u8_str);

/**
 * @brief           Check for uppercase russian symbol
 * @param u8_str    Symbol for checking
 * @return          1 if symbol is russian symbol in uppercase, 0 otherwise
 */
int is_upper(char* u8_str);

/**
 * @brief           Check symbol for being a russian vowel
 * @param u8_str    Symbol for checking
 * @return          1 if symbol is russian vowel, 0 otherwise
 */
int is_vowel(char* u8_str);

/**
 * @brief           Check symbol for being a russian vowel
 * @param u8_str    Symbol for checking
 * @return          1 if symbol is russian consonant (including 'Ъ', 'Ь'), 0 otherwise
 */
int is_cons(char* u8_str);

/**
 * @brief           Check symbol for being a special
 * @param u8_str    Symbol for checking
 * @return          1 if symbol is 'Й', 'Ъ' or 'Ь', 0 otherwise
 */
int is_special(char* u8_str);

#endif //HYPHY_UTF8_RUS_H
