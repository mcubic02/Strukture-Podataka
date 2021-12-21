#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"sedmi.h"

int main()
{
	Directory rootD = { .name = "root", .sibling = NULL, .child = NULL};
	Position root = &rootD;
	Position current = root;
	
	Stack stackHead = { .directory = NULL,.next = NULL };
	StackPosition stack = &stackHead;

	int choice = 0;
	char nameDir[MAX_SIZE] = { 0 };
	do 
	{
		printf("Choose action:\n 1-md\n2-cd dir\n3-cd...\n4-dir\n5-izlaz\n");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
		{
			printf("Write the name of new directory:");
			scanf(" %s", nameDir);
			Position new = CreateNewDirectory(nameDir);
			current->child = Insert(current, new);
			break;
		}
		case 2:
		{
			printf("Input the name of subdirectory:");
			scanf(" %s", nameDir);
			current = MoveTo(current, nameDir, stack);
			break;
		}
		case 3:
		{
			current = Pop(stack, current);
			break;
		}
		case 4:
		{
			printf("%s: \n", current->name);
			PrintDirectories(current);
			break;
		}
		default:
		{
			if(choice!=(1,2,3,4,5))
				perror("Wrong input!");
			break;
		}
		}

	} while (choice != 5);

	FreeMemory(root->child);

	return EXIT_SUCCESS;
}