#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // loop height
    for (int i = 0; i < height; i++)
    {
        // loop width
        for (int j = 0; j < width; j++)
        {
            int temp = 0;
            temp =
                round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = temp;
            image[i][j].rgbtGreen = temp;
            image[i][j].rgbtRed = temp;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // loop height
    for (int i = 0; i < height; i++)
    {
        // loop width
        for (int j = 0; j < (width / 2); j++)
        {
            int temp = 0;
            temp = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][width - j - 1].rgbtBlue = temp;
            temp = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][width - j - 1].rgbtGreen = temp;
            temp = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][width - j - 1].rgbtRed = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    // loop height
    for (int i = 0; i < height; i++)
    {
        // loop width
        for (int j = 0; j < width; j++)
        {
            // check if it is an edge pixel
            if ((i == 0) || (i == (height - 1)) || (j == 0) || (j == (width - 1)))
            {
                float pixels = 0.0;
                int green = 0, blue = 0, red = 0;
                for (int a = (i - 1); a <= (i + 1); a++)
                {
                    for (int b = (j - 1); b <= (j + 1); b++)
                    {
                        if (!(a < 0) && !(b < 0) && !(a >= height) && !(b >= width))
                        {
                            blue = blue + image[a][b].rgbtBlue;
                            green = green + image[a][b].rgbtGreen;
                            red = red + image[a][b].rgbtRed;
                            pixels++;
                        }
                    }
                }
                temp[i][j].rgbtBlue = round(blue / pixels);
                temp[i][j].rgbtGreen = round(green / pixels);
                temp[i][j].rgbtRed = round(red / pixels);
            }
            // if not edge, make 3*3 grid, average
            else
            {
                float pixels = 0.0;
                int green = 0, blue = 0, red = 0;
                for (int a = (i - 1); a <= (i + 1); a++)
                {
                    for (int b = (j - 1); b <= (j + 1); b++)
                    {

                        blue = blue + image[a][b].rgbtBlue;
                        green = green + image[a][b].rgbtGreen;
                        red = red + image[a][b].rgbtRed;
                        pixels++;
                    }
                }
                temp[i][j].rgbtBlue = round(blue / pixels);
                temp[i][j].rgbtGreen = round(green / pixels);
                temp[i][j].rgbtRed = round(red / pixels);
            }
        }
    }

    // copy temp to image now
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // loop height
    for (int i = 0; i < height; i++)
    {
        // loop width
        for (int j = 0; j < width; j++)
        {
            float gxred = 0, gyred = 0, gxgreen = 0, gygreen = 0, gxblue = 0, gyblue = 0;

            // Apply Sobel
            for (int a = -1; a <= 1; a++)
            {
                for (int b = -1; b <= 1; b++)
                {
                    int newX = i + a;
                    int newY = j + b;

                    // Check validity
                    if (newX >= 0 && newX < height && newY >= 0 && newY < width)
                    {
                        gxred += gx[a + 1][b + 1] * image[newX][newY].rgbtRed;
                        gyred += gy[a + 1][b + 1] * image[newX][newY].rgbtRed;

                        gxgreen += gx[a + 1][b + 1] * image[newX][newY].rgbtGreen;
                        gygreen += gy[a + 1][b + 1] * image[newX][newY].rgbtGreen;

                        gxblue += gx[a + 1][b + 1] * image[newX][newY].rgbtBlue;
                        gyblue += gy[a + 1][b + 1] * image[newX][newY].rgbtBlue;
                    }
                }
            }

            // SOBEL
            int red = round(sqrt(gxred * gxred + gyred * gyred));
            int green = round(sqrt(gxgreen * gxgreen + gygreen * gygreen));
            int blue = round(sqrt(gxblue * gxblue + gyblue * gyblue));

            // <255
            temp[i][j].rgbtRed = (red > 255) ? 255 : red;
            temp[i][j].rgbtGreen = (green > 255) ? 255 : green;
            temp[i][j].rgbtBlue = (blue > 255) ? 255 : blue;
        }
    }

    // copy temp to image now
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}
