#define _CRT_SECURE_NO_WARNINGS
#include "osmi_zadatak.h"
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
	else if (n < current->num)
		current->left = Insert(n, current->left);
	else
		current->right = Insert(n, current->right);
	return current;

}

int PrintInOrder(treeP current)
{
	if (!current)
		return 0;
	PrintInOrder(current->left);
	printf("%d", current->num);
	PrintInOrder(current->right);
	return 1;
}

int PrintPostOrder(treeP current)
{
	if (!current)
		return 0;
	PrintPostOrder(current->left);
	PrintPostOrder(current->right);
	printf("%d", current->num);
	return 1;
}

int PrintPreOrder(treeP current)
{
	if (!current)
		return 0;
	PrintPreOrder(current->left);
	PrintPreOrder(current->right);
	printf("%d", current->num);
	return 1;

}

treeP Delete(int n, treeP current)
{
	treeP temp = NULL;
	if (!current)
		return current;
	else if (n < current->num)
		current->left = Delete(n, current->left);
	else if (n > current->num)
		current->right = Delete(n, current->right);
	else
	{
		if (current->right && current->left)
		{
			temp = FindMax(current->left);
			current->num = temp->num;
			current->left = Delete(temp->num, current->left);
		}
		else
		{
			temp = current;
			if (!current->left)
				current = current->right;

			else if (!current->right)
				current = current->left;

			free(temp);
		}

	}


	return current;



}
treeP FindEl(int n, treeP current)
{
	if (!current)
		return current;
	else if (n < current->num)
		FindEl(n, current->left);
	else if (n > current->num)
		FindEl(n, current->right);
	else
		return NULL;
}
treeP FindMax(treeP current)
{
	while (current->right)
		current = current->right;
	return current;
}

