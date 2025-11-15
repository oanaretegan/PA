#include <stdio.h>
#include <stdlib.h>

FILE *deschideFisier(const char *nume, const char *mod)
{
    FILE*f=fopen(nume, mod);
    if(f==NULL)
    {
        printf("Nu s a reusit deschiderea fisierului");
        exit(1);
    }
    return f;
}

typedef struct node_type
{
    int id;
    struct node_type *left,*right;
} NodeT;

//ex 1 Lab
NodeT*createBinTreeFromFile(FILE*f)
{
    NodeT*p;
    int c;
    if(fscanf(f,"%d",&c)!=1)
        return NULL;
    if(c==0)
        return NULL;
    else
    {
        p=(NodeT*)malloc(sizeof(NodeT));
        if(p==NULL)
        {
            printf("Nu mai este memorie in createBinTree");
            exit(1);
        }
        p->id=c;
        p->left=createBinTreeFromFile(f);
        p->right=createBinTreeFromFile(f);
    }
    return p;
}

//ex2 lab

void preorder(NodeT*p)
{
    if(p!=NULL)
    {
        printf("%d ",p->id);
        preorder(p->left);
        preorder(p->right);
    }

}

void inorder(NodeT*p)
{
    if(p!=NULL)
    {
        inorder(p->left);
        printf("%d ",p->id);
        inorder(p->right);
    }

}

void postorder(NodeT*p)
{
    if(p!=NULL)
    {
        postorder(p->left);
        postorder(p->right);
        printf("%d ",p->id);
    }
}

//ex3

int leaf_node(NodeT*p)
{
    if(p==NULL)
        return 0;
    else if(p->left==NULL && p->right==NULL)
    {
        printf("%d ",p->id);
        return 1;
    }
    else return leaf_node(p->left)+leaf_node(p->right);
}

//ex4 lab

int intern_node(NodeT*p)
{
    if(p==NULL || (p->left==NULL && p->right==NULL))
        return 0;
    else
    {
        printf("%d ",p->id);
        return 1+intern_node(p->left)+intern_node(p->right);
    }
}

//ex5 lab

#define max(a,b) ((a)>(b)?(a):(b))

int h(NodeT*p)
{
    if(p==NULL)
        return -1;
    else return 1+max(h(p->left),h(p->right));
}

//ex6 lab
NodeT*search(NodeT*root, int key)
{
    if(root==NULL)
        return NULL;

    if(root->id==key)
        return root;
    NodeT*left=search(root->left,key);

    if(left!=NULL)
        return left;

    return search(root->right,key);

}

//ex7 lab

NodeT *creBalBinTree( int nbOfNodes )
{
    NodeT *p;
    int nLeft, nRight;
    if ( nbOfNodes <= 0 ) return NULL;
    else
    {
        nLeft = nbOfNodes / 2;
        nRight = nbOfNodes - nLeft - 1;
        p = ( NodeT * ) malloc( sizeof( NodeT ));
        printf( "Cheia = ");
        scanf( "%d", &( p->id ));
        p->left = creBalBinTree( nLeft );
        p->right = creBalBinTree( nRight );
    }
    return p;
}



int main()
{
    //ex1 lab
    FILE *f=deschideFisier("ArboriBinari.txt","r");
    NodeT*root=createBinTreeFromFile(f);
    fclose(f);

    //ex2 lab
    printf("Arborele parcurs in preordine este: ");
    preorder(root);
    printf("\n");

    printf("Arborele parcurs inordine este: ");
    inorder(root);
    printf("\n");

    printf("Arborele parcurs in postordine este: ");
    postorder(root);
    printf("\n");

    //ex3 lab
    printf("Frunzele arborelui sunt: ");
    int nr=leaf_node(root);
    printf("\nNumarul lor este: %d",nr);

    printf("\n");

    //ex4 lab
    printf("Nodurile interne ale arborelui sunt: ");
    int n=intern_node(root);
    printf("\nNumarul lor este: %d",n);

    printf("\n");

    //ex5 lab

    int inaltime=h(root);
    printf("Inaltimea arborelui este: %d\n",inaltime);

    //ex6 lab
    int key;
    printf("Dati cheia care doriti sa fie cautata in arbore: ");
    scanf("%d",&key);
    NodeT*cautat=search(root, key);
    if(cautat==NULL)
        printf("Cheia %d nu exista in arbore\n",key);
    else
    {
        int i=h(cautat);
        printf("Nodul cu cheia %d are inaltimea %d\n",key,i);
    }

    //ex7 lab

    NodeT *radacina = NULL;
    int nbOfNodes = 0;
    printf("\nNumarul de noduri din arbore este:");
    scanf("%d", &nbOfNodes );
    radacina = creBalBinTree( nbOfNodes );

    printf("Arborele parcurs inordine este: ");
    inorder(radacina);
    return 0;



    return 0;
}
