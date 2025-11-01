#include <stdio.h>
#include <stdlib.h>

//Sa se scrie programul care creeaza doua liste ordonate crescator
//dupa o cheien umerica si apoi le interclaseaza.

int *alocareVector(int capacity)
{
    int *arr=malloc(capacity*sizeof(int));
    if(arr==NULL)
    {
        printf("Nu s-a reusit alocarea memoriei\n");
        exit(1);
    }
    return arr;
}

void OrdCresc(int*arr, int size)
{
    for(int i=0; i<size; i++)
        for(int j=i+1; j<size; j++)
            if(arr[j]<arr[i])
            {
                int aux=arr[i];
                arr[i]=arr[j];
                arr[j]=aux;
            }
}

void in(int *arr, int *size,int poz, int key)
{
    for(int i=*size; i>poz; i--)
        arr[i]=arr[i-1];
    arr[poz]=key;
    (*size)++;
}

void m(int *i1, int *size1, int *i2, int *size2)
{
    int j=0;
    for(int i=0; i<(*size1); i++)
    {
        if(i2[j]<i1[i])
        {
            in(i1,&size1,i,i2[j]);
            i2[j]=0;
            j++;
        }
    }
    *size2=0;
}

void pn(int *arr, int size, int n)
{
    if(size==0)
        printf("Vida");
    else
    {
        printf("%d: ",n);
        for(int i=0; i<size; i++)
            printf("%d ",arr[i]);
        printf("\n");
    }
}
int main()
{
    int*i1=alocareVector(20);
    int*i2=alocareVector(20);
    int size1=0, size2=0;
    in(i1,&size1,0,-2);
    in(i1,&size1,0,5);
    in(i1,&size1,0,2);
    in(i1,&size1,0,30);
    in(i1,&size1,0,52);
    in(i1,&size1,0,47);
    in(i1,&size1,0,23);

    in(i2,&size2,0,90);
    in(i2,&size2,0,7);
    in(i2,&size2,0,33);
    in(i2,&size2,0,-11);
    in(i2,&size2,0,-5);

    OrdCresc(i1,size1);
    OrdCresc(i2,size2);

    pn(i1,size1,1);
    pn(i2,size2,2);

    m(i1,&size1,i2,&size2);

    pn(i1,size1,1);
    pn(i2,size2,2);

    return 0;
}
