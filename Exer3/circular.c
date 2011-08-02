/*
	Joseph Randell L. Benavidez
	CMSC 123 E-5L
	April 28, 2003
	chai356@yahoo.com

	This program is an implementation doubly circular linked list.  The main menu
	allows you to choose from 5 options: Insert, Delete, Display, Search or Quit.

	T(n) = (n)cubed + 6(n)squared + 24(n) +3
	O(n) = (n)cubed
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct node {
	char element;
	struct node *next;
	struct node *prev;
} nodetype;

typedef struct node *LIST;
typedef struct node *position;

/* initializes the list */
void MAKENULL(LIST *L) {
	*L = (nodetype *)malloc(sizeof(nodetype));
	(*L)->next = *L;
	(*L)->prev = *L;
}

/* inserts the new node to ints proper position */
void INSERT(char x, position p) {
	position temp;
	temp = p->next;
	p->next = (nodetype *)malloc(sizeof(nodetype));
	p->next->element = x;
	p->next->next = temp;
	p->next->prev = p;
	temp->prev = p->next;
	if (temp->next == p)
		p->prev = temp;
}

/* deletes the given node */
void DELETE(char x, position p) {
	position temp;
	while (x == p->next->element) {
		temp = p->next;
		p->next = p->next->next;
		p->next->prev = p;
		free(temp);
	}
}

/* frees all the memory spaced used by the program*/
void DELETEALL(position p) {
	position temp;
	while (p->next != NULL) {
		temp = p->next;
		p->next = p->next->next;
		free(temp);
	}
}

/* searches for the proper position for the new node */
position INS_POS(char x, LIST L) {
	position p, p2;
	p = L;
	p2 = L;
	while (p->next != p2) {
		if (x < p->next->element)
			return(p);
		else
			p = p->next;
	}
	return(p); /*if not found*/
}

/* prints all the elements int he list */
void PRINTLIST(LIST L) {
	position p, p2;
	p = L;
	p2 = L;
	while (p->next != p2) {
		printf("%c ",p->next->element);
		p = p->next;
	}
	printf("\n\nPress any key to continue...");
	getch();
}

/* searches for a given element */
position LOCATE(char x, LIST L) {
	position p,p2;
	p = L;
	p2 = L;
	while (p->next != p2) {
		if (x == p->next->element)
			return(p);
		else
			p = p->next;
	}
	printf("\nUnable to locate element.\n");
	printf("Press any key to continue...\n");
	getch();
	return(p);
}

/* prints the element if found */
void SEARCH(char x, position p) {
	if (p->next->element == x) {
		printf("\nPrevious:\t%c",p->next->prev->prev->element);
		printf("\nSearch:\t\t%c",p->next->element);
		while (p->next->element == x)
			p = p->next;
		printf("\nNext:\t\t%c",p->next->next->element);
		getch();
	}
}

main() {
	LIST L, p;
	char ans, element;

	MAKENULL(&L);

	do {
		clrscr();
		printf("\n	MENU\n");
		printf("[1] Insert\n");
		printf("[2] Delete\n");
		printf("[3] Display\n");
		printf("[4] Search\n");
		printf("[5] Quit\n\n");
		printf("Enter chosen number: ");
		ans = toupper(getche());
		switch (ans) {
			case '1':
				/* case 1 has a approximated runtime of (n)squared + 2n + 11 */
				printf("\n\nEnter an element to insert: ");
				element = getche();
				p = INS_POS(element, L);
				INSERT(element, p);
				break;
			case '2' :
				/* case 2 has a approximated runtime of (n)squared + 6n + 10 */
				printf("\n\nEnter element to delete: ");
				element = getche();
				p = LOCATE(element,L);
				DELETE(element, p);
				break;
			case '3' :
				/* case 4 has a approximated runtime of 3n + 9 */
				printf("\n\n");
				PRINTLIST(L);
				break;
			case '4' :
				printf("\n\nEnter element to search: ");
				element = getch();
				p = LOCATE(element,L);
				SEARCH(element, p);
				break;
			case '5' :
				break;
		}
	} while (ans != '5');
	DELETEALL(p); /* has a runtime of 4n + 1 */
}