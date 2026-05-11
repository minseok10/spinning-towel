#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"group.h"
#include"player.h"

void fileLoad(NODE * group[],char * filename) {
	FILE * players;
	NODE * temp;
	NODE * count;

	char tname[22];
	char tgender;
	char tdept[21];
	int tid;
	int tgroup; //학생 신상정보저장

	players = fopen(filename, "r");

	if (players == NULL) {
		printf("Cannot open file!\n"); //열기 에러
		exit(403);
	}
	while (fscanf(players, " %[^\t] %c %s %d %d", tname, &tgender, tdept, &tid, &tgroup) != EOF) {
		temp = malloc(sizeof(NODE));
		strcpy(temp->name, tname);
		temp->gender = tgender;
		strcpy(temp->dept, tdept);
		temp->id = tid;
		temp->group = tgroup;
		temp->next = NULL;
		//temp노드에 데이터복사
		insertList(group, temp); //group 에 temp노드 삽입
	}
	fclose(players); //파일 닫기
}

void addPlayer(NODE * group[]) {
	NODE * temp; //새 노드
	NODE * count;
	int tid; //학번식별
	int i;

	printf("StudentID: ");
	scanf("%d", &tid);
	for (i = 0; i < 5; i++) { //학번 duplicate check
		if (group[i] == NULL)
			continue;
		for (count = group[i]; 1; count = count->next) {
			if (count->id == tid) { //같은학번 발견
				printf("Player already exists!");
				printf("\n%-18s %-6s %-10s %-10s %-6s\n", "Name", "Gender", "Dept", "StudentID", "Group");
				printf("%-18s %-6c %-10s %-10d %-6d\n", count->name, count->gender, count->dept, count->id, count->group);
				return;
			}
			if (count->next == group[i]) //한 그룹스캔 끝
				break;
		}
	}

	temp = malloc(sizeof(NODE));
	temp->id = tid;
	printf("Name: ");
	scanf(" %[^\n]", temp->name);
	printf("Gender: ");
	scanf(" %c", &(temp->gender));
	printf("Dept: ");
	scanf("%s", temp->dept);
	printf("Group: ");
	scanf("%d", &(temp->group));
	//새 노드 작성 및 입력
	insertList(group, temp); //temp를 삽입
	printf("Player successfully added to group %d.\n", temp->group);
}

void rmPlayer(NODE * group[]) {
	NODE * count;
	int tid;
	int i;

	printf("StudentID: ");
	scanf("%d", &tid);
	for (i = 0; i < 5; i++) { //학번일치 scan
		if (group[i] == NULL)
			continue;
		for (count = group[i]; 1; count = count->next) {
			if (count->next->id == tid) { //count->next 가 일치하는가 검사
				removeList(group, i, count); //count 다음노드 제거
				printf("Player sucessfully removed from group %d.\n", i + 1);
				return;
			}
			if (count->next == group[i]) //한 그룹 검사끝
				break;
		}
	}
	printf("Player does not exist!\n");
}
