#define _CRT_SECURE_NO_WARNINGS
#include "sedmi.h"
#include <stdio.h>
#include<string.h>
#include<stdlib.h>

Position Insert(Position current, Position newEl)
{
	if (!current)
		return newEl;
	if (strcmp(current->name, newEl->name) < 0)
		current->sibling = Insert(current->sibling, newEl);
	else if (strcmp(current->name, newEl->name) > 0)
	{
		newEl->sibling = current;
		return newEl;
	}
	return current;
}
Position CreateNewDirectory(char name[])
{
	Position newEl = NULL;
	newEl = (Position)malloc(sizeof(Directory));
	if (!newEl)
	{
		perror("Couldn't allocate memory!");
		return NULL;
	}
	strcpy(newEl->name, name);
	newEl -> sibling = NULL;
	newEl -> child = NULL;

	return newEl;
}
StackPosition CreateStackElement(Position currDirectory)
{
	StackPosition newEl = NULL;
	newEl = (Position)malloc(sizeof(Directory));
	if (!newEl)
	{
		perror("Couldn't allocate memory!");
		return NULL;
	}
	newEl->directory = currDirectory;
	newEl->next = NULL;

	return newEl;
}

int Push(StackPosition head, StackPosition newStackEl)
{
	newStackEl->next = head->next;
	head->next = newStackEl;

	return EXIT_SUCCESS;
}
Position Pop(StackPosition head, Position current)
{
	StackPosition first = head->next;
	Position temp = NULL;

	if (!first)
	{
		perror("No parent");
		return current;
	}
	temp = first->directory;
	head->next = first->next;
	free(first);
}
int PrintDirectories(Position current)
{
	Position temp = current->child;
	while (temp)
	{
		printf("%s", temp->name);
		temp = temp->sibling;
	}
	return 1;
}
Position MoveTo(Position current, char* moveTo, StackPosition stack)
{
	Position temp = current->child;
	while (temp && strcmp(temp->name, moveTo))
		temp = temp->sibling;

	if (temp == NULL)
	{
		printf("no subdirectory %s ", moveTo);
		return current;
	}
	else
	{
		StackPosition newStackElement = CreateStackElement(current);
		Push(stack, newStackElement);
		return temp;
	}
	return temp;
}
int FreeMemory(Position root)
{
	Position current = root;
	{
		if (current && current->sibling)
			FreeMemory(current->sibling);

		if (current && current->child)
			FreeMemory(current->child);

		free(current);

		return EXIT_SUCCESS;
	}
}
