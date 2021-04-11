// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"


int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize n infile outfile\n");
        return 1;
    }

    // remember filenames and size
    int n = atoi(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }


    //logic of resize
    int triple_size = sizeof(RGBTRIPLE);

    BITMAPFILEHEADER output_bitmap_file = bf;
    BITMAPINFOHEADER output_bitmap_info = bi;

    output_bitmap_info.biHeight = bi.biHeight * n;
    output_bitmap_info.biWidth = bi.biWidth * n;

    int output_file_padding = (4 - (output_bitmap_info.biWidth * triple_size) % 4) % 4;

    output_bitmap_info.biSizeImage = abs(output_bitmap_info.biHeight * (output_bitmap_info.biWidth * triple_size +
                                         output_file_padding));

    output_bitmap_file.bfSize = output_bitmap_info.biSizeImage + 54;


    // write outfile's BITMAPFILEHEADER
    fwrite(&output_bitmap_file, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&output_bitmap_info, sizeof(BITMAPINFOHEADER), 1, outptr);

    // counter of repeats of scanline
    int scanline_counter = 0;

    // counter of the times the pixel is repeated
    int pixel_counter = 0;

    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * triple_size) % 4) % 4;

    // iterate over infile's scanlines
    for (int i = 0, output_biHeight = abs(output_bitmap_info.biHeight); i < output_biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < output_bitmap_info.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, triple_size, 1, inptr);

            // write RGB triple to outfile
            fwrite(&triple, triple_size, 1, outptr);
            pixel_counter++;

            // check if pixel it has been repeated as many times as required
            if (pixel_counter < n)
            {
                fseek(inptr, -triple_size, SEEK_CUR);
            }
            else
            {
                pixel_counter = 0;
            }
        }

        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < output_file_padding; k++)
        {
            fputc(0x00, outptr);
        }
        scanline_counter++;

        if (scanline_counter < n)
        {
            fseek(inptr, -((bi.biWidth * triple_size + padding)), SEEK_CUR);
        }
        else
        {
            scanline_counter = 0;
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}

