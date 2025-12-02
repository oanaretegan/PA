#include <stdio.h>
#include <stdlib.h>

#define MAX 100

//ex 1 Permutari
int okP(int v[MAX],int k)
{
    for(int i=1; i<k; i++)
        if( v[i]==v[k])
            return 0;
    return 1;

}

int eSolP(int n,int k)
{
    if(k==n)
        return 1;
    return 0;
}
void print(int v[MAX],int k)
{
    for(int i=1; i<=k; i++)
        printf("%d ",v[i]);


}

void backtrakingP(int n,int k,int v[MAX])
{
    for(int i=1; i<=n; i++)
    {
        v[k]=i;
        print(v,k);


        if(okP(v,k))
            if(eSolP(n,k))
            {
                printf("-solutie\n");

            }
            else
            {
                printf("\n");
                backtrakingP(n,k+1,v);
            }
        else printf("\n");

    }
}

//ex 2 Combinari
int okC(int i, int v[MAX])
{
    if(i>1&&v[i]<=v[i-1])
        return 0;
    return 1;
}

int eSolC(int i,int k)
{
    if(i==k)
        return 1;
    return 0;
}

void backtrakingC(int n, int k,int i,int *cnt, int v[MAX])
{
    int start;
    if(i>1)
        start=v[i-1]+1;
    else start=1;
    for(int j=start; j<=n; j++)
    {
        v[i]=j;
        if(okC(i,v))
        {
            if(eSolC(i,k))
            {
                print(v,i);
                printf("\n");
                (*cnt)++;
            }
            else
            {
                backtrakingC(n,k,i+1,cnt,v);
            }
        }
    }
}

//ex 3 Regine
///1= Regina. 0=liber. -1=Raza de atac
int okR(int A[MAX][MAX], int i, int j,int n)
{
    int c,l;
    for(l=1; l<i; l++)
        if(A[l][j]==1)
            return 0;
    for(l=i-1,c=j-1; l>0 && c>0; l--,c--)
        if(A[l][c]==1)
            return 0;
    for(l=i-1,c=j+1; l>0 && c<=n; l--,c++)
        if(A[l][c]==1)
            return 0;
    return 1;

}

void printR(int A[MAX][MAX],int n)
{
    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=n; j++)
        {
            if(A[i][j]==1)
                printf("R ");
            else printf(". ");
        }
        printf("\n");
    }
    printf("\n");
}

void backtrakingR(int A[MAX][MAX], int n, int i)
{
    if(i==n+1)
    {
        printR(A,n);
        return;
    }

    for(int j=1;j<=n;j++)
    {
        if(okR(A,i,j,n))
        {
            A[i][j]=1;
            backtrakingR(A,n,i+1);
            A[i][j]=0;
        }
    }

}

//ex 4 Rest

int valori[MAX];
int sol[MAX];
int rest;

int minMonede;
int solOptima[MAX];

void sortare(int v[MAX], int n)
{
    int aux;
    for(int i = 0; i < n-1; i++)
    {
        for(int j = 0; j < n-i-1; j++)
        {
            if(v[j] < v[j+1])
            {
                aux= v[j];
                v[j] = v[j+1];
                v[j+1] = aux;
            }
        }
    }
}

void backtrackingr(int i,int n, int sumaCrt, int monedaCrt)
{

    if(sumaCrt == rest)
    {
        for(int j = 0; j < n; j++)
            printf("%d ", sol[j]);
        printf("\n");

        if(monedaCrt < minMonede)
        {
            minMonede = monedaCrt;
            for( int j = 0; j < n; j++)
                solOptima[j] = sol[j];
        }
        return;
    }

    if(i == n || sumaCrt > rest)
        return;

    if(monedaCrt >= minMonede)
        return;

    sol[i] =valori[i];
    backtrackingr(i+1,n, sumaCrt + valori[i], monedaCrt + 1);

    sol[i] = 0;
    backtrackingr(i+1,n, sumaCrt, monedaCrt);
}


int main()
{
    //ex1 Permutari
    int n,v[MAX]= {0};
    printf("Valoarea lui n=");
    scanf("%d",&n);
    backtrakingP(n,1,v);

    //ex2 Combinari
    int k,cnt=0;
    printf("Valoarea lui n=");
    scanf("%d",&n);
    printf("Valoarea lui k=");
    scanf("%d",&k);
    backtrakingC(n,k,1,&cnt,v);
    printf("Sunt %d solutii\n",cnt);

    //ex 3 regine
    int A[MAX][MAX]= {0};
    printf("Valoarea lui n=");
    scanf("%d",&n);
    backtrakingR(A,n,1);

    //ex 4 Rest

    printf("Numarul de monede = ");
    scanf("%d", &n);

    printf("Restul = ");
    scanf("%d", &rest);

    printf("Valorile monedelor: ");
    for(int i = 0; i < n; i++)
        scanf("%d", &valori[i]);

    sortare(valori, n);
    minMonede = MAX;
    backtrackingr(0,n, 0, 0);
    printf("Solutia optima: ");
    for(int i = 0; i < minMonede; i++)
        printf("%d ", solOptima[i]);
    printf("\n");


    return 0;
}
