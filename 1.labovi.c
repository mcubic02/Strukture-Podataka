#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SIZE 128
#define MAX_LINE 1024

typedef struct _student{
    char ime[MAX_SIZE];
    char prezime[MAX_SIZE];
    double bodovi;
}student;
int ProcitajBrojRedakaIzDatoteke(char* nazivDatoteke);
student* AlocirajMemorijuProcitajStudente(int brojStudenata, char* nazivDatoteke);
void IspisStudenataIzDatoteke(student* studenti,int brojStudenata,double max);
int MaxBrBd(int brojStudenata, student* studenti);
int main()
{
    int brojStudenata;
    double max;
   
    student *studenti = NULL;
    char* datoteka="studenti.txt";
    brojStudenata=ProcitajBrojRedakaIzDatoteke(datoteka);
    studenti=AlocirajMemorijuProcitajStudente(brojStudenata,datoteka);
    max=int MaxBrBd(brojStudenata,studenti);
    IspisStudenataIzDatoteke(studenti,brojStudenata,max);



    return 0;
}
double MaxBrBd(int brojStudenata, student* studenti)
{
    int i,f=0;
    int max;
    max=studenti[0].bodovi;
    for(i=1;i<brojStudenata;i++)
    {
        if(studenti[i].bodovi>max) max=studenti[i].bodovi;
    }
    return max;
}

int ProcitajBrojRedakaIzDatoteke(char* nazivDatoteke)
{
    int brojac = 0;
    FILE* datoteka = NULL;
    char buffer[MAX_LINE] = {0};

    datoteka=fopen(nazivDatoteke,"r");
    if(!datoteka)
    {
        printf("Greska!/n");
        return -1;
    }
    while(!feof(datoteka))
    {
        fgets(buffer, MAX_LINE, datoteka);
        brojac++;
    }
    fclose(datoteka);

    return brojac;
}

student* AlocirajMemorijuProcitajStudente(int brojStudenata, char* nazivDatoteke)
{
    int brojac=0;
    FILE* datoteka = NULL;
    student* studenti = NULL;

    studenti = (student*)malloc(brojStudenata * sizeof(student));
    datoteka=fopen(nazivDatoteke, "r");
    if(!datoteka)
    {
        printf("Greska alociranja!/n");
        free(studenti);
        return NULL;
    }
    while(!feof(datoteka))
    {
       
        fscanf(datoteka," %s %s %lf",studenti[brojac].ime, studenti[brojac].prezime, &studenti[brojac].bodovi, );
        brojac++;
    }
    fclose(datoteka);

    return studenti;
}
void IspisStudenataIzDatoteke(student* studenti, int brojStudenata,int max)
{
    double relativno[100];
    int brojac=0;
    while(brojac!=brojStudenata)
    {
        relativno[brojac]=studenti[brojac].bodovi/max*100;
        printf("%s %s %lf %lf%",studenti[brojac].ime,studenti[brojac].prezime,studenti[brojac].bodovi,relativno[brojac]);
        brojac++;
    }

}
int main()
{
    int brojStudenata;
   
    student *studenti = NULL;
    char* datoteka="studenti.txt";
    brojStudenata=ProcitajBrojRedakaIzDatoteke(datoteka);
    studenti=AlocirajMemorijuProcitajStudente(brojStudenata,datoteka);
    IspisStudenataIzDatoteke(studenti,brojStudenata);


    return 0;
}