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
\fn read_land_states();
\brief lataa vanhan pelin maa alueet;
\param stream, struct cell board[][];

*/
/*Output:;
Used global variables:;
REMARKS when using this function:;
*********************************************************************/
void read_land_states(FILE * stream_land, struct cell(*board)[X])
{
	char land_state;
	for (int i = 0; i < Y; i++) {
		for (int j = 0; j < X; j++) {

			land_state = fgetc(stream_land);

			if (land_state == '3') {

				board[i][j].land = 3;

			}
			if (land_state == '4') {

				board[i][j].land = 4;

			}
			else if (land_state == '0') {

				board[i][j].land = 0;

			}
		}
	}
	fclose(stream_land);
}
