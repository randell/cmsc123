/*
	Joseph Randell L. Benavidez
	CMSC 123 E-5L
	May 21, 2003 11:43PM
	chai356@yahoo.com

	This program simulates a binary min heap.  The user has the option to add a node, delete the root, 
	view the current heap and find the element with the ith smallest value.  The user can input characters
	and integers.  In using the delete function, the current heap automatically restores itself.
	
	T(n) = 24(n)(log n) + 30(n) + 48(log n) + 69
	0(n) = n(log n)
*/

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#define MAXHEAP 1000

typedef struct heap {
	char elements[MAXHEAP];
	int topOfHeap;
} heaptype;

typedef struct heap *HEAP;
typedef struct heap *HHEAP;

/* sets the first available slot to 1 */
void INIT(HEAP *H) {	
	(*H)->topOfHeap = 1;
}

/* inserts a new element into the heap */
void INSERT(char ch, HEAP H){
	int j;
	int i;
	char temp;
	int flag = 0;
	
	if ( H->topOfHeap != (MAXHEAP + 1) ) {
		for (i = 1; i < (H->topOfHeap + 1); i++) {
			if (H->elements[i] == ch)
				flag = 1;
		}
		
		if (flag == 0) {	/* no duplicate found in the heap */
			H->elements[H->topOfHeap] = ch;
			j = H->topOfHeap;
			while ( (j > 1) && (H->elements[j/2] > H->elements[j]) ){
				temp = H->elements[j];
				H->elements[j] = H->elements[j/2];
				H->elements[j/2] = temp;
				j = j/2;
			}
			printf("\n\nElement '%c' inserted",ch);
			(H->topOfHeap)++;
		}
		else {	/* element already exists in the heap */
			printf("\n\nCannot insert element");
			printf("\nDuplicate found");
		}	
	}
	else {
		printf("Heap overflow");
		printf("Unable to insert element");
	}
}

/* shows the current elements in the heap */
void VIEW(HEAP H) {
	int i;
	
	if (H->topOfHeap == 1)
		printf("No element found");
	else {
		for (i = 1; i < H->topOfHeap; i++) {
			printf("%c ", H->elements[i]);
		}
	}
}

/* deletes the element with the lowest value and automatically restores the heap */
void DELETE_ROOT(HEAP H) {
	char temp;
	int j;
	
	if (H->topOfHeap != 1){
		temp = H->elements[H->topOfHeap - 1];
		(H->topOfHeap)--;
		H->elements[1] = temp;
		
		j = 1;
		
		while ( (j*2 <= (H->topOfHeap-1)) || (j*2 + 1 <= (H->topOfHeap-1)) ){
			/* swap left */
			if ( ((j*2) <= (H->topOfHeap-1)) && (H->elements[j] > H->elements[j*2]) 
			&& (H->elements[j*2] < H->elements[j*2 + 1]) ){	
				temp = H->elements[j];
				H->elements[j] = H->elements[j*2];
				H->elements[j*2] = temp;
				j = j*2;
			}
			/* swap right */
			else if ( ((j*2 +1) <= (H->topOfHeap-1)) && (H->elements[j] > H->elements[j*2 + 1]) 
			&& (H->elements[j*2] > H->elements[j*2 + 1]) ){	
				temp = H->elements[j];
				H->elements[j] = H->elements[j*2 + 1];
				H->elements[j*2 +1] = temp;
				j = j*2 + 1;
			}
		}
	}
	else
		printf("\n\nNo element found");
}

/* enables the user to know what element is the ith smallest */
void VIEWithSMALL(int i, HEAP H) {
	HEAP extH;
	char temp;
	int j;
	
	extH = H;
	
	if (H->topOfHeap > i) {
		for (j = 0; j < i; j++) {
			temp = H->elements[j + 1];
			DELETE_ROOT(extH);
		}
		printf("\n%c",temp);
	}
	else {
		printf("\nUnable to do task");
		printf("\nOnly %d elements found",H->topOfHeap - 1);
	}
	
	printf("\n\nPress any key to continue...");
	getch();
}

main() {
	HEAP H;
	char ch;
	char ans;

	clrscr();

	INIT(&H);
	
	do {
		clrscr();

		printf("\n\tBINARY HEAP MENU\n\n");
		printf("[1] Insert element\n");
		printf("[2] View Heap\n");
		printf("[3] Delete root\n");
		printf("[4] Find ith smallest\n");
		printf("[5] Quit\n\n");
		printf("Enter chosen number: ");
		ans = getche();
		switch(ans) {
			case '1':	/* insert */
				printf("\n\nEnter element to be inserted: ");
				ch = getche();
				INSERT(ch, H);
				printf("\n\nPress any key to continue...");
				getch();
				break;
			case '2':	/* view */
				printf("\n\nCurrent heap: \n\n");
				VIEW(H);
				printf("\n\nPress any key top continue...");
				getch();
				break;
			case '3':	/* delete */
				DELETE_ROOT(H);
				printf("\n\nPress any key to continue...");
				getch();
				break;
			case '4': {	/* view the ith smallest */
				int i;
				printf("\n\nEnter value for i: ");
				scanf("%d",&i);
				VIEWithSMALL(i,H);
				break;
				}
			case '5':	/* quit */
				break;
		}
	} while (ans != '5');
 
}