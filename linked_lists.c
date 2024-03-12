#include "linked_lists.h"
#include <stdio.h>
#include <stdlib.h>

//T(n)=O(1)
struct node* createSLinkList(void){ //we don't need to know the size bc memory is allocated dynamically
    struct node *head=NULL;
    return head; //we just return the pointer to the first element
}

//T(n)=O(n)
void printSList(struct node *head){
    //we need to declare a temporary pointer. We use it to access the elements of the list. Wd do not move the pointer head
    struct node* p = head;
    while(p!=NULL){ //p is NULL when we have printed all the elements (the last one has p->next=NULL, so p becomes NULL)
        printf("%d ",p->value);
        printf("%d \n",p->operation);
        p=p->next;//we go to the next element in the linked list
    }
    printf("end\n");
}

//T=O(n)
int SListLength(struct node*head){
    int count = 0;
    struct node* p = head; //temporary pointer
    while(p!=NULL){
        count++;
        p=p->next;
    }
    return count;
}



struct node* insertBeforeHead(struct node*head, int val,int oper){
    struct node * newp;
    newp=(struct node *)malloc(sizeof(struct node));
    if (newp==NULL){
        printf("error in memory of new node\n");
        return NULL;
    }
    newp->value=val;
    newp->operation=oper;
    newp->next=head; //bc we insert the new value before the head value
    head = newp; //now head is pointing again to the head element
    return head;
}


//T(n)=O(n)
struct node * insertAfterTail(struct node *head, int val, int oper){
    struct node * newp;
    newp=(struct node *)malloc(sizeof(struct node));
    if (newp==NULL){
        printf("error in memory of new node\n");
        return NULL;
    }
    newp->value=val;
    newp->operation = oper;
    struct node*p=head; //temporary pointer. we use it to access the last element
    int i=1;
    while(p!=NULL && i<SListLength(head)){
        p=p->next;//we move p until it is pointing to the last element
        i++;
    }
    newp->next=NULL;
    p->next=newp;
    return head;
}

//T(n)=O(n)
struct node* deleteSLinkList(struct node* head, int index){//deletes the element in the given position index
    struct node *q = NULL;//temporary pointer
    struct node *p = head;//temporary pointer. we use it to reach the element with index 'index'
    int i=1;

    if(index==1){//Case 1: if the element we want to remove is the first one
        head=p->next; //now head is the second element. We can safely delete the 1st one
        free(p);
        return head;
    }
    else{//Case 2: if the element is in the middle or at the tail
        if(index<1 || index> SListLength(head)){// '||' means 'or'
            printf("The position is illegal\n");
            return head;
        }
        while(p->next && i<index-1){//p->next != NULL
            p=p->next;
            i++;
        }
        q = p->next; //q is the node we want to delete
        p->next = q->next;//we skip the node q
        free(q);
        return head;
    }
}

struct node * readElement(struct node*head, int index){
    if (index>SListLength(head)) {
        printf("The specified index is illegal");
        return 0;
    }
    struct node *p=head;
    int i=1;
    while(i<index){
        p=p->next;//we move p until it is pointing to the correct element(with the given index)
        i++;
    } //we must use this while loop to find the element.
    // It's different from arrays (here we can't use the index like "array[index]")
    /*EleType e = p->value;
    printf("The value in %d position is %d\n",index,e);*/
    return p;
}