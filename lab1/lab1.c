/*!
 * @file
 *
 * @brief ECE477 Spring 2018 Lab 1 main file
 *
 * @author Mason Roach
 * @author Patrick Roy
 *
 * @date Feb 4, 2018
 *
 * This program will print "Hello World!"
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*!
 * @brief A short program to write "Hello World!" to the output terminal. If more arguments are used, will print a pyramid of a given string. Usage: "./lab1 [pyramid size] [pyramid string]" or "./lab1 [pyramid size]"
 *
 * @returns	Returns 0 on success, 1 on fail.
 */
int main(int argc, char *argv[]) {
	char* output = "Hello World!";
	int pyramidSize = 0;
	char* pyramidString;
	int i, j, k;
	
	if (argc == 1 && printf("%s\n", output) != strlen(output) + 1) {	// Print and then check if somehow something went wrong
		printf("ERROR: printf didn't print enough characters. Should have printed %lu characters.", strlen(output));
	}

	//If more arguments are present, print pyramid
	if (argc == 2 || argc == 3) { //If valid number of arguments
		if (argc == 3) { //If string argument is present
			pyramidString = argv[2];
		} else {
			pyramidString = output;
		}
		pyramidSize = atoi(argv[1]); //Second input argument is pyramid size
		if (pyramidSize < 1000){
			for (i = 0; i < pyramidSize; i++){ //for each row
				for (j = 0; j < (pyramidSize - i - 1); j++) { //print spaces before text
					for (k = 0; k < strlen(pyramidString); k++) { //print spaces of length of string
						printf(" ");
					}
					printf(" "); //print separating space
				}
				for (j = 0; j < (2 * i + 1); j++) { //print text and newline
					printf("%s ", pyramidString);
				}
				printf("\n");
			}
		} else {
			printf("Error! Pyramid size too large.\n");
		}
	}

	return 0;
} // End main
