#include <stdio.h> 
#include <conio.h> // 콘솔 입출력 함수를 제공
#include <Windows.h> // 윈도우 용의 수 많은 함수를 제공

#define CIN GetStdHandle(STD_INPUT_HANDLE) // 표준 입력 디바이스
#define COUT GetStdHandle(STD_OUTPUT_HANDLE) // 표준 출력 디바이스

/* 콘솔 색상 코드 */
#define WHITE 7 
#define RED 4
#define BLUE 1
#define YELLOW 6

enum { // 게임 시작, 종료 관련 enum 
	GAME_START = 0,
	GAME_EXIT
};

enum { // 게임 플레이어 관련 enum
	NONE = 0,
	PALYER_1,
	PALYER_2
};

typedef struct score { // 게임 스코어 관련 구조체
	int player;
	int computer;
} Score;

int OorX[3][3] = { 0, }; // O와 X의 위치를 저장하는 변수
int player = 0; // 현재 플레이어를 저장하는 변수
int gameFlag = 0; // 게임 시작 여부 관련 변수
int gameMenu = 0; // 선택된 메뉴 관련 변수
int turnCount = 0; // 게임 턴 횟수 변수
int XY[2] = { 2, 1 };

Score score = { 0, 0 }; // 게임 스코어 관련 변수

void gameScreen();
void printGameStartScreen();
void gameStartScreen();
void printGameStartScreen();
void gotoMouseXY(int x, int y);
void inputGameMenu();
void selectedGameMenu();
void gamePlayingScreen();

void inputGame();
void map_reset();
void selectedMap();

char original_map[50][50] = {
	{"-------------\n"},
	{"|   |   |   |\n"},
	{"-------------\n"},
	{"|   |   |   |\n"},
	{"-------------\n"},
	{"|   |   |   |\n"},
	{"-------------\n"}
};

int ox_map[3][4] = {
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0}
};

void main() {
	while (1) {
		gameScreen();
	}
}

void gameScreen() {
	if (!gameFlag) {
		gameStartScreen();
	}
	else {
		gamePlayingScreen();
	}
}

void gameStartScreen() {
	printGameStartScreen();

	while (gameFlag != 1) {
		inputGameMenu();
	}
}

void gamePlayingScreen() {
	system("cls");
	for (int i = 0; i < 7; i++) {
		printf(original_map[i]);
	}

	gotoMouseXY(XY[0], XY[1]);
	printf("■");
	while (gameFlag = 1) {
		inputGame();
	}
}

void printGameStartScreen() {
	printf("[현재 스코어]\n");
	printf("Player : %d vs Computer : %d\n\n", score.player, score.computer);

	printf("[게임 메뉴]\n");
	printf("▶게임하기\n");
	printf("▷게임종료");
}

void gotoMouseXY(int x, int y) { 
	COORD cur;
	cur.X = x;
	cur.Y = y;

	SetConsoleCursorPosition(COUT, cur);
}

void inputGameMenu() {
	char key = getch(); // getch()는 키보드의 하나 키를 입력 받을 수 있게 하는 함수

	if (key == 'w' || key == 'W') {
		gotoMouseXY(0, 4);
		printf("▶\n\r▷");
		gameMenu = GAME_START;
	}
	else if (key == 's' || key == 'S') {
		gotoMouseXY(0, 4);
		printf("▷\n\r▶");
		gameMenu = GAME_EXIT;
	}
	else if (key == '\r') {
		selectedGameMenu();
	}
}

void selectedGameMenu() {
	switch (gameMenu) {
	case GAME_START:
		gameFlag = 1;
		break;
	case GAME_EXIT:
		exit(0); // 프로그램을 종료 하는 함수
		break;
	}
}

void inputGame() {
	char key = getch(); // getch()는 키보드의 하나 키를 입력 받을 수 있게 하는 함수

	if (XY[0] != 2 && key == 'a' || key == 'A') {
		map_reset();
		XY[0] -= 4;
		gotoMouseXY(XY[0], XY[1]);
		printf("■");
	}
	else if (XY[0] != 10 && key == 'd' || key == 'D') {
		map_reset();
		XY[0] += 4;
		gotoMouseXY(XY[0], XY[1]);
		printf("■");
	}
	else if (XY[1] != 5 && key == 's' || key == 'S') {
		map_reset();
		XY[1] += 2;
		gotoMouseXY(XY[0], XY[1]);
		printf("■");
	}
	else if (XY[1] != 1 && key == 'w' || key == 'W') {
		map_reset();
		XY[1] -= 2;
		gotoMouseXY(XY[0], XY[1]);
		printf("■");
	}
	else if (key == '\r') {
		selectedMap();
	}

	gotoMouseXY(0, 7);
	printf("%d %d", XY[0], XY[1]);
}

void selectedMap() {
	ox_map[(XY[1] + 1) / 2 - 1][(XY[0] + 2) / 4 - 1] = 1;
}


void map_reset() {
	system("cls");
	gotoMouseXY(0, 0);
	for (int i = 0; i < 7; i++) {
		printf(original_map[i]);
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (ox_map[j][i] == 1) {
				gotoMouseXY(2+(4*i), 1+(2*j));
				printf("◎");
			}
		}
	}
}