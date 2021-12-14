#define _CRT_SECURE_NO_WARNINGS
#include<string.h>
#include "osmi.h"
#include<stdio.h>
#include<stdlib.h>

int main()
{
	int o = 0,n=0;
	treeP root = NULL;
	treeP temp = NULL;
	
	do
	{
		printf("Choose:\n");
		printf("1-Insert new element\n2-Print inorder\n3-Print postorder\n4-Print preorder\n5-Delete element\n6-Find element\n7-Exit\n");
		scanf("%d", &o);
		

		switch (o)
		{
		case 1:
			printf("Write element you want to insert:");
			scanf("%d", &n);
			root = Insert(n, root);
			break;

		case 2:
			PrintInOrder(root);
			break;

		case 3:
			PrintPostOrder(root);
			break;

		case 4:
			PrintPreOrder(root);
			break;

		case 5:
			printf("Write element you want to delete:");
			scanf("%d", &n);
			root = Delete(n, root);
			break;
		case 6:
			printf("Write element you want to find:");
			scanf("%d", &n);
			temp = FindEl(n, root);
			if (temp)
				printf("Element %d is on adress %d \n", temp->num,temp);
			else printf("The element doesn't exist");
			break;
		case 7:
			break;
		default:
			printf("\nPogresan unos");

		}
	} while (o != 7);
	return EXIT_SUCCESS;
}