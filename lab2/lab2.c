/*!
 * @file
 *
 * @brief ECE477 Spring 2018 Lab 2 main file
 *
 * @author Mason Roach
 * @author Patrick Roy
 *
 * @date Feb 12, 2018
 *
 * This program will use the SIGALARM signal to read 7 columns of data from /proc files
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>

#include "fileinfo.h"

volatile sig_atomic_t flag;


int getData(void);
void alarmHandler(int sig);

/*!
 * @brief A program to set a flag to indicate the SIGALRM has been detected
 *
 * @returns	Returns 0 on success, 1 on fail.
 */
void alarmHandler(int sig)
{
	flag = true;
}


/*!
 * @brief A program to setup to read information from the /proc directory using SIGALRM
 *
 * @returns	Returns 0 on success, 1 on fail.
 */
int main(int argc, char *argv[]) 
{
	FILE *database;
	char *headerText = "Index,\tFree Memory (kB),\tLoad Avg (1 min),\tLoad Avg (5 min),\tLoad Avg (15 min),\tRunning Processes,\tTotal Processes,\tTimestamp\n";
	unsigned int charPrinted;
	flag = false;	

	// Set up signal handler for SIGALARM
	signal(SIGALRM, alarmHandler);
	
	// Open file for writing, overwriting previous one if it exists
	database = fopen("./database.csv", "w");
	if (database == NULL) {
		printf("ERROR: cannot open file 'database.csv' for writing\n");
	}
	
	// Write header for csv file
	charPrinted = fwrite(headerText, sizeof(*headerText), strlen(headerText), database);

	// Error handling writing to the data file
	if (charPrinted != strlen(headerText)) {
		printf("ERROR: not enough characters printed to the data file.\n%u characters printed, %d expected", charPrinted, (unsigned int)strlen(headerText));
		fclose(database);
		return 1;
	}

	// Close file
	fclose(database);	

	// Set timer to 10 seconds
	alarm(10);
	
	while(1){
		if (flag) {
			if (getData()) {
				printf("ERROR: could not get data from /proc\n");
				return 1;
			} else {
				// On success, reset flag and alarm
				printf("Data collected successfully!\n");
				flag = false;
				alarm(10);
			}
		}
	}
	
	return 0;
}



/*!
 * @brief A program to read information from the /proc directory and write to a delimited file to be read by Matlab
 *
 * @returns	Returns 0 on success, 1 on fail.
 */
int getData(void)
{
	FILE *proc_meminfo, *proc_loadavg, *database;
	char *strAppend, *timeString;
	unsigned long int memFree;
	double loadavg1, loadavg5, loadavg15;
	unsigned int procRunning, procTotal, charPrinted;
	static unsigned int index = 1;
	time_t currentTime;
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
	database = fopen("./database.csv", "a");
	
	// Error handling file openning
	if (proc_meminfo == NULL || proc_loadavg == NULL || database == NULL) {
		printf("ERROR: Cannot open one or more files file\n");
		result = 1;	// Set error flag
		goto quit;	// ABORT MISSION
	}

	// Scan the files for appropriate info
	fscanf(proc_meminfo, "%*s %*d %*s %*s %lu %*s", &memFree);
	fscanf(proc_loadavg, "%lf %lf %lf %u/%u", &loadavg1, &loadavg5, &loadavg15, &procRunning, &procTotal);

	// Get current time
	currentTime = time(NULL);
	timeString = ctime(&currentTime);
	// Move to the end of the file and get number of lines in the file
	//index = findEnd(&database);

	// Create a string to append to the csv file then write to the file
	sprintf(strAppend, "%u,\t%lu,\t%.2lf,\t%.2lf,\t%.2lf,\t%u,\t%u,\t%s\n", index, memFree, loadavg1, loadavg5, loadavg15, procRunning, procTotal, timeString);
	charPrinted = fwrite(strAppend, sizeof(*strAppend), strlen(strAppend), database);

	// Error handling writing to the data file
	if (charPrinted != strlen(strAppend)) {
		printf("ERROR: not enough characters printed to the data file.\n%u characters printed, %d expected", charPrinted, (unsigned int)strlen(strAppend));
		result = 1;
		goto quit;
	}

	// Increment the index value
	index++;

quit:
	// Free the allocated memory to prevent memory leaks
	free(strAppend);

	// Close files
	fclose(proc_meminfo);
	fclose(proc_loadavg);
	fclose(database);

	return result;
} // End main
