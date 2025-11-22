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

typedef struct node
{
    int x;
    struct node*next;
} node;

void init_vector(node*adj[MAX])
{
    for(int i=0; i<MAX; i++)
        adj[i]=NULL;
}

node*CreareNod(int x)
{
    node*p=(node*)malloc(sizeof(node));
    if(p==NULL)
    {
        printf("Nu s a reusit alocarea\n");
        exit(1);
    }
    p->x=x;
    p->next=NULL;
    return p;
}

void addEnd(int u, int v, node*adj[MAX],node*end[MAX])
{
    node*p=CreareNod(v);
    if(adj[u]==NULL)
    {
        adj[u]=p;
        end[u]=p;
    }
    else
    {
        end[u]->next=p;
        end[u]=p;
    }
}
void citireMuchii(int *n, int *m, node*adj[MAX], FILE *pf,int o)
{
    fscanf(pf,"%d %d",n,m);
    node*end[MAX]= {NULL};
    for(int i=0; i<m; i++)
    {
        int x,y;
        fscanf(pf,"%d %d",&x,&y);
        addEnd(x,y,adj,end);
        if(o==0)
        {
            addEnd(y,x,adj,end);
        }

    }
}

void initVchar(char a[MAX],int n)
{
    for(int i=1; i<=n; i++)
        a[i]='W';
}
void initP(int p[MAX],int n)
{
    for(int i=1; i<=n; i++)
        p[i]=-1;
}

void afisareArboreDFS(int parinte[MAX],FILE*pf,int n)
{
    fprintf(pf,"\nArorele DFS este:\n");
    for(int i=1; i<=n; i++)
    {
        if(parinte[i]!=-1)
            fprintf(pf,"%d -> %d \n",parinte[i],i);
    }
}
void DFSiterativ(int n, node*adj[MAX],int start, FILE *pf )
{
    char color[MAX];
    int stack[MAX],parinte[MAX];
    int top=-1;
    initP(parinte,n);
    initVchar(color,n);
    for (int i = 1; i <= n; i++)
    {
        if (color[i] == 'W')
        {
            top = 0;
            stack[top] = i;
            color[i] = 'G';

            while (top >= 0)
            {
                int u = stack[top];
                top--;
                fprintf(pf, "%d ", u);
                color[u] = 'B';

                for (node *p = adj[u]; p != NULL; p = p->next)
                {
                    int v = p->x;
                    if (color[v] == 'W')
                    {
                        color[v] = 'G';
                        top++;
                        stack[top] = v;
                        parinte[v] = u;
                    }
                }
            }
        }
    }

    fprintf(pf, "\n");
    afisareArboreDFS(parinte,pf,n);

}

void DFSrecursiv(int u,node*adj[MAX],FILE*pf,char color[MAX],int fgray[MAX],int fblack[MAX],int *time)
{
    color[u]='G';
    (*time)++;
    fgray[u]=*time;
    node*p=adj[u];
    while(p!=NULL)
    {
        int v=p->x;
        if(color[v]=='W')
        {
            DFSrecursiv(v,adj,pf,color,fgray,fblack,time);
        }
        p=p->next;
    }
    color[u]='B';
    (*time)++;
    fblack[u]=*time;
    fprintf(pf,"Nodul %d are timpul %d/%d\n",u,fgray[u],fblack[u]);
}

void DFS(int n,node*adj[MAX],int start, FILE *pf)
{
    int fgray[MAX]= {0},fblack[MAX]= {0};
    char color[MAX];
    initVchar(color,n);
    int t=0;
    DFSrecursiv(start,adj,pf,color,fgray,fblack,&t);
    for(int i=1; i<=MAX; i++)
        if(color[i]=='W')
            DFSrecursiv(i,adj,pf,color,fgray,fblack,&t);
}
void freeList(node*p)
{
    while(p!=NULL)
    {
        node*q=p;
        p=p->next;
        free(q);
    }
}
void freeGraf(node*adj[MAX], int n)
{
    for(int i=1; i<=n; i++)
        freeList(adj[i]);

}
int main()
{
    int m,n,o;///o=1 graf orientat; o=0 graf neorientat
    node*adjNeorientat[MAX];
    init_vector(adjNeorientat);
    o=0;
    int start;
    printf("Dati nodul de inceput pentru graful neorientat: ");
    scanf("%d",&start);
    FILE *pf=deschide("neorientatIN.txt","r");
    citireMuchii(&n,&m,adjNeorientat,pf,o);
    fclose(pf);
    pf=deschide("neorientatOut.txt","w");
    fprintf(pf,"Parcurgerea Iterativa a grafului\n");
    DFSiterativ(n,adjNeorientat,start,pf);
    fprintf(pf,"\nParcugerea Recusiva a grafului\n");
    DFS(n,adjNeorientat,start,pf);

    fclose(pf);

    node* adjOrientat[MAX];
    init_vector(adjOrientat);
    o=1;
    printf("Dati nodul de inceput pentru graful orientat: ");
    scanf("%d",&start);
    pf=deschide("orientatIn.txt","r");
    citireMuchii(&n,&m,adjOrientat,pf,o);
    fclose(pf);
    pf=deschide("orientatOut.txt","w");
    fprintf(pf,"Parcurgerea Iterativa a grafului\n");
    DFSiterativ(n,adjOrientat,start,pf);
    fprintf(pf,"\nParcugerea Recusiva a grafului\n");
    DFS(n,adjOrientat,start,pf);
    fclose(pf);

    freeGraf(adjNeorientat,n);
    freeGraf(adjOrientat,n);


    return 0;
}
