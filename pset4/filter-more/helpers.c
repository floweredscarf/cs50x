#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Take average of red, green, and blue
            int average = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            // Update pixel values
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Swap pixels
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumBlue = 0;
            int sumGreen = 0;
            int sumRed = 0;
            int count = 0;
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    if (i + di >= 0 && i + di < height && j + dj >= 0 && j + dj < width)
                    {
                        sumBlue += copy[i + di][j + dj].rgbtBlue;
                        sumGreen += copy[i + di][j + dj].rgbtGreen;
                        sumRed += copy[i + di][j + dj].rgbtRed;
                        count++;
                    }
                }
            }
            image[i][j].rgbtBlue = round((float) sumBlue / count);
            image[i][j].rgbtGreen = round((float) sumGreen / count);
            image[i][j].rgbtRed = round((float) sumRed / count);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    int gx_kernel[3][3] = {{-1, 0 , 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy_kernel[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int gxBlue = 0;
            int gyBlue = 0;
            int gxGreen = 0;
            int gyGreen = 0;
            int gxRed = 0;
            int gyRed = 0;
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    if (i + di >= 0 && i + di < height && j + dj >= 0 && j + dj < width)
                    {
                        gxBlue += copy[i + di][j + dj].rgbtBlue * gx_kernel[di + 1][dj + 1];
                        gyBlue += copy[i + di][j + dj].rgbtBlue * gy_kernel[di + 1][dj + 1];
                        gxGreen += copy[i + di][j + dj].rgbtGreen * gx_kernel[di + 1][dj + 1];
                        gyGreen += copy[i + di][j + dj].rgbtGreen * gy_kernel[di + 1][dj + 1];
                        gxRed += copy[i + di][j + dj].rgbtRed * gx_kernel[di + 1][dj + 1];
                        gyRed += copy[i + di][j + dj].rgbtRed * gy_kernel[di + 1][dj + 1];
                    }
                }
            }
            image[i][j].rgbtBlue = fmin(round(sqrt(pow(gxBlue, 2) + pow(gyBlue, 2))), 255);
            image[i][j].rgbtGreen = fmin(round(sqrt(pow(gxGreen, 2) + pow(gyGreen, 2))), 255);
            image[i][j].rgbtRed = fmin(round(sqrt(pow(gxRed, 2) + pow(gyRed, 2))), 255);
        }
    }
    return;
}
