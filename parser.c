#include "parser.h"

size_t contains_vowel(char* u8_str, size_t word_size)
{
    size_t n = 0;
    for (int i = 0; i < word_size * 2; i += 2)
        n += is_vowel(u8_str + i);
    return n;
}

size_t copy_word(char* u8_str, size_t word_size, char* dst_buff)
{
    memcpy(dst_buff, u8_str, word_size * 2);
    return word_size;
}

size_t split_word(char* w, size_t word_size, char* dst_buff)
{
    /// Checking for abbreviations and short words
    if (word_size < 4 || (is_upper(w) && is_upper(w + 2)))
    {
        copy_word(w, word_size, dst_buff);
        return 0;
    }

    size_t hyphens;

    int iter;
    int syl;

    /// Inserting first letter
    memcpy(dst_buff, w, 2);

    iter = 2;
    hyphens = 0;
    int patterns[5] = { 0 };

    for (int i = 2; i < word_size * 2 - 4; i += 2)
    {
        /// Pattern 1: cv-v?*
        patterns[0] = is_cons(w + i - 2) && is_vowel(w + i) && is_vowel(w + i + 2);

        /// Pattern 2: vc-c*v*
        patterns[1] = is_vowel(w + i - 2) && is_cons(w + i) &&
                      is_cons(w + i + 2) && !is_special(w + i + 2) &&
                      contains_vowel(w + i + 4, word_size - i / 2 - 2);

        /// Pattern 3: *?v-*v*
        patterns[2] = is_vowel(w + i) &&
                      contains_vowel(w + i + 2, word_size - i / 2 - 1);

        /// Pattern 4: *v*c-c-c
        patterns[3] = (hyphens > 0 && is_cons(w + i - 2) && is_cons(w + i) &&
                       is_cons(w + i + 2) && !is_special(w + i + 2));

        /// Pattern 5: *v*c{ЪЬ}-vx
        patterns[4] = (i > 2 && is_cons(w + i - 2) && is_special(w + i) &&
                contains_vowel(w + i + 2, word_size - i / 2 - 1));

        /// Exception to pattern 3 for 2 vowels at the beginning
        if (i == 2 && is_vowel(w) && is_vowel(w + 2))
            patterns[2] = 0;

        /// Exception to pattern 3 for situation vc-cv
        if (patterns[2])
            patterns[2] ^= (is_vowel(w + i) && is_cons(w + i + 2) && is_cons(w + i + 4));

        syl = patterns[0] || patterns[1] || patterns[2] || patterns[3] || patterns[4];

        /// Inserting letter
        memcpy(dst_buff + iter, w + i, 2);

        iter += 2;
        if (syl)
        {
            /// Inserting dash
            dst_buff[iter++] = '\\';
            dst_buff[iter++] = '-';
            hyphens++;
        }
    }

    /// Inserting last 2 letters
    memcpy(dst_buff + iter, w + word_size * 2 - 4, 4);

    return hyphens;
}

size_t split_buff(char* u8_buf, size_t buff_size, char* dst_buff)
{
    int dashes;
    size_t iter = 0;

    for (int i = 0; i < buff_size; i += 2)
    {
        if (!is_russian(u8_buf + i))
        {
            dst_buff[iter++] = u8_buf[i--];
        }
        else
        {
            int j = i;
            while (is_russian(u8_buf + i)) i += 2;
            dashes = split_word(u8_buf + j, (i - j) / 2, dst_buff + iter);
            iter += i - j + dashes * 2;
            i -= 2;
        }
    }
    return iter;
}

int init_parser(parser* pp, const char* input_fn, const char* output_fn)
{
    *pp = calloc(1, sizeof(parser));

    if (*pp == NULL)
        return 1;

    (*pp)->io = new_io_stream(input_fn, output_fn);
    (*pp)->bf = calloc(BUFF_SIZE, sizeof(char));

    if ((*pp)->io == NULL)
        return 2;
    if ((*pp)->io->istream == NULL)
        return 3;
    if ((*pp)->io->ostream == NULL)
        return 4;
    if ((*pp)->io->buff == NULL)
        return 5;

    return 0;
}

void del_parser(parser p)
{
    if (p == NULL)
        return;

    del_io_stream(p->io);
    if (p->bf != NULL)
        free(p->bf);
    free(p);
}

void parse_file(parser p)
{
    int end_of_file = 0;
    size_t read_size;
    size_t for_write;
    while (!end_of_file)
    {
        read_size = read_utf8(p->io);
        if (read_size < INPUT_SIZE)
            end_of_file = 1;
        if (read_size > BUFF_SIZE / 2)
        {
            fprintf(stderr, "FILE_PARSER_ERROR: Too much data has been read\n");
            return;
        }
        for_write = split_buff(p->io->buff, read_size, p->bf);
        memcpy(p->io->buff, p->bf, for_write);
        p->io->buff[for_write] = '\0';
        write_utf8(p->io);
        memset(p->io->buff, '\0', BUFF_SIZE);
    }
}

// Debug function
void split_one_word_from_file(io_stream_t s, size_t sz)
{
    read_utf8(s);
    char t[128];
    int sl = split_word(s->buff, sz, t);
    fwrite(t, sizeof(char), sz * 2 + sl * 2, s->ostream);
}

// Debug function
void split_one_buffer_from_file(io_stream_t s)
{
    char buf[1024];
    int sz = read_utf8(s);
    sz = split_buff(s->buff, sz, buf);
    fwrite(buf, sizeof(char), sz, s->ostream);
}
