#include <stdio.h>
#include <stdlib.h>

#define MAX 50
#define MAX_VECINI 50
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
void init_vector(int deg[MAX],int n)
{
    for(int i=1; i<=n; i++)
        deg[i]=0;
}
void citireMuchii(int *n,int*m, int adj[MAX][MAX_VECINI],int deg[MAX],FILE *pf,int o)
{
    fscanf(pf,"%d %d",n,m);
    init_vector(deg,*n);

    for(int i=0; i<*m; i++)
    {
        int x,y;
        fscanf(pf,"%d %d",&x,&y);
        adj[x][deg[x]]=y;
        deg[x]++;
        if(o==0)
        {
            adj[y][deg[y]]=x;
            deg[y]++;
        }
    }

}

void BFS(int n, int adj[MAX][MAX_VECINI],int deg[MAX],int start, FILE *pf )
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
        for(int i=0; i<deg[u]; i++)
        {
            int v=adj[u][i];
            if(!vizitat[v])
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
    int adjNeorientat[MAX][MAX_VECINI]= {0},degNeorientat[MAX];
    o=0;
    int start;
    printf("Dati nodul de inceput pentru graful neorientat: ");
    scanf("%d",&start);
    FILE *pf=deschide("grafNeorientat.txt","r");
    citireMuchii(&n,&m,adjNeorientat,degNeorientat,pf,o);
    fclose(pf);
    pf=deschide("neorientatOut.txt","w");
    BFS(n,adjNeorientat,degNeorientat,start,pf);
    fclose(pf);

    int adjOrientat[MAX][MAX_VECINI]= {0},degOrientat[MAX];
    o=1;
    printf("Dati nodul de inceput pentru graful orientat: ");
    scanf("%d",&start);
    pf=deschide("grafOrientat.txt","r");
    citireMuchii(&n,&m,adjOrientat,degOrientat,pf,o);
    fclose(pf);
    pf=deschide("orientatOut.txt","w");
    BFS(n,adjOrientat,degOrientat,start,pf);
    fclose(pf);

    return 0;
}
