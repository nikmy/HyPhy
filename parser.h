/**
 * @headerfile  parser.h
 * @author      MyInk
 * @date        5.12.2020
 */

#ifndef HYPHY_PARSER_H
#define HYPHY_PARSER_H

#include <string.h>
#include "utf8-io.h"
#include "utf8-rus.h"

/**
 * @brief           Check substring of specified length for containing vowels
 * @param u8_str    Substring to check
 * @param word_size Length of substring
 * @return          Number of vowels in substring
 */
size_t contains_vowel(char* u8_str, size_t word_size);

/**
 * @brief           Write word from u8_str to dst_buff with hyphens
 * @param w         Word string
 * @param word_size Length of word
 * @param dst_buff  Buffer to write the final split
 * @return          Number of hyphens
 */
size_t split_word(char* w, size_t word_size, char* dst_buff);

/**
 * @brief           Split all words from buffer
 * @param u8_buf    Buffer with words to split
 * @param buff_size Buffer size
 * @param dst_buff  Buffer for split
 * @return          Number of bytes in the final split
 */
size_t split_buff(char* u8_buf, size_t buff_size, char* dst_buff);

/// @typedef Pointer to FileParser object
typedef struct FileParser
{
    io_stream_t io;
    char* bf;
} * parser;

/**
 * @brief           Initialize parser with 2 files
 * @param pp        Pointer to pointer to FileParser object
 * @param input_fn  Input file name
 * @param output_fn Output file name
 * @return          Error code
 */
int init_parser(parser* pp, const char* input_fn, const char* output_fn);

/**
 * @brief   Delete FileParser object
 * @param p Pointer to FileParser object
 */
void del_parser(parser p);

/**
 * @brief   Parse whole text from file
 * @param p Pointer to FileParser object
 */
void parse_file(parser p);

#endif //HYPHY_PARSER_H
