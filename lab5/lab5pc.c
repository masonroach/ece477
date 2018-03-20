#include <stdio.h>
#include <stdlib.h>

#define FILENAME "/dev/ACM0"

int main(int argc, char **argv)
{
	// This program will read and write serial 
	// to talk to atmega88 to play high/low game
	FILE* sfile;
	int c;

	// Open device file and error check
	sfile = fopen(FILENAME, "r+");
	if (sfile == NULL) {
		printf("ERROR: Unable to open device file\n");
		exit(0);
	}

	
	while (1) {
		// Game start character
		fputc('S', sfile);
		
		// Read start of game text
		while ((c == getc(sfile)) != EOF) printf(sfile);
		
	}
	
	fclose(sfile);
	return 0;
}
