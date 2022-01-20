#define _CRT_SECURE_NO_WARNINGS
#include "eleven.h"
#include<stdio.h>
#include<stdlib.h>

int main()
{
	char fileName[MAX_SIZE] = "drzave.txt", state[MAX_SIZE] = { 0 };

	int tabSize = 11, num=0;
	hashP H = NULL;
	H = Table(tabSize);
	ReadFile(fileName, H);
	Print(H);
	printf("\nKoju drzavu zelite pretrazivati ? ");
	scanf(" %s", state);
	printf("\nUpisite broj stanovnika:");
	scanf("%d", &num);
	Search(state, num, H);
	return 0;
}