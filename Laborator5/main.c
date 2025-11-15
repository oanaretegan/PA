#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int key;
    struct node*left,*right,*parinte;
} NodeT;

//ex1 lab

NodeT*createNode(int key)
{
    NodeT*p=(NodeT*)malloc(sizeof(NodeT));
    p->left=NULL;
    p->right=NULL;
    p->parinte=NULL;
    p->key=key;
    return p;
}

NodeT*insertNode(NodeT*root, int key)
{
    NodeT*p=root;
    NodeT*parinte=NULL;
    NodeT*nodNou=createNode(key);

    if(root==NULL)
        return nodNou;
    while(p!=NULL)
    {
        parinte=p;
        if(p->key>key)
            p=p->left;
        else if(p->key<key)
            p=p->right;
        else if(p->key==key)
        {
            free(nodNou);
            return root;
        }
    }
    if(parinte->key<key)
        parinte->right=nodNou;
    else parinte->left=nodNou;
    nodNou->parinte=parinte;
    return root;
}

//ex2 lab
NodeT*searchKey(NodeT*root, int key)
{
    if(root==NULL )
        return NULL;
    if(root->key==key)
        return root;
    else if(key<root->key)
        return searchKey(root->left,key);
    else return searchKey(root->right,key);

}

void preOrder(NodeT*root)
{
    NodeT*p=root;
    if(p!=NULL)
    {
        printf("%d ",p->key);
        preOrder(p->left);
        preOrder(p->right);
    }
}

void inOrder(NodeT*root)
{
    NodeT*p=root;
    if(p!=NULL)
    {
        inOrder(p->left);
        printf("%d ",p->key);
        inOrder(p->right);
    }
}

void postOrder(NodeT*root)
{
    NodeT*p=root;
    if(p!=NULL)
    {
        postOrder(p->left);
        postOrder(p->right);
        printf("%d ",p->key);
    }
}

//ex4 lab
NodeT*findMin(NodeT*node)
{
    if(node==NULL)
        return 0;
    if(node->left==NULL)
        return node;
    else return findMin(node->left);
}

//ex5 lab

NodeT*findMax(NodeT*node)
{

    if(node==NULL)
        return 0;
    if(node->right==NULL)
        return node;
    else return findMax(node->right);
}

//ex6
NodeT*succesor(NodeT*node)
{
    if(node==NULL)
        return NULL;
    if(node->right!=NULL)
        return findMin(node->right);
    else
    {
        NodeT*p=node->parinte;
        while(p!=NULL && node==p->right)
        {
            node=p;
            p=p->parinte;
        }
        return p;
    }
}

//ex7
NodeT*predecesor(NodeT*node)
{
    if(node==NULL)
        return NULL;
    if(node->left!=NULL)
        return findMax(node->left);
    else
    {
        NodeT*p=node->parinte;
        while(p!=NULL && node==p->left)
        {
            node=p;
            p=p->parinte;
        }
        return p;
    }
}

//ex8 lab

NodeT*deleteNode(NodeT*root, int key)
{
    if(root==NULL)
        return NULL;
    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else
    {
        if(root->left==NULL && root->right==NULL)
        {
            free(root);
            return NULL;
        }
        else if(root->left==NULL)
        {
            NodeT*p=root->right;
            p->parinte=root->parinte;
            free(root);
            return p;
        }
        else if(root->right==NULL)
        {
            NodeT*p=root->left;
            p->parinte=root->parinte;
            free(root);
            return p;
        }
        else
        {
            NodeT*p=findMin(root->right);
            root->key=p->key;
            root->right=deleteNode(root->right,p->key);

        }
    }
    return root;
}
int main()
{
    NodeT*root=NULL;

    //ex1 lab
    root=insertNode(root,15);
    root=insertNode(root,6);
    root=insertNode(root,18);
    root=insertNode(root,20);
    root=insertNode(root,17);
    root=insertNode(root,7);
    root=insertNode(root,13);
    root=insertNode(root,3);
    root=insertNode(root,2);
    root=insertNode(root,4);
    root=insertNode(root,9);

    //ex2 lab
    int key;
    printf("Introduceti cheia care doriti sa fie cautata in arbore: ");
    scanf("%d",&key);
    NodeT*c=searchKey(root,key);
    if(c==NULL)
        printf("Cheia data nu se gaseste in arbore\n");
    else printf("Cheia a fost gasita\n");

    //ex3 lab
    printf("Arborele parcurs in preordine este: ");
    preOrder(root);
    printf("\n");

    printf("Arborele parcurs inordine este: ");
    inOrder(root);
    printf("\n");

    printf("Arborele parcurs in postordine este: ");
    postOrder(root);
    printf("\n");

    //ex4lab
    NodeT*node1=findMin(root->left);
    printf("Cel mai mic nod din subarborele stang are cheia: %d \n",node1->key);
    NodeT*node2=findMin(root->right);
    printf("Cel mai mic nod din subarborele drept are cheia: %d\n",node2->key);

    //ex5 lab
    node1=findMax(root->left);
    printf("Cel mai mare nod din subarborele stang are cheia: %d \n",node1->key);
    node2=findMax(root->right);
    printf("Cel mai mare nod din subarborele drept are cheia: %d\n",node2->key);

    //ex6 lab + ex7 lab +ex8lab
    //folosim cheia cautata la ex 3
    if(c!=NULL)
    {
        NodeT*s=succesor(c);
        printf("Succesorul nodului avand cheia %d este %d\n",c->key,s->key);
        NodeT*p=predecesor(c);
        printf("Predecesorul nodului avand cheia %d este %d\n",c->key,p->key);
        root=deleteNode(root,key);
        printf("Arborele parcurs in preordine dupa stergerea nodului cu cheia %d este: ",key);
        preOrder(root);
    }


    return 0;
}
