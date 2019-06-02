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

 /*-------------------------------------------------------------------*
 *    GLOBAL VARIABLES                                                *
 *--------------------------------------------------------------------*/
 /* Control flags */
#define DEBUG

/* Globaal constants */
#define Y 50
#define X 70
#define HOLE  4
#define MUD  3
#define IN_MUD_W 5
#define IN_MUD_Y 6
#define TIME 100
#define FILE_LIVES "life.txt"
#define FILE_LAND "land.txt"
/* Globaal variables */

/* Globaal structures */
struct cell
{
	int current;
	int future;
	int land;
};
/*-------------------------------------------------------------------*
*    FUNCTION PROTOTYPES                                             *
*--------------------------------------------------------------------*/
void zero_the_boards(struct cell board[Y][X]);
void first_board(struct cell  board[Y][X]);
void print_first_board(struct cell  board[Y][X]);
void check_rules_and_put_to_place(struct cell  board[Y][X]);
void print_new_board(struct cell  board[Y][X]);
void read_states(FILE * stream, struct cell  board[Y][X]);
void read_land_states(FILE * stream_land, struct cell(*board)[X]);
void start_game(struct cell  board[Y][X]);
void save_file(struct cell  board[Y][X]);
