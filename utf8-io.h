/**
 * @headerfile      utf8-rus.h
 * @author          MyInk
 * @date            5.12.2020
 */

#ifndef HYPHY_UTF8_IO_H
#define HYPHY_UTF8_IO_H

#include <stdio.h>
#include <malloc.h>

/// @def BUFF_SIZE  Size of temporary buffer
#define BUFF_SIZE 1024

/// @def INPUT_SIZE Size of continuously readable buffer
#define INPUT_SIZE 400

/// @typedef Pointer to IOStream object
typedef struct IOStream
{
    FILE* istream;
    FILE* ostream;
    char* buff;
} * io_stream_t;

/**
 * @brief               Create IOStream object
 * @param input_fn      Input file name
 * @param output_fn     Output file name
 * @return              Pointer to created IOStream object
 */
io_stream_t new_io_stream(const char* input_fn, const char* output_fn);

/**
 * @brief           Remove IOStream object
 * @param stream    Pointer to IOStream object for removing
 */
void del_io_stream(io_stream_t stream);

/**
 * @brief           Check for russian symbol
 * @param u8_str    Symbol for checking
 */
int is_russian(char* u8_str);

/**
 * @brief           Read next INPUT_SIZE (or less) bytes in buff
 * @param stream    Pointer to IOStream object
 * @return          Number of read bytes
 */
size_t read_utf8(io_stream_t stream);

/**
 * @brief           Write from buff to file
 * @param stream    Pointer to IOStream object
 * @return          Number of written bytes
 */
size_t write_utf8(io_stream_t stream);

#endif //HYPHY_UTF8_IO_H
