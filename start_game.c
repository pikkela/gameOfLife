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
\fn start_game();
\brief päävalikko;
\param struct cell board[][];
*/
/*
Output:;
Used global variables:;
REMARKS when using this function:;
*********************************************************************/
void start_game(struct cell  board[Y][X])
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

	FILE *stream = fopen(FILE_LIVES, "r");
	FILE *stream_land = fopen(FILE_LAND, "r");

	switch (start) {
	case 1:

		zero_the_boards(board);
		first_board(board);

		break;
	case 2:

		if (stream) {

			read_land_states(stream_land, board);
			read_states(stream, board);

		}
		else if (stream == NULL) {

			mvwprintw(win, 1, 1, " file not found starting a new game!!!");
			wrefresh(win);
			Sleep(TIME);

			zero_the_boards(board);
			first_board(board);

		}
		break;
	default:
		break;
	}
}
