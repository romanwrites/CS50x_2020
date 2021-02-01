#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            uint8_t average = roundf(((double)image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen) / 3);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
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
            uint16_t red = roundf(0.393 * (double)image[i][j].rgbtRed + 0.769 * (double)image[i][j].rgbtGreen + 0.189 * (double)image[i][j].rgbtBlue);
            uint16_t green = roundf(0.349 * (double)image[i][j].rgbtRed + 0.686 * (double)image[i][j].rgbtGreen + 0.168 * (double)image[i][j].rgbtBlue);
            uint16_t blue = roundf(0.272 * (double)image[i][j].rgbtRed + 0.534 * (double)image[i][j].rgbtGreen + 0.131 * (double)image[i][j].rgbtBlue);
            image[i][j].rgbtRed = red <= 255 ? (uint8_t)red : 255;
            image[i][j].rgbtGreen = green <= 255 ? (uint8_t)green : 255;
            image[i][j].rgbtBlue = blue <= 255 ? (uint8_t)blue : 255;
        }
    }
    return;
}

void swap(uint8_t *a, uint8_t *b)
{
    uint8_t tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            swap(&image[i][j].rgbtRed, &image[i][width - j - 1].rgbtRed);
            swap(&image[i][j].rgbtGreen, &image[i][width - j - 1].rgbtGreen);
            swap(&image[i][j].rgbtBlue, &image[i][width - j - 1].rgbtBlue);
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE blurred[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0)
            {
                if (j == 0)
                {
                    blurred[i][j].rgbtRed = roundf(((double)image[i][j].rgbtRed + image[i][j + 1].rgbtRed + \
                                            image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 4);
                    blurred[i][j].rgbtGreen = roundf(((double)image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + \
                                                image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 4);
                    blurred[i][j].rgbtBlue = roundf(((double)image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + \
                                                image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 4);
                }
                else if (j == width - 1)
                {
                    blurred[i][j].rgbtRed = roundf(((double)image[i][j].rgbtRed + image[i][j - 1].rgbtRed + \
                                            image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed) / 4);
                    blurred[i][j].rgbtBlue = roundf(((double)image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + \
                                            image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue) / 4);
                    blurred[i][j].rgbtGreen = roundf(((double)image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + \
                                            image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen) / 4);
                }
                else
                {
                    blurred[i][j].rgbtRed = roundf(((double)image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i][j - 1].rgbtRed + \
                                            image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed) / 6);
                    blurred[i][j].rgbtBlue = roundf(((double)image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i][j - 1].rgbtBlue + \
                                            image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue) / 6);
                    blurred[i][j].rgbtGreen = roundf(((double)image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i][j - 1].rgbtGreen + \
                                            image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen) / 6);
                }
            }
            else if (i == height - 1)
            {
                if (j == 0)
                {
                    blurred[i][j].rgbtRed = roundf(((double)image[i][j].rgbtRed + image[i][j + 1].rgbtRed + \
                                            image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed) / 4);
                    blurred[i][j].rgbtBlue = roundf(((double)image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + \
                                            image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue) / 4);
                    blurred[i][j].rgbtGreen = roundf(((double)image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + \
                                            image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen) / 4);
                }
                else if (j == width - 1)
                {
                    blurred[i][j].rgbtRed = roundf(((double)image[i][j].rgbtRed + image[i][j - 1].rgbtRed + \
                                            image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed) / 4);
                    blurred[i][j].rgbtBlue = roundf(((double)image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + \
                                            image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue) / 4);
                    blurred[i][j].rgbtGreen = roundf(((double)image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + \
                                            image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen) / 4);
                }
                else
                {
                    blurred[i][j].rgbtRed = roundf(((double)image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i][j - 1].rgbtRed + \
                                            image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i - 1][j - 1].rgbtRed) / 6);
                    blurred[i][j].rgbtBlue = roundf(((double)image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i][j - 1].rgbtBlue + \
                                            image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue) / 6);
                    blurred[i][j].rgbtGreen = roundf(((double)image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i][j - 1].rgbtGreen + \
                                            image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen) / 6);
                }
            }
            else
            {
                if (j == 0)
                {
                    blurred[i][j].rgbtRed = roundf(((double)image[i][j].rgbtRed + image[i][j + 1].rgbtRed + \
                                            image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + \
                                            image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 6);
                    blurred[i][j].rgbtBlue = roundf(((double)image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + \
                                            image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + \
                                            image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 6);
                    blurred[i][j].rgbtGreen = roundf(((double)image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + \
                                            image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + \
                                            image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 6);
                }
                else if (j == width - 1)
                {
                    blurred[i][j].rgbtRed = roundf(((double)image[i][j].rgbtRed + image[i][j - 1].rgbtRed + \
                                            image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed + \
                                            image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed) / 6);
                    blurred[i][j].rgbtBlue = roundf(((double)image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + \
                                            image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue + \
                                            image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue) / 6);
                    blurred[i][j].rgbtGreen = roundf(((double)image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + \
                                            image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen + \
                                            image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen) / 6);
                }
                else
                {
                    blurred[i][j].rgbtRed = roundf(((double)image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i][j - 1].rgbtRed + \
                                            image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i - 1][j - 1].rgbtRed + 
                                            image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed) / 9);
                    blurred[i][j].rgbtBlue = roundf(((double)image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i][j - 1].rgbtBlue + \
                                            image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue + 
                                            image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue) / 9);
                    blurred[i][j].rgbtGreen = roundf(((double)image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i][j - 1].rgbtGreen + \
                                            image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen + 
                                            image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen) / 9);
                }
            }
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = blurred[i][j].rgbtRed;
            image[i][j].rgbtGreen = blurred[i][j].rgbtGreen;
            image[i][j].rgbtBlue = blurred[i][j].rgbtBlue;
        }
    }
    return;
}
