/*
	Joseph Randell L. Benavidez
	CMSC 123 E-5L
	April 28, 2003
	chai356@yahoo.com

	This program is an implementation singly linked list.  The main menu
	allows you to choose from 4  options: Insert, Delete, Display or Quit.

	T(n) = 7(n)squared + 11(n)squared + 11
	O(n) = (n)squared
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct node {
	char element;
	struct node *next;
} nodetype;

typedef struct node *LIST;
typedef struct node *position;

/* initializes the new list */
void MAKENULL(LIST *L) {
	*L = (nodetype *)malloc(sizeof(nodetype));
	(*L)->next = NULL;
}

/* inserts the new node to its proper position in the list */
void INSERT(char x, position p) {
	position temp;
	temp = p->next;
	p->next = (nodetype *)malloc(sizeof(nodetype));
	p->next->element = x;
	p->next->next = temp;
}

/* deletes a node */
void DELETE(char x, position p) {
	position temp;
	while (x == p->next->element) {
		temp = p->next;
		p->next = p->next->next;
		free(temp);
	}
}

/* frees all memory space used during runtime */
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

/* prints all elements in the list */
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

/* searches for a given element if it exists in the tree */
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
		printf("[4] Quit\n\n");
		printf("Enter chosen number: ");
		ans = toupper(getche());
		switch (ans) {
			case '1': 
				/* case 1 has an approximated running time of 3n + 11 */
				printf("\n\nEnter an element to insert: ");
				element = getche();
				p = INS_POS(element, L);
				INSERT(element, p);
				break;
			case '2' : 
				/* case 2 has an approximated running time of 7n + 7 */
				printf("\n\nEnter element to delete: ");
				element = getche();
				p = LOCATE(element,L);
				DELETE(element,p);
				break;
			case '3' : 
				/* case 3 has an approximated running time of 3n + 6 */
				printf("\n\n");
				PRINTLIST(L);
				break;
			case '4' : 
				/* case 4 has an approximated running time of 1 */
				break;
		}
	} while (ans != '4');
	DELETEALL(p);	/* DELETEALL has an approximated runnnig time of 4n + 2 */
}