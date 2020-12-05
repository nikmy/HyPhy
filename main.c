/**
 * @project_name        HyPhy
 * @full_name           HyPhy UTF-8 Text Hyphenation Lib
 * @author              MyInk
 * @copyright           Nikita Mysov, 2020
 */

#include "parser.h"

int main()
{
    parser p = NULL;
    if (init_parser(&p, "input.txt", "output.txt") == 0)
        parse_file(p);
    del_parser(p);
}