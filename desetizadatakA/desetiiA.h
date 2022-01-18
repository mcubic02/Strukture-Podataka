#ifndef DESETIIA_H
#define DESETIIA_H
#define MAX_SIZE 32
struct _tree;
typedef struct _tree* treeP;
typedef struct _tree
{
	char cityName[MAX_SIZE];
	int population;
	treeP left;
	treeP right;
}tree;

struct _List;
typedef struct _List* Position;
typedef struct _List
{
	char stateName[MAX_SIZE];
	treeP city;
	Position next;
}List;

Position CreateListElement(char* State);
int ReadListFromFile(char* fileName, Position head);
Position CreateListElement(char* State);
int AddListElement(Position head, Position newState);
int InsertBefore(Position head, Position position, Position newState);
Position FindBefore(Position head, Position position);
int InsertAfter(Position position, Position newElement);
int Print(Position head);
int Search(char* stateName, int num,Position head);
treeP Insert(treeP newCity, treeP current);
treeP CreateNewEl(char* name, int pop);
int AddTreeElement(char* fileName, Position newState);
int PrintEl(int num, treeP current);

#endif