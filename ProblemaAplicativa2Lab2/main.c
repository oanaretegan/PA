#include <stdio.h>
#include <stdlib.h>

FILE *deschide(const char *nume, const char *mod)
{
    FILE *pf=fopen(nume, mod);
    if(pf==NULL)
    {
        perror(nume);
        exit(1);
    }
    return pf;

}
typedef struct node
{
    int key;
    struct node *next;
} NodeT;

NodeT*creareNod(int givenKey)
{
    NodeT*p=(NodeT*)malloc(sizeof(NodeT));
    p->key=givenKey;
    p->next=NULL;
    return p;
}

void insert_last(NodeT**first, NodeT**last, int givenKey)
{
    NodeT *p=creareNod(givenKey);
    if(*first==NULL)
    {
        *first=p;
        *last=p;
    }
    else
    {
        (*last)->next=p;
        *last=p;

    }
}
void CreareLista(FILE *pf, NodeT**first, NodeT**last)
{
    int key;
    while(fscanf(pf,"%d",&key)==1)
    {
        insert_last(first,last,key);
    }

}

void afiseaza_lista(NodeT*first)
{
    NodeT *p=first;
    printf("Lista este: ");
    if(p==NULL)
        printf("Vida");
    else
    {

        while(p!=NULL)
        {
            printf("%d ",p->key);
            p=p->next;
        }
    }
    printf("\n");
}

int search(NodeT*first,int givenKey)
{
    NodeT*p=first;
    while(p!=NULL)
    {
        if(p->key==givenKey)
            return 1;
        p=p->next;
    }
    return 0;
}
NodeT*Intersectie(NodeT*first1, NodeT*first2, NodeT**lastI)
{

    NodeT*p=first1;
    NodeT*firstI=NULL;
    while(p!=NULL)
    {
        if(search(first2,p->key))
            insert_last(&firstI,lastI,p->key);
        p=p->next;
    }
    return firstI;
}

NodeT*Reuniune(NodeT*first1, NodeT*first2,NodeT**lastR)
{
    NodeT*p=first1,*q=first2,*firstR=NULL;
   while(p != NULL && q != NULL)
    {
        if(p->key == q->key)
        {
            insert_last(&firstR, lastR, p->key);
            p = p->next;
            q = q->next;
        }
        else if(p->key < q->key)
        {
            insert_last(&firstR, lastR, p->key);
            p = p->next;
        }
        else
        {
            insert_last(&firstR, lastR, q->key);
            q = q->next;
        }
    }

    while(p != NULL)
    {
        insert_last(&firstR, lastR, p->key);
        p = p->next;
    }
    while(q != NULL)
    {
        insert_last(&firstR, lastR, q->key);
        q = q->next;
    }
    return firstR;
}

int main()
{
    FILE *pf1=deschide("F1","r");
    FILE *pf2=deschide("F2","r");
    NodeT*first1=NULL,*last1=NULL,*first2=NULL,*last2=NULL;

    CreareLista(pf1,&first1, &last1);
    CreareLista(pf2,&first2,&last2);

    afiseaza_lista(first1);
    afiseaza_lista(first2);

    NodeT*firstI=NULL,*lastI=NULL;

    firstI=Intersectie(first1,first2,&lastI);

    printf("Intersectia: \n");
    afiseaza_lista(firstI);

    NodeT*firstR=NULL,*lastR=NULL;
    firstR=Reuniune(first1,first2,&lastR);

    printf("Reuniunea: \n");
    afiseaza_lista(firstR);

    return 0;
}
