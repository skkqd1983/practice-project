#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <conio.h> // 콘솔 입출력 함수를 제공
#include <Windows.h> // 윈도우 용의 수 많은 함수를 제공

#define CIN GetStdHandle(STD_INPUT_HANDLE) // 표준 입력 디바이스
#define COUT GetStdHandle(STD_OUTPUT_HANDLE) // 표준 출력 디바이스

/* 콘솔 색상 코드 */
#define WHITE 7 
#define RED 4
#define BLUE 1

typedef struct score { // 게임 스코어 관련 구조체
	int player;
	int computer;
} Score;

Score score = { 0, 0 }; // 게임 스코어 관련 변수

int gameFlag = 0; // 게임 시작 여부 관련 변수
int gameEnd = 0; //게임 종료 여부 변수
int start = 0; //게임 시작 여부 변수
int XY[2] = { 2, 1 }; //현 선택 좌표 변수

void printGameStartScreen();
void gameStartScreen();
void printGameStartScreen();
void MouseXY(int x, int y);
void inputGameMenu();
void selectedGameMenu();
void gamePlayingScreen();

void inputGame();
void map_reset();
void selectedMap();
void computer_selectedMap();
int win_test(int who);

char original_map[50][50] = {
	{"-------------\n"},
	{"|   |   |   |\n"},
	{"-------------\n"},
	{"|   |   |   |\n"},
	{"-------------\n"},
	{"|   |   |   |\n"},
	{"-------------\n"}
};

int ox_map[3][3] = {
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0}
};

void main() {
	while (1) {
		if (gameFlag == 0) {
			gameEnd = 0;
			gameStartScreen();
		}
		else {
			gamePlayingScreen();
		}
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

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			ox_map[i][j] = 0;
		}
	}

	MouseXY(XY[0], XY[1]);
	printf("■");
	while (gameFlag == 1) {
		inputGame();
	}
}

void printGameStartScreen() {
	system("cls");
	printf("[현재 스코어]\n");
	printf("Player : %d vs Computer : %d\n\n", score.player, score.computer);

	printf("[게임 메뉴]\n");
	printf("▶게임하기\n");
	printf("▷게임종료");
}

void MouseXY(int x, int y) { 
	COORD pos;
	pos.X = x;
	pos.Y = y;

	SetConsoleCursorPosition(COUT, pos);
}

void inputGameMenu() {
	char key = getch(); // getch()는 키보드의 하나 키를 입력 받을 수 있게 하는 함수

	if (key == 'w' || key == 'W') {
		MouseXY(0, 4);
		printf("▶\n\r▷");
		start = 0;
	}
	else if (key == 's' || key == 'S') {
		MouseXY(0, 4);
		printf("▷\n\r▶");
		start = 1;
	}
	else if (key == '\r') {
		selectedGameMenu();
	}
	MouseXY(0, 6);
}

void selectedGameMenu() {
	switch (start) {
	case 0:
		gameFlag = 1;
		break;
	case 1:
		exit(0); // 프로그램을 종료 하는 함수
		break;
	}
}

void inputGame() {
	char key = getch(); // getch()는 키보드의 하나 키를 입력 받을 수 있게 하는 함수

	if (XY[0] != 2 && gameEnd != 1 && (key == 'a' || key == 'A')) {
		map_reset();
		XY[0] -= 4;
		MouseXY(XY[0], XY[1]);
		printf("■");
	}
	else if (XY[0] != 10 && gameEnd != 1 && (key == 'd' || key == 'D')) {
		map_reset();
		XY[0] += 4;
		MouseXY(XY[0], XY[1]);
		printf("■");
	}
	else if (XY[1] != 5 && gameEnd != 1 && (key == 's' || key == 'S')) {
		map_reset();
		XY[1] += 2;
		MouseXY(XY[0], XY[1]);
		printf("■");
	}
	else if (XY[1] != 1 && gameEnd != 1 && (key == 'w' || key == 'W')) {
		map_reset();
		XY[1] -= 2;
		MouseXY(XY[0], XY[1]);
		printf("■");
	}
	else if (key == '\r') {
		if (gameEnd == 0 && ox_map[(XY[1]-1)/2][(XY[0]-2)/4] == 0) {
			selectedMap();
		}
		else if (gameEnd == 1) {
			gameFlag = 0;
		}
	}

	MouseXY(0, 7);
	/*
	for (int i = 0; i < 3; i++) {
		printf("%d %d %d\n", ox_map[i][0], ox_map[i][1], ox_map[i][2]);
	}
	printf("gameFlag : %d\n", gameFlag);
	printf("gameEnd : %d\n", gameEnd);
	*/
}

void selectedMap() {
	ox_map[(XY[1] + 1) / 2 - 1][(XY[0] + 2) / 4 - 1] = 1;

	map_reset();
	if (win_test(1) == 1) {
		MouseXY(0, 8);
		printf("[player] 승리!");
		gameEnd = 1;
	}
	else if (win_test(1) == 2) {
		MouseXY(0, 8);
		printf("[DRAW]");
		gameEnd = 1;
	}
	else {
		computer_selectedMap();
		map_reset();

		if (win_test(2) == 1) {
			MouseXY(0, 8);
			printf("[computer] 승리!");
			gameEnd = 1;
		}
		else if (win_test(2) == 2) {
			MouseXY(0, 8);
			printf("[DRAW]");
			gameEnd = 1;
		}
	}
}

void computer_selectedMap() {
	srand((unsigned int)time(NULL));
	int count = 0;
	
	for (int i = 0; i < 3; i++) { //검사1 - 가로 행 체크
		count = 0;
		for (int j = 0; j < 3; j++) {
			if (ox_map[i][j] == 1) {
				count += 1;
			}
			if (count >= 2) { //한 줄에서 1이 2개 발견될 시
				for (int l = 0; l < 3; l++) { //빈자리 체크 후 2입력
					if (ox_map[i][l] == 0) {
						ox_map[i][l] = 2;
						/*
						gotoMouseXY(0, 11);
						printf("가로행 체크");
						*/
						return;
					}
				}
			}
		}
	}

	for (int i = 0; i < 3; i++) { //검사2 - 세로 행 체크
		count = 0;
		for (int j = 0; j < 3; j++) {
			if (ox_map[j][i] == 1) {
				count += 1;
			}
			if (count >= 2) { //한 줄에서 1이 2개 발견될 시
				for (int l = 0; l < 3; l++) { //빈자리 체크 후 2입력
					if (ox_map[l][i] == 0) {
						ox_map[l][i] = 2;
						/*
						gotoMouseXY(0, 11);
						printf("세로행 체크");
						*/
						return;
					}
				}
			}
		}
	}

	for (int i = 0; i < 2; i++) { //검사3 - 대각선 행 체크
		count = 0;
		for (int j = 0; j < 3; j++) {
			if (i == 0) {
				if (ox_map[j][j] == 1) {
					count += 1;
				}
				if (count >= 2) { //한 줄에서 1이 2개 발견될 시
					for (int l = 0; l < 3; l++) { //빈자리 체크 후 2입력
						if (ox_map[l][l] == 0) {
							ox_map[l][l] = 2;
							/*
							gotoMouseXY(0, 11);
							printf("대각선행1 체크");
							*/
							return;
						}
					}
				}
			}
			else {
				if (ox_map[j][2-j] == 1) {
					count += 1;
				}
				if (count >= 2) { //한 줄에서 1이 2개 발견될 시
					for (int l = 0; l < 3; l++) { //빈자리 체크 후 2입력
						if (ox_map[l][2-l] == 0) {
							ox_map[l][2-l] = 2;
							/*
							gotoMouseXY(0, 11);
							printf("대각선행2 체크");
							*/
							return;
						}
					}
				}
			}
		}
	}

	while (1) { //검사에서 아무것도 걸리지 않는다면 랜덤 배치
		int rand1 = (rand() % 3+1)*2;
		int rand2 = (rand() % 3+1)*4;
		if (ox_map[rand1 / 2 - 1][rand2 / 4 - 1] == 0) {
			ox_map[rand1 / 2 - 1][rand2 / 4 - 1] = 2;
			MouseXY(0, 11);
			printf("랜덤 지정");
			break;
		}
	}
}

int win_test(int who) { //각 턴이 끝나면 1 혹은 2를 입력받아 승리했는지 검사
	
	int count = 0;

	for (int i = 0; i < 3; i++) { //검사1 - 가로 행 체크
		count = 0;
		for (int j = 0; j < 3; j++) {
			if (ox_map[i][j] == who) {
				count += 1;
			}
			if (count == 3) { //한 줄에서 1이 3개 발견될 시
				if (who == 1) {
					score.player += 1;
				}
				else if (who == 2) {
					score.computer += 1;
				}
				return 1;
			}
		}
	}

	for (int i = 0; i < 3; i++) { //검사2 - 세로 행 체크
		count = 0;
		for (int j = 0; j < 3; j++) {
			if (ox_map[j][i] == who) {
				count += 1;
			}
			if (count == 3) { //한 줄에서 1이 3개 발견될 시
				if (who == 1) {
					score.player += 1;
				}
				else if (who == 2) {
					score.computer += 1;
				}
				return 1;
			}
		}
	}

	for (int i = 0; i < 2; i++) { //검사3 - 대각선 행 체크
		count = 0;
		for (int j = 0; j < 3; j++) {
			if (i == 0) {
				if (ox_map[j][j] == who) {
					count += 1;
				}
				if (count == 3) { //한 줄에서 1이 3개 발견될 시
					if (who == 1) {
						score.player += 1;
					}
					else if (who == 2) {
						score.computer += 1;
					}
					return 1;
				}
			}
			else {
				if (ox_map[j][2 - j] == who) {
					count += 1;
				}
				if (count == 3) { //한 줄에서 1이 3개 발견될 시
					if (who == 1) {
						score.player += 1;
					}
					else if (who == 2) {
						score.computer += 1;
					}
					return 1;
				}
			}
		}
	}

	count = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (ox_map[i][j] != 0) {
				count += 1;
			}

			if (count == 9) {
				return 2;
			}
		}
	}
	return 0;
}

void map_reset() {
	system("cls");
	MouseXY(0, 0);
	for (int i = 0; i < 7; i++) {
		printf(original_map[i]);
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (ox_map[j][i] == 1) {
				MouseXY(2+(4*i), 1+(2*j));
				SetConsoleTextAttribute(COUT, BLUE);
				printf("●");
			}
			else if (ox_map[j][i] == 2) {
				MouseXY(2 + (4 * i), 1 + (2 * j));
				SetConsoleTextAttribute(COUT, RED);
				printf("●");
			}
		}
	}
	SetConsoleTextAttribute(COUT, WHITE);
}