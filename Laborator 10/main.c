#include <stdio.h>
#include <stdlib.h>

const int a[]= {500,200,100,50,10,5,1};

void descompunere(int x)
{
    for(int i=0; i<7; i++)
    {
        while(x>=a[i])
        {

            printf("%d ",a[i]);
            x-=a[i];
        }
    }
    printf("\n");
}

typedef struct activitate
{
    char nume[20];
    int oraI,oraF,minI,minF;
} act;

void citireAct(act v[50], int *n)
{
    printf("Introduce ti numarul de activitati: ");
    scanf("%d",n);
    printf("Introduce ti numele activitatii, ora si minutul de incepere, ora si minutul de final: \n");
    for(int i=0; i<*n; i++)
    {
        printf("Numele activitati: ");
        scanf("%s",v[i].nume);
        printf("Ora de inceput:\n[ora]: ");
        scanf("%d",&v[i].oraI);
        printf("[minutul]: ");
        scanf("%d",&v[i].minI);
        printf("Ora de final:\n[ora]: ");
        scanf("%d",&v[i].oraF);
        printf("[minutul]: ");
        scanf("%d",&v[i].minF);
    }
}

void ordonare(act v[50],int n)
{
    for(int i=0; i<n-1; i++)
    {
        for(int j=i+1; j<n; j++)
            if((v[i].oraF>v[j].oraF)||(v[i].oraF==v[j].oraF && v[i].minF>v[j].minF))
            {
                act aux=v[i];
                v[i]=v[j];
                v[j]=aux;
            }

    }
}

void activitati( act v[50], int n)
{
    ordonare(v,n);
    int u=0;
    printf("Activitatile: \n");

    for(int i=0; i<n; i++)
    {
        int s=v[i].oraI*60+v[i].minI, f=v[i].oraF*60+v[i].minF;
        if(s>=u)
        {
            printf("%s (%d:%02d-%d:%02d)\n",v[i].nume, v[i].oraI,v[i].minI,v[i].oraF,v[i].minF);
            u=f;
        }

    }
}

int putere2(int n)
{
    int x=1;
    while(n)
    {
        x*=2;
        n--;
    }
    return x;
}

void termeni(int nr)
{
    int r[50]= {0},contor=0;
    while(nr)
    {
        r[contor]=nr%2;
        nr/=2;
        contor++;

    }

    for(int i=contor-1; i>=0; i--)
    {
        if(r[i]!=0)
            printf("%d ",putere2(i));
    }
    printf("\n");
}
int main()
{
    int x;
    printf("Introduce ti suma:  ");
    scanf("%d",&x);
    descompunere(x);


    act v[50];
    int n;
    citireAct(v,&n);
    activitati(v,n);

    printf("Introduce ti numarul: ");
    scanf("%d",&x);
    termeni(x);
    return 0;
}
