#ifndef DEVETI_H
#define DEVETI_H

struct _tree;
typedef struct _tree* treeP;
typedef struct _tree
{
	int num;
	treeP left;
	treeP right;
}tree;

struct _List;
typedef struct _List* Position;
typedef struct _List
{
	int number;
	Position next;
}List;


treeP Insert(int n, treeP current);
treeP CreateNewEl(int n);
int replace(treeP current);
int InsertInList(Position head, int number);
int InsertTreeInList(treeP current, Position head);
int InFile(Position Head1, Position Head2);
#endif
