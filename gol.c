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

 /*-------------------------------------------------------------------*
 *    GLOBAL VARIABLES                                                *
 *--------------------------------------------------------------------*/
 /* Control flags */
#define DEBUG

/* Globaal constants */
#define I 30
#define J 30
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
/*********************************************************************
*    MAIN PROGRAM                                                      *
**********************************************************************/
void main(void) {

	struct cell board[I][J];
	
	zero_the_boards(board);
	int ran;
/****************************************************/
	srand(time(0));			/*luodaan eka siviilisaatio*/
	for (int i = 0; i < I; i++) {
		for (int j = 0; j < J; j++) {
			int ran = rand() % 15;
			if (ran <= 8) {
				board[i][j].current = 1;
			}
		}
	}							/*päättyy tähän*/
	/******************************************/
	for (int i = 0; i < I; i++) {/*tulostaa ekan siviilisaation*/
		for (int j = 0; j < J; j++) {
			printf("%d ", board[i][j].current);
		}
		printf("\n");
	}

	/*päättyy tähän*/
	/*******************************************/
	int count = 0;
	int stop = 0;
	while (stop == 0) {
		for (int i = 0; i < I; i++) {
			for (int j = 0; j < J; j++) {

				if (board[i][j].current == 1) {
					if (j != J - 1) {
						if (board[i][j + 1].current == 1) count++;
					}
					if (j != 0) {
						if (board[i][j - 1].current == 1) count++;
					}
					if (i != 0) {
						if (board[i - 1][j].current == 1) count++;
						if (j != 0 && board[i - 1][j - 1].current == 1) count++;
						if (j != J - 1 && board[i - 1][j + 1].current == 1) count++;
					}
					if (i != I - 1) {
						if (board[i + 1][j].current == 1) count++;
						if (j != 0 && board[i + 1][j - 1].current == 1) count++;
						if (j != J - 1 && board[i + 1][j + 1].current == 1) count++;
					}

					if (count == 1 || count == 0 || count >= 4) {
						board[i][j].future = 0;
					}
					if (count == 2 || count == 3) {
						board[i][j].future = 1;
					}
					count = 0;
				}
				else if (board[i][j].current == 0) {
					if (j != J - 1) {
						if (board[i][j + 1].current == 1) count++;
					}
					if (j != 0) {
						if (board[i][j - 1].current == 1) count++;
					}
					if (i != 0) {
						if (board[i - 1][j].current == 1) count++;
						if (j != 0 && board[i - 1][j - 1].current == 1) count++;
						if (j != J - 1 && board[i - 1][j + 1].current == 1) count++;
					}
					if (i != I - 1) {
						if (board[i + 1][j].current == 1) count++;
						if (j != 0 && board[i + 1][j - 1].current == 1) count++;
						if (j != J - 1 && board[i + 1][j + 1].current == 1) count++;
					}

					if (count == 3) {
						board[i][j].future = 1;
					}
					count = 0;
				}
			}
		}


		printf("\n");
		for (int i = 0; i < I; i++) {
			for (int j = 0; j < J; j++) {
				board[i][j].current = board[i][j].future;
				printf("%d ", board[i][j].current);
			}
			printf("\n");
		}

		Sleep(1000);
		system("cls");
		getche();
	}

}
 /* end of main */

/*********************************************************************
*    FUNCTIONS                                                     *
**********************************************************************/
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
	printf("jouuuuuu");
	for (int i = 0; i < I; i++) {		/*nollaa current ja future*/
		for (int j = 0; j < J; j++) {
			board[i][j].current = 0;
			board[i][j].future = 0;
		}
	}
}
