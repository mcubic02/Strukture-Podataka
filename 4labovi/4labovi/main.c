#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_SIZE 1024

struct Polinom_;

typedef struct Polinom_* listPoli;
typedef struct Polinom_ {
    int koef;
    int eks;
    listPoli next;
}Polinom;

//int Zbroj(listPoli p1, listPoli p2);
int CitajDatoteku(char* imeDat, listPoli p1, listPoli p2);
int CitajPolinom(char* buffer, listPoli p);
int Sortiraj(listPoli novi, listPoli p);
listPoli NoviPolinom(int k, int e);
int UmetniNakon(listPoli pozicija, listPoli novi);
listPoli PronadiPrije(listPoli p, listPoli element);
int Izbrisi(listPoli p, listPoli element);
int Ispis(listPoli first);
int Zbroji(listPoli Zbroj, listPoli p1, listPoli p2);
int Mnozenje(listPoli Umnozak, listPoli p1, listPoli p2);

int main()
{

    Polinom P1 = { .next = NULL, .koef = 0, .eks = 0 };
    listPoli p1 = &P1;

    Polinom P2 = { .next = NULL , .koef = 0, .eks = 0 };
    listPoli p2 = &P2;


    Polinom _zbroj = { .next = NULL , .koef = 0, .eks = 0 };
    listPoli zbroj = &_zbroj;

    Polinom _umnozak = { .next = NULL , .koef = 0, .eks = 0 };
    listPoli umnozak = &_umnozak;

    char nazivDat[] = "polinomi.txt";
    CitajDatoteku(nazivDat, p1, p2);
    Ispis(p1->next);
    Ispis(p2->next);
    Zbroji(zbroj, p1, p2);
    Ispis(zbroj->next);
    Mnozenje(umnozak, p1, p2);
    Ispis(umnozak->next);

    return 0;
}
int CitajDatoteku(char* imeDat, listPoli p1, listPoli p2)
{
    char buffer1[MAX_SIZE] = { 0 };
    char buffer2[MAX_SIZE] = { 0 };
    //printf("\nUslo u citaj datoteku");
    FILE* dat = NULL;
    dat = fopen(imeDat, "r");

    if (!dat) {
        perror("Greska pri otvaranju datoteke");
        return -1;
    }

    fgets(buffer1, MAX_SIZE, dat);
    CitajPolinom(buffer1, p1);
    fgets(buffer2, MAX_SIZE, dat);
    CitajPolinom(buffer2, p2);
    fclose(dat);
    return EXIT_SUCCESS;
}
int CitajPolinom(char* buffer, listPoli p)
{
    //printf("\nUslo u citaj polinom");
    int koef = 0, eks = 0, pok = 0, n = 0;
    listPoli temp = NULL;

    while (buffer[pok] != '\0') {
        //printf("\nUslo u While");
        sscanf(buffer + pok, " %d %d %n", &koef, &eks, &n);
        pok += n;
        //printf("\nprije novi polinom");
        temp = NoviPolinom(koef, eks);
        //printf("\nposlije novi polinom");
        if (temp == NULL) {
            perror("Can't allocate ");
            return -2;
        }

        Sortiraj(temp, p);
        printf("\nSortirano!");

    }
    return EXIT_SUCCESS;
}
listPoli NoviPolinom(int k, int e) {
    listPoli novi = NULL;
    novi = (listPoli)malloc(sizeof(Polinom));
    //printf("\nUslo u Novi polinom");
    if (!novi)
    {
        perror("Can't allocate novii");
        return NULL;
    }
    novi->koef = k;
    novi->eks = e;
    novi->next = NULL;

    return novi;
    free(novi);
}

int Sortiraj(listPoli element, listPoli head)
{
    //printf("\nUslo u Sortiraj");
    listPoli temp = head->next, prethodni = NULL;
 
    while ((temp != NULL) && ((element->eks) < (temp->eks)))
        temp = temp->next;

    if (temp != NULL && (element->eks == temp->eks)) {

        if (temp->koef + element->koef) {

            temp->koef = temp->koef + element->koef;
        }

        else {

            Izbrisi(temp, head);
            free(element);
        }
    }

    else {

        prethodni = PronadiPrije(head, temp);
        UmetniNakon(prethodni, element);
    }

    return EXIT_SUCCESS;

}
int UmetniNakon(listPoli pozicija, listPoli novi)
{
   // printf("\nUslo u umetni nakon");
    novi->next = pozicija->next;
    pozicija->next = novi;
    return EXIT_SUCCESS;
}
int Izbrisi(listPoli p, listPoli element)
{
   // printf("\nUslo u izbrisi");
    listPoli delete = element;
    listPoli temp = NULL;


    if (delete)
    {
        temp = PronadiPrije(p, delete);
        temp->next = delete->next;
        free(element);

    }

    return EXIT_SUCCESS;

}
listPoli PronadiPrije(listPoli p, listPoli element)
{
   // printf("\nUslo u pronadi prije");
    listPoli temp = NULL;
    temp = p;
    while (temp->next != element)temp = temp->next;

    return temp;
}

int Ispis(listPoli first)
{
   // printf("\nUslo u ispis");
    printf("\n");
    listPoli temp = first;
    while (temp != NULL)
    {
        printf("\t%dx^%d", temp->koef, temp->eks);
        temp = temp->next;
    }
    printf("Ispisani elementi");
    return EXIT_SUCCESS;
}
int Zbroji(listPoli Zbroj, listPoli p1, listPoli p2)
{
   // printf("\nUslo u zbroji");
    listPoli temp1 = p1->next;
    listPoli temp2 = p2->next;
    listPoli novi = NULL;
    listPoli pom = NULL;
    while (temp1 != NULL && temp2 != NULL)
    {
        if (temp1->eks == temp2->eks)
        {
            novi = NoviPolinom(temp1->koef + temp2->koef, temp1->eks);
            Sortiraj(novi, Zbroj);
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
        else if (temp1->eks < temp2->eks)
        {
            novi = NoviPolinom(temp1->koef, temp1->eks);
            Sortiraj(novi, Zbroj);
            temp1 = temp1->next;
        }
        else
        {
            novi = NoviPolinom(temp2->koef, temp2->eks);
            Sortiraj(novi, Zbroj);
            temp2 = temp2->next;
        }

    }
    if (temp1 == NULL)pom = temp2;
    else pom = temp1;
    while (pom != NULL)
    {
        novi = NoviPolinom(pom->koef, pom->eks);
        Sortiraj(novi, Zbroj);
        pom = pom->next;
    }
    return EXIT_SUCCESS;
}
int Mnozenje(listPoli Umnozak, listPoli p1, listPoli p2)
{
    printf("\nUslo u mnozenje");
    listPoli temp1 = p1->next;
    listPoli temp2 = p2->next;
    listPoli novi = NULL;
    while (temp1)
    {
      //  printf("\nUslo u temp1");
        temp2 = p1;
        while (temp2)
        {
           // printf("\nUslo u temp2");
            novi = NoviPolinom(temp1->koef * temp2->koef, temp1->eks + temp2->eks);
            Sortiraj(novi, Umnozak);
            temp2 = temp2->next;
        }
        temp1 = temp1->next;

    }
    return EXIT_SUCCESS;
}