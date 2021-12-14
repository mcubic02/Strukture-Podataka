
#ifndef OSMI_H
#define OSMI_H

struct _tree;
typedef struct _tree* treeP;
typedef struct _tree
{
	int num;
	treeP left;
	treeP right;
}tree;

treeP Insert(int n, treeP root);
treeP CreateNewEl(int n);
int PrintInOrder(treeP current);
int PrintPostOrder(treeP current);
int PrintPreOrder(treeP current);
treeP Delete(int n, treeP current);
treeP FindEl(int n, treeP current);
treeP FindMax(treeP current);


#endif