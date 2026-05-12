#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#ifdef _WIN32
#define strcasecmp _stricmp
#else
#include<strings.h>
#endif
#include"group.h"
#include"player.h"

char command();
void gameplay(NODE * group[]);

int main(int argc, char * argv[]) {
	NODE * group[5] = { NULL, }; //구조체 포인터 배열
	char filename[256] = "players.txt"; //파일이름
	int num; //show 입력

	if (argc == 2)
		snprintf(filename, sizeof(filename), "%s", argv[1]); //명령줄 인수
	fileLoad(group, filename);
	printPlayer(group, 0);

	while (1) {
		switch (command()) {
		case 'a':
			addPlayer(group);
			break;
		case 's':
			printf("Which group? (0:all) ");
			scanf("%d", &num);
			printPlayer(group, num);
			break;
		case 'r':
			rmPlayer(group);
			break;
		case 'p':
			gameplay(group);
			break;
		case 'q':
			savePlayer(group);
			plush(group); //전체할당 해제
			printf("File saved. Bye!\n");
			return 0;
		default:
			continue;
		}
	}
	return 1;
}

char command() { //명령어를 입력받아 특정 문자를 반환
	char cmd[10];
	printf("\n>>");
	scanf("%9s", cmd);
	if (strcasecmp(cmd, "show") == 0) //소문자처리 _stricmp
		return 's';
	if (strcasecmp(cmd, "add") == 0)
		return 'a';
	if (strcasecmp(cmd, "remove") == 0)
		return 'r';
	if (strcasecmp(cmd, "play") == 0)
		return 'p';
	if (strcasecmp(cmd, "quit") == 0)
		return 'q';
	return 0;
}

void gameplay(NODE * group[]) {
	FILE * query; //게임파일 쿼리
	NODE * x, *y; //편의용 임시
	NODE *temp = malloc(sizeof(NODE)); //술래의 정보 저장
	int i;
	int ag, ap = 1; //술래 group, player
	int tg, tp; //타겟 group, player
	int prev; //술래가어디그룹이었는가
	int ch;
	size_t len;

	char filename[20] = "game.txt";
	while ((ch = getchar()) == ' ' || ch == '\t');
	if (ch != '\n' && ch != EOF) {
		ungetc(ch, stdin);
		if (fgets(filename, sizeof(filename), stdin) != NULL) {
			len = strlen(filename);
			if (len > 0 && filename[len - 1] == '\n')
				filename[len - 1] = '\0';
		}
	}

	query = fopen(filename, "r");
	if (query == NULL) {
		printf("\nError opening file!\n");
		return;
	}

	for (i = 0; i < 5; i++) {
		if (group[i])
			break;
		if (i == 4) {
			printf("And then there were none...\n");
			return;
		}
	}
	ag = i + 1; //술래 조

	for (x = group[ag - 1], i = 1; i < ap; x = x->next, i++); //첫 술래

	strcpy(temp->name, "");
	strcpy(temp->dept, "");
	temp->gender = 0;
	temp->id = 0;
	temp->group = 0;
	temp->next = NULL; //술래공간 초기화

	exchangeList(temp, x); //술래로 이동

	for (y = group[ag - 1]; 1; y = y->next) { //x 주소를 next로 가지는 node의 주소를 y에 저장
		if (y->next == x) {
			removeList(group, ag - 1, y); //x 노드 제거
			break;
		}
		if (y->next == group[ag - 1]) //무한루프방지
			break;
	}

	printf("From                          To\n");
	while (fscanf(query, "%d %d", &tg, &tp) != EOF) {
		if (group[tg - 1] == NULL) //빈그룹건너뛰기
			continue;
		for (y = group[tg - 1], i = 1; i < tp; y = y->next, i++); //타겟 위치
		prev = temp->group;
		exchangeList(temp, y); //타겟을 술래로
		printf("%-15s (Group %d)  ->  %-15s (Group %d)\n", y->name, prev, temp->name, tg);
	}
	printf("\nGame over!\n");
	printf("%s (Group %d) is out.\n", temp->name, tg);
	free(temp); //술래 제거
	fclose(query); //파일 닫기
}
