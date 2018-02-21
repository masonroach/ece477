/*!
 * @file
 *
 * @brief ECE477 Spring 2018 Lab 3 main file
 *
 * @author Mason Roach
 * @author Patrick Roy
 *
 * @date Feb 19, 2018
 *
 * This program will use the command line to play tic tac toe, creating an html output
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int printBoard(char *board)
{
	FILE *html;
	unsigned int charPrinted;
	// String to begin file and open tags, set board up, auto reload page every 10 seconds
	const char *beginString = "<!DOCTYPE html>\n<html>\n<head>\n<meta http-equiv=\"Refresh\" content=\"5\">\n</head>\n<body>\n<h1>TIC-TAC-TOE</h1>\n";
	// String to end file and close tags
	const char *endString = "</body>\n</html>";
	char *boardString;

	// Allocate memory for strings
        boardString = (char *)malloc(sizeof(char)*256);

        // Error handling malloc
        if (boardString == NULL) {
                printf("ERROR: cannot allocate enough memory for strings\n");
                return 1;
        }



	// Open file for writing and check for errors
	html = fopen("tictactoe.html", "w");
	if (html == NULL) {
		printf("ERROR: Cannot open html file for writing!\n");
		free(boardString);
		return 1;
	}
	
	// Write html header text and error check
	charPrinted = fwrite(beginString, sizeof(*beginString), strlen(beginString), html);
	if (charPrinted != strlen(beginString)) {
		printf("ERROR: Wrong number of characters written to file!\n");
		free(boardString);
		fclose(html);
		return 1;
	}

	// Set up board as a table to be written to html file
	sprintf(boardString, "<table border = \"2\">\n<tr>\n<td>%c</td><td>%c</td><td>%c</td>\n</tr>\n<tr>\n<td>%c</td><td>%c</td><td>%c</td>\n</tr>\n<tr>\n<td>%c</td><td>%c</td><td>%c</td>\n</tr>\n</table>", board[0], board[1], board[2], board[3], board[4], board[5], board[6], board[7], board[8]);

	
	// Write board to html and error check
	charPrinted = fwrite(boardString, sizeof(*boardString), strlen(boardString), html);
	if (charPrinted != strlen(boardString)) {
                printf("ERROR: Wrong number of characters written to file!\n");
		free(boardString);
		fclose(html);
                return 1;
        }


	// Write end html to file and error check
	charPrinted = fwrite(endString, sizeof(*endString), strlen(endString), html);
        if (charPrinted != strlen(endString)) {
                printf("ERROR: Wrong number of characters written to file!\n");
		free(boardString);
		fclose(html);
                return 1;
        }

	// Close file and return success
	fclose(html);


	return 0;
}


int computerMove(char *board)
{
	unsigned int comMove = -1;
	unsigned int r = -1;
	
	if (strlen(board) < 9) {
		printf("ERROR: invalid board string.\n");
		return 1;
	}
	srand(time(NULL));
	
	/*
	 * If computer can win, win
	 */
	// Row 1
	if (comMove == -1) {
		if (board[0] == 'O' && board[1] == 'O' && board[2] == '_') comMove = 2;
		if (board[0] == 'O' && board[1] == '_' && board[2] == 'O') comMove = 1;
		if (board[0] == '_' && board[1] == 'O' && board[2] == 'O') comMove = 0;
	}
	// Row 2
	if (comMove == -1) {
		if (board[3] == 'O' && board[4] == 'O' && board[5] == '_') comMove = 5;
		if (board[3] == 'O' && board[4] == '_' && board[5] == 'O') comMove = 4;
		if (board[3] == '_' && board[4] == 'O' && board[5] == 'O') comMove = 3;
 	}
	// Row 3
	if (comMove == -1) {
		if (board[6] == 'O' && board[7] == 'O' && board[8] == '_') comMove = 8;
		if (board[6] == 'O' && board[7] == '_' && board[8] == 'O') comMove = 7;
		if (board[6] == '_' && board[7] == 'O' && board[8] == 'O') comMove = 6;
 	}
	// Column 1
	if (comMove == -1) {
		if (board[0] == 'O' && board[3] == 'O' && board[6] == '_') comMove = 6;
		if (board[0] == 'O' && board[3] == '_' && board[6] == 'O') comMove = 3;
		if (board[0] == '_' && board[3] == 'O' && board[6] == 'O') comMove = 0;
	}
	// Column 2
	if (comMove == -1) {
		if (board[1] == 'O' && board[4] == 'O' && board[7] == '_') comMove = 7;
		if (board[1] == 'O' && board[4] == '_' && board[7] == 'O') comMove = 4;
		if (board[1] == '_' && board[4] == 'O' && board[7] == 'O') comMove = 1;
 	}
	// Column 3
	if (comMove == -1) {
		if (board[2] == 'O' && board[5] == 'O' && board[8] == '_') comMove = 8;
		if (board[2] == 'O' && board[5] == '_' && board[8] == 'O') comMove = 5;
		if (board[2] == '_' && board[5] == 'O' && board[8] == 'O') comMove = 2;
 	}
	// Diagonal 1
	if (comMove == -1) {
		if (board[0] == 'O' && board[4] == 'O' && board[8] == '_') comMove = 8;
		if (board[0] == 'O' && board[4] == '_' && board[8] == 'O') comMove = 4;
		if (board[0] == '_' && board[4] == 'O' && board[8] == 'O') comMove = 0;
 	}
	// Diagonal 2
	if (comMove == -1) {
		if (board[2] == 'O' && board[4] == 'O' && board[6] == '_') comMove = 6;
		if (board[2] == 'O' && board[4] == '_' && board[6] == 'O') comMove = 4;
		if (board[2] == '_' && board[4] == 'O' && board[6] == 'O') comMove = 2;
 	}


	/*
	 *  If player can win, block it
	 */	
	// Row 1
	if (comMove == -1) {
		if (board[0] == 'X' && board[1] == 'X' && board[2] == '_') comMove = 2;
		if (board[0] == 'X' && board[1] == '_' && board[2] == 'X') comMove = 1;
		if (board[0] == '_' && board[1] == 'X' && board[2] == 'X') comMove = 0;
	}
	// Row 2
	if (comMove == -1) {
		if (board[3] == 'X' && board[4] == 'X' && board[5] == '_') comMove = 5;
		if (board[3] == 'X' && board[4] == '_' && board[5] == 'X') comMove = 4;
		if (board[3] == '_' && board[4] == 'X' && board[5] == 'X') comMove = 3;
	}
	// Row 3
	if (comMove == -1) {
		if (board[6] == 'X' && board[7] == 'X' && board[8] == '_') comMove = 8;
		if (board[6] == 'X' && board[7] == '_' && board[8] == 'X') comMove = 7;
		if (board[6] == '_' && board[7] == 'X' && board[8] == 'X') comMove = 6;
	}
	// Column 1
	if (comMove == -1) {
		if (board[0] == 'X' && board[3] == 'X' && board[6] == '_') comMove = 6;
		if (board[0] == 'X' && board[3] == '_' && board[6] == 'X') comMove = 3;
		if (board[0] == '_' && board[3] == 'X' && board[6] == 'X') comMove = 0;
	}
	// Column 2
	if (comMove == -1) {
		if (board[1] == 'X' && board[4] == 'X' && board[7] == '_') comMove = 7;
		if (board[1] == 'X' && board[4] == '_' && board[7] == 'X') comMove = 4;
		if (board[1] == '_' && board[4] == 'X' && board[7] == 'X') comMove = 1;
	}
	// Column 3
	if (comMove == -1) {
		if (board[2] == 'X' && board[5] == 'X' && board[8] == '_') comMove = 8;
		if (board[2] == 'X' && board[5] == '_' && board[8] == 'X') comMove = 5;
		if (board[2] == '_' && board[5] == 'X' && board[8] == 'X') comMove = 2;
	}
	// Diagonal 1
	if (comMove == -1) {
		if (board[0] == 'X' && board[4] == 'X' && board[8] == '_') comMove = 8;
		if (board[0] == 'X' && board[4] == '_' && board[8] == 'X') comMove = 4;
		if (board[0] == '_' && board[4] == 'X' && board[8] == 'X') comMove = 0;
	}
	// Diagonal 2
	if (comMove == -1) {
		if (board[2] == 'X' && board[4] == 'X' && board[6] == '_') comMove = 6;
		if (board[2] == 'X' && board[4] == '_' && board[6] == 'X') comMove = 4;
		if (board[2] == '_' && board[4] == 'X' && board[6] == 'X') comMove = 2;
	}

	// Otherwise, pick first spot
	for (r = 0; r < 9 && comMove == -1; r++){
		if (board[r] == '_') {
			comMove = r;
			break;
		}
	}
	
	if (comMove == -1) {
		printf("ERROR: No available space for computer to play!\n");
		return 1;
	}
	
	board[comMove] = 'O';
	return 0;
}


/*!
 * @brief Program will play a tic-tac-toe game with user on the command line. The output
 * is the tictactoe.html file
 *
 * @returns	Returns 0 on success, 1 on fail.
 */
int main(int argc, char *argv[])
{
	char board[9] = "_________"; // Begin with blank board
	int quit = 0; // 
	int userMove;
	int error;

	// Play the game, waiting for user to quit
	while (!quit) {
		// Print board
		error = printBoard(board);
		if (error) {
			printf("Exiting with error writing to html file.\n");
			break;
		}

		// Ask for user input until valid move is made
		userMove = 0;
		do {
			printf("Enter a valid move:\n-----------\n %c | %c | %c \n-----------\n %c | %c | %c \n-----------\n %c | %c | %c \n-----------\n", 
board[0] == '_' ? '1' : board[0],
board[1] == '_' ? '2' : board[1],
board[2] == '_' ? '3' : board[2],
board[3] == '_' ? '4' : board[3],
board[4] == '_' ? '5' : board[4],
board[5] == '_' ? '6' : board[5],
board[6] == '_' ? '7' : board[6],
board[7] == '_' ? '8' : board[7],
board[8] == '_' ? '9' : board[8]);
			// Get user move
			scanf("%d", &userMove);

			// If move is valid but space is already taken, reset userMove
			if ((userMove < 10 && userMove > 0) && (board[userMove-1] != '_')) {
				userMove = 0;
				printf("Space already taken, please choose another.\n");
			}

		} while (userMove > 9 || userMove < 1);
		board[userMove-1] = 'X';
	
		// Computer moves
		error = computerMove(board);
		if (error) {
			printf("Exiting with error making computer's move.\n");
			break;
		}
			
		// Check win condition

		// If one player has won, offer user another chance to play
	}

	return 0;
}
