#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int key;
    struct node *next;
} NodeT;

NodeT* search(NodeT* first, int givenKey)
{
    NodeT* p=first;
    while(p!=NULL)
    {
        if(p->key==givenKey)
            return p;
        else p=p->next;
    }
    return NULL;
}

NodeT*creareNod(int givenKey)
{
    NodeT*p=(NodeT*)malloc(sizeof(NodeT));
    p->key=givenKey;
    p->next=NULL;
    return p;
}

void insert_first(NodeT**first, NodeT**last, int givenKey)
{
    NodeT *p=creareNod(givenKey);
    if(*first==NULL)
    {
        *first=p;
        *last=p;
    }
    else
    {
        p->next=*first;
        *first=p;
    }
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

void insert_after_key(NodeT**first, NodeT**last, int afterKey, int givenKey)
{
    NodeT*p=search(*first, afterKey);
    if(p!=NULL)
    {
        NodeT*q=creareNod(givenKey);
        q->next=p->next;
        p->next=q;
        if(p==*last)
            *last=q;
    }
}

void afiseaza_lista(NodeT*first)
{
    NodeT *p=first;
    printf("Lista este: ");
    while(p!=NULL)
    {
        printf("%d ",p->key);
        p=p->next;
    }
    printf("\n");
}

void delete_first(NodeT**first, NodeT**last)
{
    NodeT*p=*first;
    if(*first!=NULL)
    {
        *first=(*first)->next;
        free(p);
        if(*first==NULL)
            *last=NULL;
    }
}

void delete_last(NodeT**first, NodeT**last)
{
    NodeT*p=*first;
    NodeT* q=*last;
    if(*first !=NULL)
    {
        while(p->next!=q)
            p=p->next;
        if(p==*first)
            *first=*last=NULL;
        else
        {
            p->next=NULL;
            *last=p;
        }
        free(q);
    }
}

void delete_key(NodeT**first, NodeT**last, int givenKey)
{
    NodeT*p=*first,*q;
    while(p!=NULL)
    {
        if(p->key==givenKey)
            break;
        q=p;
        p=p->next;
    }
    if(p!=NULL)
    {
        if(p==*first)
        {
            *first=(*first)->next;
            free(p);
            if(*first==NULL)
                *last=NULL;
        }
        else
        {
            q->next=p->next;
            if(p==*last)
                *last=q;
            free(p);
        }
    }
    else
    {
        printf("Cheia %d nu a fost gasita in lista\n",givenKey);
    }
}

int *alocareVector(int capacity)
{
    int *arr=malloc(capacity*sizeof(int));
    if(arr==NULL)
    {
        printf("Nu s-a putut aloca memoria\n");
        exit(1);
    }
    return arr;
}


int search2 (int *arr, int size, int key)
{
    for(int i=0; i<size; i++)
        if(arr[i]==key)
            return i;
    return -1;
}

void afisare_indice_cheie(int *arr, int size, int key)
{
    int i=search2(arr, size, key);
    if(i!=-1)
        printf("Indexul elementului %d este %d\n", key,i);
    else printf("Elementul cu cheia %d nu se gaseste in vector\n",key);
}

void insert_first2(int *arr, int *size, int key)
{
    for(int i=*size-1; i>=0; i--)
        arr[i+1]=arr[i];
    (*size)++;
    arr[0]=key;
}

void insert_last2(int *arr, int *size, int key)
{
    arr[*size]=key;
    (*size)++;
}

void delete_first2(int *arr, int *size)
{
    for(int i=1; i<*size; i++)
        arr[i-1]=arr[i];
    (*size)--;
}

void delete_last2(int *arr, int *size)
{
    arr[*size-1]=0;
    (*size)--;
}

void delete_key2(int *arr, int *size, int key)
{
    int i=search2(arr, size, key);
    if(i!=-1)
    {
        for(int j=i; j<*size; j++)
            arr[j]=arr[j+1];
        (*size)--;
    }
    else printf("Elementul cu cheia %d nu se afla in vector\n", key);
}

void print(int *arr, int size)
{
    printf("Lista este: \n");
    for(int i=0; i<size; i++)
        printf("%d ",arr[i]);
    printf("\n");
}

//Problema Optionala 1

void inversare_lista(NodeT**first, NodeT**last)
{
    NodeT *ant=NULL, *crt=*first, *next=NULL;
    *first=*last;
    while(crt!=NULL)
    {
        next=crt->next;
        crt->next=ant;
        ant=crt;
        crt=next;
    }
    *first=ant;

}

//Problema Optionala 2

void inserare_lista_ordonata(NodeT**first, NodeT**last,int givenKey)
{
    if(search(*first,givenKey)!=NULL)
    {
        printf("Nodul se afla deja in lista\n");
    }
    else
    {
        if(*first==NULL || (*first)->key > givenKey)
            insert_first(first,last,givenKey);
        else
        {
            NodeT*p=*first, *q=(*first)->next;
            while(q!=NULL && q->key < givenKey)
            {
                p=q;
                q=q->next;
            }

            insert_after_key(first,last,p->key, givenKey);
        }
    }
}

//Problema Propusa 3

NodeT*cautareL_k(NodeT *first, NodeT*last,int k)
{
    NodeT*p=first, *q=first;
    int contor=0;
    while( p!=NULL && contor<k)
    {
        p=p->next;
        contor++;
    }

    if(contor<k)
    {
        printf("Lista este prea scurta\n");
        return NULL;
    }
    while(p!=NULL)
    {
        p=p->next;
        q=q->next;
    }
    return q;
}

//Problema Propusa 4

typedef struct nod
{
    int key;
    struct nod *next;
} NodeTC;

NodeTC*search3(NodeTC*pNode,int givenKey)
{
    NodeTC*p=pNode;
    do
    {
        if(p->key==givenKey)
            return p;
        p=p->next;
    }while(p!=pNode);
    return NULL;
}

void insert_first3(NodeTC**pNode,int givenKey)
{
    NodeTC*nodNou=(NodeTC*)malloc(sizeof(NodeTC));
    nodNou->key=givenKey;
    if(*pNode==NULL)
    {
        nodNou->next=nodNou;
        *pNode=nodNou;
    }
    else
    {
        NodeTC*p=*pNode;
        while(p->next!=*pNode)
            p=p->next;
        nodNou->next=*pNode;
        p->next=nodNou;
        *pNode=nodNou;

    }

}

void insert_after_Key(NodeTC**pNode,int key, int givenKey)
{
    NodeTC*nodNou=(NodeTC*)malloc(sizeof(NodeTC));
    nodNou->key=givenKey;
    if(*pNode==NULL)
    {
        nodNou->next=nodNou;
        *pNode=nodNou;
    }
    else
    {
        NodeTC*p=*pNode;
        while(p->next!=(*pNode))
            if(p->key==key)
            {
                nodNou->next=p->next;
                p->next=nodNou;
                return;
            }
            else
                p=p->next;
        printf("Nodul cu cheia %d nu se afla in lista\n",key);
        free(nodNou);

    }
}

void delete_key3(NodeTC **pNode, int key)
{
    if (*pNode == NULL)
    {
        printf("Lista este goala.\n");
        return;
    }

    NodeTC *p = *pNode;
    NodeTC *q = NULL;

    if (p->next == p && p->key == key)
    {
        free(p);
        *pNode = NULL;
        return;
    }

    do
    {
        if (p->key == key)
            break;

        q = p;
        p = p->next;
    }
    while (p != *pNode);

    if (p->key != key)
    {
        printf("Nodul cu cheia %d nu se afla in lista\n", key);
        return;
    }

    if (p == *pNode)
    {
        NodeTC *last = *pNode;
        while (last->next != *pNode)
            last = last->next;

        last->next = p->next;
        *pNode = p->next;
        free(p);
    }
    else
    {
        q->next = p->next;
        free(p);
    }
}

void printLC(NodeTC*pNode)
{
    NodeTC*p=pNode;
    printf("Lista este: ");
    while(p->next!=pNode)
    {
        printf("%d ",p->key);
        p=p->next;
    }

    printf("\n");
}
int main()
{
    NodeT *first,*last;
    first=last=NULL;

    //ex 3 laborator
    insert_first(&first,&last, 4);
    insert_first(&first,&last, 1);
    insert_last(&first,&last,3);

    NodeT*s=search(first,2);
    if(s==NULL)
        printf("Cheia 2 nu a fost gasita\n");
    else printf("Cheia 2 a fost gasita\n");

    s=search(first,3);
    if(s==NULL)
        printf("Cheia 3 nu a fost gasita\n");
    else printf("Cheia 3 a fost gasita\n");

    insert_after_key(&first,&last,4,22);
    insert_after_key(&first,&last,3,25);
    afiseaza_lista(first);


    //ex 5 laborator

    delete_first(&first, &last);
    delete_last(&first,&last);
    delete_key(&first, &last, 22);
    delete_key(&first,&last,8);
    afiseaza_lista(first);

    //ex 6 laborator

    int size=0;
    int*arr=alocareVector(10);
    insert_first2(arr,&size,5);
    insert_first2(arr,&size,2);
    insert_first2(arr,&size,7);
    insert_last2(arr,&size,12);
    insert_last2(arr,&size,13);
    print(arr, size);
    afisare_indice_cheie(arr,size,2);
    afisare_indice_cheie(arr,size,20);
    delete_first2(arr,&size);
    delete_key2(arr, &size, 12);
    print(arr,size);
    free(arr);

    //Problema Propusa 1
    inversare_lista(&first, &last);
    afiseaza_lista(first);

    //Problema Propusa 2
    NodeT*f,*l;
    f=NULL;
    l=NULL;
    insert_last(&f,&l,1);
    insert_last(&f,&l,3);
    insert_last(&f,&l,7);
    insert_last(&f,&l,12);
    afiseaza_lista(f);

    inserare_lista_ordonata(&f,&l,6);
    inserare_lista_ordonata(&f,&l,-1);
    inserare_lista_ordonata(&f,&l,13);

    afiseaza_lista(f);

    //Problema Propusa 3
    NodeT* aux=cautareL_k(f,l,3);
    if(aux!=NULL)
        printf("Nodul aflat la Lenght-%d are cheia %d\n",3,aux->key);

    //Problema Propusa 4
    NodeTC*pNode=NULL;
    insert_first3(&pNode,2);
    insert_first3(&pNode,8);
    insert_first3(&pNode,13);
    insert_first3(&pNode,22);
    insert_first3(&pNode,30);
    NodeTC *s2 = search3(pNode, 2);
    if (s2 == NULL)
        printf("Cheia 2 nu a fost gasita\n");
    else
        printf("Cheia 2 a fost gasita\n");

    s2 = search3(pNode, 3);
    if (s2 == NULL)
        printf("Cheia 3 nu a fost gasita\n");
    else
        printf("Cheia 3 a fost gasita\n");

    insert_after_Key(&pNode, 4, 22);
    insert_after_Key(&pNode, 30, 3);

    delete_key3(&pNode, 13);

    printLC(pNode);
    return 0;
}
