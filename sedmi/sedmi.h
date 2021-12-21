#ifndef SEDMI_H
#define SEDMI_H

#define MAX_SIZE 124

struct _Directory;
typedef struct _Directory* Position;
typedef struct _Directory {
	char name[MAX_SIZE];
	Position sibling;
	Position child;
}Directory;

struct _Stack;
typedef struct _Stack* StackPosition;
typedef struct _Stack {
	Position directory;
	StackPosition next;
}Stack;

Position Insert(Position current, Position newEl);
Position CreateNewDirectory(char name[]);
StackPosition CreateStackElement(Position directory);
int Push(StackPosition head, StackPosition newStackEl);
Position Pop(StackPosition head, Position current);
int PrintAllSubdirectories(Position current);
Position MoveToSubdirectory(Position current, char* destinationName, StackPosition stack);
int FreeMemory(Position root);
int UserEnteringInt();

#endif