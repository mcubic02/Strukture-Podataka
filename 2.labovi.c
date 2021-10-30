#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define _CRT_SECURE_NO_WARNINGS
#define MAX_SIZE 50

struct _Person;
typedef struct _Person* Position;
typedef struct _Person {
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	int birthYear;
	Position next;
	
}Person;

int PrependList(Position head, char* name, char* surname, int birthYear);
Position CreatePerson(char* name, char* surname, int birthYear);
int InsertAfter(Position position, Position newPerson);
int PrintList(Position first);
int AppendList(Position first, char* name, char* surname, int birthYear);
Position FindLast(Position head);
Position FindBySurname(Position head, char* surname);
int Delete(Position head, char* surname);
Position FindBefore(Position first, Position position);

int main(int argc, char**argv) {

	Person Head = { .next = NULL, .name = {0}, .surname = {0}, .birthYear = 0 };
	Position p = &Head;
	char name[MAX_SIZE] = { 0 };
	char surname[MAX_SIZE] = { 0 };
	int birthYear = 0;
	int input = 0;
	Position Search = NULL;
	do
	{
		printf("Odaberite radnju: 1-dodavanje na pocetak, 2-ispis liste, 3-dodavanje na kraj liste, 4-pronalazak po prezimenu, 5-brisanje elementa, 0-izlaz");
		scanf_s("%d", &input);
			if (input == 1) {
				printf("Upisi novu osobu :\n");
				printf("Name:");scanf_s(" %s", name,sizeof(name));
				printf("Surname:");scanf_s(" %s", surname, sizeof(surname));
				printf("Birth year:");scanf_s("%d", &birthYear);
				PrependList(p, name, surname, birthYear);
			}
			else if (input == 2)PrintList(p->next);
			else if (input == 3) 
			{
				printf("Upisi novu osobu :\n");
				printf("Name:");scanf_s(" %s", &name,sizeof(name));
				printf("Surname:");scanf_s(" %s", &surname,sizeof(surname));
				printf("Birth year:");scanf_s("%d", &birthYear);
				AppendList(p->next, name, surname, birthYear);


			}
			else if (input == 4) {
				printf("Upisi prezime koje zelis pronaci:");
				scanf_s(" %s", &surname,sizeof(surname));
				Search = FindBySurname(p, surname);
				if (Search)printf(" %s %s %d", name, surname, birthYear);
				else printf("Nema trazengo prezimena");
			}
			else
			{
				printf("Upisi prezime osobe koju zelis izbrisati:");
				scanf_s(" %s", &surname,sizeof(surname));
				Delete(p, surname);
			}

	} while (input != 0 && input > 0 && input < 6);

	return EXIT_SUCCESS;
}
int PrependList(Position head, char* name, char* surname, int birthYear) {
	Position newPerson = NULL;
	
	newPerson=CreatePerson(name, surname, birthYear);
	InsertAfter(head, newPerson);

	return EXIT_SUCCESS;
}
Position CreatePerson(char* name, char* surname, int birthYear)
{
	Position newPerson = NULL;
	newPerson = (Position)malloc(sizeof(Person));

	if (!newPerson)
	{
		perror("Can't allocate memory!");
		return NULL;
	}
	strcpy_s(newPerson->name,sizeof(newPerson->name), name);
	strcpy_s(newPerson->surname, sizeof(newPerson->surname), surname);
	newPerson->birthYear = birthYear;
	return newPerson;
}
int InsertAfter(Position position, Position newPerson)
{
	newPerson->next = position->next;
	position->next = newPerson;
	return EXIT_SUCCESS;
}
int PrintList(Position first)
{
	Position temp = first;
	while (temp)
	{
		printf("Name: %s Surname: %s Birth year: %d\n", temp->name, temp->surname, temp->birthYear);
		temp = temp->next;
	}
	
	return EXIT_SUCCESS;
}
int AppendList(Position head, char* name, char* surname, int birthYear)
{
	Position newPerson = NULL;
	Position temp=NULL;
	temp=FindLast(head);
	
	newPerson = CreatePerson(name, surname,    birthYear);
	InsertAfter(temp, newPerson);
	
	return EXIT_SUCCESS;
}
Position FindLast(Position head)
{
	Position temp = head;
	while (temp->next != NULL)temp = temp->next;
	return temp;
}
Position FindBySurname(Position head, char* surname)
{

	Position temp = head;
	while (temp)
	{
		if (strcmp(temp->surname, surname)==0)return temp;
		temp = temp->next;
	}
	return temp;
}
int Delete(Position head, char* surname)
{
	Position deletePerson = NULL;
	Position temp = NULL;

	deletePerson=FindBySurname(head, surname);
	if (deletePerson)
	{
		temp = FindBefore(head, deletePerson);
		temp->next = deletePerson->next;
		free(deletePerson);

	}
	else printf("Nema trazenog prezimena");

	return EXIT_SUCCESS;

}
Position FindBefore(Position head, Position position)
{
	Position temp = head;
	while (temp->next != position)temp = temp->next;
	return temp;

}
