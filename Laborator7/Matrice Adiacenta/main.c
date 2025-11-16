#include <stdio.h>
#include <stdlib.h>

#define MAX 50
FILE *deschide(const char *nume, const char *mod)
{
    FILE*pf=fopen(nume,mod);
    if(pf==NULL)
    {
        printf("Nu s a reusit deschiderea fisierului\n");
        exit(1);
    }
    return pf;
}

void citireMuchii(int *n,int*m, int adj[MAX][MAX],FILE *pf,int o)
{
    fscanf(pf,"%d %d",n,m);
    for(int i=0; i<m; i++)
    {
        int x,y;
        fscanf(pf,"%d %d",&x,&y);
        adj[x][y]=1;
        if(o==0)
            adj[y][x]=1;
    }

}

void BFS(int n, int adj[MAX][MAX],int start, FILE *pf )
{
    int vizitat[MAX]= {0};
    int queue[MAX];
    int front=0,rear=0;

    vizitat[start]=1;
    queue[rear]=start;
    rear++;

    while(front<rear)
    {
        int u=queue[front];
        front++;
        fprintf(pf,"%d ",u);
        for(int v=1; v<=n; v++)
        {
            if(adj[u][v]&&!vizitat[v])
            {
                vizitat[v]=1;
                queue[rear]=v;
                rear++;
            }
        }
    }

}


int main()
{
    int m,n,o;///o=1 graf orientat; o=0 graf neorientat
    int adjNeorientat[MAX][MAX]={0};
    o=0;
    int start;
    printf("Dati nodul de inceput pentru graful neorientat: ");
    scanf("%d",&start);
    FILE *pf=deschide("grafNeorientat.txt","r");
    citireMuchii(&n,&m,adjNeorientat,pf,o);
    fclose(pf);
    pf=deschide("neorientatOut.txt","w");
    BFS(n,adjNeorientat,start,pf);
    fclose(pf);

    int adjOrientat[MAX][MAX]={0};
    o=1;
    printf("Dati nodul de inceput pentru graful orientat: ");
    scanf("%d",&start);
    pf=deschide("grafOrientat.txt","r");
    citireMuchii(&n,&m,adjOrientat,pf,o);
    fclose(pf);
    pf=deschide("orientatOut.txt","w");
    BFS(n,adjOrientat,start,pf);
    fclose(pf);

    return 0;
}
