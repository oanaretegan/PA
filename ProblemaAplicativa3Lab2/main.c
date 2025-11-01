#include <stdio.h>
#include <stdlib.h>
#include<string.h>

typedef struct student
{
    char nume[30];
    float nota;
    struct student *next;
}Student;

void StergereStudent(Student *s)
{
    if(s==NULL || s->next==NULL)
    {
        printf("Nu se poate efectua stergerea doar cu informatiile furnizate");
        return;
    }
    Student *p=s->next;
    strcpy(s->nume,p->nume);
    s->nota=p->nota;
    s->next=p->next;
    free(p);
}

void afisare(Student *first)
{
    Student*p=first;
    while(p!=NULL)
    {
        printf("%s (%1.f)\n",p->nume,p->nota);
        p=p->next;
    }
    printf("\n");
}

int main()
{
    Student *s1 = (Student*)malloc(sizeof(Student));
    strcpy(s1->nume, "Ana");
    s1->nota = 8.5;

    Student *s2 = (Student*)malloc(sizeof(Student));
    strcpy(s2->nume, "Mihai");
    s2->nota = 4.0;

    Student *s3 = (Student*)malloc(sizeof(Student));
    strcpy(s3->nume, "Ioana");
    s3->nota = 7.0;

    s1->next = s2;
    s2->next = s3;
    s3->next = NULL;

    printf("Lista initiala:\n");
    afisare(s1);

    printf("Stergem studentul cu nota sub 5...\n");
    StergereStudent(s2);

    printf("Lista dupa stergere:\n");
    afisare(s1);

    return 0;
}
