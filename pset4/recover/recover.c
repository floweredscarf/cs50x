#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card
    FILE *card = fopen(argv[1], "r");

    // Create a buffer for a block of data
    uint8_t buffer[512];

    char filename[8];
    int filenumber = 0;
    FILE *img;

    // While there's still data left to read from the memory card
    while (fread(buffer, 1, 512, card) == 512)
    {
        // Create JPEGs from the data
        // If start of new JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // If first JPEG
            if (filenumber == 0)
            {
                sprintf(filename, "%03i.jpg", filenumber);
                filenumber++;
                img = fopen(filename, "w");
                fwrite(buffer, 1, 512, img);
            }
            // Else
            else
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", filenumber);
                filenumber++;
                img = fopen(filename, "w");
                fwrite(buffer, 1, 512, img);
            }
        }
        // Else
        else
        {
            // If already found JPEG
            if (filenumber != 0)
            {
                fwrite(buffer, 1, 512, img);
            }
        }
    }
    fclose(img);
    fclose(card);
}