#define _CRT_SECURE_NO_WARNINGS
#include "desetizadatakB.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_SIZE 32
int main()
{
	treeP root = NULL;
	char StatesFileName[MAX_SIZE] = { 0 }, stateName[MAX_SIZE] = { 0 };
	int pop = 0;
	printf("Which file do you want to read from?");
	scanf(" %s", StatesFileName);
	root = ReadFromFile(StatesFileName, root);
	printf("Enter which state do you want to search:");
	scanf(" %s", stateName);
	printf("Finding cities with greater population than:");
	scanf("%d", &pop);
	FindState(stateName, root, pop);
	return 0;
}