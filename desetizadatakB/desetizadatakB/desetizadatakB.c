#define _CRT_SECURE_NO_WARNINGS
#include "desetizadatakB.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_SIZE 32
treeP CreateNewEl(char* name, Position head)
{
	
	treeP new = (treeP)malloc(sizeof(tree));
	if (!new)
	{
		perror("Couldn't allocate memory!");
		return NULL;
	}
	strcpy(new->stateName, name);
	new->left = NULL;
	new->right = NULL;
	new->cities = head;
	return new;
}
Position CreateListElement(char* City, int pop)
{
	Position newCity = NULL;
	newCity = (Position)malloc(sizeof(List));

	if (!newCity)
	{
		perror("Can't allocate memory!");
		return NULL;
	}
	strcpy_s(newCity->cityName, sizeof(newCity->cityName), City);
	newCity->population = pop;
	return newCity;
}
treeP ReadFromFile(char* fileName, treeP root)
{
	Position head = NULL;
	int check = 0;
	char State[MAX_SIZE] = { 0 }, CityFile[MAX_SIZE] = { 0 };
	FILE* dat = NULL;
	treeP newState = NULL;
	dat = fopen(fileName, "r");
	if (!dat)
	{
		perror("Can't open file");
		return NULL;
	}
	while (!feof(dat))
	{
		check = fscanf(dat, " %s %s", State, CityFile);
		if (check != 0)
		{
			perror("Couldn't read file");
			return NULL;
		}
		head = ReadCitiesFile(CityFile, head);
		newState = CreateNewEl(State,head);
		root = AddElToTree(newState, root);
		
	}
	fclose(dat);
	return root;
}
treeP AddElToTree(treeP newState, treeP current)
{
	if (!current)
		return newState;
	else if (strcmp(newState->stateName, current->stateName) < 0)
		current->left = AddElToTree(newState, current->left);
	else
		current->right = AddElToTree(newState, current->right);
	return current;
}
Position ReadCitiesFile(char* fileName, Position head)
{
	char CityName[MAX_SIZE] = { 0 };
	int Population = 0, check=0;
	FILE* dat = NULL;
	Position newCity = NULL;
	dat = fopen(fileName, "r");
	if (!dat)
	{
		perror("Can't open file");
		return 0;
	}
	while (!feof(dat))
	{
		check =fscanf(dat, " %s %d", CityName, &Population);
		if (check != 0)
		{
			perror("Couldn't read file");
			return NULL;
		}
		newCity = CreateListElement(CityName, Population);
		head = AddElToList(newCity, head);
	}
	fclose(dat);
	return head;
}
Position AddElToList(Position newCity, Position head)
{
	int f = 0;
	Position temp=head;
	if (!head)
		return newCity;
	else
		while (temp != NULL)
		{
			if (newCity->population < temp->population)
				InsertBefore(head,temp, newCity);
			else if (newCity->population == temp->population)
			{
				if (strcmp(newCity->cityName, temp->cityName) < 0)
					InsertBefore(head, temp, newCity);
				else
					InsertAfter(temp, newCity);
			}
			temp = temp->next;
		}
	temp = head;
	while (temp != NULL)
		if (strcmp(newCity->cityName, temp->cityName)==0)f = 1;
	if (f == 0)
		InsertBefore(head, temp, newCity);
	return head;

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
int FindState(char* stateName, treeP current, int pop)
{
	if (!current)
	{
		perror("No tree!");
		return NULL;
	}
	if (strcmp(stateName, current->stateName) == 0)
	{
		PrintGreater(current, pop);
		return EXIT_SUCCESS;
	}	
	else if (strcmp(stateName, current->stateName) < 0)
		FindState(stateName, current->left, pop);
	else if(strcmp(stateName, current->stateName) > 0)
		FindState(stateName, current->right, pop);
	else
	{
		perror("Couldn't find state");
		return EXIT_FAILURE;
	}

}
int PrintGreater(treeP current, int pop)
{
	Position temp = current->cities;
	printf("Cities with greater value are:");
	while (temp != NULL)
	{
		if (pop < temp->population)
			printf(" %s", temp->cityName);
		temp = temp->next;
	}
}