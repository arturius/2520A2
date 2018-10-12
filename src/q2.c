/*  q2.c
    Main Function file for CIS 2520 Assignment 2 question 2.
    By: James Arthur Anderson
    Student ID #: 1013076
    Date: Oct. 14, 2018
*/
#include"A2.h"

int main(int argc,char **argv){
    int i;
    double convert;
    stackNode *val1, *val2;
    double result;
    stackNode *list;
    stackNode *holding;
    if (argc == 2){
        for (i = 0;argv[1][i]; i++){
            /*Code is based of the the pseudo code from https://en.wikipedia.org/Reverse_Polish_notation
            */
            switch (argv[1][i]){
                case '+':
                    val1 = popStack(&list);
                    val2 = popStack(&list);
                    result = val2->value + val1->value;
                    free(val1);
                    free(val2);
                    holding = newStackNode(result);
                    pushNode(&list,holding);
                    break;

                case '-':
                    val1 = popStack(&list);
                    val2 = popStack(&list);
                    result = val2->value - val1->value;
                    free(val1);
                    free(val2);
                    holding = newStackNode(result);
                    pushNode(&list,holding);
                    break;

                case '*':
                    val1 = popStack(&list);
                    val2 = popStack(&list);
                    result = val2->value * val1->value;
                    free(val1);
                    free(val2);
                    holding = newStackNode(result);
                    pushNode(&list,holding);

                    break;

                case '/':
                    val1 = popStack(&list);
                    val2 = popStack(&list);
                    result = val2->value / val1->value;
                    free(val1);
                    free(val2);
                    holding = newStackNode(result);
                    pushNode(&list,holding);

                    break;

                default:
                    convert = (double)argv[1][i] - '0';//converting char to a double
                    printf("convert %f\n",convert);
                    holding = newStackNode(convert);
                    pushNode(&list,holding);
            }
        }
        holding = popStack(&list);
        printf ("Value is %.2f\n",holding->value);
        free(holding);
    }else{
        printf("Invalid number of command line arguments\n");
    }
    return 0;
}
//returns and removes the  node from the top of a given stack
stackNode *popStack (stackNode **list){
    stackNode *returnNode;
    returnNode = *list;
    *list = (*list)-> next;
    returnNode-> next = NULL;
    return returnNode;
}
//pushes node to the top of a given stack
void pushNode (stackNode **list, stackNode *newNode){
    newNode-> next = *list;
    *list = newNode;
}
//creates a new stack node
stackNode *newStackNode(double value){
    stackNode *newNode = NULL;
    newNode = malloc(sizeof(stackNode));
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}



