// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
	uint8_t	*header;
	int16_t	sample;

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

	// Copy header from input file to output file
	header = (uint8_t *) calloc(HEADER_SIZE, sizeof(uint8_t));
	if (!header)
	{
		printf("Memory error\n");
		return (1);
	}
	if (fread(header, sizeof(uint8_t), HEADER_SIZE, input) != HEADER_SIZE)
	{
		printf("Error: cannot read from %s\n", argv[1]);
		fclose(input);
		fclose(output);
		free(header);
		return (1);
	}
	if (fwrite(header, sizeof(uint8_t), HEADER_SIZE, output) != HEADER_SIZE)
	{
		printf("Error: cannot write in %s\n", argv[2]);
		fclose(input);
		fclose(output);
		free(header);
		return (1);
	}
	// Read samples from input file and write updated data to output file
	while (fread(&sample, sizeof(int16_t), 1, input) == 1)
	{
		sample = (int16_t) (sample * factor);
		if (fwrite(&sample, sizeof(int16_t), 1, output) != 1)
		{
			printf("Error: cannot write in %s\n", argv[2]);
			fclose(input);
			fclose(output);
			free(header);
			return (1);
		}	
	}
	// Close files
	fclose(input);
	fclose(output);
	free(header);
}
