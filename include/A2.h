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
    char *plateNum;
    int millage;
    int returnDate;
    int profit;

    carNode *next;
};
//functions
void newCarNode(carNode **givenList, char *givenPlate, int givenMillage);
void popNode (carNode **givenList, carNode *targetNode)

void transferNode(carNode **sourceList, carNode **destList, carNode *givenNode);
void printList(carNode **givenList);

void rentCar(carNode **rented, carNode **avalible,int givenDate);
void carReturned (carNode **rented, carNode **targetList, int targetFlag, carNode *givenPlate, int newMillage);
carNode *checkForPlate(carNode **givenList, char *givenPlate);
void insertAndSortNode(int sortFlag, carNode *givenNode, carNode **targetList);

void deleteNode(carNode *targetNode);
void deleteList (carNode **targetList);

//int listSize(carNode **givenList);
//void loadLnkdLsts();
//void writeLnkdLsts();
/*Question 2 structs and Functions*/


#endif

  
