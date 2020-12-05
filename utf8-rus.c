#include "utf8-rus.h"

int is_alpha(char* u8_str)
{
    return ((unsigned)u8_str[0] == 0xFFFFFFD0 || (unsigned)u8_str[0] == 0xFFFFFFD1);
}

int is_upper(char* u8_str)
{
    return ((unsigned)u8_str[0] == 0xFFFFFFD0 && (unsigned)u8_str[1] <= 0xFFFFFFAF);
}

int is_vowel(char* u8_str)
{
    if (!is_alpha(u8_str))
        return 0;

    if (is_upper(u8_str))
    {
        switch ((unsigned)u8_str[1])
        {
            case 0xFFFFFF90:
            case 0xFFFFFF95:
            case 0xFFFFFF81:
            case 0xFFFFFF98:
            case 0xFFFFFF9E:
            case 0xFFFFFFA3:
            case 0xFFFFFFAB:
            case 0xFFFFFFAD:
            case 0xFFFFFFAE:
            case 0xFFFFFFAF:
                return 1;
            default:
                return 0;
        }
    }

    switch ((unsigned)u8_str[1])
    {
        case 0xFFFFFFB0:
        case 0xFFFFFFB5:
        case 0xFFFFFF91:
        case 0xFFFFFFB8:
        case 0xFFFFFFBE:
        case 0xFFFFFF83:
        case 0xFFFFFF8B:
        case 0xFFFFFF8D:
        case 0xFFFFFF8E:
        case 0xFFFFFF8F:
            return 1;
        default:
            return 0;
    }
}

int is_cons(char* u8_str)
{
    return (is_alpha(u8_str) && !is_vowel(u8_str));
}

int is_special(char* u8_str)
{
    if (!is_alpha(u8_str))
        return 0;
    switch ((unsigned )u8_str[1])
    {
        case 0xFFFFFF8A:
        case 0xFFFFFF8C:
        case 0xFFFFFFB9:
            return 1;
        default:
            return 0;
    }
}
