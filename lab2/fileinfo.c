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
#include <time.h>

#include "fileinfo.h"

/*!
 * @brief A program to read information from the /proc directory and write to a delimited file to be read by Matlab
 *
 * @returns	Returns 0 on success, 1 on fail.
 */
int readProc(void) {
	FILE *proc_meminfo, *proc_loadavg, *etc_hostname, *database;
	char *strAppend, *compName;
	unsigned long int memFree;
	double loadavg1, loadavg5, loadavg15;
	unsigned int procRunning, procTotal, charPrinted;
	unsigned long int index = 1;
	int result = 0;		// Default 0 to assume success
	
	time_t t = time(NULL);	// Code to get current time
	struct tm tm = *localtime(&t);

	// Allocate memory for strings
	strAppend = (char *)malloc(sizeof(char)*256);
	compName = (char *)malloc(sizeof(char)*32);

	// Error handling malloc
	if (strAppend == NULL || compName == NULL) {
		printf("ERROR: cannot allocate enough memory\n");
		result = 1;	// Set error flag
		goto quit;	// ABORT MISSION
	}
	
	// Open the virtual files as read-only
	proc_meminfo = fopen("/proc/meminfo", "r");
	proc_loadavg = fopen("/proc/loadavg", "r");
	etc_hostname = fopen("/etc/hostname", "r");
	database = fopen("./database.csv", "r+");
	
	// Error handling file openning
	if (proc_meminfo == NULL || proc_loadavg == NULL || etc_hostname == NULL || database == NULL) {
		printf("ERROR: Cannot open one or more files file\n");
		result = 1;	// Set error flag
		goto quit;	// ABORT MISSION
	}

	// Scan the files for appropriate info
	fscanf(proc_meminfo, "%*s %*d %*s %*s %lu %*s", &memFree);
	fscanf(proc_loadavg, "%lf %lf %lf %u/%u", &loadavg1, &loadavg5, &loadavg15, &procRunning, &procTotal);
	fscanf(etc_hostname, "%s", compName);

	// Move to the end of the file and get number of lines in the file
	index = findEnd(&database);

	// Create a string to append to the csv file then write to the file
	sprintf(strAppend, "%lu,\t%lu,\t%.2lf,\t%.2lf,\t%.2lf,\t%u,\t%u,\t%d-%d-%d %02d:%02d:%02d,\t%s\n", index, memFree, loadavg1, loadavg5, loadavg15, procRunning, procTotal, tm.tm_mon+1, tm.tm_mday, tm.tm_year+1900, tm.tm_hour, tm.tm_min, tm.tm_sec, compName);
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
	free(compName);

	// Close files
	fclose(proc_meminfo);
	fclose(proc_loadavg);
	fclose(etc_hostname);
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
