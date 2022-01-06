#define _CRT_SECURE_NO_WARNINGS
#include "desetiiA.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_SIZE 32

Position CreateListElement(char* State)
{
	Position newState = NULL;
	newState = (Position)malloc(sizeof(List));

	if (!newState)
	{
		perror("Can't allocate memory!");
		return NULL;
	}
	strcpy_s(newState->stateName, sizeof(newState->stateName), State);
	return newState;
}
int ReadListFromFile(char* fileName, Position head)
{
	char State[MAX_SIZE] = { 0 }, CityFile[MAX_SIZE] = { 0 };
	FILE* dat = NULL;
	Position newState = NULL;
	dat = fopen(fileName, "r");
	if (!dat)
		perror("Can't open file");
	while (!feof(dat))
	{
		fscanf(dat, " %s %s", State, CityFile);
		newState = CreateListElement(State);
		AddListElement(head, newState);
		AddTreeElement(CityFile, newState);
	}
	return EXIT_SUCCESS;
}
int AddListElement(Position head, Position newState)
{
	Position temp = head;
	int f = 0;
	if (!newState)
		perror("Couldn't allocate memory");
	if (temp->next == NULL)
	{
		temp->next = newState;
		newState->next = NULL;
	}
	else
	{
		while (temp != NULL)
		{
			if (strcmp(newState->stateName, temp->stateName) < 0)
				InsertBefore(head, temp, newState);
			temp = temp->next;
		}
		temp = head;
		while (temp != NULL)
		{
			if (strcmp(newState->stateName, temp->stateName) == 0)
				f++;
			temp = temp->next;
		}
		if (f == 0)InsertBefore(head, temp, newState);
	}
	return EXIT_SUCCESS;
}
int InsertBefore(Position head, Position position, Position newState)
{
	Position before = NULL;
	before = FindBefore(head, position);
	InsertAfter(before, newState);

	return EXIT_SUCCESS;
}
Position FindBefore(Position head, Position position)
{
	Position temp = head;
	while (temp->next != position)temp = temp->next;
	return temp;

}
int InsertAfter(Position position, Position newElement)
{
	newElement->next = position->next;
	position->next = newElement;
	return EXIT_SUCCESS;
}
int Print(Position head)
{
	Position temp = head->next;
	while (temp)
	{

		printf(" %s", temp->stateName);
		PrintTree(temp->city);
		temp = temp->next;

	}
	return EXIT_SUCCESS;
}
AddTreeElement(char* fileName,Position newState)
{
	treeP root = NULL;
	FILE* dat = NULL;
	dat = fopen(fileName, "r");
	fscanf(dat, " %s %d", CityName, Population);
	newState->city = root;
	treeP newCity = NULL;
	newCity = CreateNewEl(CityName, Population);
	root = Insert(newCity, root);
	
}
treeP CreateNewEl(char* name, int pop)
{
	treeP new = (treeP)malloc(sizeof(tree));
	if (!new)
	{
		perror("Couldn't allocate memory!");
		return NULL;
	}
	strcpy(new->cityName, name);
	new->population = pop;
	new->left = NULL;
	new->right = NULL;
	return new;
}
treeP Insert(treeP newCity,treeP current)
{
	if (!current)
		return newCity;
	else if (newCity->population<current->population)
		current->left = Insert(newCity, current->left);
	else if (newCity->population == current->population)
	{
		if (strcmp(newCity->cityName, current->cityName) < 0)
			Insert(newCity, current->left)
		else
			Insert(newCity, current->right);
	}
	else
		current->right = Insert(newCity, current->right);
	return current;

}
int PrintTree(treeP current)
{
	if (!current)
		return 0;
	PrintInOrder(current->left);
	printf(" %s" , current->cityName);
	PrintInOrder(current->right);
	return 1;
}
int Search(char* stateName, int num, Position head)
{
	Position temp = head->next;
	while (temp)
	{
		if (strcmp(stateName, temp->stateName) == 0)
			break;
		temp = temp->next;
	}
	treeP current = temp->city;
	PrintEl(num, current);
	

}
int PrintEl(int num, treeP current)
{
	if (!current)
		return 1;
	else if (num < current->num)
	{
		printf(" %s", current->cityName);
		PrintEl(num, current->right)
	}
	else 
		PrintEl(num, current->left);

	return EXIT_SUCCESS;
}