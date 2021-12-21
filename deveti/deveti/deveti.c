#define _CRT_SECURE_NO_WARNINGS
#include "deveti.h"
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

treeP CreateNewEl(int n)
{
	treeP new = (treeP)malloc(sizeof(tree));
	if (!new)
	{
		perror("Couldn't allocate memory!");
		return NULL;
	}
	new->num = n;
	new->left = NULL;
	new->right = NULL;
	return new;
}

treeP Insert(int n, treeP current)
{
	if (!current)
		return CreateNewEl(n);
	else if (n > current->num)
		current->left = Insert(n, current->left);
	else
		current->right = Insert(n, current->right);
	return current;

}

int replace(treeP current)
{
	int temp = 0;
	if (!(current->left && current->right))
	{
		temp = current->num;
		current->num = 0;
		return temp;
	}
	else if (current->left && current->right)
	{
		temp = current->num;
		current->num= replace(current->left) + replace(current->right);
		temp += current->num;
		return temp;
	}
	else if (!current->left && current->right)
	{
		temp = current->num;
		current->num = replace(current->right);
		temp += current->num;
		return temp;
	}
	else
	{
		temp = current->num;
		current->num = replace(current->left);
		temp += current->num;
		return temp;
	}
	return current->num;

}
Position CreateListElement(int number)
{
	Position newEl = NULL;
	newEl = (Position)malloc(sizeof(List));

	if (!newEl)
	{
		perror("Can't allocate memory!");
		return NULL;
	}

	newEl->number =number;
	newEl->next = NULL;
	return newEl;
}
int InsertInList(Position head, int number)
{
	Position temp = head;
	Position newEl = NULL;
	newEl = CreateListElement(number);
	if (!newEl)
	{
		perror("Can't allocate memory");
		return EXIT_FAILURE;
	}
	while (temp->next)
		temp = temp->next;

	newEl->next = temp->next;
	temp->next = newEl;

	return EXIT_SUCCESS;
}
int InsertTreeInList(treeP current, Position head)
{
	treeP temp = current;
	if (temp && temp->left)
		InsertTreeInList(temp->left, head);
	if (temp)
		InsertInList(head, temp->num);
	if (temp && temp->right)
		InsertTreeInList(temp->right, head);

	return EXIT_SUCCESS;
}
int InFile(Position Head1, Position Head2)
{
	FILE* file = NULL;
	Position temp = Head1->next;
	Position temp2 = Head1->next;


	file = fopen("binarytree.txt", "w");
	if (!file)
	{
		perror("Could not open file");
		return EXIT_FAILURE;
	}

	fprintf(file, "Poèetno stablo: \n");

	while (temp)
	{
		fprintf(file, "%d ", temp->number);
		temp = temp->next;
	}
	fprintf(file, "\n");

	fprintf(file, "Stablo nakon izmjena vrijednosti: \n");
	while (temp2)
	{
		fprintf(file, "%d ", temp2->number);
		temp2 = temp2->next;
	}

	fclose(file);
	return EXIT_SUCCESS;
}