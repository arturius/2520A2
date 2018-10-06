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
    char rentalRecord[] = "listFile.bin";
/*
    fp = fopen(rentalRecord,"rb"+);
    if (fp == NULL){
        fprintf(stderr,"The file'%s' failed to open\n",rentalRecord);
        exit(1);
    }*/

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
                scanf(" %s", plateNum);
                printf("Please enter miles traveled\n");
                scanf("%d", &milage);
                insertAndSortNode(newCarNode(plateNum, milage,0),&avalible,1);
                break;
            
            case 2:
                printf("Please enter a licence Plate number\n");
                scanf(" %s", plateNum);
                printf("Please enter miles traveled\n");
                scanf("%d", &milage);
                carReturned(&rented, &avalible, plateNum, milage);
                break;

            case 3:
                printf("Please enter a licence Plate number\n");
                scanf(" %s", plateNum);
                printf("Please enter miles traveled\n");
                scanf("%d", &milage);
                carReturned(&rented, &repair, plateNum, milage);
                break;

            case 4:
                printf("Please enter a licence Plate number\n");
                scanf(" %s", plateNum);
                temp = checkForPlate(&repair, plateNum);
                if (temp){
                    transferNode(&repair, &avalible, temp, 1);
                    printf("Car succesfuly tranfered from repair to avalbile to rent\n");
                }else{
                    printf("Invaled Plate Number\n");
                }
                break;

            case 5:
                printf("Please enter a return date (yymmdd)\n");
                scanf("%d",&date);
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
carNode *newCarNode(char *givenPlate, int givenMillage, int givenReturnDate){
    carNode *newNode;
    newNode = malloc(sizeof (carNode));
    newNode->millage = givenMillage;
    newNode->returnDate = givenReturnDate;
    newNode->plateNum = malloc(strlen(givenPlate)+1);
    strcpy(newNode->plateNum, givenPlate);

    newNode->next = NULL;
    return newNode;
}

void popNode (carNode **givenList, carNode *targetNode){
    carNode *list, *temp;
    list = *givenList;
    if (list == targetNode){
        temp = list;
        *givenList = list->next;
        temp-> next = NULL;
    }else{
        while(list){
            if (list-> next == targetNode){
                temp = list ->next;
                list->next = (list->next)->next;
                temp-> next = NULL;
            } 
            list = list->next;
        }
    }
}

void transferNode(carNode **sourceList, carNode **destList, carNode *givenNode, int sortFlag){
    popNode(sourceList,givenNode);
    insertAndSortNode( givenNode, destList,sortFlag);
}

void printList(carNode **givenList){
    carNode *list;
    list = *givenList;
    while(list){
        printf("Plate #: %s, Mileage: %d, Expected return date: %d\n", list-> plateNum, list-> millage, list-> returnDate);
        list = list->next;
    }
}

void rentCar(carNode **rented, carNode **avalible,int givenDate){
    carNode *temp = NULL;
    
    temp = *avalible;
    
    if (temp){
        temp->returnDate = givenDate;
        transferNode(avalible, rented, temp,2);
        printf("Car succesfuly rented\n");
    }else{
            printf("Invaled Plate Number\n");
    }
    
}

void carReturned (carNode **rented, carNode **targetList, char *givenPlate, int newMillage){
    carNode *temp = NULL;
    
    temp = checkForPlate(rented, givenPlate);
    if (temp){
        temp->returnDate = 0;
        transferNode(rented, targetList, temp,1);
        printf("Car succesfuly returned\n");
    }else{
        printf("Invaled Plate Number\n");
    }
}

carNode *checkForPlate(carNode **givenList, char *givenPlate){
    carNode *list;
    list = *givenList;
    while(list){
        if (strcmp(list->plateNum, givenPlate)==0){
            return list;
        }
        list = list->next;
    }

    return NULL;
}
void insertAndSortNode(carNode *givenNode, carNode **targetList, int sortFlag){
    carNode *list;
    carNode *temp = NULL;
    list = *targetList;
    printf("Sorting nodes\n");
    if (!list){
        *targetList = givenNode;
        return;
    }
    switch (sortFlag){
        case 1:
            while (list && givenNode-> millage > list->millage){
                temp = list;
                list = list->next; 
            }
            if (!temp){
                givenNode->next = *targetList;
                *targetList = givenNode;
            }else{
                temp->next = givenNode;
                givenNode->next = list;
            }
            break;
        case 2:
            while (list && givenNode-> returnDate > list->returnDate){
                temp = list;
                list = list->next; 
            }
            if (!temp){
                givenNode->next = *targetList;
                *targetList = givenNode;
            }else{
                temp->next = givenNode;
                givenNode->next = list;
            }          
            break;
        default:
            printf("Invalid sortflag\n");
    }
}

void deleteNode(carNode *targetNode){
    free(targetNode->plateNum);
    free(targetNode);
}

void deleteList (carNode **targetList){
    while(*targetList){
        
    }
}

int listSize(carNode **givenList){
    int count = 0;
    carNode *list = *givenList;
    while(list){
        count++;
        list= list->next;
    }
    return count;
}
/* Structure for files
first 3 values representing the lenth of the linked lists: rented, avalible and repair in that order
the next values are a number of carNodes up to the lenth of their repected lists 
after that there will all the licence plate insequetial order
*/
carNode *copyNode(carNode *givenNode){
    carNode *newNode;
    newNode = malloc(sizeof (carNode));
    newNode->millage = givenNode-> millage;
    newNode->returnDate =  givenNode-> returnDate;
    newNode->plateNum = malloc(strlen(givenNode-> plateNum)+1);
    strcpy(newNode->plateNum, givenNode-> plateNum);

    newNode->next = givenNode->next;
    return newNode;

}

void loadLnkdLsts(FILE *fp, carNode **rented, carNode **avalible, carNode **repair){
    int rentLen = 0;
    int avalibleLen = 0;
    int repairLen = 0;
    int i;
    carNode *holding;
    fseek (fp, 0, SEEK_SET);
    fread (&rentLen,sizeof(int),1,fp);
    fread (&avalibleLen,sizeof(int),1,fp);
    fread (&repairLen,sizeof(int),1,fp);
    fseek(fp, sizeof(int)*3, SEEK_SET);

    for(i = 1; i<= rentLen;i++){
        fread()
    }

}

void writeLnkdLsts(FILE *fp, carNode **rented, carNode **avalible, carNode **repair){
    int rentLen = listSize(rented);
    int avalibleLen = listSize(avalible);
    int repairLen = listSize(repair);
    carNode *holding, *list;
    fseek (fp,0,SEEK_SET);
    fwrite(&rentLen,sizeof(int),fp);
    fwrite(&avalibleLen,sizeof(int),fp);
    fwrite(&repairLen, sizeof(int),fp);
    
    list = *rented;
    while (list){
        holding = copyNode(list);
        holding->next = NULL;
        fwrite(&holding,sizeof(carNode),fp);//have to fix the string problem 
        deleteNode(holding);
        list = list->next;
    }
    
    list = *avalible;
    while (list){
        holding = copyNode(list);
        holding->next = NULL;
        fwrite(&holding,sizeof(carNode),fp);
        deleteNode(holding);
        list = list->next;
    }

    list = *repair;
    while (list){
        holding = copyNode(list);
        holding->next = NULL;
        fwrite(&holding,sizeof(carNode),fp);
        deleteNode(holding);
        list = list->next;
    }
}
