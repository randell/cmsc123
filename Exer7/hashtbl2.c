/*
	Joseph Randell L. Benavidez
	CMSC 123 E-5L
	May 20, 2003
	chai356@yahoo.com
	
	This program simulates a directory using a hash table.  The user is not required to enter the size
	of the table because it is already set to 26 (number of letters in the alphabet).  During the 
	execution of the program, the user has the option to add a contact person, search if a given
	contact exists in the dictionary, view names in a certain key, view persons in all of the keys,
	delete a name or delete all the contacts in the phonebook.
	
	T(n) = 21(n) + 19
	O(n) = n
*/

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
	char *element;
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

/* inserts the new names into the hash table if does not exist anywhere in the hash table yet */
void INSERT(char *mystring, HASHTABLE H) {
	position p, new_cell;
	LIST L;

	L = H->lists[HASH(mystring[0])];
	p = L->next;

	while ( (p != NULL) && (strcmp(p->element,mystring) != 0) )
		p = p->next;

	if (p == NULL){	/* name does not exist in the phonebook yet */
  		new_cell = (position) malloc(sizeof(nodetype));
    	if (new_cell == NULL)
     		printf("\n\nOut of space!!!");
    	else {
			L = H->lists[HASH(mystring[0])];
     		new_cell->next = L->next;
     		new_cell->element = mystring;
     		L->next = new_cell;
     	}
     	printf("\nName inserted");
	}
	else {
		printf("\nUnable to insert name.");
		printf("\nSame name already exist in the directory.");
	}
		
	printf("\n\nPress any key to continue...");
	getch();
}

/* returns the key where the new name will be placed*/
HASH(char x) {
	int hashval;
	
	switch(x) {
		case 'a':	hashval = 0;	break;
		case 'b':	hashval = 1;	break;
		case 'c':	hashval = 2;	break;
		case 'd':	hashval = 3;	break;
		case 'e':	hashval = 4;	break;
		case 'f':	hashval = 5;	break;
		case 'g':	hashval = 6;	break;
		case 'h':	hashval = 7;	break;
		case 'i':	hashval = 8;	break;
		case 'j':	hashval = 9;	break;
		case 'k':	hashval = 10;	break;
		case 'l':	hashval = 11;	break;
		case 'm':	hashval = 12;	break;
		case 'n':	hashval = 13;	break;
		case 'o':	hashval = 14;	break;
		case 'p':	hashval = 15;	break;
		case 'q':	hashval = 16;	break;
		case 'r':	hashval = 17;	break;
		case 's':	hashval = 18;	break;
		case 't':	hashval = 19;	break;
		case 'u':	hashval = 20;	break;
		case 'v':	hashval = 21;	break;
		case 'w':	hashval = 22;	break;
		case 'x':	hashval = 23;	break;
		case 'y':	hashval = 24;	break;
		case 'z':	hashval = 25;	break;
		default:	hashval = 25;	break;
	}
	
	return(hashval);
}

/* searches if a name exists in the phonebook */
void FIND_NUM(char *mystring, HASHTABLE H) {
	position p;
	LIST L;
	
	L = H->lists[HASH(mystring[0])];
	p = L->next;
	
	while ( (p != NULL) && (strcmp(p->element,mystring) != 0) ){
		p = p->next;
	}
	
	if (p == NULL)
		printf("\n%s does not exist in the directory.",mystring);
	else if (strcmp(p->element,mystring) == 0)
		printf("\n%s exists in the directory.",mystring);
		
	printf("\n\nPress any key to continue");
	getch();
}

/* lets the user view names in given a certain key */
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
				printf("\n%s",p->element);
			p = p->next;
		}
		printf("\n\n");
	}
	else
		printf("Key does not exist...\n\n");
		
	printf("Press any key to continue...");
	getch();
}

/* lets the user view all existing names in the directory separated by keys */
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
				printf("\n%s",p->element);
			p = p->next;
		}
		printf("\n\n");
		getch();
	}
	printf("Press any key to go back to menu...");
	getch();
}

/* deletes an existing name */
void DELETE_NUM(char *mystring, HASHTABLE H) {
	position p, temp;
	LIST L;

	L = H->lists[HASH(mystring[0])];
	p = L->next;

	while ( (p != NULL) && (strcmp(p->element,mystring) != 0) )
		p = p->next;

	if (strcmp(p->element,mystring) == 0)	{ 
		temp = p;
		p->element = NULL;
		p = NULL;
		free(p);
		p = temp->next;
		printf("\nName deleted");
	}
	else
		printf("\nName not found!");
	
	printf("\n\nPress any key to continue...");
	getch();
}

/* deletes all existing name in the phonebook */
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
	printf("\n\nDirectory empty");
	printf("\n\nPress any key to continue...");
	getch();
}

main() {
	HASHTABLE H;
	char ans;
	char *mystring;
	int size = 26;
	
	clrscr();
	
	H = INIT(size);
	mystring = (char *)malloc(sizeof(char));
	
	do{
		clrscr();
		printf("\n\tDIRECTORY\n\n");
		printf("[1] Add a name\n");
		printf("[2] Search existing name\n");
		printf("[3] View names in a key\n");
		printf("[4] View all names\n");
		printf("[5] Delete an existing name\n");
		printf("[6] Delete all names\n");
		printf("[7] Quit\n\n");
		printf("Enter chosen number: ");
		ans = getche();
		switch(ans){
			case '1':	/* adds a name into the directory */
				printf("\n\nEnter new name: ");
				scanf("%s",mystring);
				INSERT(mystring, H);
				break;
			case '2':	/* search for a name if it exists in the directory */
				printf("\n\nEnter name to search: ");
				scanf("%s",mystring);
				FIND_NUM(mystring, H);
				break;
			case '3':	/* view all names in a key */
				printf("\n");
				VIEWKEY(H);
				break;
			case '4':	/* view all existing names */
				printf("\n");
				VIEWALL(H);
				break;
			case '5':	/* delete an existing name */
				printf("\n\nEnter name to delete: ");
				scanf("%s",mystring);
				DELETE_NUM(mystring, H);
				break;
			case '6':	/* delete all names in directory */
				DELETE_ALL(H);
				break;
			case '7':	/* quit */
				break;
		}
	}while(ans != '7');
}