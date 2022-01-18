#define _CRT_SECURE_NO_WARNINGS
#include "eleven.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define _CRT_SECURE_NO_WARNINGS

int ReadFromFiles(char* file, hashP H)
{
	char buffer[MAX_SIZE], State[MAX_SIZE], CityFile[MAX_SIZE];
	FILE* dat = NULL;
	int result = 0;

	dat = fopen(file, "r");
	if (!dat)
	{
		perror("Can't open file");
		return -1;
	}
	while (!feof(dat))
	{
		fscanf(dat, "%s %s", State, CityFile);

		InsertToHash(H, State, CityFile);
	}
	fclose(dat);
	return 0;
}
int InsertToHash(hashP H, char* State, char* CityFile)
{
	Position newEl = NULL;
	ListH L = NULL;
	int hashKey = Find(State, H->tabSize);

	newEl = CreateListElement(State);
	if (newEl == NULL)
		return -1;
	newEl->city = AddTreeElement(CityFile, newEl);

	
	if (!H->hashList[hashKey])
		H->hashList[hashKey] = newEl;
	else {
		L = H->hashList[hashKey];
		while (L->next != NULL && strcmp(L->next->stateName, State) < 0)
			L = L->next;
		InsertAfter(L, newEl);
	}
	return 0;
}
hashP Table(int tabSize)
{
	hashP H = NULL;
	int i = 0;

	H = (hashP)malloc(sizeof(hashT));

	if (H == NULL) {
		perror("Greska inicijalizacije memorije!");
		return NULL;
	}
	H->tabSize = tabSize;

	H->hashList = (List*)malloc(sizeof(List) * H->tabSize);
	if (H->hashList == NULL)
	{
		perror("Greska inicijalizacije memorije");
		return -1;
	}

	for (i = 0;i < H->tabSize;i++)
		H->hashList[i] = NULL;
	return H;	
}


Position Find(char key, hashP H)
{
	ListH temp;

	int index = whichKey(key, H->tabSize);
	temp = H->hashList[index];
	while (temp && temp->stateName != key)
		temp = temp->next;

	return temp;
}

Position CreateListElement(char* State)
{
	Position newState = NULL;
	newState = (Position)malloc(sizeof(List));

	if (!newState)
	{
		perror("Can't allocate memory!");
		return NULL;
	}

	strcpy(newState->stateName, State);

	return newState;
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
int AddTreeElement(char* fileName, Position newState)
{
	char CityName[MAX_SIZE] = { 0 };
	int Population = 0;
	treeP newCity = NULL;
	treeP root = NULL;
	FILE* dat = NULL;
	dat = fopen(fileName, "r");
	while (!feof(dat))
	{
		fscanf(dat, "%s %d", CityName, &Population);
		newCity = CreateNewEl(CityName, Population);
		root = Insert(newCity, root);
	}

	newState->city = root;

	return EXIT_SUCCESS;
}
treeP Insert(treeP newCity, treeP current)
{
	if (!current)
		return newCity;

	else if (newCity->population < current->population)
		current->left = Insert(newCity, current->left);

	else if (newCity->population == current->population)
	{
		if (strcmp(newCity->cityName, current->cityName) < 0)
			Insert(newCity, current->left);
		else
			Insert(newCity, current->right);
	}
	else
		current->right = Insert(newCity, current->right);
	return current;

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
int PrintTree(treeP current)
{

	if (!current) {
		return 0;
	}

	PrintTree(current->left);
	printf("\n\t\t %s", current->cityName);
	PrintTree(current->right);
	return 1;
}
int Search(char* stateName, int num, Position head)
{

	Position temp = head->next;
	Position temp1 = NULL;
	while (temp->next)
	{

		if (strcmp(temp->stateName, stateName) == 0)
			break;
		temp = temp->next;
		printf("\ntemp: %s", temp->stateName);
	}

	treeP current = temp->city;
	printf("\nGradovi sa vise od %d stanovnika:", num);
	PrintEl(num, current);

	return EXIT_SUCCESS;
}
int PrintEl(int num, treeP current)
{

	if (current)
	{

		PrintEl(num, current->left);
		if (current->population > num)
			printf(" %s", current->cityName);
		PrintEl(num, current->right);
	}


	return EXIT_SUCCESS;
}
int PrintAll(hashP H)
{
	ListH L = NULL;
	for (int i = 0; i < H->tabSize; i++) {
		L = H->hashList[i];
		if (L != NULL) {
			while (L != NULL) {
				printf("Drzava: %s\n", L->stateName);
				printf(" Grad:                Broj Stanovnika:\n");
				PrintTree(L->city);
				L = L->next;
			}
		}
	}
	return 0;
}