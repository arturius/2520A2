/*  A2.h
    Header File for : CIS 2520 Assignment 2.
    By: James Arthur Anderson
    Student ID #: 1013076
    Date: Oct. 14, 2018
*/
/*including of standard libraries*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#ifndef A2_H
#define A2_H
/*Question 1 stucts and functions*/
//structs
typedef struct carNodeStruct carNode;
struct carNodeStruct{
    int millage;
    int returnDate;
    double profit;
    char plateNum[10];
    carNode *next;
};
//functions
carNode *newCarNode( char givenPlate[10], int givenMillage, int givenReturnDate);
void popNode (carNode **givenList, carNode *targetNode);

void transferNode(carNode **sourceList, carNode **destList, carNode *givenNode,int sortFlag);
void printList(carNode **givenList);
double totalProfit(carNode **rented, carNode **avalible, carNode **repair);

void rentCar(carNode **rented, carNode **avalible,int givenDate);
void carReturned (carNode **rented, carNode **targetList, char givenPlate[10], int newMillage);
carNode *checkForPlate(carNode **givenList, char givenPlate[10]);
void insertAndSortNode( carNode *givenNode, carNode **targetList, int sortFlag);
/*If sortflag = 0 puts it in the front of the list, if sortFlag = 1 then sorting by milage fromgreatest to least, if Sort flag =2 then sorting by return date */

void deleteCarNode(carNode *targetNode);
void deleteCarList (carNode **targetList);

carNode *copyNode(carNode *givenNode);
int listSize(carNode **givenList);
void loadLnkdLsts(FILE *fp, carNode **rented, carNode **avalible, carNode **repair);
void writeLnkdLsts(FILE *fp, carNode **rented, carNode **avalible, carNode **repair);
/*Question 2 structs and Functions*/
//structs
typedef struct stackNodeStruct stackNode;
struct stackNodeStruct{
    double value;
    stackNode *next;
};
//functions
stackNode *popStack (stackNode **list);
void pushNode (stackNode **list, stackNode *newNode);
stackNode *newStackNode(double value);

void deleteStackNode(stackNode *targetNode);
void deleteStackList (stackNode **targetList);
#endif

  
