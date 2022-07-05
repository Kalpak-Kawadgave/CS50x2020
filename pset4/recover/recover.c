#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //check for the correct usage
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    //open memory card
    FILE *card = fopen(argv[1], "r");
    int name = 0;

    //Create a buffer memory to store chunks of 512 bytes
    BYTE buffer[512];

    //string to extract filenames
    char *filename = malloc(8 * sizeof(char));

    //read till the end of card
    while (fread(buffer, 512, 1, card) > 0)
    {
        //if new header is found
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            sprintf(filename, "%03i.jpg", name);
            FILE *img = fopen(filename, "w");
            fwrite(buffer, 512, 1, img);
            fclose(img);
            name++;
        }

        //if you need to write in the same file
        else if (name > 0)
        {
            FILE *img = fopen(filename, "a");
            fwrite(buffer, 512, 1, img);
            fclose(img);
        }
    }

    //free all the memory
    free(filename);
    fclose(card);
}