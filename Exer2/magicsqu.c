/*
	Joseph Randell L. Benavidez
	CMSC 123 E-5L
	April 25, 2003
	chai356@yahoo.com

	Problem: A program that constructs an n * n magic square for any odd value of n
	
	This program applies the concept of "de la Loubere's algorithm" in solving magic squares.
*/
	
/*	T(n) = 17*sqr(n) + 4*n - 6	*/
/*	O(n) = sqr(n)				*/

#include <stdio.h>
#include <conio.h>

#define n 9

main() {
	int row,column,i;
	int m[n][n];
	clrscr();
	if ((n % 2) != 0) {
		/* initializes all the cells to zero */
		for (row = 0; row < n; row++) {
			for (column = 0; column < n; column++) {
				m[row][column] = 0;
			}
		}
		row = 0;	/* locates the first row */
		column = n/2;	/* locates the median of the columns */
		m[row][column] = 1;	/* set the value of the cell */
		for (i = 2; i <= n * n; i++) {
			row--;
			column++;
			/* exceeds the upperbound of the square */
			if ((row < 0) && (column <= (n-1) )) {
				row = n - 1;
			}
			/* exceeds the upperbound and right side of the square */
			else if ((row < 0) && (column > (n-1) )) {
				row++; row++; column--;
			}
			/* exceeds the right side of the square */
			else if ((row >= 0) && (column > (n-1) )) {
				column = 0;
			}
			/* does not exceed the bounds of the square */
			if (m[row][column] != 0) {
			   row++; row++; column--;
			}
			m[row][column] = i;	/* sets the i as the value of the cell */
		}
	}
	for (row = 0; row < n; row++) {
		for (column = 0; column < n; column++)
			printf("%d\t",m[row][column]);
		printf("\n");
	}
	getch();
}