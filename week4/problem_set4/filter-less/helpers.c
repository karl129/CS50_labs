#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            BYTE gray = (BYTE) ((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0 + 0.5);
            image[i][j].rgbtBlue = gray;
            image[i][j].rgbtGreen = gray;
            image[i][j].rgbtRed = gray;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // 超过255一个字节存不下
            WORD sepia_red =
                (WORD) (0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue + 0.5);
            WORD sepia_green =
                (WORD) (0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue + 0.5);
            WORD sepia_blue =
                (WORD) (0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue + 0.5);

            image[i][j].rgbtBlue = fmin(255, sepia_blue);
            image[i][j].rgbtGreen = fmin(255, sepia_green);
            image[i][j].rgbtRed = fmin(255, sepia_red);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // 为 buffer 分配内存
    RGBTRIPLE *buffer = (RGBTRIPLE *) malloc(sizeof(RGBTRIPLE) * width);
    if (buffer == NULL)
    {
        // 处理内存分配失败的情况
        printf("内存分配失败\n");
        return;
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
            buffer[j] = image[i][j];
        for (int j = 0; j < width; j++)
            image[i][j] = buffer[width - j - 1];
    }
    free(buffer);
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // 创建临时数组，用于存储模糊处理后的像素
    RGBTRIPLE temp[height][width];

    // 对每个像素应用模糊算法
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // 初始化计算平均值所需的变量
            int count = 0;
            int sumRed = 0, sumGreen = 0, sumBlue = 0;

            // 遍历当前像素周围的3x3区域
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    // 计算相邻像素的索引
                    int ni = i + di;
                    int nj = j + dj;

                    // 如果相邻像素位于图像内部，则将其颜色值加入到求和变量中
                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        sumRed += image[ni][nj].rgbtRed;
                        sumGreen += image[ni][nj].rgbtGreen;
                        sumBlue += image[ni][nj].rgbtBlue;
                        count++;
                    }
                }
            }
            // 计算平均值并将其赋给临时数组
            temp[i][j].rgbtRed = (BYTE) (sumRed / (float) count + 0.5);
            temp[i][j].rgbtGreen = (BYTE) (sumGreen / (float) count + 0.5);
            temp[i][j].rgbtBlue = (BYTE) (sumBlue / (float) count + 0.5);
        }
    }

    // 将临时数组中的像素值复制回原始图像数组
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }

    return;
}
