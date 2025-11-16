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
    for(int i=0;i<MAX;i++)
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
void citireMuchii(int *n, int *m, node*adj[MAX], FILE *pf,int o)
{
    fscanf(pf,"%d %d",n,m);
    for(int i=0; i<m; i++)
    {
        int x,y;
        fscanf(pf,"%d %d",&x,&y);
        node*p=CreareNod(y);
        p->next=adj[x];
        adj[x]=p;
        if(o==0)
        {
            node*q=CreareNod(x);
            q->next=adj[y];
            adj[y]=q;
        }

    }
}

void BFS(int n, node*adj[MAX],int start, FILE *pf )
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
        for(node *p=adj[u];p!=NULL;p=p->next)
        {
            int v=p->x;
            if(!vizitat[v])
            {
                vizitat[v]=1;
                queue[rear]=v;
                rear++;
            }
        }
    }

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
    for(int i=1;i<=n;i++)
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
    BFS(n,adjNeorientat,start,pf);
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
    BFS(n,adjOrientat,start,pf);
    fclose(pf);

    freeGraf(adjNeorientat,n);
    freeGraf(adjOrientat,n);


    return 0;
}
