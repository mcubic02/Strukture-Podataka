
#define _CRT_SECURE_NO_WARNINGS
#include "desetiiA.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_SIZE 32

int main()
{
	char state[MAX_SIZE] = { 0 };
	int num = 0;
	char nazivDat[MAX_SIZE] = { 0 };
	treeP root = NULL;
	List Head = { .next = NULL, .stateName = {0} };
	Position p = &Head;
	printf("Upisite ime datoteke u koju zelite upisati:");
	scanf_s(" %s", nazivDat, sizeof(nazivDat));
	ReadListFromFile(nazivDat, p);
	Print(p);
	printf("Koju drzavu zelite pretrazivati?");scanf(" %s", state);
	printf("Upisite broj stanovnika:");scanf("%d", &num);
	Search(state, num,p);




}

