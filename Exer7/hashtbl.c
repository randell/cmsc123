/*
	Joseph Randell L. Benavidez
	CMSC 123 E-5L
	May 20, 2003
	chai356@yahoo.com
	
	This program simulates a phonebook (not knowing the owner of the numbers) using a hash table.
	The user can only choose to enter a table size not lower than 10 for faster searching.
	During the execution of the program, the user has the option to add a new number, search if a given
	number exists in the phonebook, view numbers in a certain key, view numbers in all of the keys,
	delete a number or delete all the numbers in the phonebook.
	
	T(n) = 21(n) + 19
	O(n) = n
*/

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#define MIN_TABLE_SIZE 10

typedef struct node {
	int element;
	struct node *next;
} nodetype;

typedef struct node *LIST;
typedef struct node *position;

typedef struct hashtbl{
	int tblsize;
	LIST *lists;
} hashtbltype;

typedef struct hashtbl *HASHTABLE;

/* initializing the hash table */
HASHTABLE INIT(int tblsize){
	HASHTABLE H;
	int i;

	if (tblsize < MIN_TABLE_SIZE) {
		printf("Table size too small");
		return NULL;
	}
	
	/* allocate table */
	H = (hashtbltype *)malloc( sizeof(hashtbltype) );
	if(H == NULL)
		printf("Out of space!!!");

	H->tblsize = tblsize;
	
	/* allocate pointers */
	H->lists = (LIST *)malloc( sizeof(LIST) * H->tblsize );

	if (H->lists == NULL)
		printf("Out of space!!!");

	/* allocate list headers */
	for (i = 0; i < H->tblsize; i++) {
		H->lists[i] = (LIST)malloc( sizeof(nodetype) );
		if(H->lists[i] == NULL)
			printf("Out of space!!!");
		else
			H->lists[i]->next = NULL;
	}
    return H;
}

/* inserts the new number into the hash table if does not exist anywhere in the hash table yet */
void INSERT(int num, HASHTABLE H) {
	position p, new_cell;
	LIST L;

	L = H->lists[HASH(num, H->tblsize)];
	p = L->next;

	while ((p != NULL) && (p->element != num))
		p = p->next;

	if (p == NULL){	/* number does not exist in the phonebook yet */
  		new_cell = (position) malloc(sizeof(nodetype));
    	if (new_cell == NULL)
     		printf("\n\nOut of space!!!");
    	else {
			L = H->lists[HASH(num, H->tblsize)];
     		new_cell->next = L->next;
     		new_cell->element = num;
     		L->next = new_cell;
     	}
     	printf("\nNumber inserted");
	}
	else {
		printf("\nUnable to insert number.");
		printf("\nSame number already exist in the phonebook.");
	}
		
	printf("\n\nPress any key to continue...");
	getch();
}

/* returns the key where the new number will be placed*/
HASH(int num, int tblsize) {
	int hashval;
	
	hashval = num % tblsize;
	
	return(hashval);
}

/* searches if a number exists in the phonebook */
void FIND_NUM(int num, HASHTABLE H) {
	position p;
	LIST L;
	
	L = H->lists[HASH(num, H->tblsize)];
	p = L->next;
	
	while ((p != NULL) && (p->element != num)) {
		p = p->next;
	}
	
	if (p == NULL)
		printf("\n%d does not exist in the list.",num);
	else if (p->element == num)
		printf("\n%d exists in the list.",num);
		
	printf("\n\nPress any key to continue");
	getch();
}

/* lets the user view numbers in given a certain key */
void VIEWKEY(HASHTABLE H) {
	position p;
	LIST L;
	int i;
	
	printf("Enter key [0 to %d]: ",H->tblsize);
	scanf("%d",&i);
	
	if (i < H->tblsize) {
		L = H->lists[i];
		p = L->next;
		
		printf("\nKey %d",i);
		while (p != NULL) {
			if (p->element != NULL)
				printf("\n%d",p->element);
			p = p->next;
		}
		printf("\n\n");
	}
	else
		printf("Key does not exist...\n\n");
		
	printf("Press any key to continue...");
	getch();
}

/* lets the user view all existing numbers in the phonebook separated by keys */
void VIEWALL(HASHTABLE H) {
	position p;
	LIST L;
	int i;

	for (i = 0; i < H->tblsize; i++) {
		L = H->lists[i];
		p = L->next;
		
		printf("\nKey %d",i);
		while(p != NULL) {
			if (p->element != NULL)
				printf("\n%d",p->element);
			p = p->next;
		}
		printf("\n\n");
		getch();
	}
	printf("Press any key to go back to menu...");
	getch();
}

/* deletes an existing number */
void DELETE_NUM(int num, HASHTABLE H) {
	position p, temp;
	LIST L;

	L = H->lists[HASH(num, H->tblsize)];
	p = L->next;

	while ((p != NULL) && (p->element != num))
		p = p->next;

	if (p->element == num) {
		temp = p;
		p->element = NULL;
		p = NULL;
		free(p);
		p = temp->next;
		printf("\nNumber deleted");
	}
	else
		printf("\nNumber not found!");
	
	printf("\n\nPress any key to continue...");
	getch();
}

/* deletes all existing number in the phonebook */
void DELETE_ALL(HASHTABLE H) {
	position p, temp;
	LIST L;
	int i;

	for (i = 0; i < H->tblsize; i++) {
		L = H->lists[i];
		p = L->next;

		while (p != NULL) {
			temp = p;
			p->element = NULL;
			p = NULL;
			free(p);
			p = temp->next;
		}
	}
	printf("\n\nPhonebook empty");
	printf("\n\nPress any key to continue...");
	getch();
}

main() {
	HASHTABLE H;
	char ans;
	int size = 0;
	int num;
	
	clrscr();
	
	while (size < 10) {	/* repeats until the user enters a proper value */
		printf("\nPlease enter desired phonebok size[at least 10]: ");
		scanf("%d",&size);
		if (size < 10)
			printf("\nThe size of your phonebook should be at least 10.\n");
		printf("\nPress any key to continue...");
		getch();
		clrscr();
	}
	
	H = INIT(size);

	do{
		clrscr();
		printf("\n\tPHONEBOOK\n\n");
		printf("[1] Add new number\n");
		printf("[2] Search existing number\n");
		printf("[3] View numbers in a key\n");
		printf("[4] View all numbers\n");
		printf("[5] Delete an existing number\n");
		printf("[6] Delete all numbers\n");
		printf("[7] Quit\n\n");
		printf("Enter chosen number: ");
		ans = getche();
		switch(ans){
			case '1':	/* adds a number into the phonebook*/
				printf("\n\nEnter new phonenumber: ");
				scanf("%d",&num);
				INSERT(num, H);
				break;
			case '2':	/* search for a number if it exists in the phonebook */
				printf("\n\nEnter number to search: ");
				scanf("%d",&num);
				FIND_NUM(num, H);
				break;
			case '3':	/* view all elements in a key */
				printf("\n");
				VIEWKEY(H);
				break;
			case '4':	/* view all existing numbers */
				printf("\n");
				VIEWALL(H);
				break;
			case '5':	/* delete an existing number */
				printf("\n\nEnter number to delete: ");
				scanf("%d",&num);
				DELETE_NUM(num, H);
				break;
			case '6':	/* delete all numbers in phonebook */
				DELETE_ALL(H);
				break;
			case '7':	/* quit */
				break;
		}
	}while(ans != '7');
}