#include <stdio.h>


int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover card.raw\n");
        return 1;
    }

    char *file = argv[1];

    // Size of photos
    const int PIC_SIZE = 512;


    FILE *input_file = fopen(file, "r");

    if (input_file == NULL)
    {
        fprintf(stderr, "Could not open %s\n", file);
        return 2;
    }

    // if not write unsigned the compiler cries
    unsigned char buffer[PIC_SIZE];

    //out file
    FILE *output_file = NULL;

    // space for file name
    char image[7];

    // number of files
    int n = 0;


    while (fread(buffer, PIC_SIZE, 1, input_file) == 1)
    {
        // find de begin of images
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            buffer[3] >= 0xe0 && buffer[3] <= 0xef)
        {
            // if image already exists close file
            if (n > 0)
            {
                fclose(output_file);
            }

            // make on dynamic number of image
            sprintf(image, "%03d.jpg", n);

            // open image
            output_file = fopen(image, "w");

            if (output_file == NULL)
            {
                fprintf(stderr, "Could not create image %s\n", image);
                return 3;
            }

            n++;

        }

        //write to image
        if (output_file != NULL)
        {
            fwrite(buffer, PIC_SIZE, 1, output_file);
        }
    }

    // close output file
    fclose(output_file);

    // close input file
    fclose(input_file);

    return 0;
}