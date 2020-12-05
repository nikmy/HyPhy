#include "utf8-io.h"

io_stream_t new_io_stream(const char* input_fn, const char* output_fn)
{
    FILE* i = fopen(input_fn, "r");
    FILE* o = fopen(output_fn, "w+");

    char* buff = calloc(BUFF_SIZE, sizeof(char));
    io_stream_t stream = malloc(sizeof(struct IOStream));

    stream->istream = i;
    stream->ostream = o;
    stream->buff = buff;

    return stream;
}

void del_io_stream(io_stream_t stream)
{
    if (stream == NULL)
        return;

    if (stream->istream != NULL)
        fclose(stream->istream);
    if (stream->ostream != NULL)
        fclose(stream->ostream);
    if (stream->buff != NULL)
        free(stream->buff);

    stream->buff = NULL;
    stream->istream = NULL;
    stream->ostream = NULL;

    free(stream);
    stream = NULL;
}

int is_russian(char* u8_str)
{
    return (unsigned)u8_str[0] > 0xFFFFFF00;
}

size_t read_utf8(io_stream_t stream)
{
    if (stream == NULL)
        return fprintf(stderr,"UTF8_IO_ERROR: Uninitialized IOStream\n");

    if (stream->istream == NULL)
        return fprintf(stderr, "UTF8_IO_ERROR: Uninitialized IStream\n");

    size_t read_size;
    read_size = fread(stream->buff, sizeof(char), INPUT_SIZE, stream->istream);

    if (read_size < INPUT_SIZE || !is_russian(stream->buff + INPUT_SIZE - 2))
        return read_size;

    for (int i = INPUT_SIZE; i < BUFF_SIZE / 2; i++)
    {
        fread(stream->buff + i, 1, sizeof(char), stream->istream);
        if (!is_russian(stream->buff + i))
            return read_size + i - INPUT_SIZE + 1;
    }

    return BUFF_SIZE;
}

size_t write_utf8(io_stream_t stream)
{
    if (stream == NULL)
        return fprintf(stderr, "UTF8_IO_ERROR: Uninitialized IOStream\n");

    if (stream->ostream == NULL)
        return fprintf(stderr, "UTF8_IO_ERROR: Uninitialized OStream\n");

    size_t size;
    for (size = 0; size < BUFF_SIZE; size++)
    {
        if (stream->buff[size] == '\0')
            break;
    }

    return fwrite(stream->buff, sizeof(char), size, stream->ostream);
}
