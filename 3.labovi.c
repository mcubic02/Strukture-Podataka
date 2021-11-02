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
int InsertPersonAfter(Position head, Position position, char* name, char* surname, int birthYear);
int InsertPersonBefore(Position first, Position position, char* name, char* surname, int birthYear);
int InputDat(Position first, char* nazivDat);
int ReadDat(Position head, char* nazivDat);
int SortedList(Position head, char* name, char* surname, int birthYear);
int SortList(Position first, Position pSort);

int main(int argc, char** argv) {

	Person Head = { .next = NULL, .name = {0}, .surname = {0}, .birthYear = 0 };
	Position p = &Head;

	Person HeadSorted = { .next = NULL,.name = {0},.surname = {0},.birthYear = 0 };
	Position pSort = &HeadSorted;

	char name[MAX_SIZE] = { 0 };
	char surname[MAX_SIZE] = { 0 };
	int birthYear = 0;
	int input = 0;
	Position position = NULL;
	char nazivDat[MAX_SIZE] = { 0 };



	Position Search = NULL;
	do
	{
		printf("Odaberite radnju: 1-dodavanje na pocetak, 2-ispis liste, 3-dodavanje na kraj liste, 4-pronalazak po prezimenu, 5-brisanje elementa, 6-dodavanje elementa iza zeljenog, 7-dodavanje elementa ispred zeljenog, 8-sortiranje po prezimenu, 9-upisivanje u datoteku, 10-citanje iz datoteke, 0-izlaz");
		scanf_s("%d", &input);
		if (input < 0 && input>7)printf("Ta opcija ne postoji");
		else if (input == 1) {
			printf("Upisi novu osobu :\n");
			printf("Name:");scanf_s(" %s", name, sizeof(name));
			printf("Surname:");scanf_s(" %s", surname, sizeof(surname));
			printf("Birth year:");scanf_s("%d", &birthYear);
			PrependList(p, name, surname, birthYear);
		}
		else if (input == 2)PrintList(p->next);
		else if (input == 3)
		{
			printf("Upisi novu osobu :\n");
			printf("Name:");scanf_s(" %s", &name, sizeof(name));
			printf("Surname:");scanf_s(" %s", &surname, sizeof(surname));
			printf("Birth year:");scanf_s("%d", &birthYear);
			AppendList(p->next, name, surname, birthYear);


		}
		else if (input == 4) {
			printf("Upisi prezime koje zelis pronaci:");
			scanf_s(" %s", &surname, sizeof(surname));
			Search = FindBySurname(p, surname);
			if (Search)printf(" %s %s %d", name, surname, birthYear);
			else printf("Nema trazengo prezimena");
		}
		else if (input == 5)
		{
			printf("Upisi prezime osobe koju zelis izbrisati:");
			scanf_s(" %s", &surname, sizeof(surname));
			Delete(p, surname);
		}
		else if (input == 6)
		{
			printf("Upisi prezime osobe iza koje zelis dodati element:");scanf_s(" %s", surname, sizeof(surname));
			position = FindBySurname(p, surname);
			if (position)
			{
				printf("Upisi novu osobu :\n");
				printf("Name:");scanf_s(" %s", name, sizeof(name));
				printf("Surname:");scanf_s(" %s", surname, sizeof(surname));
				printf("Birth year:");scanf_s("%d", &birthYear);
				InsertPersonAfter(p, position, name, surname, birthYear);
			}
			else printf("Nema osobe s tim prezimenom.");
		}
		else if (input == 7)
		{
			printf("Upisi prezime osobe ispred koje zelis dodati element:");scanf_s(" %s", surname, sizeof(surname));
			position = FindBySurname(p, surname);
			if (position)
			{
				printf("Upisi novu osobu :\n");
				printf("Name:");scanf_s(" %s", name, sizeof(name));
				printf("Surname:");scanf_s(" %s", surname, sizeof(surname));
				printf("Birth year:");scanf_s("%d", &birthYear);
				InsertPersonBefore(p->next, position, name, surname, birthYear);
			}
			else printf("Nema osobe s tim prezimenom.");
		}
		else if (input == 8)
		{
			SortList(p->next, pSort->next);
		}
		else if (input == 9)
		{
			printf("Upisite ime datoteke u koju zelite upisati:");
			scanf_s(" %s", nazivDat, sizeof(nazivDat));
			InputDat(p->next, nazivDat);
		}
		else
		{
			printf("Upisite ime datoteke koju zelite procitati:");
			scanf_s(" %s", nazivDat, sizeof(nazivDat));
			ReadDat(p->next, nazivDat);
		}



	} while (input != 0);

	return EXIT_SUCCESS;
}
int PrependList(Position head, char* name, char* surname, int birthYear) {
	Position newPerson = NULL;

	newPerson = CreatePerson(name, surname, birthYear);
	InsertAfter(head, newPerson);
	SortedList(head, name, surname, birthYear);
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
	strcpy_s(newPerson->name, sizeof(newPerson->name), name);
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
	Position temp = NULL;
	temp = FindLast(head);

	newPerson = CreatePerson(name, surname, birthYear);
	InsertAfter(temp, newPerson);
	SortedList(head, name, surname, birthYear);
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
		if (strcmp(temp->surname, surname) == 0)return temp;
		temp = temp->next;
	}
	return temp;
}
int Delete(Position head, char* surname)
{
	Position deletePerson = NULL;
	Position temp = NULL;

	deletePerson = FindBySurname(head, surname);
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
int InsertPersonAfter(Position head, Position position, char* name, char* surname, int birthYear)
{
	Position newPerson = NULL;
	newPerson = CreatePerson(name, surname, birthYear);
	InsertAfter(position, newPerson);
	SortedList(head, name, surname, birthYear);
	return EXIT_SUCCESS;
}
int InsertPersonBefore(Position first, Position position, char* name, char* surname, int birthYear)
{
	Position newPerson = NULL;
	Position before = NULL;
	Position head = NULL;
	newPerson = CreatePerson(name, surname, birthYear);
	before = FindBefore(first, position);
	InsertAfter(before, newPerson);
	head = FindBefore(head, first);
	SortedList(head, name, surname, birthYear);
	return EXIT_SUCCESS;
}
int InputDat(Position first, char* nazivDat)
{
	Position temp = first;
	FILE* dat = NULL;
	dat = fopen(nazivDat, "w");
	if (!dat)
	{
		perror("Ne moze se otvoriti datoteka");
		return -1;
	}
	while (temp)
	{
		fprintf(dat, " %s %s %d \n", temp->name, temp->surname, temp->birthYear);
		temp = temp->next;

	}
	fclose(dat);
	return EXIT_SUCCESS;
}
int ReadDat(Position head, char* nazivDat)
{
	FILE* dat = NULL;
	char name[MAX_SIZE] = { 0 };
	char surname[MAX_SIZE] = { 0 };
	int birthYear = 0;

	dat = fopen( nazivDat, "r");
	if (!dat)
	{
		perror("Ne moze se otvoriti datoteka");
		return -1;
	}
	char buffer[100] = { 0 };
	Position temp = head;
	while (!feof(dat))
	{
		if (fgets(buffer, 100, dat))
		{
			if (sscanf(buffer, " %s %s %d", name, surname, &birthYear) == 3)AppendList(head, name, surname, birthYear);
		}
	}
	fclose(dat);
	return EXIT_SUCCESS;

}
int SortedList(Position head, char* name, char* surname, int birthYear)
{
	Position newPerson = NULL;
	newPerson = CreatePerson(name, surname, birthYear);

	Position temp = NULL;
	temp = head->next;

	Position previous = NULL;

	if (!newPerson)return -1;
	if (!temp)InsertAfter(head, newPerson);

	else
	{
		while (temp && (strcmp(surname, temp->surname) > 0))
			temp = temp->next;

		previous = FindBefore(head, temp);
		InsertAfter(previous, newPerson);

	}
	return EXIT_SUCCESS;
}
int SortList(Position first, Position pSort)
{
	Position temp = NULL;
	Position sortTemp = NULL;

	temp = first;
	sortTemp = pSort;

	while (temp)
	{
		strcpy(temp->name, sortTemp->name);
		strcpy(temp->surname, sortTemp->surname);
		temp->birthYear = sortTemp->birthYear;

		temp = temp->next;
		sortTemp = sortTemp->next;
	}
	return EXIT_SUCCESS;
}


