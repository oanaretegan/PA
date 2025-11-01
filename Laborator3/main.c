#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int key;
    struct node *next;
} NodeT;

//ex1 lab
NodeT*createNode(int key)
{
    NodeT*p=(NodeT*)malloc(sizeof(NodeT));
    p->key=key;
    p->next=NULL;
    return p;
}

void push(NodeT**stack, int key)
{
    NodeT*p=createNode(key);
    if(*stack==NULL)
    {
        *stack=p;
    }
    else
    {
        p->next=*stack;
        (*stack)=p;


    }
}

void pop(NodeT**stack)
{
    if(*stack==NULL)
        printf("Stiva este goala\n");
    else
        *stack=(*stack)->next;
}

void print_stack(NodeT*stack)
{
    NodeT*p=stack;
    printf("Stiva este: ");
    while(p!=NULL)
    {
        printf("%d ",p->key );
        p=p->next;
    }
    printf("\n");
}

//ex2
#define CAPACITY 10

typedef struct _queue
{
    int vec[CAPACITY];
    int size,head,tail;
} queue;

void initQueue(queue *q)
{
    q->head=0;
    q->size=0;
    q->tail=0;
}

void enqueue(queue*q,int key)
{
    if(q->size==CAPACITY)
    {
        printf("Coada este plina\n");
        return;
    }
    q->vec[q->tail]=key;
    q->tail=(q->tail +1)%CAPACITY;
    q->size++;
}

int dequeue(queue*q)
{
    if(q->size==0)
    {
        printf("Coada este goala\n");
        return -1;
    }
    int key=q->vec[q->head];
    q->head=(q->head+1)%CAPACITY;
    q->size--;
    return key;

}

void printQueue(queue *q)
{
    if(q->size==0)
    {
        printf("Coada este goala\n");
        return;
    }
    printf("Coada este: \n");
    for(int i=0; i<q->size; i++)
    {
        int index=(q->head+i)%CAPACITY;
        printf("%d ",q->vec[index]);
    }
    printf("\n");

}

//ex3 lab
typedef struct node2
{
    int key;
    struct node2*next;
    struct node2*prev;
} Node;

typedef struct list_header
{
    Node*first;
    Node*last;
} listHeader;

Node* createNod(int key)
{
    Node*p=(Node*)malloc(sizeof(Node));
    p->key=key;
    p->prev=NULL;
    p->next=NULL;
    return p;
}

void insert_first(listHeader*L, int key)
{
    Node*p=createNod(key);
    if(L->first==NULL)
    {
        L->first=L->last=p;
    }
    else
    {
        L->first->prev=p;
        p->next=L->first;
        L->first=p;
    }
}

void insert_last(listHeader *L,int key)
{
    Node*p=createNod(key);
    if(L->first==NULL)
        L->first=L->last=p;
    else
    {
        L->last->next=p;
        p->prev=L->last;
        L->last=p;
    }
}

Node*NodeDL(listHeader*L,int key)
{
    if(L->first==NULL)
    {
        printf("Lista goala\n");
        return;
    }
    else
    {
        Node *p=L->first;
        while(p!=NULL)
        {
            if(p->key==key)
                return p;
            p=p->next;
        }
        return NULL;
    }
}

void insert_after_key(listHeader*L,int afterKey, int key)
{
    Node*p=NodeDL(L,afterKey);
    if(p)
    {
        Node*q=createNod(key);
        q->prev=p;
        q->next=p->next;
        if(p->next!=NULL)
            (p->next)->prev=q;
        else
            L->last=q;
        p->next=q;

    }
}

void printf_forward(listHeader*L)
{
    Node*p=L->first;
    if(p==NULL)
        printf("Lista este goala\n");
    else
    {
        printf("Lista este:\n");
        while(p!=NULL)
        {
            printf("%d ",p->key);
            p=p->next;
        }
        printf("\n");

    }
}

void delete_first(listHeader *L)
{
    if(L->first==NULL)
    {
        printf("Lista este goala\n");
        return;
    }
    Node*p=L->first;
    L->first=L->first->next;
    if(L->first != NULL)
        L->first->prev=NULL;
    else
        L->last = NULL;
    free(p);
}

void delete_last(listHeader *L)
{
    if(L->first==NULL)
    {
        printf("Lista este goala\n");
        return;
    }
    Node*p=L->last;
    L->last=L->last->prev;
    if(L->last != NULL)
        L->last->next=NULL;
    else
        L->first = NULL;
    free(p);
}

void delete_key(listHeader *L, int key)
{
    if(L->first==NULL)
    {
        printf("Lista este goala\n");
        return;
    }
    Node*p=NodeDL(L,key);
    if(p)
    {
        if (p->prev != NULL)
            p->prev->next = p->next;
        else
            L->first = p->next;

        if (p->next != NULL)
            p->next->prev = p->prev;
        else
            L->last = p->prev;
        free(p);

    }

}
void print_backward(listHeader *L)
{
    Node*p=L->last;
    if(p==NULL)
        printf("Lista este goala\n");
    else
    {
        printf("Lista este:\n");
        while(p!=NULL)
        {
            printf("%d ",p->key);
            p=p->prev;
        }
        printf("\n");

    }
}
int main()
{
    NodeT*stack=NULL;

    //ex1 lab
    push(&stack,1);
    push(&stack,2);
    push(&stack,3);

    print_stack(stack);

    pop(&stack);

    print_stack(stack);

    //ex2 lab
    queue q;
    initQueue(&q);

    enqueue(&q,4);
    enqueue(&q,15);
    enqueue(&q,2);
    enqueue(&q,7);
    enqueue(&q,14);

    printQueue(&q);

    int e1=dequeue(&q);
    int e2=dequeue(&q);


    printQueue(&q);

    //ex3 lab
    listHeader L= {NULL,NULL};

    insert_first(&L,12);
    insert_last(&L,100);
    insert_after_key(&L,12,78);

    printf_forward(&L);
    print_backward(&L);

    delete_first(&L);
    printf_forward(&L);

    delete_key(&L,100);
    printf_forward(&L);

    delete_last(&L);
    printf_forward(&L);

    return 0;

}
