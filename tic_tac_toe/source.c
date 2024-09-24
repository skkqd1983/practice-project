#include <stdio.h> 
#include <stdlib.h>
#include <conio.h> // �ܼ� ����� �Լ��� ����
#include <Windows.h> // ������ ���� �� ���� �Լ��� ����

#define CIN GetStdHandle(STD_INPUT_HANDLE) // ǥ�� �Է� ����̽�
#define COUT GetStdHandle(STD_OUTPUT_HANDLE) // ǥ�� ��� ����̽�

/* �ܼ� ���� �ڵ� */
#define WHITE 7 
#define RED 4
#define BLUE 1
#define YELLOW 6

enum { // ���� ����, ���� ���� enum 
	GAME_START = 0,
	GAME_EXIT
};

enum { // ���� �÷��̾� ���� enum
	NONE = 0,
	PALYER_1,
	PALYER_2
};

typedef struct score { // ���� ���ھ� ���� ����ü
	int player;
	int computer;
} Score;

int OorX[3][3] = { 0, }; // O�� X�� ��ġ�� �����ϴ� ����
int player = 0; // ���� �÷��̾ �����ϴ� ����
int gameFlag = 0; // ���� ���� ���� ���� ����
int gameMenu = 0; // ���õ� �޴� ���� ����
int turnCount = 0; // ���� �� Ƚ�� ����
int gameEnd = 0; //���� ���� ���� ����
int XY[2] = { 2, 1 };

Score score = { 0, 0 }; // ���� ���ھ� ���� ����

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
void computer_selectedMap();
int win_test();

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

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			ox_map[i][j] = 0;
		}
	}

	gotoMouseXY(XY[0], XY[1]);
	printf("��");
	while (gameFlag = 1) {
		inputGame();
	}
}

void printGameStartScreen() {
	system("cls");
	printf("[���� ���ھ�]\n");
	printf("Player : %d vs Computer : %d\n\n", score.player, score.computer);

	printf("[���� �޴�]\n");
	printf("�������ϱ�\n");
	printf("����������");
}

void gotoMouseXY(int x, int y) { 
	COORD cur;
	cur.X = x;
	cur.Y = y;

	SetConsoleCursorPosition(COUT, cur);
}

void inputGameMenu() {
	char key = getch(); // getch()�� Ű������ �ϳ� Ű�� �Է� ���� �� �ְ� �ϴ� �Լ�

	if (key == 'w' || key == 'W') {
		gotoMouseXY(0, 4);
		printf("��\n\r��");
		gameMenu = GAME_START;
	}
	else if (key == 's' || key == 'S') {
		gotoMouseXY(0, 4);
		printf("��\n\r��");
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
		exit(0); // ���α׷��� ���� �ϴ� �Լ�
		break;
	}
}

void inputGame() {
	char key = getch(); // getch()�� Ű������ �ϳ� Ű�� �Է� ���� �� �ְ� �ϴ� �Լ�

	if (XY[0] != 2 && gameEnd != 1 && (key == 'a' || key == 'A')) {
		map_reset();
		XY[0] -= 4;
		gotoMouseXY(XY[0], XY[1]);
		printf("��");
	}
	else if (XY[0] != 10 && gameEnd != 1 && (key == 'd' || key == 'D')) {
		map_reset();
		XY[0] += 4;
		gotoMouseXY(XY[0], XY[1]);
		printf("��");
	}
	else if (XY[1] != 5 && gameEnd != 1 && (key == 's' || key == 'S')) {
		map_reset();
		XY[1] += 2;
		gotoMouseXY(XY[0], XY[1]);
		printf("��");
	}
	else if (XY[1] != 1 && gameEnd != 1 && (key == 'w' || key == 'W')) {
		map_reset();
		XY[1] -= 2;
		gotoMouseXY(XY[0], XY[1]);
		printf("��");
	}
	else if (key == '\r') {
		if (gameEnd == 0) {
			selectedMap();
		}
		else {
			gameFlag = 0;
		}
	}

	gotoMouseXY(0, 7);
	//printf("%d %d", XY[0], XY[1]);
	for (int i = 0; i < 3; i++) {
		printf("%d %d %d\n", ox_map[i][0], ox_map[i][1], ox_map[i][2]);
	}
}

void selectedMap() {
	ox_map[(XY[1] + 1) / 2 - 1][(XY[0] + 2) / 4 - 1] = 1;
	if (win_test(1) == 1) {
		gotoMouseXY(0, 13);
		printf("[player] �¸�!");
		gameEnd = 1;
	}
	else {
		computer_selectedMap();
		map_reset();

		if (win_test(2) == 1) {
			gotoMouseXY(0, 13);
			printf("[computer] �¸�!");
			gameEnd = 1;
		}
	}
}

void computer_selectedMap() {
	srand((unsigned int)time(NULL));
	int count = 0;
	
	for (int i = 0; i < 3; i++) { //�˻�1 - ���� �� üũ
		count = 0;
		for (int j = 0; j < 3; j++) {
			if (ox_map[i][j] == 1) {
				count += 1;
			}
			if (count >= 2) { //�� �ٿ��� 1�� 2�� �߰ߵ� ��
				for (int l = 0; l < 3; l++) { //���ڸ� üũ �� 2�Է�
					if (ox_map[i][l] == 0) {
						ox_map[i][l] = 2;
						/*
						gotoMouseXY(0, 11);
						printf("������ üũ");
						*/
						return;
					}
				}
			}
		}
	}

	for (int i = 0; i < 3; i++) { //�˻�2 - ���� �� üũ
		count = 0;
		for (int j = 0; j < 3; j++) {
			if (ox_map[j][i] == 1) {
				count += 1;
			}
			if (count >= 2) { //�� �ٿ��� 1�� 2�� �߰ߵ� ��
				for (int l = 0; l < 3; l++) { //���ڸ� üũ �� 2�Է�
					if (ox_map[l][i] == 0) {
						ox_map[l][i] = 2;
						/*
						gotoMouseXY(0, 11);
						printf("������ üũ");
						*/
						return;
					}
				}
			}
		}
	}

	for (int i = 0; i < 2; i++) { //�˻�3 - �밢�� �� üũ
		count = 0;
		for (int j = 0; j < 3; j++) {
			if (i == 0) {
				if (ox_map[j][j] == 1) {
					count += 1;
				}
				if (count >= 2) { //�� �ٿ��� 1�� 2�� �߰ߵ� ��
					for (int l = 0; l < 3; l++) { //���ڸ� üũ �� 2�Է�
						if (ox_map[l][l] == 0) {
							ox_map[l][l] = 2;
							/*
							gotoMouseXY(0, 11);
							printf("�밢����1 üũ");
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
				if (count >= 2) { //�� �ٿ��� 1�� 2�� �߰ߵ� ��
					for (int l = 0; l < 3; l++) { //���ڸ� üũ �� 2�Է�
						if (ox_map[l][2-l] == 0) {
							ox_map[l][2-l] = 2;
							/*
							gotoMouseXY(0, 11);
							printf("�밢����2 üũ");
							*/
							return;
						}
					}
				}
			}
		}
	}

	while (1) { //�˻翡�� �ƹ��͵� �ɸ��� �ʴ´ٸ� ���� ��ġ
		int rand1 = (rand() % 3+1)*2;
		int rand2 = (rand() % 3+1)*4;
		if (ox_map[rand1 / 2 - 1][rand2 / 4 - 1] == 0) {
			ox_map[rand1 / 2 - 1][rand2 / 4 - 1] = 2;
			gotoMouseXY(0, 11);
			printf("���� ����");
			break;
		}
	}
}

int win_test(int who) { //�� ���� ������ 1 Ȥ�� 2�� �Է¹޾� �¸��ߴ��� �˻�
	
	int count = 0;

	for (int i = 0; i < 3; i++) { //�˻�1 - ���� �� üũ
		count = 0;
		for (int j = 0; j < 3; j++) {
			if (ox_map[i][j] == who) {
				count += 1;
			}
			if (count == 3) { //�� �ٿ��� 1�� 3�� �߰ߵ� ��
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

	for (int i = 0; i < 3; i++) { //�˻�2 - ���� �� üũ
		count = 0;
		for (int j = 0; j < 3; j++) {
			if (ox_map[j][i] == who) {
				count += 1;
			}
			if (count == 3) { //�� �ٿ��� 1�� 3�� �߰ߵ� ��
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

	for (int i = 0; i < 2; i++) { //�˻�3 - �밢�� �� üũ
		count = 0;
		for (int j = 0; j < 3; j++) {
			if (i == 0) {
				if (ox_map[j][j] == who) {
					count += 1;
				}
				if (count == 3) { //�� �ٿ��� 1�� 3�� �߰ߵ� ��
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
				if (count == 3) { //�� �ٿ��� 1�� 3�� �߰ߵ� ��
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
	return 0;
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
				SetConsoleTextAttribute(COUT, BLUE);
				printf("��");
			}
			else if (ox_map[j][i] == 2) {
				gotoMouseXY(2 + (4 * i), 1 + (2 * j));
				SetConsoleTextAttribute(COUT, RED);
				printf("��");
			}
		}
	}
	SetConsoleTextAttribute(COUT, WHITE);
}