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
\fn print_first_board();
\brief tulostaa ensimmäisen laudan;
\param struct cell board[][];
*/
/*
Output:;
Used global variables:;
REMARKS when using this function:;
*********************************************************************/
void print_first_board(struct cell  board[Y][X])
{
	int row, col;
	getmaxyx(stdscr, row, col);
	int rowm = row / 2 - (Y / 2);
	int colm = col / 2 - (X / 2);
	move(rowm, colm - 2);

	for (int i = 0; i < Y; i++) {/*tulostaa ekan siviilisaation*/
		move(rowm + i, colm - 2);
		for (int j = 0; j < X; j++) {
			if (board[i][j].land == MUD) {
				attron(COLOR_PAIR(1));
			}

			else if (board[i][j].land == HOLE) {
				attron(COLOR_PAIR(2));
			}
			else
			{
				attron(COLOR_PAIR(3));
			}
			if (board[i][j].current == 0) {
				printw(". ");
			}
			else {
				if (board[i][j].current == 1) {
					attron(COLOR_PAIR(4));
				}
				if (board[i][j].current == 2) {
					attron(COLOR_PAIR(5));
				}
				printw("%d ", board[i][j].current);
			}
			attroff(COLOR_PAIR(2));
			attroff(COLOR_PAIR(1));
			attroff(COLOR_PAIR(3));
			attroff(COLOR_PAIR(4));
			attroff(COLOR_PAIR(5));

		}
		printw("\n");

	}
	refresh();

	Sleep(1000);
	clear();
}
