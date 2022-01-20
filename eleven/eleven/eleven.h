#ifndef ELEVEN_H
#define ELEVEN_H
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
typedef struct _List* ListH;
typedef struct _List
{
	char stateName[MAX_SIZE];
	treeP city;
	Position next;
}List;
struct _hashT;
typedef struct _hashT* hashP;
typedef struct _hashT
{
	int tabSize;
	ListH* hashList;
}hashT;

hashP Table(int tabSize);
int ReadFile(char* file, hashP H);
Position Find(char* key, int tabSize);
Position CreateListElement(char* State);
int InsertBefore(Position head, Position position, Position newState);
Position FindBefore(Position head, Position position);
int InsertAfter(Position position, Position newElement);
int AddTreeElement(char* fileName, Position newState);
treeP Insert(treeP newCity, treeP current);
treeP CreateNewEl(char* name, int pop);
int PrintTree(treeP current);
int Search(char* stateName, int num, hashP H);
int PrintEl(int num, treeP current);
int Print(hashP H);



#endif //ELEVEN_H!