#define _CRT_SECURE_NO_WARNINGS
#include "peti.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
	//char fileName = { 0 };
	double result = 0;
	/*printf("Enter file name:");
	scanf(" %s", fileName);*/
	CalculatePostfixFile(&result, "postfix.txt");
	printf("Result is %.2lf", result);
	return EXIT_SUCCESS;
}