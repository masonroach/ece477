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


int printBoard(char *board, int xwins, int owins, int ties)
{
	FILE *html;
	unsigned int charPrinted;
	// String to begin file and open tags, set board up, auto reload page every 10 seconds
	const char *beginString= "<!DOCTYPE html>\n<html>\n<head>\n<meta http-equiv=\"Refresh\" content=\"5\">\n</head>\n<body>\n<h1>TIC-TAC-TOE</h1>\n";
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
	sprintf(boardString, "<h4>X Wins: %d, O Wins: %d, Ties: %d</h4><table border = \"2\">\n<tr>\n<td>%c</td><td>%c</td><td>%c</td>\n</tr>\n<tr>\n<td>%c</td><td>%c</td><td>%c</td>\n</tr>\n<tr>\n<td>%c</td><td>%c</td><td>%c</td>\n</tr>\n</table>", xwins, owins, ties, board[0], board[1], board[2], board[3], board[4], board[5], board[6], board[7], board[8]);

	
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
 * @brief Function will check the win conditions of the board and return a value
 * indicating if someone has won and who that is
 *
 * @returns	Returns 0 on no win, 1 on player win, 2 on computer win.
 */
int checkWin(char *board)
{
	// Check computer win conditions
	if ((board[0] == 'O' && board[1] == 'O' && board[2] == 'O') ||
	(board[3] == 'O' && board[4] == 'O' && board[5] == 'O') ||
	(board[6] == 'O' && board[7] == 'O' && board[8] == 'O') ||
	(board[0] == 'O' && board[3] == 'O' && board[6] == 'O') ||
	(board[1] == 'O' && board[4] == 'O' && board[7] == 'O') ||
	(board[2] == 'O' && board[5] == 'O' && board[8] == 'O') ||
	(board[0] == 'O' && board[4] == 'O' && board[8] == 'O') ||
	(board[2] == 'O' && board[4] == 'O' && board[6] == 'O')
	) {return 2;}
	
	// Check player win conditions
	if ((board[0] == 'X' && board[1] == 'X' && board[2] == 'X') ||
	(board[3] == 'X' && board[4] == 'X' && board[5] == 'X') ||
	(board[6] == 'X' && board[7] == 'X' && board[8] == 'X') ||
	(board[0] == 'X' && board[3] == 'X' && board[6] == 'X') ||
	(board[1] == 'X' && board[4] == 'X' && board[7] == 'X') ||
	(board[2] == 'X' && board[5] == 'X' && board[8] == 'X') ||
	(board[0] == 'X' && board[4] == 'X' && board[8] == 'X') ||
	(board[2] == 'X' && board[4] == 'X' && board[6] == 'X')
	) {return 1;}

	return 0;

}


/*!
 * @brief Function will check to see if a tie has occurred
 *
 *
 * @returns	Returns 0 on no tie, 1 on tie.
 */
int checkTie(char *board)
{
	if (	board[0] != '_' && 
		board[1] != '_' && 
		board[2] != '_' &&
		board[3] != '_' &&
		board[4] != '_' &&
		board[5] != '_' &&
		board[6] != '_' &&
		board[7] != '_' &&
		board[8] != '_'){ return 1; }
	return 0;
}


/*!
 * @brief Function will clear the game board after a game has concluded
 *
 *
 *
 */
void clearBoard(char *board)
{
	int i;
	for (i = 0; i < 9; i++) {
		board[i] = '_';
	}
}

/*!
 * @brief Function will request user input for either 'X' or 'O' and return index of array
 * where the user played
 *
 */
int playerMove(char xo, char *board)
{
	// Ask for user input until valid move is made
	int userMove = 0;
	do {
		printf("Player %c: Enter a valid move:\n-----------\n %c | %c | %c \n-----------\n %c | %c | %c \n-----------\n %c | %c | %c \n-----------\n", 
			xo,
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
	return userMove-1;
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
	char playAgain;
	int quit = 0, winner = 0, error, numPlayers, xwins = 0, owins = 0, ties = 0;
	
	error = printBoard(board, xwins, owins, ties);
	if (error) {
		printf("Exiting with error writing to html file.\n");
		quit = 1;
	}
	
	// Open chromium to display tictactoe game in background
	system("chromium-browser tictactoe.html &");

	// 1 or 2 players?
	printf("Enter number of \"human\" players: ");
	scanf("%d", &numPlayers);
	// If input is anythinng other than 2, there will be 1 player
	if (numPlayers != 2) numPlayers = 1;

	// Play the game, waiting for user to quit
	while (!quit) {
		// Print board
		error = printBoard(board, xwins, owins, ties);
		if (error) {
			printf("Exiting with error writing to html file.\n");
			break;
		}

		// Ask for user input
		board[playerMove('X', board)] = 'X';
	
		// Computer moves if player didn't win, handle win/tie cases at end of loop
		if (!checkWin(board) && !checkTie(board)) {
			if (numPlayers == 1) {
				// One player, 
				error = computerMove(board);
				if (error) {
					printf("Exiting with error making computer's move.\n");
					break;
				}
			} else {
				// Two players, give other player a chance to move
				board[playerMove('O', board)] = 'O';
				
			}
		}

		// Print board
		error = printBoard(board, xwins, owins, ties);
		if (error) {
			printf("Exiting with error writing to html file.\n");
			break;
		}
			
		// Check win condition
		winner = checkWin(board);
		if (winner) {
			printf("Player %c wins!\n", winner == 1?'X':'O');
			// Add winner's total to running tallies
			winner == 1 ? xwins++ : owins++;
			printf("X wins | O wins | Draws\n-----------------------\n   %d   |   %d    |   %d\n\nPlay again? (y/n) ", xwins, owins, ties);
			scanf(" %c", &playAgain);
			// If one player has won, offer user another chance to play
			if (playAgain != 'y' && playAgain != 'Y') {
				quit = 1;
			}
			clearBoard(board);
		// Check tie condition
		} else if (checkTie(board)) {
			printf("It's a draw!\n");
			ties++;
			printf("X wins | O wins | Draws\n-----------------------\n   %d   |   %d    |   %d\n\nPlay again? (y/n) ", xwins, owins, ties);
			scanf(" %c", &playAgain);
			// offer user another chance to play
			if (playAgain != 'y' && playAgain != 'Y') {
				quit = 1;
			}
			clearBoard(board);
		}
		

	}

	return 0;
}
