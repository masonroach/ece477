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

#ifndef ECE477_FILEINFO_H
#define ECE477_FILEINFO_H

/*!
 * @brief A program to read information from the /proc directory and write to a delimited file to be read by Matlab
 *
 * @returns	Returns 0 on success, 1 on fail.
 */
int readProc();

/*!
 * @brief A short code block that will move the file pointer to the end of the file and return the number
 *	of lines passed through
 * @returns	Number of lines passed through
 */
unsigned int findEnd(FILE **f);

#endif
