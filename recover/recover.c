#include <cs50.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
// check if jpeg

bool checkJPEG(uint8_t x[]);

int main(int argc, char *argv[])
{
    // fopen the card
    // should accept exactly one command line argument (argc == 2); if not return 1 and show err
    // message if unable to open, return 1 and show error keep in mind the file naming protocol

    // accept single-line argument
    if (!(argc == 2))
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // open card.raw
    FILE *card = fopen(argv[1], "r");

    if (card == 0)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // create buffer
    uint8_t buffer[512];
    // create a counter for file names
    int counter = -1;
    // Declare the file as Null
    FILE *img = NULL;
    // iterate through the whole code file
    while (fread(buffer, 1, 512, card) == 512) // This already checks if file has enough data and loops till it has
    {
        // send buffer to checkJPEG()
        if (checkJPEG(buffer) == true)
        {
            // check if any file open, close if there is
            if (img != NULL)
            {
                fclose(img);
            }
            // increment the counter, we will use this for naming the file
            counter++;
            // create a .jpeg file with name (store in array and name file as array)
            char filename[8];
            sprintf(filename, "%03i.jpg", counter);
            img = fopen(filename, "w");
            // write bytes from buffer[512] into the newly created .jpg file or while img != null
        }
        if (img != NULL)
        {
            fwrite(buffer, 1, 512, img);
        }
    }
    if (img != NULL)
    {
        fclose(img);
    }
    fclose(card);
}

bool checkJPEG(uint8_t x[])
{
    if (((x[0] == 0xff) && (x[1] == 0xd8) && (x[2] == 0xff)) && ((x[3] >= 0xe0) && (x[3] <= 0xef)))
    {
        return true;
    }
    return false;
}
