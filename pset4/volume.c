// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
// Check command-line arguments
if (argc != 4)
{
printf("Usage: ./volume input.wav output.wav factor\n");
return 1;
}

// Open files and determine scaling factor
FILE *input = fopen(argv[1], "r");
if (input == NULL)
{
printf("Could not open file.\n");
return 1;
}

FILE *output = fopen(argv[2], "w");
if (output == NULL)
{
printf("Could not open file.\n");
return 1;
}

float factor = atof(argv[3]);
unsigned char *header = malloc(sizeof(char) * HEADER_SIZE);
fread(header, sizeof(uint8_t), HEADER_SIZE, input);
fwrite(header, sizeof(uint8_t), HEADER_SIZE, output);
free(header);

int16_t *buf = malloc(sizeof(int16_t) * 1);
while (fread(buf, sizeof(int16_t), 1, input) > 0)
{
double tmp = *buf * factor;
*buf = (int16_t)tmp;
fwrite(buf, sizeof(int16_t), 1, output);
}
free(buf);
// Close files
fclose(input);
fclose(output);
}

