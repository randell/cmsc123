/*
	Joseph Randell L. Benavidez
	CMSC 123 E-5L
	May 19, 2003
	chai356@yahoo.com
	
	This program simulates a binary tree.  The program allows the user to input characters (elements)
	into the initially empty tree.  Until the user quits, he has the option to print the current
	inorder, preorder or postorder listing of the tree.
	
	Add-ons: The user also has the option to print the current minimum and maximum element in the tree.
	
	T(n) = 4(n) + 17
	O(n) = n
	Big-Omega = log n
*/

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

typedef struct treenode {
	char element;
	struct treenode *left;
	struct treenode *right;
} nodetype;

typedef struct treenode *TREE;
typedef struct treenode *position;

/* initializes a new empty tree */
void MAKENULL(TREE *T) {	
	*T = (nodetype *)malloc(sizeof(nodetype));
	*T = NULL;
	(*T)->left = NULL;
	(*T)->right = NULL;
}

/* inserts the new element in its proper position */
TREE INS_POS(char x, TREE T) {
	if (T == NULL) {
		T = (nodetype *)malloc(sizeof(nodetype));
		if (T == NULL)
			printf("Out of Space!");
		else {
			T->element = x;
			T->left = NULL;
			T->right = NULL;
		}
  }
  else if (x < T->element)
		T->left = INS_POS(x, T->left);
  else if (x > T->element)
		T->right = INS_POS(x, T->right);
		
	return(T);
}

/* checks if a given element exists in the tree */
void LOCATE(char x, TREE T) {
	position p;
	p = T;
	
	if (x == p->element) {
   		printf("\n\nElement %c found in tree",p->element);
   	}
	else if (p == NULL) {
		printf("\n\nUnable to locate element %c.",x);
	}
	else if (x < p->element)
   		LOCATE(x, p->left);
 	else if (x > p->element) 
		LOCATE(x, p->right);
	
	printf("\n\nPress any key to continue...");
	getch();
}

/* prints the inorder listing of the current tree */
void INORDER(TREE T) {
	position p;
	p = T;
	
	if (p != NULL) {
		INORDER(p->left);
		printf("%c ",p->element);
		INORDER(p->right);
	}
}

/* prints the preorder listing of the current tree */
void PREORDER(TREE T) {
	position p;
	p = T;

	if (p != NULL) {
		printf("%c ",p->element);
		PREORDER(p->left);
		PREORDER(p->right);
	}
}

/* prints the postorder listing of the current tree */
void POSTORDER(TREE T) {
	position p;
	p = T;
	
	if (p != NULL) {
		POSTORDER(p->left);
		POSTORDER(p->right);
		printf("%c ",p->element);
	}
}

/* locates the leftmost element of the tree */
void LOCATE_MIN(TREE T) {
	position p;
	p = T;
	
	if (p != NULL) {
		while (p->left != NULL) {
			p = p->left;
		}	
		printf("%c",p->element);
	}
	else
		printf("Tree is empty");
	printf("\n\nPress any key to continue...");
	getch();
}

/* locates the rightmost element of the tree */
void LOCATE_MAX(TREE T) {
	position p;
	p = T;
	
	if (p != NULL) {
		while (p->right != NULL) {
			p = p->right;
		}	
		printf("%c",p->element);
	}
	else
		printf("Tree is empty");
	printf("\n\nPress any key to continue...");
	getch();
}

/* TREE DELETE_NODE(char x, TREE T){
	TREE temp, child;

	if (T == NULL)
		printf("\nElement not found!\n");
	else if (x < T->element)
		T->left = DELETE_NODE(x, T->left);
  	else if (x > T->element)
		T->right = DELETE_NODE(x, T->right);
  	else if (T->left && T->right) {
		temp = FIND_MIN(T->right);
		T->element = temp->element;
		T->right = DELETE_NODE(T->element, T->right);
	}
	else {
		temp = T;
		if(T->left==NULL)
  			child=T->right;
		if(T->right==NULL)
  			child=T->left;
  		free(temp);
  		
  		return(child);
  	}
  	
	return T;
}

TREE FIND_MIN(TREE T) {
	if (T == NULL)
		return NULL;
	else if(T->left == NULL)
		return(T);
	else
		return(FIND_MIN(T->left));
} */

main() {
	TREE T, p;
	char ans, element;

	MAKENULL(&T);
	
	do {
		clrscr();
		printf("\n	BINARY TREE MENU\n");
		printf("[1] Insert\n");
		printf("[2] Search\n");
		printf("[3] Show Inorder traversal\n");
		printf("[4] Show Preorder traversal\n");
		printf("[5] Show Postorder traversal\n");
		printf("[6] Show leftmost element\n");
		printf("[7] Show rightmost element\n");
		printf("[8] Quit\n\n");
		printf("Enter chosen number: ");
		ans = getche();
		switch(ans) {
			case '1':	/* inserting an element */
				printf("\n\nEnter an element to insert: ");
				element = getche();
				T = INS_POS(element, T);
				break;
			case '2':	/* searching an element */
				printf("\n\nEnter the element you want to search: ");
				element = getche();
				LOCATE(element, T);
				break;
			case '3':	/* inorder traversal */
				printf("\n\nInorder Listing:\n\n");
				INORDER(T);
				printf("\n\nPress any key to continue...");
				getch();
				break;
			case '4':	/* preorder traversal */
				printf("\n\nPreorder Listing:\n\n");
				PREORDER(T);
				printf("\n\nPress any key to continue...");
				getch();
				break;
			case '5':	/* postorder traversal */
				printf("\n\nPostorder Listing:\n\n");
				POSTORDER(T);
				printf("\n\nPress any key to continue...");
				getch();
				break;
			case '6':	/* locate minimum element */
				printf("\n\nMinimum element: ");
				LOCATE_MIN(T);
				break;
			case '7':	/* locate maximum element */
				printf("\n\nMaximum element: ");
				LOCATE_MAX(T);
				break;
			case '8':	/* quit */
				break;
		}
	} while (ans != '8');
}