#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "deveti.h"

int main()
{
	time_t t=0;
	treeP root = NULL;
	Position Head1 = NULL;
	Position Head2 = NULL;

	List headListElement1 = { .number = 0, .next = NULL };
	Head1 = &headListElement1;

	List headListElement2 = { .number = 0, .next = NULL };
	Head2 = &headListElement2;

	int choice = 0;
	int newNum = 0;

	srand((unsigned)&t);

	do
	{
		printf("Izaberi \n");
		
		printf(" 1 - Dodaj nasumièni broj \n 2 - Zamjeni svaki cvor zbrojem potomaka i ispisi obe liste u datoteku"
			" 0 - Izlaz \n");
		scanf("%d", &choice);
		
		switch (choice)
		{
		case 1:
		{
			Position newEl = NULL;
			Position newListEl = NULL;
			if (!root)
			{
				newNum = rand() % (90 - 10 + 1) + 10;
				tree headElement = { .num = newNum, .left = NULL, .right = NULL };
				root = &headElement;
			}
			else
			{
				newNum = rand() % (90 - 10 + 1) + 10;
				
				Insert(newNum, root);
			}
			printf("Number inserted: %d \n", newNum);
			break;
		}
		case 2:
		{
			InsertTreeInList(root, Head1);
			replace(root);
			InsertTreeInList(root, Head2);
			InFile(Head1, Head2);
			break;
		}
		default:
		{
			if (choice !=0)
			{
				printf("Wrong input, please try again \n \n");
				break;
			}
		}

		}

	} while (choice != 0);

	return 0;
}