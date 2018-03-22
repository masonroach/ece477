#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define FILENAME "/dev/ACM0"

int main(int argc, char **argv)
{
	// This program will read and write serial 
	// to talk to atmega88 to play high/low game
	FILE *sfile;
	char getStr[50];
	unsigned char guess;

	// Open device file and error check
	sfile = fopen(FILENAME, "r+");
	if (sfile == NULL) {
		printf("ERROR: Unable to open device file, code %d\n", errno);
		exit(0);
	}

	
	while (1) {
		
		// Read and print start of game text
		if (fgets(getStr, 50, sfile) == NULL) {
			printf("ERROR: Unable to read from device file 1, code %d\n", errno);
			exit(0);
		}		
		printf("%s\n", getStr);	
	
		guess = 127;
		
		// Game start character
		fputc('0', sfile);

		// For each guessing round
		while(1){
			// Receives "Enter your guess:"
			if (fgets(getStr, 1, sfile) == NULL) {
				printf("ERROR: Unable to read from device file 2, code %d\n", errno);
                        	exit(0);
			}
			printf("%s\n", getStr);
			
			// Makes guess
			sprintf(getStr, "%d", guess);
			fputs(getStr, sfile);
		
			// Receives feedback, "HIGH", "LOW", or "CORRECT"
			if (fgets(getStr, 1, sfile) == NULL) {
                                printf("ERROR: Unable to read from device file 3, code %d\n", errno);
                                exit(0);
                        }
			printf("%s\n", getStr);

			// Adjust guess or quit game with communication error
			if (getStr[0] == 'L') guess /= 2; // low
			else if (getStr[0] == 'H') guess += (255 - guess) / 2; // high
			else if (getStr[0] == 'C') { printf("Correct number: %d\n", guess); break; } // correct
			else { printf("Incorrect feedback, received %c, exiting\n", getStr[0]); exit(0); }
			
			
		}
	}
	
	fclose(sfile);
	return 0;
}
