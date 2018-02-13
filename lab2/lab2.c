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

#define SAMPLE_RATE 60

#include <unistd.h>
#include <signal.h>

#include "fileinfo.h"

/*!
 * @brief Handler for the alarm for the readProc call
 */
void alrm_handler() {
	readProc();	// Call the function to add to the file
	signal(SIGALRM, alrm_handler);	// Set a new signal alarm
	if (alarm(SAMPLE_RATE)) printf("WARNING: Cancelled an alarm early\n");	// Set a new alarm
} // End alarm handler

/*!
 * @brief Program will initialize an alarm for reading the /proc information
 *
 * @returns	Returns 0 on success, 1 on fail.
 */
int main(int argc, char *argv[]) {
	signal(SIGALRM, alrm_handler);	// Set a new interupt for when the alarm goes off
	alarm(SAMPLE_RATE);		// Set the alarm

	while (1) pause();		// Pause will simply wait until it recieves a signal

	return 0;
} // End main

