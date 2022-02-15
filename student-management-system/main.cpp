#define _CRT_SECURE_NO_WARNINGS
#include"main.h"


int main() {
	while (1) {
		printMenu();
		char buffer = _getch();
		switch (buffer) {
		case '1':
			inputStudInfo();
			break;
		case '2':
			printStudInfo();
			break;
		case '3':
			saveStudInfo();
			break;
		case '4':
			readStudInfo();
			break;
		case '5':
			countStudNum();
			break;
		case '6':
			findStudInfo();
			break;
		case '7':
			changeStudInfo();
			break;
		case '8':
			deleteStudInfo();
			break;
		case 0:
			return 0;
			break;
		default:
			printf("input error...");
			system("pause");
			system("cls");
			break;
		}
	}
	return 0;
}

void printMenu() {
	printf("*************************************************\n");
	printf("*\t欢迎使用高校学生成绩管理系统V1.0\t*\n");
	printf("*\t\t请选择功能\t\t\t*\n");
	printf("*************************************************\n");
	printf("*\t\t1.录入学生信息\t\t\t*\n");
	printf("*\t\t2.打印学生信息\t\t\t*\n");
	printf("*\t\t3.保存学生信息\t\t\t*\n");
	printf("*\t\t4.读取学生信息\t\t\t*\n");
	printf("*\t\t5.统计所有学生人数\t\t*\n");
	printf("*\t\t6.查找学生信息\t\t\t*\n");
	printf("*\t\t7.修改学生信息\t\t\t*\n");
	printf("*\t\t8.删除学生信息\t\t\t*\n");
	printf("*\t\t0.退出系统\t\t\t*\n");
	printf("*************************************************\n");
}
void inputStudInfo() {
	stuNode* newStud = (stuNode*)malloc(sizeof(stuNode));
	newStud->next = NULL;
	stuNode* tail = head;
	while (head != NULL && tail->next != NULL) {
		tail = tail->next; //loop untill tail is tail
	}
	if (head == NULL) {
		head = newStud;
	}else{
		tail->next = newStud;
	}

	printf("请输入学生姓名：\n");
	scanf_s("%s", newStud->stud.stuName, sizeof(newStud->stud.stuName));
	printf("请输入性别：\n");
	scanf_s("%s", newStud->stud.stuGender, sizeof(newStud->stud.stuGender));
	printf("请输入学生年龄：\n");
	scanf_s("%d", &newStud->stud.stuAge);
	printf("请输入学号：\n");
	scanf_s("%d", &newStud->stud.stuID);
	printf("请输入成绩：\n");
	scanf_s("%d", &newStud->stud.stuScore);
	printf("学生信息录入成功。\n\n");
	system("pause");
	system("cls");
}
void printStudInfo() {
	system("cls");
	stuNode* oper = head;//operating node
	if (oper == NULL) {
		printf("系统中暂无学生信息，请录入后再来打印查看。\n\n");
	}else{
		printf("*********************************************************************************\n");
		printf("*\t\t\t欢迎使用高校学生成绩管理系统V1.0\t\t\t*\n");
		printf("*********************************************************************************\n");
		printf("*\t学号\t*\t姓名\t*\t性别\t*\t年龄\t*\t成绩\t*\n");
		printf("*********************************************************************************\n");
		while (oper!=NULL){
			printf("*\t%d\t*\t%s\t*\t%s\t*\t%d\t*\t%d\t*\n",
				oper->stud.stuID,
				oper->stud.stuName,
				oper->stud.stuGender,
				oper->stud.stuAge,
				oper->stud.stuScore);
			oper = oper->next;
			printf("*********************************************************************************\n");
		}
	}
	system("pause");
	system("cls");
}
void saveStudInfo() {
	FILE* operFile;
	operFile = fopen(".\\data.dat", "w"); //.dat
	if (operFile == NULL) {
		printf("打开文件失败...\n");
		return;
	}
	stuNode* oper = head;
	while (oper != NULL) {
		fprintf(operFile,"*\t%d\t*\t%s\t*\t%s\t*\t%d\t*\t%d\t*\n",
			oper->stud.stuID,
			oper->stud.stuName,
			oper->stud.stuGender,
			oper->stud.stuAge,
			oper->stud.stuScore
			);
		oper = oper->next;
	}
	fclose(operFile);
	printf("数据保存成功。\n");
	system("pause");
	system("cls");
}
void readStudInfo() {
	system("cls");
	FILE* operFile;
	operFile = fopen(".\\data.dat", "r");
	if (operFile == NULL) {
		printf("打开文件失败。\n");
		return;
	}
	stuNode* oper = (stuNode*)malloc(sizeof(stuNode));
	oper->next = NULL;
	head = oper;
	char str[200];
	int i = 0;
	while (fscanf(operFile,"%s",str)!=EOF) {
		if (strcmp(str, "*") && str != NULL) {
			switch (i) {
			case 0:
				oper->stud.stuID = atoi(str); //stdlib.h
				break;
			case 1:
				strcpy(oper->stud.stuName, str);
				break;
			case 2:
				strcpy(oper->stud.stuGender, str);
				break;
			case 3:
				oper->stud.stuScore = atoi(str);
				break;
			case 4:
				oper->stud.stuScore = atoi(str);
			default:
				stuNode* newStud = (stuNode*)malloc(sizeof(stuNode));
				newStud->next = NULL; //init new_student_node
				oper->next = newStud;
				oper = newStud;
				oper->stud.stuID = atoi(str);
				i = 0; //
				break;
			}
			i++;
		}
	}
	printStudInfo();
}
void countStudNum() {
	int count = 0;
	stuNode* oper = head;
	while (oper != NULL) {
		count++;
		oper = oper->next;
	}
	printf("学生总人数：%d\n\n", count);
	system("pause");
	system("cls");
}
void findStudInfo() {
	system("cls");
	int key;
	printf("请输入查找学生学号：");
	scanf("%d", &key);
	stuNode* oper = head;
	bool isShowHead = false;
	bool isFindStu = false;
	while (oper!=NULL)	{
		if (key == oper->stud.stuID) {
			if (!isShowHead) {
				printf("*********************************************************************************\n");
				printf("*\t学号\t*\t姓名\t*\t性别\t*\t年龄\t*\t成绩\t*\n");
				printf("*********************************************************************************\n");
				isShowHead = true;
			}
			printf("*\t%d\t*\t%s\t*\t%s\t*\t%d\t*\t%d\t*\n",
				oper->stud.stuID,
				oper->stud.stuName,
				oper->stud.stuGender,
				oper->stud.stuAge,
				oper->stud.stuScore
			);
			isFindStu = true;
			printf("*********************************************************************************\n");
		}
		oper = oper->next;
	}
	if (!isFindStu) {
		printf("学号输入有误，系统中暂无该学生信息。\n\n");
	}
	system("pause");
	system("cls");
}
void changeStudInfo() {
	int key;
	printf("请输入欲修改学生的学号：");
	scanf("%d", &key);
	stuNode* oper = head;
	bool isShowHead = false;
	bool isFindStu = false;
	while (oper != NULL)
	{
		if (key == oper->stud.stuID) {
			if (!isShowHead) {
				printf("*********************************************************************************\n");
				printf("*\t学号\t*\t姓名\t*\t性别\t*\t年龄\t*\t成绩\t*\n");
				printf("*********************************************************************************\n");
				isShowHead = true;
			}
			printf("*\t%d\t*\t%s\t*\t%s\t*\t%d\t*\t%d\t*\n",
				oper->stud.stuID,
				oper->stud.stuName,
				oper->stud.stuGender,
				oper->stud.stuAge,
				oper->stud.stuScore
			);
			//修改学生信息
			printf("请输入学生姓名：\n");
			scanf_s("%s", oper->stud.stuName, sizeof(oper->stud.stuName));
			printf("请输入性别：\n");
			scanf_s("%s", oper->stud.stuGender, sizeof(oper->stud.stuGender));
			printf("请输入学生年龄：\n");
			scanf_s("%d", &oper->stud.stuAge);
			printf("请输入学号：\n");
			scanf_s("%d", &oper->stud.stuID);
			printf("请输入成绩：\n");
			scanf_s("%d", &oper->stud.stuScore);
			isFindStu = true;
			printf("*********************************************************************************\n");
			printf("学生信息修改成功，请注意及时保存。\n\n");
		}
		oper = oper->next;
	}

	if (!isFindStu) {
		printf("学号输入有误，系统中暂无该学生信息，无法进行修改。\n\n");
	}

	system("pause");
	system("cls");
}
void deleteStudInfo() {
	system("cls");
	int key;
	printf("请输入删除学生的学号：");
	scanf("%d", &key);
	stuNode* oper = head;
	stuNode* beforeNode = head;
	bool isShowHead = false;
	bool isFindStu = false;
	while (oper != NULL)
	{
		if (key == oper->stud.stuID) {
			if (!isShowHead) {
				printf("*********************************************************************************\n");
				printf("*\t学号\t*\t姓名\t*\t性别\t*\t年龄\t*\t成绩\t*\n");
				printf("*********************************************************************************\n");
				isShowHead = true;
			}
			printf("*\t%d\t*\t%s\t*\t%s\t*\t%d\t*\t%d\t*\n",
				oper->stud.stuID,
				oper->stud.stuName,
				oper->stud.stuGender,
				oper->stud.stuAge,
				oper->stud.stuScore
			);
			isFindStu = true;
			printf("*********************************************************************************\n");
			if (oper == head) {
				head = oper->next;
			}else if (oper->next == NULL) {
				oper = beforeNode;
				oper->next = NULL;
			}else {
				beforeNode->next = oper->next;
			}
			printf("删除成功，请记得保存。\n\n");
		}
		beforeNode = oper;
		oper = oper->next;
	}
	if (!isFindStu) {
		printf("学号输入有误，系统中暂无该学生信息，无法进行删除操作。\n\n");
	}
	system("pause");
	system("cls");
}