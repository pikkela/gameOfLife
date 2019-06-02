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
 * 1.  NAME Simon Hiltunen
 *     $Source$
 * 2.  DESCRIPTION Elämän peli
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
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>
#include <ncurses.h>
#include "Header.h"
/*********************************************************************
;	F U N C T I O N    D E S C R I P T I O N
;---------------------------------------------------------------------;
/**
\fn print_new_board();
\brief tulostaa uuden pelilaudan;
\param struct cell board[][];
*/
/*
Output:;
Used global variables:;
REMARKS when using this function:;

********************************************************************/
void print_new_board(struct cell  board[Y][X])
{
	int row, col;


	WINDOW * win = newwin(4, 27, 1, 1);
	refresh();
	box(win, '*', '*');

	getmaxyx(stdscr, row, col);

	int rowm = row / 2 - (Y / 2);
	int colm = col / 2 - (X / 2);



	move(rowm, colm - 2);

	for (int i = 0; i < Y; i++) {

		move(rowm + i, colm - 2);

		for (int j = 0; j < X; j++) {

			/**********COLORS*********************/
			board[i][j].current = board[i][j].future;

			if (board[i][j].land == MUD) {

				attron(COLOR_PAIR(1));

			}

			else if (board[i][j].land == HOLE) {

				attron(COLOR_PAIR(2));

			}
			else{

				attron(COLOR_PAIR(3));

			}
			/****************************************/
			if (board[i][j].current == 0) {

				printw(". ");

			}
			if(board[i][j].current == 1 || board[i][j].current == IN_MUD_W) {

				attron(COLOR_PAIR(4));
				printw("%d ", board[i][j].current);

			}
			if (board[i][j].current == 2 || board[i][j].current == IN_MUD_Y) {

				attron(COLOR_PAIR(5));
				printw("%d ", board[i][j].current);

			}

			attroff(COLOR_PAIR(1));
			attroff(COLOR_PAIR(2));
			attroff(COLOR_PAIR(3));
			attroff(COLOR_PAIR(4));
			attroff(COLOR_PAIR(5));

		}

		printw("\n");
	}
	mvwprintw(win, 1, 1, "press any key to stop...");

	wrefresh(win);
	refresh();
	Sleep(TIME);
	clear();
}
