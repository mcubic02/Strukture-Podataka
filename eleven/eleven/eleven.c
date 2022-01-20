#define _CRT_SECURE_NO_WARNINGS
#include "eleven.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define _CRT_SECURE_NO_WARNINGS

hashP Table(int tabSize)
{
	
	hashP H = NULL;
	int i = 0;

	H = (hashP)malloc(sizeof(hashT));

	if (H == NULL) {
		perror("Couldn't allocate!");
		return NULL;
	}
	H->tabSize = tabSize;
	
	H->hashList = (List*)malloc(sizeof(List) * H->tabSize);
	if (H->hashList == NULL)
	{
		perror("Couldn't allocate!");
		return -1;
	}

	for (i = 0;i < H->tabSize;i++)
		H->hashList[i] = NULL;
	
	return H;
}

int ReadFile(char* file, hashP H)
{

	char buffer[MAX_SIZE], State[MAX_SIZE], CityFile[MAX_SIZE] = {0};
	FILE* dat = NULL;
	int result = 0;

	dat = fopen(file, "r");
	int i = 0;

	if (!dat)
	{
		perror("Can't open file");
		return -1;
	}
	while (!feof(dat))
	{
		printf("\nU while %d. put", i + 1);
		i++;
		fscanf(dat, "%s %s", State, CityFile);
		InsertToHash(H, State, CityFile);
	}
	fclose(dat);
	return 0;
}
int InsertToHash(hashP H, char* State, char* CityFile)
{
	Position newEl = NULL;
	ListH H1 = NULL;
	int tabSize = H->tabSize;
		int hashKey = Find(State, H->tabSize);
	newEl = CreateListElement(State);
	if (newEl == NULL)
		return -1;
	AddTreeElement(CityFile, newEl);

	
	if (!H->hashList[hashKey])
		H->hashList[hashKey] = newEl;
	else {
		H1 = H->hashList[hashKey];
		while (H1->next && strcmp(H1->next->stateName, State) < 0)
			H1 = H1->next;
		InsertAfter(H1, newEl);
	}
	return 0;
}

Position Find(char* stateName, int tabSize)
{
	
	int res = 0;
	
	for (int i = 0; i < 5; i++) {

		if (stateName[i] == '\0')
			break;	
		res += stateName[i];
	}
	
	return (res % tabSize);
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
int Search(char* stateName, int num, hashP H)
{
	ListH F = NULL;
	ListH H1 = NULL;
	int i = 0;
	i = Find(stateName, H->tabSize);
	H1 = H->hashList[i];
	while (H1 != NULL) {
		if (strcmp(H1->stateName, stateName) == 0) {
			ListH F = H1;
		}
		H1 = H1->next;
	}


	treeP current = F->city;
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
int Print(hashP H)
{
	ListH H1 = NULL;
	for (int i = 0; i < H->tabSize; i++) {
		H1 = H->hashList[i];
		
			while (H1) {
				printf("\n%s", H1->stateName);
				PrintTree(H1->city);
				H1 = H1->next;
			}
		
	}
	return 0;
}