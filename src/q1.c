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
    /*Loading file*/
    fp = fopen(rentalRecord,"rb");
    if (fp == NULL){
        fprintf(stderr,"The file'%s' failed to open\n",rentalRecord);
        exit(1);
    }
    loadLnkdLsts(fp,&rented,&avalible,&repair);
    fclose(fp);
    /*Main program operation*/
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
                printf("\n");
                break;

            case 7:
                printf ("Total profit is $%.2f.\n",totalProfit(&rented,&avalible,&repair));
                fp = fopen(rentalRecord,"wb");
                    if (fp == NULL){
                    fprintf(stderr,"The file'%s' failed to open\n",rentalRecord);
                    exit(1);
                }
                writeLnkdLsts(fp, &rented, &avalible, &repair);
                fclose(fp);
                break;

            default:
                printf("Invalid transaction code ");
            
        }
 
    }while(transCode != 7);
    
    return 0;
}
/*creates new carnode given a plate number, milage and potential return date*/
carNode *newCarNode(char givenPlate[10], int givenMillage, int givenReturnDate){
    carNode *newNode;
    newNode = malloc(sizeof (carNode));
    newNode->millage = givenMillage;
    newNode->returnDate = givenReturnDate;
    strcpy(newNode->plateNum, givenPlate);

    newNode->next = NULL;
    return newNode;
}
/*pops a given node from a list*/
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
/*transfers the node from one list to another with it being sorted acording to the sortflag*/
void transferNode(carNode **sourceList, carNode **destList, carNode *givenNode, int sortFlag){
    popNode(sourceList,givenNode);
    insertAndSortNode( givenNode, destList,sortFlag);
}
/*prints the platenumber mileage and expected return date of all th cars in a given node*/
void printList(carNode **givenList){
    carNode *list;
    list = *givenList;
    while(list){
        printf("Plate #: %s, Mileage: %d, Expected return date: %d\n", list-> plateNum, list-> millage, list-> returnDate);
        list = list->next;
    }
}
/*calculates the total profits of all the cars*/
double totalProfit(carNode **rented, carNode **avalible, carNode **repair){
    double profit = 0;
    carNode *list;
    
    list = *rented;
    while (list){
        profit += list->profit;
        list = list->next;
    }
    list = *repair;
    while (list){
        profit += list->profit;
        list = list->next;
    }
    list = *avalible;
    while (list){
        profit += list->profit;
        list = list->next;
    }
    return profit;
}

void rentCar(carNode **rented, carNode **avalible,int givenDate){
    carNode *temp = NULL;
    
    temp = *avalible;
    
    if (temp){
        temp->returnDate = givenDate;
        transferNode(avalible, rented, temp,2);
        printf("Car succesfuly rented\n");
    }else{
        printf("No car avalible to rent\n");
    }
    
}

void carReturned (carNode **rented, carNode **targetList, char givenPlate[10], int newMillage){
    carNode *temp = NULL;
    double charge = 0;
    temp = checkForPlate(rented, givenPlate);
    if (temp){
        temp->returnDate = 0;
        if (newMillage < 100){
            charge = 40;
        }else{
            charge = 40 + (0.15*(newMillage-100));
        }
        printf("Charge of $%.2f is required\n",charge);
        temp-> millage += newMillage;
        temp-> profit += charge;
        transferNode(rented, targetList, temp,1);
        printf("Car succesfuly returned\n");
    }else{
        printf("Invaled Plate Number\n");
    }
}
/*checks to see if a given licennce plate is in a given linked list and returns it if found; returns null if not found*/
carNode *checkForPlate(carNode **givenList, char givenPlate[10]){
    carNode *list;
    list = *givenList;
    while(list){
        if (strcmp(list->plateNum, givenPlate)==0){
            return list;
        }
        list = list->next;
    }

    return NULL;//if plate number is not in list
}
/*inserts a node into a given list base on the sort flag*/
void insertAndSortNode(carNode *givenNode, carNode **targetList, int sortFlag){
    carNode *list;
    carNode *temp = NULL;
    list = *targetList;
    
    //check and insert if given list is empty
    if (!list){
        *targetList = givenNode;
        return;
    }

    switch (sortFlag){
        case 1:// sorting by least millage
            /*sorting algorith is a modified version from the c02-f18 lecture slides*/
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
        case 2:// sorting by lowest date
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

void deleteCarNode(carNode *targetNode){
    free(targetNode);
}

void deleteCarList (carNode **targetList){
    carNode *temp;
    while(*targetList){
        temp = (*targetList)->next;
        deleteCarNode(*targetList);
        *targetList = temp;
    }
}
//calculates the size of a given list
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
first 3 values representing the lenth of the linked lists: rented, avalible and repair; in that order
the next values are a number of carNodes up to the lenth of their repected lists one after the other
*/

/*returns a copy of a given node*/
carNode *copyNode(carNode *givenNode){
    carNode *newNode;
    newNode = malloc(sizeof (carNode));
    newNode->millage = givenNode-> millage;
    newNode->returnDate =  givenNode-> returnDate;
    
    strcpy(newNode->plateNum, givenNode-> plateNum);

    newNode->next = givenNode->next;
    return newNode;

}

void loadLnkdLsts(FILE *fp, carNode **rented, carNode **avalible, carNode **repair){
    int rentLen = 0;
    int avalibleLen = 0;
    int repairLen = 0;
    int i;
    carNode holding;
    /*geting size of each linked list*/
    fseek (fp, 0, SEEK_SET);
    fread (&rentLen,sizeof(int),1,fp);
    fread (&avalibleLen,sizeof(int),1,fp);
    fread (&repairLen,sizeof(int),1,fp);
    fseek(fp, sizeof(int)*3, SEEK_SET);
    /*reading and storing rented cars*/
    for(i = 1; i<= rentLen;i++){
        fread(&holding,sizeof(carNode),1,fp);
        insertAndSortNode(newCarNode(holding.plateNum, holding.millage, holding.returnDate), rented, 2);
    }
    /*reading and storing avalible cars*/
    for(i = 1; i<= avalibleLen;i++){
        fread(&holding,sizeof(carNode),1,fp);
        insertAndSortNode(newCarNode(holding.plateNum, holding.millage, holding.returnDate), avalible, 1);
    }
    /*reading and storing cars in repair*/
    for(i = 1; i<= repairLen;i++){
        fread(&holding,sizeof(carNode),1,fp);
        insertAndSortNode(newCarNode(holding.plateNum, holding.millage, holding.returnDate), repair, 1);
    }
 }

void writeLnkdLsts(FILE *fp, carNode **rented, carNode **avalible, carNode **repair){
    int rentLen = listSize(rented);
    int avalibleLen = listSize(avalible);
    int repairLen = listSize(repair);
    carNode *holding, *list;
    /*calculating and writing the size of each linked list to the file*/
    fseek (fp,0,SEEK_SET);
    fwrite(&rentLen,sizeof(int),1,fp);
    fwrite(&avalibleLen,sizeof(int),1,fp);
    fwrite(&repairLen, sizeof(int),1,fp);
    /*writing the rented list*/
    list = *rented;
    while (list){
        holding = copyNode(list);
        holding->next = NULL;
        fwrite(holding,sizeof(carNode),1,fp);
        deleteCarNode(holding);
        list = list->next;
    }
    /*writing the avalible cars list*/
    list = *avalible;
    while (list){
        holding = copyNode(list);
        holding->next = NULL;
        fwrite(holding,sizeof(carNode),1,fp);
        deleteCarNode(holding);
        list = list->next;
    }
    /*writing the reapired car list*/
    list = *repair;
    while (list){
        holding = copyNode(list);
        holding->next = NULL;
        fwrite(holding,sizeof(carNode),1,fp);
        deleteCarNode(holding);
        list = list->next;
    }
}
