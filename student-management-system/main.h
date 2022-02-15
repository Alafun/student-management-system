#pragma once

//import header
#include<stdio.h>
#include<conio.h>  //_getch()
#include<stdlib.h> //system()
#include<string.h> //strlen()

//define datastruct
typedef struct stuInfo {
	char stuName[20];
	char stuGender[4];
	int stuAge;
	int stuID; //key
	int stuScore;
}stuInfo;
typedef struct stuNode {
	stuInfo stud;
	struct stuNode* next;
}stuNode;
stuNode* head = NULL;

//declaration zone
void printMenu();
void inputStudInfo();
void printStudInfo();
void saveStudInfo();
void readStudInfo();
void countStudNum();
void findStudInfo();
void changeStudInfo();
void deleteStudInfo();
