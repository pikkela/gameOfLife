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
\fn read_states();
\brief lataa vanhan pelin;
\param stream, struct cell board[][];

*/
/*Output:;
Used global variables:;
REMARKS when using this function:;
*********************************************************************/

void read_states(FILE * stream, struct cell  board[Y][X])
{
	char state;

	for (int i = 0; i < Y; i++) {
		for (int j = 0; j < X; j++) {

			state = fgetc(stream);

			if (state == '1') {

				board[i][j].current = 1;
				board[i][j].future = 1;

			}
			if (state == '2') {

				board[i][j].current = 2;
				board[i][j].future = 2;

			}
			if (state == '0') {

				board[i][j].current = 0;
				board[i][j].future = 0;

			}
		}
	}
	fclose(stream);
}
