#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int BLOCK_SIZE = 512;
typedef uint8_t BYTE;

BYTE jpg_header[3] = {0xff, 0xd8, 0xff};

bool is_header(BYTE buffer[]);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }
    FILE *raw_file = fopen(argv[1], "r");
    if (raw_file == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    BYTE buffer[BLOCK_SIZE];
    int jpg_count = 0;

    // 按 512 字节遍历文件
    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, raw_file) == BLOCK_SIZE)
    {
        // 如果是jpg的header
        if (is_header(buffer))
        {
            // 打开一个新jpg文件
            char buffer_name[8];
            sprintf(buffer_name, "%03i.jpg", jpg_count++);
            FILE *jpg_file = fopen(buffer_name, "w");
            if (jpg_file == NULL)
            {
                printf("Could not create file.\n");
                fclose(raw_file);
                return 1;
            }
            do
            {
                fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, jpg_file);
            }
            while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, raw_file) == BLOCK_SIZE && !is_header(buffer));
            fclose(jpg_file);
            // 指针回到 发现新jpg的地方
            fseek(raw_file, -BLOCK_SIZE, SEEK_CUR);
        }
    }
    // 检查文件是否读到了结尾
    if (feof(raw_file))
    {
        // Close files
        fclose(raw_file);
        return 0;
    }
    else
    {
        // Close files
        fclose(raw_file);
        return 1;
    }
}

// 检查是否是jpg开头
bool is_header(BYTE buffer[])
{
    for (int i = 0; i < 3; i++)
    {
        if (buffer[i] != jpg_header[i])
            return false;
    }
    if (buffer[3] <= 0xef && buffer[3] >= 0xe0)
        return true;
    else
        return false;
}
