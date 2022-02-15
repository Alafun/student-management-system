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
	printf("*\t��ӭʹ�ø�Уѧ���ɼ�����ϵͳV1.0\t*\n");
	printf("*\t\t��ѡ����\t\t\t*\n");
	printf("*************************************************\n");
	printf("*\t\t1.¼��ѧ����Ϣ\t\t\t*\n");
	printf("*\t\t2.��ӡѧ����Ϣ\t\t\t*\n");
	printf("*\t\t3.����ѧ����Ϣ\t\t\t*\n");
	printf("*\t\t4.��ȡѧ����Ϣ\t\t\t*\n");
	printf("*\t\t5.ͳ������ѧ������\t\t*\n");
	printf("*\t\t6.����ѧ����Ϣ\t\t\t*\n");
	printf("*\t\t7.�޸�ѧ����Ϣ\t\t\t*\n");
	printf("*\t\t8.ɾ��ѧ����Ϣ\t\t\t*\n");
	printf("*\t\t0.�˳�ϵͳ\t\t\t*\n");
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

	printf("������ѧ��������\n");
	scanf_s("%s", newStud->stud.stuName, sizeof(newStud->stud.stuName));
	printf("�������Ա�\n");
	scanf_s("%s", newStud->stud.stuGender, sizeof(newStud->stud.stuGender));
	printf("������ѧ�����䣺\n");
	scanf_s("%d", &newStud->stud.stuAge);
	printf("������ѧ�ţ�\n");
	scanf_s("%d", &newStud->stud.stuID);
	printf("������ɼ���\n");
	scanf_s("%d", &newStud->stud.stuScore);
	printf("ѧ����Ϣ¼��ɹ���\n\n");
	system("pause");
	system("cls");
}
void printStudInfo() {
	system("cls");
	stuNode* oper = head;//operating node
	if (oper == NULL) {
		printf("ϵͳ������ѧ����Ϣ����¼���������ӡ�鿴��\n\n");
	}else{
		printf("*********************************************************************************\n");
		printf("*\t\t\t��ӭʹ�ø�Уѧ���ɼ�����ϵͳV1.0\t\t\t*\n");
		printf("*********************************************************************************\n");
		printf("*\tѧ��\t*\t����\t*\t�Ա�\t*\t����\t*\t�ɼ�\t*\n");
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
		printf("���ļ�ʧ��...\n");
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
	printf("���ݱ���ɹ���\n");
	system("pause");
	system("cls");
}
void readStudInfo() {
	system("cls");
	FILE* operFile;
	operFile = fopen(".\\data.dat", "r");
	if (operFile == NULL) {
		printf("���ļ�ʧ�ܡ�\n");
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
	printf("ѧ����������%d\n\n", count);
	system("pause");
	system("cls");
}
void findStudInfo() {
	system("cls");
	int key;
	printf("���������ѧ��ѧ�ţ�");
	scanf("%d", &key);
	stuNode* oper = head;
	bool isShowHead = false;
	bool isFindStu = false;
	while (oper!=NULL)	{
		if (key == oper->stud.stuID) {
			if (!isShowHead) {
				printf("*********************************************************************************\n");
				printf("*\tѧ��\t*\t����\t*\t�Ա�\t*\t����\t*\t�ɼ�\t*\n");
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
		printf("ѧ����������ϵͳ�����޸�ѧ����Ϣ��\n\n");
	}
	system("pause");
	system("cls");
}
void changeStudInfo() {
	int key;
	printf("���������޸�ѧ����ѧ�ţ�");
	scanf("%d", &key);
	stuNode* oper = head;
	bool isShowHead = false;
	bool isFindStu = false;
	while (oper != NULL)
	{
		if (key == oper->stud.stuID) {
			if (!isShowHead) {
				printf("*********************************************************************************\n");
				printf("*\tѧ��\t*\t����\t*\t�Ա�\t*\t����\t*\t�ɼ�\t*\n");
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
			//�޸�ѧ����Ϣ
			printf("������ѧ��������\n");
			scanf_s("%s", oper->stud.stuName, sizeof(oper->stud.stuName));
			printf("�������Ա�\n");
			scanf_s("%s", oper->stud.stuGender, sizeof(oper->stud.stuGender));
			printf("������ѧ�����䣺\n");
			scanf_s("%d", &oper->stud.stuAge);
			printf("������ѧ�ţ�\n");
			scanf_s("%d", &oper->stud.stuID);
			printf("������ɼ���\n");
			scanf_s("%d", &oper->stud.stuScore);
			isFindStu = true;
			printf("*********************************************************************************\n");
			printf("ѧ����Ϣ�޸ĳɹ�����ע�⼰ʱ���档\n\n");
		}
		oper = oper->next;
	}

	if (!isFindStu) {
		printf("ѧ����������ϵͳ�����޸�ѧ����Ϣ���޷������޸ġ�\n\n");
	}

	system("pause");
	system("cls");
}
void deleteStudInfo() {
	system("cls");
	int key;
	printf("������ɾ��ѧ����ѧ�ţ�");
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
				printf("*\tѧ��\t*\t����\t*\t�Ա�\t*\t����\t*\t�ɼ�\t*\n");
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
			printf("ɾ���ɹ�����ǵñ��档\n\n");
		}
		beforeNode = oper;
		oper = oper->next;
	}
	if (!isFindStu) {
		printf("ѧ����������ϵͳ�����޸�ѧ����Ϣ���޷�����ɾ��������\n\n");
	}
	system("pause");
	system("cls");
}