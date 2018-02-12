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

#ifndef ECE477_FILEINFO_H
#define ECE477_FILEINFO_H

/*!
 * @brief A program to read information from the /proc directory and write to a delimited file to be read by Matlab
 *
 * @returns	Returns 0 on success, 1 on fail.
 */
unsigned int findEnd(FILE **f);

#endif
