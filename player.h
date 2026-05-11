#pragma once //node 형식 재정의 방지
struct node {
	char name[22];
	char gender;
	char dept[21];
	int id;
	int group;
	struct node * next;
};
typedef struct node NODE;

void fileLoad(NODE * group[], char *);
void addPlayer(NODE * group[]);
void rmPlayer(NODE * group[]);
