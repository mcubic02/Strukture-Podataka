#ifndef DESETIZADATAKB_H
#define DESETIZADATAKB_H

#define MAX_SIZE 32
struct _List;
typedef struct _List* Position;
typedef struct _List
{
	char cityName[MAX_SIZE];
	int population;
	Position next;
}List;
struct _tree;
typedef struct _tree* treeP;
typedef struct _tree
{
	char stateName[MAX_SIZE];
	treeP left;
	treeP right;
	Position cities;
}tree;



treeP CreateNewEl(char* name,Position head);
Position CreateListElement(char* City, int pop);
treeP ReadFromFile(char* fileName, treeP root);
Position ReadCitiesFile(char* fileName, Position head);
Position AddElToList(Position newCity, Position head);
treeP AddElToTree(treeP newState, treeP current);
int InsertBefore(Position head, Position position, Position newState);
Position FindBefore(Position head, Position position);
int InsertAfter(Position position, Position newElement);
int FindState(char* stateName, treeP current, int pop);
int PrintGreater(treeP current, int pop);
#endif // !DESETIZADATAKB_H
