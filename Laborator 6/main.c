#include <stdio.h>
#include <stdlib.h>

#define M 7

typedef struct node
{
    int key;
    struct node *next;
} NodeT;

//ex1
void initializareTabela(NodeT* hTable[M])
{
    for(int i=0; i<M; i++)
        hTable[i]=NULL;
}

int hash(int key)
{
    return key%M;
}

NodeT* creareNod(int key)
{
    NodeT*p=(NodeT*)malloc(sizeof(NodeT));
    p->key=key;
    p->next=NULL;
    return p;
}

void insertElement(NodeT* hTable[M],int key)
{
    int index=hash(key);
    NodeT*p=creareNod(key);
    p->next=hTable[index];
    hTable[index]=p;
}

NodeT*findElement(NodeT*hTable[M],int key)
{
    int index=hash(key);
    NodeT*p=hTable[index];
    while(p!=NULL)
    {
        if(p->key==key)
            return p;
        p=p->next;
    }
    return NULL;
}
void deleteElement(NodeT*hTable[M],int key)
{
    int index=hash(key);
    NodeT*p=hTable[index];
    NodeT*q=NULL;
    while(p!=NULL)
    {
        if(p->key==key)
        {
            if(q==NULL)
                hTable[index]=p->next;
            else q->next=p->next;
            free(p);
            return;
        }
        q=p;
        p=p->next;
    }
}

void afisare(NodeT*hTable[M])
{
    for(int i=0; i<M; i++)
    {
        printf("%d: ",i);
        NodeT*p=hTable[i];
        while(p!=NULL)
        {
            printf("%d-> ",p->key);
            p=p->next;
        }
        printf("NULL\n");
    }
}

//ex2

int hL(int key,int i)
{
    return (hash(key)+i)%M;
}
void init_vector(int h[M])
{
    for(int i=0; i<M; i++)
        h[i]=-1;
}
void inserare(int h[M],int key)
{
    int index=hash(key),i=0;
    do
    {
        index=hL(key,i);
        i++;
    }
    while(h[index]!=-1&&i<M);
    if(i>=M)
        printf("Tabela este plina, nu se mai pot face inserari");
    else
        h[index]=key;


}

int searchL(int h[M],int key)
{
    int i=0,index;
    do
    {
        index=hL(key,i);
        if(h[index]==key)
            return index;
        i++;
    }
    while(i<M);
    return -1;
}

//ex3

int hP(int key,int i)
{
    return (hash(key)+i+i*i)%M;
}

void insert(int h[M], int key)
{
    int index,i=0;
    do
    {
        index=hP(key,i);
        i++;
    }
    while(h[index]!=-1 && i<M);
    if(i>=M)
        printf("Tabela este plina, nu se mai pot insera elemente");
    else
        h[index]=key;
}

int searchP(int h[M],int key)
{
    int i=0,index;
    do
    {
        index=hP(key,i);
        if(h[index]==key)
            return index;
        i++;
    }
    while(i<M);
    return -1;
}

//ex4

int hash2(int key)
{
    return 5-(key%5);
}
int hVD(int key,int i)
{
    return (hash(key)+i*hash2(key))%M;
}

void insrt(int h[M],int key)
{
    int index,i=0;
    do
    {
        index=hVD(key,i);
        i++;
    }
    while(h[index]!=-1 && i<M);
    if(h[index]!=-1)
        printf("Tabela este plina, nu se mai pot insera elemente\n");
    else
        h[index]=key;
}
int searchVD(int h[M],int key)
{
    int i=0,index;
    do
    {
        index=hVD(key,i);
        if(h[index]==key)
            return index;
        i++;
    }
    while(i<M);
    return -1;
}

void afis(int h[M])
{
    for(int i=0; i<M; i++)
        printf("%d ",h[i]);
    printf("\n");
}

int main()
{
    NodeT*hTable[M];
    initializareTabela(hTable);

    //ex1

    insertElement(hTable,36);
    insertElement(hTable,14);
    insertElement(hTable,26);
    insertElement(hTable,21);
    insertElement(hTable,5);
    insertElement(hTable,19);
    insertElement(hTable,4);
    printf("Tabela de dispersie (Metoda Chaining) este:\n");
    afisare(hTable);
    int key;
    printf("Dati o cheie: ");
    scanf("%d",&key);
    NodeT*p=findElement(hTable,key);
    if(p!=NULL)
    {
        printf("Cheia a fost gasita!\n");
        deleteElement(hTable,key);
        printf("Tabela de dispersie in urma eliminarii elementului cu cheia %d este:\n",key);
        afisare(hTable);
    }
    else printf("Cheia nu a fost gasita\n");

    //ex2
    int h[M],g;
    init_vector(h);
    inserare(h,19);
    inserare(h,36);
    inserare(h,5);
    inserare(h,21);
    inserare(h,4);
    inserare(h,26);
    inserare(h,14);

    printf("Tabela de dispersie(Verificare Liniara) este: ");
    afis(h);
    printf("Dati o cheie: ");
    scanf("%d",&key);
    g=searchL(h,key);
    if(g!=-1)
    printf("Cheia a fost gasita la pozitia %d\n",g);
    else printf("Cheia nu a fost gasita\n");

    //ex3

    init_vector(h);
    insert(h,19);
    insert(h,36);
    insert(h,5);
    insert(h,21);
    insert(h,4);
    insert(h,26);
    insert(h,14);

    printf("Tabela de dispersie (Verificare Polinomiala) este: ");
    afis(h);

    printf("Dati o cheie: ");
    scanf("%d",&key);
    g=searchP(h,key);
    if(g!=-1)
    printf("Cheia a fost gasita la pozitia %d\n",g);
    else printf("Cheia nu a fost gasita\n");

    //ex4
    init_vector(h);

    insrt(h,19);
    insrt(h,36);
    insrt(h,5);
    insrt(h,21);
    insrt(h,4);
    insrt(h,26);
    insrt(h,14);

    printf("Tabela de disperie (Verificare Dubla) este: ");
    afis(h);

    printf("Dati o cheie: ");
    scanf("%d",&key);
    g=searchVD(h,key);
    if(g!=-1)
    printf("Cheia a fost gasita la pozitia %d\n",g);
    else printf("Cheia nu a fost gasita\n");

    return 0;
}
