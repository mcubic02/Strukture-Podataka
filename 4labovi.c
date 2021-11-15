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
int CitajPolinom(char *buffer, listPoli p);
int Sortiraj(listPoli novi, listPoli p);
listPoli NoviPolinom(int k, int e);
int UmetniNakon(listPoli pozicija, listPoli novi);
listPoli PronadiPrije(listPoli p,listPoli element);
int Izbrisi(listPoli p, listPoli element);
int DodajNakon(listPoli prosli, listPoli element);
int Ispis(listPoli first);
int Zbroji(listPoli Zbroj, listPoli p1, listPoli p2);
int Mnozenje(listPoli Umnozak, listPoli p1, listPoli p2);

int main()
{

Polinom P1 = { .next = NULL, .koef = 0, .eks = 0 };
listPoli p1 = &P1;

Polinom P2 = { .next = NULL , .koef = 0, .eks = 0 };
listPoli p2 = &P2;


Polinom _zbroj= { .next = NULL , .koef = 0, .eks = 0 };
listPoli zbroj = &_zbroj;

Polinom _umnozak = { .next = NULL , .koef = 0, .eks = 0 };
listPoli umnozak = &_umnozak;

char nazivDat[]="polinomi";
CitajDatoteku(nazivDat, p1, p2);
Ispis(p1 -> next);
Ispis(p2 -> next);
Zbroji(zbroj, p1, p2);
Ispis(zbroj->next);
Mnozenje(umnozak, p1, p2);
Ispis(umnozak->next);

return 0;
}
int CitajDatoteku(char* imeDat, listPoli p1, listPoli p2)
{
    char buffer1[MAX_SIZE]={0};
    char buffer2[MAX_SIZE]={0};

    FILE* dat=NULL;
    dat = fopen(imeDat, "r");

    if (!dat){
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
int CitajPolinom(char *buffer, listPoli p)
{
    int koef=0, eks=0, pok=0, n=0;
    listPoli temp = NULL;

    while(buffer[pok]!='\0'){
        
        sscanf(buffer + pok, " %d %d %n", &koef, &eks, &n);
        pok+=n;
    
        temp=NoviPolinom(koef,eks);
        
        if(temp==NULL){
            perror("Can't allocate ");
            return -2;
        }
       
        Sortiraj(temp, p);
        printf("Sortirano!");
        
     }
     return EXIT_SUCCESS;
}
listPoli NoviPolinom(int k, int e){
    listPoli novi = NULL;
    novi = (listPoli) malloc (sizeof(listPoli));

    if(!novi)
    {
        perror("Can't allocate novii");
        return NULL;
    }

    novi -> koef = k;
    novi -> eks = e;
    novi -> next = NULL;

    return novi;
    free(novi);
}

int Sortiraj(listPoli novi, listPoli p)
{
    listPoli temp=p->next;
    listPoli pom = NULL;
    
    if(!temp)
    {
        UmetniNakon(p,novi);
        printf("Prvi element");
    }
    else
    {
        while((novi->eks < temp->eks) && temp) temp = temp->next;

        if((novi -> eks == temp -> eks) && temp)
        {
            if(temp->koef + novi->koef)temp->koef += novi -> koef;
            else
            {
                Izbrisi(temp,p);
                free(novi);
            }
        }
        else
        {
            pom = PronadiPrije(p, temp);
            DodajNakon(pom, novi);

        }
    }
    return EXIT_SUCCESS;
    
}
int UmetniNakon(listPoli pozicija, listPoli novi)
{
	novi->next = pozicija->next;
	pozicija->next = novi;
	return EXIT_SUCCESS;
}
int Izbrisi(listPoli p, listPoli element)
{
	listPoli delete = element;
	listPoli temp = NULL;

	
	if (delete)
	{
		temp = PronadiPrije(p, delete);
		temp->next = delete -> next;
		free(element);

	}

	return EXIT_SUCCESS;

}
listPoli PronadiPrije(listPoli p, listPoli element)
{   
    listPoli temp = NULL;
    temp = p;
	while (temp->next != element)temp = temp -> next;

	return temp;
}
int DodajNakon(listPoli prosli, listPoli element)
{

    element -> next = prosli->next;
	prosli->next = element;
	return EXIT_SUCCESS;
}
int Ispis(listPoli first)
{
    listPoli temp = first;
    while(temp!=NULL)
    {
        printf("%dx^%d", temp -> koef,temp -> eks);
        temp = temp -> next;
    }
    return EXIT_SUCCESS;
}
int Zbroji(listPoli Zbroj, listPoli p1, listPoli p2)
{
    listPoli temp1 = p1->next;
    listPoli temp2 = p2 -> next;
    listPoli novi=NULL;
    listPoli pom = NULL;
    while(temp1 != NULL && temp2 != NULL)
    {
        if(temp1 -> eks == temp2 -> eks)
        {
            novi=NoviPolinom(temp1->koef+temp2->koef,temp1
             -> eks);
             Sortiraj(novi, Zbroj);
             temp1 = temp1 -> next;
             temp2 = temp2 -> next;
        }
        else if(temp1 -> eks < temp2 -> eks)
        {
            novi=NoviPolinom(temp1 -> koef, temp1 -> eks);
            Sortiraj(novi, Zbroj);
            temp1 = temp1 -> next;
        }
        else
        {
            novi=NoviPolinom(temp2 -> koef, temp2 -> eks);
            Sortiraj(novi, Zbroj);
            temp2= temp2 -> next;
        }
        
    }
    if(temp1 == NULL)pom = temp2;
    else pom = temp1;
    while(pom != NULL)
    {
        novi = NoviPolinom(pom->koef, pom -> eks);
        Sortiraj(novi, Zbroj);
        pom = pom -> next;
    }
    return EXIT_SUCCESS;
}
int Mnozenje(listPoli Umnozak, listPoli p1, listPoli p2)
{
    listPoli temp1 = p1;
    listPoli temp2 = p2;
    listPoli novi = NULL;
    while(temp1)
    {
        while(temp2)
        {
            novi = NoviPolinom(temp1 -> koef * temp2 -> koef, temp1 -> eks + temp2 -> eks);
            Sortiraj(novi, Umnozak);
            temp2 = temp2 -> next;
        }
        temp1 = temp1 -> next;

    }
}
