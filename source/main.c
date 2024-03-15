#include <stdio.h>
#include <stdlib.h>
#include "linked_lists.h"
#include <string.h>


int ask_input(void){ //used to ask the user for the number of lines of operations
    int num;
    printf("Enter a number n of lines of operations:");
    scanf("%d", &num);
    return num;
}

int generate_num(int min, int max){ //used to (pseudo) randomly generate the operators, operands and number of operations
    return min + rand() % (max - min + 1); //(max - min + 1) is the range
}

void del_list(struct node *L){ //used to delete a linked list before creating a new one for the following line of operations. Needed to save memory
    int len = SListLength(L);
    for (int k = 0; k<len ;k++) //for all the elements in the linked list
        L = deleteSLinkList(L, 1);
}

void compute(struct node *L,int num_operations){ //computes the result of a sequence of operations
    float result = 0;
    int operation = SUM;
    for (int i=1;i<=num_operations;i++){ //for all the operations in the linked list
        struct node *p = readElement(L, i); //retrieves a node of the linked list (in which a specific operation is stored)
        switch (operation){ //depending on the operator, something different is done
            case SUM:
                result += (float) p->value; break;
            case SUB:
                result -= (float) p->value; break;
            case MUL:
                result *= (float) p->value; break;
            case DIV:
                result /= (float) p->value; break;
            default: break;
        }
        operation = p->operation;
    }
    L = insertAfterTail(L, (int) result,RESULT); //the result is stored in a new node at the end of the linked list
    //printSList(L);
}

void write_on_file(struct node *L, int num_operations, int write_name){ //used to create the string containing the operation from the info stored in the linked list
    char line[100] = "";

    for(int i=1; i<=num_operations;i++){ //for all the nodes in the linked list
        struct node *p = readElement(L, i);
        char val[5];
        sprintf(val, "%d", p->value); //the operand is written into the string

        char oper[5];
        int operation = p->operation;
        switch (operation){ //one of +,-,*,/,= is added, depending on the particular operator
            case SUM:
                *oper = '+'; break;
            case SUB:
                *oper = '-'; break;
            case MUL:
                *oper = '*'; break;
            case DIV:
                *oper = '/'; break;
            case LAST:
                *oper = '='; break;
            default: *oper = '\n'; break; //after the result has been written, a \n is added
        }
        strcat(line, val);
        strcat(line, oper);
    }
    printf("%s",line);

    //now that we have the string to write on the file, we open it and we copy the string at the end of it
    FILE* fp;
    fp = fopen("result.txt", "a");
    if(write_name == 0)
        fprintf(fp,"22562325\n");
    fprintf(fp, "%s", line);
    fclose(fp);

}

int main() {

    int lines = ask_input(); //retrieves the number of lines of operations

    for (int i = 0; i< lines; i++){ //for all the lines of operations
        int num_operations = generate_num(3, 5); //returns the number of operations to be done in this line

        struct node*L; //creates a linked list. every of its nodes will store info about an operation
        L = createSLinkList();

        int operation = generate_num(0,3); //decides whether it is +,-,*,/
        L = insertBeforeHead(L,generate_num(0,100),operation); //the first element must be temporarily put in the 1st place
        for (int j = 0; j<num_operations-2;j++){//fills the list with the randomly generated operations
            operation = generate_num(0,3); //decides whether it is +,-,*,/
            //additions and subtractions are less important than multiplications and divisions, so they must be added at the end of the linked list,
            // so as to ensure that they will be evaluated after all the multiplications and divisions when we will solve the operations in sequential order
            if (operation == SUM || operation == SUB){ 
                L = insertAfterTail(L, generate_num(0,100),operation);
            }
            else { //we have a multiplication or a division, so we must add them at the front of the linked list
                L = insertBeforeHead(L,generate_num(0,100),operation);
            }
        }
        L = insertAfterTail(L, generate_num(0,100),LAST); //this is the last operand. it has no operator associated to it

        compute(L,num_operations); //performs the operations

        //now the list contains all the operands, the operators and the final result.
        int write_name = i; //we use write_name to see if it is necessary to write the student ID in the file (it is done only when i==0)
        write_on_file(L,num_operations+1,write_name); //saves everything on a file

        del_list(L); //deletes the list
    }

    return 0;
}
