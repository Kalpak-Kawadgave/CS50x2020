#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            float k = (image[a + 0][b + 0].rgbtRed + image[a + 0][b + 0].rgbtGreen + image[a + 0][b + 0].rgbtBlue) / 3.00;
            int l = round(k);
            image[a + 0][b + 0].rgbtRed = l;
            image[a + 0][b + 0].rgbtGreen = l;
            image[a + 0][b + 0].rgbtBlue = l;
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

                temp1 = image[a + 0][b + 0].rgbtRed;
                temp2 = image[a + 0][b + 0].rgbtGreen;
                temp3 = image[a + 0][b + 0].rgbtBlue;

                image[a + 0][b + 0].rgbtRed = image[a + 0][width - 1 - b].rgbtRed;
                image[a + 0][b + 0].rgbtGreen = image[a + 0][width - 1 - b].rgbtGreen;
                image[a + 0][b + 0].rgbtBlue = image[a + 0][width - 1 - b].rgbtBlue;

                image[a + 0][width - 1 - b].rgbtRed = temp1;
                image[a + 0][width - 1 - b].rgbtGreen = temp2;
                image[a + 0][width - 1 - b].rgbtBlue = temp3;
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

                temp1 = image[a + 0][b + 0].rgbtRed;
                temp2 = image[a + 0][b + 0].rgbtGreen;
                temp3 = image[a + 0][b + 0].rgbtBlue;

                image[a + 0][b + 0].rgbtRed = image[a + 0][width - 1 - b].rgbtRed;
                image[a + 0][b + 0].rgbtGreen = image[a + 0][width - 1 - b].rgbtGreen;
                image[a + 0][b + 0].rgbtBlue = image[a + 0][width - 1 - b].rgbtBlue;

                image[a + 0][width - 1 - b].rgbtRed = temp1;
                image[a + 0][width - 1 - b].rgbtGreen = temp2;
                image[a + 0][width - 1 - b].rgbtBlue = temp3;
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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int copyr [height + 2][width + 2];
    int copyg [height + 2][width + 2];
    int copyb [height + 2][width + 2];

    for (int a = 0; a < height + 2; a++)
    {
        for (int b = 0; b < width + 2; b++)
        {
            copyr[a][b] = 0;
            copyg[a][b] = 0;
            copyb[a][b] = 0;
        }
    }
    for (int a = 1; a < height + 1; a++)
    {
        for (int b = 1; b < width + 1; b++)
        {
            copyr[a][b] = image[a - 1][b - 1].rgbtRed;
            copyg[a][b] = image[a - 1][b - 1].rgbtGreen;
            copyb[a][b] = image[a - 1][b - 1].rgbtBlue;
        }
    }
    float Gx,  Gy;
    int v;
    for (int a = 1; a < height + 1; a++)
    {
        for (int b = 1; b < width + 1; b++)
        {
            Gx = -1 * copyr[a - 1][b - 1] + 0 * copyr[a - 1][b + 0] + 1 * copyr[a - 1][b + 1] +
                 -2 * copyr[a + 0][b - 1] + 0 * copyr[a + 0][b + 0] + 2 * copyr[a + 0][b + 1] +
                 -1 * copyr[a + 1][b - 1] + 0 * copyr[a + 1][b + 0] + 1 * copyr[a + 1][b + 1];
            Gy = -1 * copyr[a - 1][b - 1] - 2 * copyr[a - 1][b + 0] - 1 * copyr[a - 1][b + 1]
                 + 0 * copyr[a + 0][b - 1] + 0 * copyr[a + 0][b + 0] + 0 * copyr[a + 0][b + 1]
                 + 1 * copyr[a + 1][b - 1] + 2 * copyr[a + 1][b + 0] + 1 * copyr[a + 1][b + 1];
            v = round(sqrt(Gx * Gx + Gy * Gy));
            if (v > 255)
            {
                v = 255;
            }
            image[a - 1][b - 1].rgbtRed = v;

            Gx = -1 * copyg[a - 1][b - 1] + 0 * copyg[a - 1][b + 0] + 1 * copyg[a - 1][b + 1] +
                 -2 * copyg[a + 0][b - 1] + 0 * copyg[a + 0][b + 0] + 2 * copyg[a + 0][b + 1] +
                 -1 * copyg[a + 1][b - 1] + 0 * copyg[a + 1][b + 0] + 1 * copyg[a + 1][b + 1];
            Gy = -1 * copyg[a - 1][b - 1] - 2 * copyg[a - 1][b + 0] - 1 * copyg[a - 1][b + 1]
                 + 0 * copyg[a + 0][b - 1] + 0 * copyg[a + 0][b + 0] + 0 * copyg[a + 0][b + 1]
                 + 1 * copyg[a + 1][b - 1] + 2 * copyg[a + 1][b + 0] + 1 * copyg[a + 1][b + 1];
            v = round(sqrt(Gx * Gx + Gy * Gy));
            if (v > 255)
            {
                v = 255;
            }
            image[a - 1][b - 1].rgbtGreen = v;

            Gx = -1 * copyb[a - 1][b - 1] + 0 * copyb[a - 1][b + 0] + 1 * copyb[a - 1][b + 1] +
                 -2 * copyb[a + 0][b - 1] + 0 * copyb[a + 0][b + 0] + 2 * copyb[a + 0][b + 1] +
                 -1 * copyb[a + 1][b - 1] + 0 * copyb[a + 1][b + 0] + 1 * copyb[a + 1][b + 1];
            Gy = -1 * copyb[a - 1][b - 1] - 2 * copyb[a - 1][b + 0] - 1 * copyb[a - 1][b + 1]
                 + 0 * copyb[a + 0][b - 1] + 0 * copyb[a + 0][b + 0] + 0 * copyb[a + 0][b + 1]
                 + 1 * copyb[a + 1][b - 1] + 2 * copyb[a + 1][b + 0] + 1 * copyb[a + 1][b + 1];
            v = round(sqrt(Gx * Gx + Gy * Gy));
            if (v > 255)
            {
                v = 255;
            }
            image[a - 1][b - 1].rgbtBlue = v;
        }
    }
    return;
}