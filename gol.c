/***************************************************************************
 *   Copyright (C) $YEAR$ by $AUTHOR$   *
 *   $EMAIL$   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

 /*********************************************************************
 *
 * 1.  NAME
 *     $Source$
 * 2.  DESCRIPTION
 *
 * 6.  VERSIONS
 *       Original:
 *         $Date$ / $Author$
 *
 *       Version history:
 *       $Log$
 *
 **********************************************************************/

 /*-------------------------------------------------------------------*
 *    HEADER FILES                                                    *
 *--------------------------------------------------------------------*/
#include<stdio.h>
#include <time.h>
#include <stdlib.h>
#include<Windows.h>
#include<ncurses.h>

 /*-------------------------------------------------------------------*
 *    GLOBAL VARIABLES                                                *
 *--------------------------------------------------------------------*/
 /* Control flags */
#define DEBUG

/* Globaal constants */
#define I 30
#define J 30
#define FILE_NAME "life.txt"
/* Globaal variables */

/* Globaal structures */
struct cell
{
	int current;
	int future;
};
/*-------------------------------------------------------------------*
*    FUNCTION PROTOTYPES                                             *
*--------------------------------------------------------------------*/
void zero_the_boards(struct cell board[I][J]);
void first_board(struct cell  board[I][J]);
void print_first_board(struct cell  board[I][J]);
void check_rules_and_put_to_place(struct cell  board[I][J]);
void print_new_board(struct cell  board[I][J]);
void read_states(FILE * stream, struct cell  board[I][J]);
void create_box();
void start_game(struct cell  board[I][J]);
void save_file(struct cell  board[I][J]);
/*********************************************************************
*    MAIN PROGRAM                                                      *
**********************************************************************/
void main(void) {

	struct cell board[I][J];

	int row, col;

	initscr();

	/*WINDOW * win = newwin(I, J, 1, 20);
	refresh();
	box(win, 0, 0);
	wrefresh(win);*/
	
	start_game(board);
	
	print_first_board(board);

	nodelay(stdscr, TRUE);
	while (getch() == ERR) {
		
		check_rules_and_put_to_place(board);
		print_new_board(board);
		
	}

	endwin();

	/*tulostaa siviilisaation tekstitiedostoon*/

	save_file(board);
	
} /* end of main */




/*********************************************************************
*    FUNCTIONS                                                     *
**********************************************************************/

/*********************************************************************
;	F U N C T I O N    D E S C R I P T I O N
;---------------------------------------------------------------------
; NAME:save_file()
; DESCRIPTION: tallentaa pelin
;	Input: struct cell board[][]
;	Output:
;  Used global variables:
; REMARKS when using this function:
;*********************************************************************/
void save_file(struct cell  board[I][J])
{
	FILE *file_ptr = fopen(FILE_NAME, "w");
	for (int i = 0; i < I; i++) {
		for (int j = 0; j < J; j++) {
			fprintf(file_ptr, "%d", board[i][j].current);
		}
	}
	fclose(file_ptr);
}
/*********************************************************************
;	F U N C T I O N    D E S C R I P T I O N
;---------------------------------------------------------------------
; NAME:start_game()
; DESCRIPTION: päävalikko
;	Input: struct cell board[][]
;	Output:
;  Used global variables:
; REMARKS when using this function:
;*********************************************************************/
void start_game(struct cell  board[I][J])
{

	WINDOW * win = newwin(4, 27, 1, 20);
	refresh();
	box(win, '*', '*');

	int start;
	mvwprintw(win, 1, 1, "  press 1 for new game.");
	mvwprintw(win, 2, 1, "  press 2 to load game.");
	wrefresh(win);
	refresh();
	scanf("%d", &start);
	FILE *stream = fopen(FILE_NAME, "r");

	switch (start) {
	case 1:
		zero_the_boards(board);
		first_board(board);
		break;
	case 2:

		if (stream) {

			read_states(stream, board);

		}
		else if (stream == NULL) {
			mvwprintw(win, 1, 1, " file not found starting a new game!!!");
			wrefresh(win);
			Sleep(5000);
			zero_the_boards(board);
			first_board(board);
		}
		break;
	default:
		break;
	}
}

/*********************************************************************
;	F U N C T I O N    D E S C R I P T I O N
;---------------------------------------------------------------------
; NAME:read_states()
; DESCRIPTION: lataa vanhan pelin
;	Input:stream, struct cell board[][]
;	Output:
;  Used global variables:
; REMARKS when using this function:
;*********************************************************************/

void read_states(FILE * stream, struct cell  board[I][J])
{
	char state;

	for (int i = 0; i < J; i++) {
		for (int j = 0; j < I; j++) {

			state = fgetc(stream);

			if (state == '1') {
				board[i][j].current = 1;
				board[i][j].future = 1;
			}
			if (state == '2') {
				board[i][j].current = 2;
				board[i][j].future = 2;
			}
			else if (state == '0') {
				board[i][j].current = 0;
				board[i][j].future = 0;
			}
		}
	}
	fclose(stream);
}
/*********************************************************************
;	F U N C T I O N    D E S C R I P T I O N
;---------------------------------------------------------------------
; NAME:print_new_board()
; DESCRIPTION: tulostaa uuden pelilaudan
;	Input: struct cell board[][]
;	Output:
;  Used global variables:
; REMARKS when using this function:
;*********************************************************************/
void print_new_board(struct cell  board[I][J])
{
	int row, col;
	WINDOW * win = newwin(4, 27, 1, 1);
	refresh();
	box(win, '*', '*');


	getmaxyx(stdscr, row, col);
	int rowm = row / 2 - (I / 2);
	int colm = col / 2 - (J / 2);

	move(rowm, colm - 2);

	for (int i = 0; i < I; i++) {

		move(rowm + i, colm - 2);

		for (int j = 0; j < J; j++) {

			board[i][j].current = board[i][j].future;
			if (board[i][j].current == 0) {
				printw(". ");
			}
			else {
				printw("%d ", board[i][j].current);
			}
		}

		printw("\n");
	}
	mvwprintw(win, 1, 1, "press any key to stop...");


	wrefresh(win);
	refresh();
	Sleep(1000);
	clear();
}
/*********************************************************************
;	F U N C T I O N    D E S C R I P T I O N
;---------------------------------------------------------------------
; NAME:check_rules_and_put_to_place()
; DESCRIPTION: tarkistaa solut ja laskee uusien paikat
;	Input: struct cell board[][]
;	Output:
;  Used global variables:
; REMARKS when using this function:
;*********************************************************************/

/*vertailee populaatio ykkösen*/
void check_rules_and_put_to_place(struct cell  board[I][J])
{
	int count = 0;
	int count2 = 0;
	for (int i = 0; i < I; i++) {
		for (int j = 0; j < J; j++) {

			if (board[i][j].current == 1|| board[i][j].current == 2) {
				if (j != J - 1) {
					if (board[i][j + 1].current == 1) count++;
					else if (board[i][j + 1].current == 2) count2++;
				}
				if (j != 0) {
					if (board[i][j - 1].current == 1) count++;
					else if (board[i][j - 1].current == 2) count2++;
				}
				if (i != 0) {
					if (board[i - 1][j].current == 1) count++;
					else if (board[i - 1][j].current == 2) count2++;

					if (j != 0 && board[i - 1][j - 1].current == 1) count++;
					else if (j != 0 && board[i - 1][j - 1].current == 2) count2++;

					if (j != J - 1 && board[i - 1][j + 1].current == 1) count++;
					else if (j != J - 1 && board[i - 1][j + 1].current == 2) count2++;
				}
				if (i != I - 1) {
					if (board[i + 1][j].current == 1) count++;
					else if (board[i + 1][j].current == 2) count2++;

					if (j != 0 && board[i + 1][j - 1].current == 1) count++;
					else if (j != 0 && board[i + 1][j - 1].current == 2) count2++;

					if (j != J - 1 && board[i + 1][j + 1].current == 1) count++;
					else if (j != J - 1 && board[i + 1][j + 1].current == 2) count2++;
				}
				if (board[i][j].current == 1) {
					if (count == 1 || count == 0 || count >= 4) {
						board[i][j].future = 0;
					}
					if (count == 2 || count == 3) {
						board[i][j].future = 1;
					}
					if (count2 > count) {
						board[i][j].future = 2;
					}
				}
				if (board[i][j].current == 2) {
					if (count2 == 1 || count2 == 0 || count2 >= 4) {
						board[i][j].future = 0;
					}
					if (count2 == 2 || count2 == 3) {
						board[i][j].future = 2;
					}
					if (count > count2) {
						board[i][j].future = 1;
					}
				}
				count = 0;
				count2 = 0;
			}
			else if (board[i][j].current == 0) {
				if (j != J - 1) {
					if (board[i][j + 1].current == 1) count++;
					else if (board[i][j + 1].current == 2) count2++;
				}
				if (j != 0) {
					if (board[i][j - 1].current == 1) count++;
					else if (board[i][j - 1].current == 2) count2++;
				}
				if (i != 0) {
					if (board[i - 1][j].current == 1) count++;
					else if (board[i - 1][j].current == 2) count2++;

					if (j != 0 && board[i - 1][j - 1].current == 1) count++;
					else if (j != 0 && board[i - 1][j - 1].current == 2) count2++;

					if (j != J - 1 && board[i - 1][j + 1].current == 1) count++;
					else if (j != J - 1 && board[i - 1][j + 1].current == 2) count2++;
				}
				if (i != I - 1) {
					if (board[i + 1][j].current == 1) count++;
					else if (board[i + 1][j].current == 2) count2++;

					if (j != 0 && board[i + 1][j - 1].current == 1) count++;
					else if (j != 0 && board[i + 1][j - 1].current == 2) count2++;

					if (j != J - 1 && board[i + 1][j + 1].current == 1) count++;
					else if (j != J - 1 && board[i + 1][j + 1].current == 2) count2++;
				}

				if (count == 3) {
					board[i][j].future = 1;
				}
				else if (count2 == 3) {
					board[i][j].future = 2;
				}
				count = 0;
				count2 = 0;
			}
		}
	}
	/********************************************/
	/*vertailee populaatio kakkosen*/
/*	for (int i = 0; i < I; i++) {
		for (int j = 0; j < J; j++) {

			if (board[i][j].current == 2) {
				if (j != J - 1) {
					if (board[i][j + 1].current == 2) count++;
				}
				if (j != 0) {
					if (board[i][j - 1].current == 2) count++;
				}
				if (i != 0) {
					if (board[i - 1][j].current == 2) count++;
					if (j != 0 && board[i - 1][j - 1].current == 2) count++;
					if (j != J - 1 && board[i - 1][j + 1].current == 2) count++;
				}
				if (i != I - 1) {
					if (board[i + 1][j].current == 2) count++;
					if (j != 0 && board[i + 1][j - 1].current == 2) count++;
					if (j != J - 1 && board[i + 1][j + 1].current == 2) count++;
				}

				if (count == 1 || count == 0 || count >= 4) {
					board[i][j].future = 0;
				}
				if (count == 2 || count == 3) {
					board[i][j].future = 2;
				}
				count = 0;
			}
			else if (board[i][j].current == 0) {
				if (j != J - 1) {
					if (board[i][j + 1].current == 2) count++;
				}
				if (j != 0) {
					if (board[i][j - 1].current == 2) count++;
				}
				if (i != 0) {
					if (board[i - 1][j].current == 2) count++;
					if (j != 0 && board[i - 1][j - 1].current == 2) count++;
					if (j != J - 1 && board[i - 1][j + 1].current == 2) count++;
				}
				if (i != I - 1) {
					if (board[i + 1][j].current == 2) count++;
					if (j != 0 && board[i + 1][j - 1].current == 2) count++;
					if (j != J - 1 && board[i + 1][j + 1].current == 2) count++;
				}

				if (count == 3) {
					board[i][j].future = 2;
				}
				count = 0;
			}
		}
	}*/
}
/*********************************************************************
;	F U N C T I O N    D E S C R I P T I O N
;---------------------------------------------------------------------
; NAME:print_first_board()
; DESCRIPTION: tulostaa ensimmäisen laudan
;	Input: struct cell board[][]
;	Output:
;  Used global variables:
; REMARKS when using this function:
;*********************************************************************/
void print_first_board(struct cell  board[I][J])
{
	int row, col;
	getmaxyx(stdscr, row, col);
	int rowm = row / 2 - (I / 2);
	int colm = col / 2 - (J / 2);
	move(rowm, colm - 2);

	for (int i = 0; i < I; i++) {/*tulostaa ekan siviilisaation*/
		move(rowm + i, colm - 2);
		for (int j = 0; j < J; j++) {
			if (board[i][j].current == 0) {
				printw(". ");
			}
			else {
				printw("%d ", board[i][j].current);
			}
		}
		printw("\n");

	}
	refresh();

	Sleep(1000);
	clear();
}
/*********************************************************************
;	F U N C T I O N    D E S C R I P T I O N
;---------------------------------------------------------------------
; NAME:zero_the_boards()
; DESCRIPTION: nollaa structit
;	Input: struct cell board[][]
;	Output:
;  Used global variables:
; REMARKS when using this function:
;*********************************************************************/

void zero_the_boards(struct cell board[I][J])
{

	for (int i = 0; i < I; i++) {		/*nollaa current ja future*/
		for (int j = 0; j < J; j++) {
			board[i][j].current = 0;
			board[i][j].future = 0;
		}
	}
}
/*********************************************************************
;	F U N C T I O N    D E S C R I P T I O N
;---------------------------------------------------------------------
; NAME:first_board()
; DESCRIPTION: luo ensimmäisen pelilaudan
;	Input: struct cell board[][]
;	Output:
;  Used global variables:
; REMARKS when using this function:
;*********************************************************************/
void first_board(struct cell  board[I][J])
{
	int ran;
	int first = J / 2;
	srand(time(0));			/*luodaan eka siviilisaatio*/
	for (int i = 0; i < I; i++) {
		for (int j = 0; j < J; j++) {
			int ran = rand() % 15;
			if (ran <= 8 && j <= first) {
				if (j > first-3) {
					board[i][j - 3].current = 1;
				}
				else { board[i][j].current = 1; }
			}
			if (ran <= 8 && j >= first) {
				if (j < first+3) {
					board[i][j + 3].current = 2;
				}
				else { 
					board[i][j].current = 2; 
				}
			}
		}
	}
}