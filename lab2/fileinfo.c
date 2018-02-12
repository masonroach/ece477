/*!
 * @file
 *
 * @brief ECE477 Spring 2018 Lab 2 header file
 *
 * @author Mason Roach
 * @author Patrick Roy
 *
 * @date Feb 12, 2018
 *
 * Header file for the functions needed to read file info in lab 2.
 */

#include <stdio.h>

/*!
 * @brief Moves character file pointer to the end of the file
 *
 * @returns	Returns number of passed through, usually number of lines in the file
 */
unsigned int findEnd(FILE **f) {
	char c;
	unsigned int lines = 0;

	for (c = fgetc(*f); c != (unsigned char)EOF; c = fgetc(*f)) {
		if (c == '\n') {
			lines++;
		}
	}

	return lines;
}
