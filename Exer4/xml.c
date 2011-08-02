/*
	Joseph Randell L. Benavidez
	CMSC 123 E-5L
	May 10, 2003
	chai356@yahoo.com
	
	This program simulates an xml compiler.  First, the program reads from a source xml file.
	it then reads the file one character at a time.  Using a stack and some of the stack operations,
	the program checks the possible sources of error int the xml.
	
	O(n) = n (depends on the length of the file
*/


#include <stdio.h>
#include <conio.h>     
#include <io.h>
#include <string.h>       
             
typedef struct node{                                                                                     
	char elements;
	struct node *next;
} nodetype;

typedef struct node *LIST;
typedef struct node *position;

void MAKENULL(LIST *L) {
	*L = (nodetype *)malloc(sizeof(nodetype));
	(*L)->next = NULL;
}

/* removes the top element in the stack */
void pop(LIST L){
	position temp;
	temp = L->next;
	L->next = L->next->next;
	free(temp);
}

/* inserts a new element in the stack */
void push(LIST L, char ch){
	position temp;
	temp = L->next;
	L->next = (nodetype *)malloc(sizeof(nodetype));
	L->next->elements = ch;
	L->next->next = temp;
}

/* checks if the character is a slash */
int isSlash(char ch) {
	switch(ch){
		case '/':	return 1;
		default:	return 0;
	}
}

main() {
	LIST L,root;
	int x;
	char ch,ch2,ch3;
	int i;
	FILE *f;
	int cnt = 0;

	clrscr();

	MAKENULL(&L);
	MAKENULL(&root);

	if ((f = fopen("stacks.xml","r")) != NULL) {	/* checks if file is accessible */
		printf("File opened.\n\n");
		while ((x = getc(f)) != EOF) {	/* reads the file per character */
			ch = x;
			if (ch == '<') {	/* checks if character is an open delimiter */
				if ((x = getc(f)) != EOF) {	/* checks the next character after the open delimiter */
					ch = x;
					if (!isSlash(ch)) {	/* checks if it is a slash */
						push(L,ch);
						push(root,ch);
					}
					else if ( (isSlash(ch)) &&  ((x = getc(f)) != EOF) ){	/* or not a slash */
						ch = x;
						if (ch == L->next->elements) {	/* if character is equal to the top of the stack */
							pop(L);
						}
						else if (ch != L->next->elements) {	/* if not equal to the top of the stack */
							printf("Error: </%c> needed. </%c> found.\n",L->next->elements,ch);
							pop(L);
						}
						push(root,ch);
					}
				}
			}
		}
		fclose(f);
	}
	else
		printf("Error: Unable to open file");	/* tells the user that the file is inaccessible */

	if ((f = fopen("stacks.xml","r")) != NULL) {
		while ((x = getc(f)) != EOF) {	/* reads the file per character */
			ch = x;
			if ( (ch == '>') && (cnt == 0) ){
				x = getc(f);
				ch = x;
				while ((ch != '<') && ((ch == '\t') || (ch== '\n')) ) {
					x = getc(f);
					ch = x;
				}
				if (ch == '<')
					printf("there is a root element");
				else
					printf("no root element");
				cnt++;
			}
		}
		fclose(f);
	}


	printf("\n\nPress any key to exit.");
	getch();
}