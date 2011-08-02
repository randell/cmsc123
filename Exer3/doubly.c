/*
	Joseph Randell L. Benavidez
	CMSC 123 E-5L
	April 28, 2003
	chai356@yahoo.com

	This program is an implementation doubly linked list.  The main menu
	allows you to choose from 5 options: Insert, Delete, Display, Search or Quit.

	T(n) = 8(n)squared + 14(n) + 12
	O(n) = (n)squared
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

/* initializes a new list */
void MAKENULL(LIST *L) {
	*L = (nodetype *)malloc(sizeof(nodetype));
	(*L)->next = NULL;
	(*L)->prev = NULL;
}

/* searches for the proper position of the new node */
position INS_POS(char x, LIST L) {
	position p;
	p = L;
	while (p->next != NULL) {
		if (x < p->next->element)
			return(p);
		else
			p = p->next;
	}
	return(p); /*if not found*/
}

/* inserts the new node into its proper position */
void INSERT(char x, position p) {
	position temp;
	temp = p->next;
	p->next = (nodetype *)malloc(sizeof(nodetype));
	p->next->element = x;
	p->next->next = temp;
	p->next->prev = p;
	temp->prev = p->next;
}

/* deletes a node */
void DELETE(char x, position p) {
	position temp;
	while (x == p->next->element) {
		temp = p->next;
		p->next = p->next->next;
		p->next->prev = p;
		free(temp);
	}
}

/* frees all memory space used by the program during runtime */
void DELETEALL(position p) {
	position temp;
	while (p->next != NULL) {
		temp = p->next;
		p->next = p->next->next;
		free(temp);
	}
}

/* prints all the elements in the list */
void PRINTLIST(LIST L) {
	position p;
	p = L;
	while (p->next != NULL) {
		printf("%c ",p->next->element);
		p = p->next;
	}
	printf("\n\nPress any key to continue...");
	getch();
}

/* searches a given element if it exists */
position LOCATE(char x, LIST L) {
	position p;
	p = L;
	while (p->next != NULL) {
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

/* prints a located element */
void SEARCH(char x, position p) {
	if (p->next->element == x) {
		if (p->next->prev->prev != NULL)
			printf("\nPrevious:\t%c",p->element);
		else
			printf("\nPrevious:\tNo element found.");
		printf("\nSearch:\t\t%c",p->next->element);

		while (x == p->next->element) {
			p = p->next;
		}
		if (p->next->element == NULL)
			printf("\nNext:\t\tNo element found.");
		else
			printf("\nNext:\t\t%c",p->next->element);
		getch();
	}
}

main() {
	LIST L, p, p2;
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
				/* case 1 has an approximated running time of 3n + 12 */
				printf("\n\nEnter an element to insert: ");
				element = getche();
				p = INS_POS(element, L);
				INSERT(element, p);
				break;
			case '2' :
				/* case 2 has an approximated running time of 8n + 10 */
				printf("\n\nEnter element to delete: ");
				element = getche();
				p = LOCATE(element,L);
				DELETE(element, p);
				break;
			case '3' :
				/* case 3 has an approximated running time of 3n + 4 */
				printf("\n\n");
				PRINTLIST(L);
				break;
			case '4' :
				/* case 4 has an approximated running time of 4n + 14 */
				printf("\n\nEnter element to search: ");
				element = getch();
				p = LOCATE(element,L);
				SEARCH(element, p);
				break;
			case '5' :
				break;
		}
	} while (ans != '5');
	DELETEALL(p); /* DELETEALL has an approximated runnning time of 4n + 1 */
}