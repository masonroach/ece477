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

/*!
 * @brief A short program to write "Hello World!" to the output terminal.
 *
 * @returns	Returns 0 on success, 1 on fail.
 */
int main(int argc, char *argv[]) {
	char* output = "Hello World!\n";
	
	if (printf("%s", output) != strlen(output)) {	// Print and then check if somehow something went wrong
		printf("ERROR: printf didn't print enough characters. Should have printed %lu characters.", strlen(output));
	}

	return 0;
} // End main
