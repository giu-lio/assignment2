#ifndef PERSONAL_ASSIGNMENT_2_LINKED_LISTS_H
#define PERSONAL_ASSIGNMENT_2_LINKED_LISTS_H

#define SUM 0
#define SUB 1
#define MUL 2
#define DIV 3
#define LAST 88
#define RESULT 99

typedef int EleType;
struct node{
    EleType operation;
    EleType value; //we use EleType instead of int bc it's more convenient to modify the type of value in some functions
    struct node *next; //pointer to the next element of the linked  list
};

extern struct node* createSLinkList(void);
extern void printSList(struct node *head);
extern int SListLength(struct node*head);
extern struct node* insertBeforeHead(struct node*head, int val, int oper);
extern struct node * insertAfterTail(struct node *head, int val, int oper);
extern struct node* deleteSLinkList(struct node* head, int index);
extern struct node * readElement(struct node*head, int index);

#endif //PERSONAL_ASSIGNMENT_2_LINKED_LISTS_H
