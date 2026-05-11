#include"group.h"
#include"player.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void printPlayer(NODE * group[], int n) {
	int i;
	NODE * count;
	if (n < 0 || n > 5) {
		printf("number error\n"); //숫자 조건
		return;
	}

	if (n == 0) {
		for (i = 1; i < 6; i++)
			printPlayer(group, i); //0일경우 재귀함수
	}
	else {
		printf("\n%-18s %-6s %-10s %-9s\n", "Name", "Gender", "Dept", "StudentID");
		printf("================== GROUP %d ===================\n", n);
		if (group[n - 1] == NULL) //빈 그룹
			return;
		count = group[n - 1];
		printf("%-18s %-6c %-10s %-9d\n", count->name, count->gender, count->dept, count->id); //그룹의 head
		for (count = group[n - 1]->next; count != group[n - 1]; count = count->next) //그 나머지
			printf("%-18s %-6c %-10s %-9d\n", count->name, count->gender, count->dept, count->id);
	}
}

void insertList(NODE * group[], NODE * temp) { //삽입
	NODE * count;

	if (group[temp->group - 1] == NULL) { //빈공간
		temp->next = temp;
		group[temp->group - 1] = temp;
	}
	else {
		for (count = group[temp->group - 1]; count->next != group[temp->group - 1]; count = count->next); //끝부분에다가삽입
		temp->next = count->next;
		count->next = temp;
	}
}

void removeList(NODE * group[],int i, NODE * count) { //count->next 노드 제거
	NODE * temp;
	if (group[i] == group[i]->next) { //1개남았을때
		free(group[i]);
		group[i] = NULL;
	}
	else { //count다음 노드 제거
		temp = count->next;
		count->next = temp->next;
		if (temp == group[i])
			group[i] = count->next;
		free(temp);
	}
}

void exchangeList(NODE * x, NODE *y) { //플레이어 정보교환
	NODE temp; //임시저장

	strcpy(temp.name, x->name);
	temp.gender = x->gender;
	strcpy(temp.dept, x->dept);
	temp.id = x->id;

	strcpy(x->name, y->name);
	x->gender = y->gender;
	strcpy(x->dept, y->dept);
	x->id = y->id;

	strcpy(y->name, temp.name);
	y->gender = temp.gender;
	strcpy(y->dept, temp.dept);
	y->id = temp.id;

	x->group = y->group; //술래(x)에 전그룹 저장
}

void savePlayer(NODE * group[]) {
	FILE * save; //저장 파일

	int i;
	NODE * count;

	save = fopen("result_game.txt", "w");
	for (i = 0; i < 5; i++) {
		if (group[i] == NULL) //빈 그룹
			continue;
		count = group[i];
		fprintf(save, "%s\t%c\t%s\t%d\t%d\n", count->name, count->gender, count->dept, count->id, count->group); //그룹의 head
		for (count = group[i]->next; count != group[i]; count = count->next) //그 나머지
			fprintf(save, "%s\t%c\t%s\t%d\t%d\n", count->name, count->gender, count->dept, count->id, count->group);
	}
	fclose(save); //파일 닫기
}

void plush(NODE * group[]) {
	int i;
	NODE * count;
	for (i = 0; i < 5; i++) {
		while (group[i] != NULL) { //group 이 빌 때까지
			for (count = group[i]; count->next != group[i]; count = count->next);
			removeList(group, i, count);
		}
	}
}
