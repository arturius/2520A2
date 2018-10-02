/*  q1.c
    Main Function file for CIS 2520 Assignment 2 question 1.
    By: James Arthur Anderson
    Student ID #: 1013076
    Date: Oct. 14, 2018
*/
#include"A2.h"

int main(){
    int transCode = 0;
    char plateNum[10];
    int milage;
    int date;
    FILE *fp = NULL;
    carNode *rented = NULL;
    carNode *avalible = NULL;
    carNode *repair = NULL;
    carNode *temp = NULL;
    
    printf("Hello and welcome to car rental company database\n");
    do{
        printf("Please enter a transaction code\n");
        printf("Press 1 to add a new car to the avalible to rent list\n");
        printf("Press 2 to add a returned car to the avaliable to rent list\n");
        printf("Press 3 to add a returned car to the repair list\n");
        printf("Press 4 to transfer a car from the the repair list to the avalible to rent list\n");
        printf("Press 5 to rent the first avalible car\n");
        printf("Press 6 to print all the lists\n");
        printf("Press 7 to quit\n");
        scanf("%d", &transCode);
        switch (transCode){
            case 1:
                printf("Please enter a licence Plate number\n");
                scanf("%s", &plateNum);
                prinf("Please enter miles traveled\n");
                scanf("%d", &milage);
                newCarNode(&avalible, plateNum, milage);
                break;
            
            case 2:
                printf("Please enter a licence Plate number\n");
                scanf("%s", &plateNum);
                prinf("Please enter miles traveled\n");
                scanf("%d", &milage);
                carReturned(&rented, &avalible, 1, plateNum, milage);
                break;

            case 3:
                printf("Please enter a licence Plate number\n");
                scanf("%s", &plateNum);
                prinf("Please enter miles traveled\n");
                scanf("%d", &milage);
                carReturned(&rented, &repair, 2, plateNum, milage);
                break;

            case 4:
                printf("Please enter a licence Plate number\n");
                scanf("%s", &plateNum);
                temp = checkForPlate(&repair, plateNum);
                if (temp){
                    transferNode(&repair, &avalible, temp);
                    printf("Car succesfuly tranfered from repair to avalbile to rent\n");
                }else{
                    printf("Invaled Plate Number\n");
                }
                break;

            case 5:
                printf("Please enter a return date (yymmdd)\n");
                scanf("%d",&date)
                rentCar(&rented, &avalible, date);
                break;

            case 6:
                printf("Showing All the lists\nRented Cars:\n");
                printList(&rented);
                printf("Cars Avalible to Rent:\n");
                printList(&avalible);
                printf("Cars in repair\n");
                printList(&repair);
                break;

            case 7:
                
                break;

            default:
                printf("Invalid transaction code ");
            
        }
 
    }while(transCode != 7);
    
    return 0;
}
void newCarNode(carNode **givenList, carNode *toAdd, char *givenPlate, int givenMillage){

}

void popNode (carNode **givenList, carNode *targetNode){

}

void transferNode(carNode **sourceList, carNode **destList, carNode *givenNode){
    
}

void printList(carNode **givenList){

}

void rentCar(carNode **rented, carNode **avalible,int givenDate){
    carNode *temp = NULL;
    
    temp = checkForPlate(, plateNum);
    if (temp){
        transferNode(rented, avalible, temp);
        printf("Car succesfuly tranfered from repair to avalbile to rent\n");
    }else{
        printf("Invaled Plate Number\n");
    }
}

void carReturned (carNode **rented, carNode **targetList, int targetFlag, carNode *givenPlate, int newMillage){

}

carNode *checkForPlate(carNode **givenList, char *givenPlate){
    carNode *list;
    list = *givenList
    while(list){
        if (strcmp(list->plateNum, givenPlate)==0){
            return list;
        }
        list = list->next;
    }

    return NULL;
}
void insertAndSortNode(int sortFlag, carNode *givenNode, carNode **targetList){

}

void deleteNode(carNode *targetNode){
    free(targetNode->plateNum);
    free(targetNode);
}

void deleteList (carNode **targetList){
    while()
}
