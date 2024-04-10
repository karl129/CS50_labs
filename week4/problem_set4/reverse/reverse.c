#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

bool check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // TODO #1
    if (argc != 3)
    {
        printf("Usage: ./volume input.wav output.wav\n");
        return 1;
    }

    // Open input file for reading
    // TODO #2
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Can't open input file.\n");
        return 1;
    }

    // Read header
    // TODO #3
    WAVHEADER wav_header;
    fread(&wav_header, sizeof(wav_header), 1, input);

    // Use check_format to ensure WAV format
    // TODO #4
    if (check_format(wav_header) == false)
    {
        printf("Not a wave file.\n");
        fclose(input);
        return 1;
    }
    // Open output file for writing
    // TODO #5
    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Can't create output file.\n");
        fclose(input);
        return 1;
    }
    // Write header to file
    // TODO #6
    fwrite(&wav_header, sizeof(wav_header), 1, output);

    // Use get_block_size to calculate size of block
    // TODO #7
    int block_size = get_block_size(wav_header);

    // Write reversed audio to file
    // TODO #8
    BYTE buffer[block_size];
    // 指示符移动到最后一个block
    fseek(input, -block_size, SEEK_END);
    int header_size = sizeof(wav_header);
    //
    while (ftell(input) >= header_size)
    {
        fread(buffer, block_size, 1, input);
        fwrite(buffer, block_size, 1, output);
        // 遍历完一个之后，往前退两个
        if (fseek(input, -2 * block_size, SEEK_CUR)) // 如果没有返回 0， 移动失败
        {
            printf("Failed to seek.\n");
            fclose(input);
            fclose(output);
            return 1;
        }
    }
    fclose(input);
    fclose(output);
    return 0;
}

bool check_format(WAVHEADER header)
{
    char wav[4] = {'W', 'A', 'V', 'E'};
    // TODO #4
    for (int i = 0; i < 4; i++)
    {
        if (header.format[i] != wav[i])
            return false;
    }
    return true;
}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    return header.numChannels * header.bitsPerSample / 8;
}
