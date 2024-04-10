#include <math.h>
#include <stdbool.h>

#include "helpers.h"

bool in_fig(int ni, int nj, int height, int width);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            BYTE gray = (BYTE) round(((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0));
            image[i][j].rgbtBlue = gray;
            image[i][j].rgbtGreen = gray;
            image[i][j].rgbtRed = gray;
        }
    }
    return;
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // 为 buffer 分配内存
    RGBTRIPLE buffer[width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
            buffer[j] = image[i][j];
        for (int j = 0; j < width; j++)
            image[i][j] = buffer[width - j - 1];
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int count = 0;
            int sumRed = 0, sumGreen = 0, sumBlue = 0;
            // 遍历周围 3*3
            for (int ki = i - 1; ki <= i + 1; ki++)
            {
                for (int kj = j - 1; kj <= j + 1; kj++)
                {
                    if (in_fig(ki, kj, height, width))
                    {
                        sumRed += image[ki][kj].rgbtRed;
                        sumGreen += image[ki][kj].rgbtGreen;
                        sumBlue += image[ki][kj].rgbtBlue;
                        count++;
                    }
                }
            }
            // 计算平均值并将其赋给临时数组
            temp[i][j].rgbtRed = (BYTE) round((sumRed / (float) count));
            temp[i][j].rgbtGreen = (BYTE) round((sumGreen / (float) count));
            temp[i][j].rgbtBlue = (BYTE) round((sumBlue / (float) count));
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
            image[i][j] = temp[i][j];
    }
    return;
}

// 判断是否在图像里
bool in_fig(int ni, int nj, int height, int width)
{
    return (ni >= 0 && ni < height && nj >= 0 && nj < width);
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumRedx = 0, sumGreenx = 0, sumBluex = 0, sumRedy = 0, sumGreeny = 0, sumBluey = 0;
            // 遍历周围 3*3
            for (int ki = 0; ki < 3; ki++)
            {
                for (int kj = 0; kj < 3; kj++)
                {
                    int ni = i - 1 + ki;
                    int nj = j - 1 + kj;
                    if (in_fig(ni, nj, height, width))
                    {
                        sumRedx += image[ni][nj].rgbtRed * gx[ki][kj];
                        sumGreenx += image[ni][nj].rgbtGreen * gx[ki][kj];
                        sumBluex += image[ni][nj].rgbtBlue * gx[ki][kj];

                        sumRedy += image[ni][nj].rgbtRed * gy[ki][kj];
                        sumGreeny += image[ni][nj].rgbtGreen * gy[ki][kj];
                        sumBluey += image[ni][nj].rgbtBlue * gy[ki][kj];
                    }
                }
            }
            // 索尔算法合并x、y
            int newRed = round(sqrt(pow(sumRedx, 2) + pow(sumRedy, 2)));
            int newGreen = round(sqrt(pow(sumGreenx, 2) + pow(sumGreeny, 2)));
            int newBlue = round(sqrt(pow(sumBluex, 2) + pow(sumBluey, 2)));
            // 赋给临时变量
            temp[i][j].rgbtRed = fmin(255, newRed);
            temp[i][j].rgbtGreen = fmin(255, newGreen);
            temp[i][j].rgbtBlue = fmin(255, newBlue);
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
            image[i][j] = temp[i][j];
    }
    return;
}
