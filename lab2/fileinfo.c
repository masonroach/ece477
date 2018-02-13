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
#include <stdlib.h>
#include <string.h>

#include "fileinfo.h"

/*!
 * @brief A program to read information from the /proc directory and write to a delimited file to be read by Matlab
 *
 * @returns	Returns 0 on success, 1 on fail.
 */
int readProc(void) {
	FILE *proc_meminfo, *proc_loadavg, *database;
	char *strAppend;
	unsigned long int memFree;
	double loadavg1, loadavg5, loadavg15;
	unsigned int procRunning, procTotal, charPrinted;
	unsigned long int index = 1;
	int result = 0;		// Default 0 to assume success

	// Allocate memory for strings
	strAppend = (char *)malloc(sizeof(char)*256);

	// Error handling malloc
	if (strAppend == NULL) {
		printf("ERROR: cannot allocate enough memory\n");
		result = 1;	// Set error flag
		goto quit;	// ABORT MISSION
	}
	
	// Open the virtual files as read-only
	proc_meminfo = fopen("/proc/meminfo", "r");
	proc_loadavg = fopen("/proc/loadavg", "r");
	database = fopen("./database.csv", "r+");
	
	// Error handling file openning
	if (proc_meminfo == NULL || proc_loadavg == NULL || database == NULL) {
		printf("ERROR: Cannot open one or more files file\n");
		result = 1;	// Set error flag
		goto quit;	// ABORT MISSION
	}

	// Scan the files for appropriate info
	fscanf(proc_meminfo, "%*s %*d %*s %*s %lu %*s", &memFree);
	fscanf(proc_loadavg, "%lf %lf %lf %u/%u", &loadavg1, &loadavg5, &loadavg15, &procRunning, &procTotal);

	// Move to the end of the file and get number of lines in the file
	index = findEnd(&database);

	// Create a string to append to the csv file then write to the file
	sprintf(strAppend, "%lu,\t%lu,\t%.2lf,\t%.2lf,\t%.2lf,\t%u,\t%u\n", index, memFree, loadavg1, loadavg5, loadavg15, procRunning, procTotal);
	charPrinted = fwrite(strAppend, sizeof(*strAppend), strlen(strAppend), database);
	
	// Error handling writing to the data file
	if (charPrinted != strlen(strAppend)) {
		printf("ERROR: not enough characters printed to the data file.\n%u characters printed, %d expected", charPrinted, (int)strlen(strAppend));
		result = 1;
		goto quit;
	}

quit:
	// Free the allocated memory to prevent memory leaks
	free(strAppend);

	// Close files
	fclose(proc_meminfo);
	fclose(proc_loadavg);
	fclose(database);

	return result;
} // End readProc

/*!
 * @brief Moves character file pointer to the end of the file
 *
 * @returns	Returns number of passed through, usually number of lines in the file
 */
unsigned int findEnd(FILE **f) {
	signed char c;		// Needs to be signed. Does not work on RPi if not
	unsigned int lines = 0;

	for (c = fgetc(*f); c != EOF; c = fgetc(*f)) {
		if (c == '\n') {
			lines++;
		}
	}

	return lines;
} // End findEnd
