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
\fn check_rules_and_put_to_place();
\brief tarkistaa solut ja laskee uusien paikat;
\param struct cell board[][];
*/
/*
Output:;
Used global variables:;
REMARKS when using this function:;
*********************************************************************/

/*vertailee populaatiot*/
void check_rules_and_put_to_place(struct cell  board[Y][X])
{
	int count = 0;
	int count2 = 0;
	int mud_count = 0;
	for (int i = 0; i < Y; i++) {
		for (int j = 0; j < X; j++) {
			/********************LASKETAAN YMPÄRISTÖSSÄ OLEVAT ELÄVÄT SOLUT**************************************************/
			if (board[i][j].current == 1 || board[i][j].current == 2 || board[i][j].current == IN_MUD_W || board[i][j].current == IN_MUD_Y) {
				if (board[i][j].land == MUD && board[i][j].current != IN_MUD_W && board[i][j].current != IN_MUD_Y) mud_count++;/*Tarkastetaan onko solu mudassa*/

				if (j != X - 1) {

					if (board[i][j + 1].current == 1 || board[i][j + 1].current == IN_MUD_W) count++;
					else if (board[i][j + 1].current == 2 || board[i][j + 1].current == IN_MUD_Y) count2++;

				}
				if (j != 0) {

					if (board[i][j - 1].current == 1 || board[i][j - 1].current == IN_MUD_W) count++;
					else if (board[i][j - 1].current == 2 || board[i][j - 1].current == IN_MUD_Y) count2++;

				}
				if (i != 0) {

					if (board[i - 1][j].current == 1 || board[i - 1][j].current == IN_MUD_W) count++;
					else if (board[i - 1][j].current == 2 || board[i - 1][j].current == IN_MUD_Y) count2++;

					if (j != 0 && board[i - 1][j - 1].current == 1 || board[i - 1][j - 1].current == IN_MUD_W) count++;
					else if (j != 0 && board[i - 1][j - 1].current == 2 || board[i - 1][j - 1].current == IN_MUD_Y) count2++;

					if (j != X - 1 && board[i - 1][j + 1].current == 1 || board[i - 1][j + 1].current == IN_MUD_W) count++;
					else if (j != X - 1 && board[i - 1][j + 1].current == 2 || board[i - 1][j + 1].current == IN_MUD_Y) count2++;
				}
				if (i != Y - 1) {

					if (board[i + 1][j].current == 1 || board[i + 1][j].current == IN_MUD_W) count++;
					else if (board[i + 1][j].current == 2 || board[i + 1][j].current == IN_MUD_Y) count2++;

					if (j != 0 && board[i + 1][j - 1].current == 1 || board[i + 1][j - 1].current == IN_MUD_W) count++;
					else if (j != 0 && board[i + 1][j - 1].current == 2 || board[i + 1][j - 1].current == IN_MUD_Y) count2++;

					if (j != X - 1 && board[i + 1][j + 1].current == 1 || board[i + 1][j + 1].current == IN_MUD_W) count++;
					else if (j != X - 1 && board[i + 1][j + 1].current == 2 || board[i + 1][j + 1].current == IN_MUD_Y) count2++;

				}
				/*********************LAITETAAN UUDET SOLUT PAIKALLEEN****************************************************/

				if (board[i][j].land != HOLE && mud_count != 1 ) {/*tarkastetaan että solu ei ole reiässä eikä mudassa*/

					if (board[i][j].current == 1 || board[i][j].current == IN_MUD_W) {
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
					if (board[i][j].current == 2 || board[i][j].current == IN_MUD_Y) {
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
				}

				count = 0;
				count2 = 0;
				/**************************************/
			}
			if (board[i][j].land != HOLE && mud_count != 1 ) {

				 if (board[i][j].current == 0) {

					if (j != X - 1) {

						if (board[i][j + 1].current == 1 || board[i][j + 1].current == IN_MUD_W) count++;
						else if (board[i][j + 1].current == 2 || board[i][j + 1].current == IN_MUD_Y) count2++;

					}

					if (j != 0) {

						if (board[i][j - 1].current == 1 || board[i][j - 1].current == IN_MUD_W) count++;
						else if (board[i][j - 1].current == 2 || board[i][j - 1].current == IN_MUD_Y) count2++;

					}

					if (i != 0) {

						if (board[i - 1][j].current == 1 || board[i - 1][j].current == IN_MUD_W) count++;
						else if (board[i - 1][j].current == 2 || board[i - 1][j].current == IN_MUD_Y) count2++;

						if (j != 0 && board[i - 1][j - 1].current == 1 || board[i - 1][j - 1].current == IN_MUD_W) count++;
						else if (j != 0 && board[i - 1][j - 1].current == 2 || board[i - 1][j - 1].current == IN_MUD_Y) count2++;

						if (j != X - 1 && board[i - 1][j + 1].current == 1 || board[i - 1][j + 1].current == IN_MUD_W) count++;
						else if (j != X - 1 && board[i - 1][j + 1].current == 2 || board[i - 1][j + 1].current == IN_MUD_Y) count2++;

					}

					if (i != Y - 1) {

						if (board[i + 1][j].current == 1 || board[i + 1][j].current == IN_MUD_W) count++;
						else if (board[i + 1][j].current == 2 || board[i + 1][j].current == IN_MUD_Y) count2++;

						if (j != 0 && board[i + 1][j - 1].current == 1 || board[i + 1][j - 1].current == IN_MUD_W) count++;
						else if (j != 0 && board[i + 1][j - 1].current == 2 || board[i + 1][j - 1].current == IN_MUD_Y) count2++;

						if (j != X - 1 && board[i + 1][j + 1].current == 1 || board[i + 1][j + 1].current == IN_MUD_W) count++;
						else if (j != X - 1 && board[i + 1][j + 1].current == 2 || board[i + 1][j + 1].current == IN_MUD_Y) count2++;

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

			if (board[i][j].land == HOLE) {
				board[i][j].future == 0;
			}
			if (mud_count == 1 && board[i][j].current == 1) {
				board[i][j].future = IN_MUD_W;
				mud_count = 0;
			}
			else if (mud_count == 1 && board[i][j].current == 2) {
				board[i][j].future = IN_MUD_Y;
				mud_count = 0;
			}
		}
	}
}
