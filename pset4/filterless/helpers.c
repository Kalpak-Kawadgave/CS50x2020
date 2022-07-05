#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            float k = (image[a][b].rgbtRed + image[a][b].rgbtGreen + image[a][b].rgbtBlue) / 3.00;
            int l = round(k);
            image[a][b].rgbtRed = l;
            image[a][b].rgbtGreen = l;
            image[a][b].rgbtBlue = l;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            float k = (0.393 * (float) image[a][b].rgbtRed + 0.769 * (float) image[a][b].rgbtGreen + 0.189 * (float) image[a][b].rgbtBlue);
            float l = (0.349 * (float) image[a][b].rgbtRed + 0.686 * (float) image[a][b].rgbtGreen + 0.168 * (float) image[a][b].rgbtBlue);
            float m = (0.272 * (float) image[a][b].rgbtRed + 0.534 * (float) image[a][b].rgbtGreen + 0.131 * (float) image[a][b].rgbtBlue);
            int x = round(k);
            int y = round(l);
            int z = round(m);
            if (x > 255)
            {
                x = 255;
            }
            if (y > 255)
            {
                y = 255;
            }
            if (z > 255)
            {
                z = 255;
            }
            image[a][b].rgbtRed = x;
            image[a][b].rgbtGreen = y;
            image[a][b].rgbtBlue = z;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    if (width % 2 == 0)
    {
        for (int a = 0; a < height; a++)
        {
            for (int b = 0; b < width / 2; b++)
            {
                int temp1 = 0;
                int temp2 = 0;
                int temp3 = 0;

                temp1 = image[a][b].rgbtRed;
                temp2 = image[a][b].rgbtGreen;
                temp3 = image[a][b].rgbtBlue;

                image[a][b].rgbtRed = image[a][width - 1 - b].rgbtRed;
                image[a][b].rgbtGreen = image[a][width - 1 - b].rgbtGreen;
                image[a][b].rgbtBlue = image[a][width - 1 - b].rgbtBlue;

                image[a][width - 1 - b].rgbtRed = temp1;
                image[a][width - 1 - b].rgbtGreen = temp2;
                image[a][width - 1 - b].rgbtBlue = temp3;
            }
        }
    }
    else
    {
        for (int a = 0; a < height; a++)
        {
            for (int b = 0; b < (width - 1) / 2 ; b++)
            {
                int temp1 = 0;
                int temp2 = 0;
                int temp3 = 0;

                temp1 = image[a][b].rgbtRed;
                temp2 = image[a][b].rgbtGreen;
                temp3 = image[a][b].rgbtBlue;

                image[a][b].rgbtRed = image[a][width - 1 - b].rgbtRed;
                image[a][b].rgbtGreen = image[a][width - 1 - b].rgbtGreen;
                image[a][b].rgbtBlue = image[a][width - 1 - b].rgbtBlue;

                image[a][width - 1 - b].rgbtRed = temp1;
                image[a][width - 1 - b].rgbtGreen = temp2;
                image[a][width - 1 - b].rgbtBlue = temp3;
            }
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int copyr [height][width];
    int copyg [height][width];
    int copyb [height][width];
    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            copyr[a][b] = image[a][b].rgbtRed;
        }
    }
    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            copyg[a][b] = image[a][b].rgbtGreen;
        }
    }
    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            copyb[a][b] = image[a][b].rgbtBlue;
        }
    }
    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            //middle
            if (a > 0 && a < height - 1 && b > 0 && b < width - 1)
            {
                copyr[a][b] = round((image[a - 1][b - 1].rgbtRed + image[a - 1][b].rgbtRed + image[a - 1][b + 1].rgbtRed
                                     + image[a][b - 1].rgbtRed + image[a][b].rgbtRed + image[a][b + 1].rgbtRed
                                     + image[a + 1][b - 1].rgbtRed + image[a + 1][b].rgbtRed + image[a + 1][b + 1].rgbtRed) / 9.00);
                copyg[a][b] = round((image[a - 1][b - 1].rgbtGreen + image[a - 1][b].rgbtGreen + image[a - 1][b + 1].rgbtGreen
                                     + image[a][b - 1].rgbtGreen + image[a][b].rgbtGreen + image[a][b + 1].rgbtGreen
                                     + image[a + 1][b - 1].rgbtGreen + image[a + 1][b].rgbtGreen + image[a + 1][b + 1].rgbtGreen) / 9.00);
                copyb[a][b] = round((image[a - 1][b - 1].rgbtBlue + image[a - 1][b].rgbtBlue + image[a - 1][b + 1].rgbtBlue
                                     + image[a][b - 1].rgbtBlue + image[a][b].rgbtBlue + image[a][b + 1].rgbtBlue
                                     + image[a + 1][b - 1].rgbtBlue + image[a + 1][b].rgbtBlue + image[a + 1][b + 1].rgbtBlue) / 9.00);
            }
            //edges
            else if (a == 0 && b > 0 && b < width - 1)
            {
                copyr[a][b] = round((image[a][b - 1].rgbtRed + image[a][b].rgbtRed + image[a][b + 1].rgbtRed
                                     + image[a + 1][b - 1].rgbtRed + image[a + 1][b].rgbtRed + image[a + 1][b + 1].rgbtRed) / 6.00);
                copyg[a][b] = round((image[a][b - 1].rgbtGreen + image[a][b].rgbtGreen + image[a][b + 1].rgbtGreen
                                     + image[a + 1][b - 1].rgbtGreen + image[a + 1][b].rgbtGreen + image[a + 1][b + 1].rgbtGreen) / 6.00);
                copyb[a][b] = round((image[a][b - 1].rgbtBlue + image[a][b].rgbtBlue + image[a][b + 1].rgbtBlue
                                     + image[a + 1][b - 1].rgbtBlue + image[a + 1][b].rgbtBlue + image[a + 1][b + 1].rgbtBlue) / 6.00);
            }
            else if (a > 0 && b == 0 && a < height - 1)
            {
                copyr[a][b] = round((image[a - 1][b].rgbtRed + image[a - 1][b + 1].rgbtRed + image[a][b].rgbtRed
                                     + image[a][b + 1].rgbtRed + image[a + 1][b].rgbtRed + image[a + 1][b + 1].rgbtRed) / 6.00);
                copyg[a][b] = round((image[a - 1][b].rgbtGreen + image[a - 1][b + 1].rgbtGreen + image[a][b].rgbtGreen
                                     + image[a][b + 1].rgbtGreen + image[a + 1][b].rgbtGreen + image[a + 1][b + 1].rgbtGreen) / 6.00);
                copyb[a][b] = round((image[a - 1][b].rgbtBlue + image[a - 1][b + 1].rgbtBlue + image[a][b].rgbtBlue
                                     + image[a][b + 1].rgbtBlue + image[a + 1][b].rgbtBlue + image[a + 1][b + 1].rgbtBlue) / 6.00);
            }
            else if (a == height - 1 && b > 0 && b < width - 1)
            {
                copyr[a][b] = round((image[a - 1][b - 1].rgbtRed + image[a - 1][b].rgbtRed + image[a - 1][b + 1].rgbtRed
                                     + image[a][b - 1].rgbtRed + image[a][b].rgbtRed + image[a][b + 1].rgbtRed) / 6.00);
                copyg[a][b] = round((image[a - 1][b - 1].rgbtGreen + image[a - 1][b].rgbtGreen + image[a - 1][b + 1].rgbtGreen
                                     + image[a][b - 1].rgbtGreen + image[a][b].rgbtGreen + image[a][b + 1].rgbtGreen) / 6.00);
                copyb[a][b] = round((image[a - 1][b - 1].rgbtBlue + image[a - 1][b].rgbtBlue + image[a - 1][b + 1].rgbtBlue
                                     + image[a][b - 1].rgbtBlue + image[a][b].rgbtBlue + image[a][b + 1].rgbtBlue) / 6.00);
            }
            else if (a > 0 && b == width - 1 && a < height - 1)
            {
                copyr[a][b] = round((image[a - 1][b - 1].rgbtRed + image[a - 1][b].rgbtRed + image[a][b - 1].rgbtRed
                                     + image[a][b].rgbtRed + image[a + 1][b - 1].rgbtRed + image[a + 1][b].rgbtRed) / 6.00);
                copyg[a][b] = round((image[a - 1][b - 1].rgbtGreen + image[a - 1][b].rgbtGreen + image[a][b - 1].rgbtGreen
                                     + image[a][b].rgbtGreen + image[a + 1][b - 1].rgbtGreen + image[a + 1][b].rgbtGreen) / 6.00);
                copyb[a][b] = round((image[a - 1][b - 1].rgbtBlue + image[a - 1][b].rgbtBlue + image[a][b - 1].rgbtBlue
                                     + image[a][b].rgbtBlue + image[a + 1][b - 1].rgbtBlue + image[a + 1][b].rgbtBlue) / 6.00);
            }
            //corners
            else if (a == 0 && b == 0)
            {
                copyr[a][b] = round((image[a][b].rgbtRed + image[a][b + 1].rgbtRed
                                     + image[a + 1][b].rgbtRed + image[a + 1][b + 1].rgbtRed) / 4.00);
                copyg[a][b] = round((image[a][b].rgbtGreen + image[a][b + 1].rgbtGreen
                                     + image[a + 1][b].rgbtGreen + image[a + 1][b + 1].rgbtGreen) / 4.00);
                copyb[a][b] = round((image[a][b].rgbtBlue + image[a][b + 1].rgbtBlue
                                     + image[a + 1][b].rgbtBlue + image[a + 1][b + 1].rgbtBlue) / 4.00);
            }
            else if (a == height - 1 && b == width - 1)
            {
                copyr[a][b] = round((image[a][b].rgbtRed + image[a][b - 1].rgbtRed
                                     + image[a - 1][b].rgbtRed + image[a - 1][b - 1].rgbtRed) / 4.00);
                copyg[a][b] = round((image[a][b].rgbtGreen + image[a][b - 1].rgbtGreen
                                     + image[a - 1][b].rgbtGreen + image[a - 1][b - 1].rgbtGreen) / 4.00);
                copyb[a][b] = round((image[a][b].rgbtBlue + image[a][b - 1].rgbtBlue
                                     + image[a - 1][b].rgbtBlue + image[a - 1][b - 1].rgbtBlue) / 4.00);
            }
            else if (a == height - 1 && b == 0)
            {
                copyr[a][b] = round((image[a - 1][b].rgbtRed + image[a - 1][b + 1].rgbtRed
                                     + image[a][b].rgbtRed + image[a][b + 1].rgbtRed) / 4.00);
                copyg[a][b] = round((image[a - 1][b].rgbtGreen + image[a - 1][b + 1].rgbtGreen
                                     + image[a][b].rgbtGreen + image[a][b + 1].rgbtGreen) / 4.00);
                copyb[a][b] = round((image[a - 1][b].rgbtBlue + image[a - 1][b + 1].rgbtBlue
                                     + image[a][b].rgbtBlue + image[a][b + 1].rgbtBlue) / 4.00);
            }
            else if (a == 0 && b == width - 1)
            {
                copyr[a][b] = round((image[a][b - 1].rgbtRed + image[a][b].rgbtRed
                                     + image[a + 1][b - 1].rgbtRed + image[a + 1][b].rgbtRed) / 4.00);
                copyg[a][b] = round((image[a][b - 1].rgbtGreen + image[a][b].rgbtGreen
                                     + image[a + 1][b - 1].rgbtGreen + image[a + 1][b].rgbtGreen) / 4.00);
                copyb[a][b] = round((image[a][b - 1].rgbtBlue + image[a][b].rgbtBlue
                                     + image[a + 1][b - 1].rgbtBlue + image[a + 1][b].rgbtBlue) / 4.00);
            }
        }
    }
    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            image[a][b].rgbtRed = copyr[a][b];
        }
    }
    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            image[a][b].rgbtGreen = copyg[a][b];
        }
    }
    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            image[a][b].rgbtBlue = copyb[a][b];
        }
    }
    return;
}