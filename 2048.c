#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
// 定义颜色代码
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define WHITE "\x1b[37m"
#define RESET "\x1b[0m"
#define SIZE 4
//改变文本颜色：
//\033[30m：黑色
//\033[31m：红色
//\033[32m：绿色
//\033[33m：黄色
//\033[34m：蓝色
//\033[35m：洋红色
//\033[36m：青色
//\033[37m：白色
//改变背景颜色：
//\033[40m：黑色
//\033[41m：红色
//\033[42m：绿色
//\033[43m：黄色
//\033[44m：蓝色
//\033[45m：洋红色
//\033[46m：青色
//\033[47m：白色
//控制样式：
//\033[0m：重置所有属性
//\033[1m：粗体
//\033[4m：下划线
//\033[5m：闪烁
//\033[7m：反显
void initializeBoard(int board[SIZE][SIZE]);
void addRandomTile(int board[SIZE][SIZE]);
void printBoard(int board[SIZE][SIZE]);
void changeColor(int board[SIZE][SIZE], int i, int j);
void changeLR(int board[SIZE][SIZE], int i, int j, int temp);
void changeUD(int board[SIZE][SIZE], int i, int j, int temp);
int moveLeft(int board[SIZE][SIZE]);
int moveRight(int board[SIZE][SIZE]);
int moveUp(int board[SIZE][SIZE]);
int moveDown(int board[SIZE][SIZE]);
int checkWin(int board[SIZE][SIZE]);
int checkGameOver(int board[SIZE][SIZE]);
int won = 0;
int total = 0;
char* colors[SIZE * SIZE];

int main() {
	int board[SIZE][SIZE];
	char command;
	int moved;

	//srand(time(0));
	unsigned int seed = (unsigned int)time(0);
	srand(seed);
	initializeBoard(board);

	while (1) {
		printBoard(board);
		printf("输入指令 (1/←: 左, 2/→: 右, 3/↑: 上, 4/↓: 下, 5: 重新开始, 0: 退出): ");
		command = _getch();
		if (command != -32) {
			printf("%c\n", command);
		}
		moved = 0;
		switch (command) {
		case '1':
			moved = moveLeft(board);
			break;
		case '2':
			moved = moveRight(board);
			break;
		case '3':
			moved = moveUp(board);
			break;
		case '4':
			moved = moveDown(board);
			break;
		case '0':
			printf("已退出\n");
			return 0;
		case '5':
			initializeBoard(board);
			break;
		case -32:
			command = _getch();
			switch (command)
			{
			case 72:printf("↑\n"); moved = moveUp(board); break;
			case 80:printf("↓\n"); moved = moveDown(board); break;
			case 75:printf("←\n"); moved = moveLeft(board); break;
			case 77:printf("→\n"); moved = moveRight(board); break;
			default:break;
			}
			break;
		default:
			//printf("Invalid command.\n");
			continue;
		}

		if (moved) {
			addRandomTile(board);
		}

		if (!won && checkWin(board)) {
			printBoard(board);
			printf("恭喜!你已经获得了2048,按非0键继续\n");
			int GoOn = 0;
			while (!GoOn) {
				command = _getch();
				switch (command) {
				case '0':printf("已退出\n");
					return 0;
				default:
					GoOn = 1;
					break;
				}
			}
		}

		if (checkGameOver(board)) {
			printBoard(board);
			printf("Game Over. Try again!(5: 重新开始, 0: 退出)\n");
			int retry = 0;
			while (!retry) {
				command = _getch();
				switch (command) {
				case '0':printf("已退出\n");
					return 0;
				case '5':
					initializeBoard(board);
					retry = 1;
					break;
				default:
					continue;
				}
			}
		}
	}

	return 0;
}

void initializeBoard(int board[SIZE][SIZE]) {
	total = 0;
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			board[i][j] = 0;
			colors[i * SIZE + j] = WHITE;
		}
	}
	addRandomTile(board);
	addRandomTile(board);
}

void addRandomTile(int board[SIZE][SIZE]) {
	int empty[SIZE * SIZE][2];
	int emptyCount = 0;

	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (board[i][j] == 0) {
				empty[emptyCount][0] = i;
				empty[emptyCount][1] = j;
				emptyCount++;
			}
		}
	}

	if (emptyCount > 0) {
		int randomIndex = rand() % emptyCount;
		int row = empty[randomIndex][0];
		int col = empty[randomIndex][1];
		board[row][col] = (rand() % 2 + 1) * 2;
		colors[row * SIZE + col] = CYAN;
	}
}

void printBoard(int board[SIZE][SIZE]) {
	for (int i = 0; i < 9; i++) {
		printf("\033[A");
		printf("\033[K");
	}
	printf("\n");
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			printf("%s%5d%s", colors[i * SIZE + j], board[i][j], RESET);
		}
		printf("\n");
	}
	printf("\n分数:%d\n\n", total);
}
void changeColor(int board[SIZE][SIZE], int i, int j) {
	if (board[i][j] >= 2048) {
		colors[i * SIZE + j] = RED;
	}
	else if (board[i][j] >= 512) {
		colors[i * SIZE + j] = MAGENTA;
	}
	else if (board[i][j] >= 64) {
		colors[i * SIZE + j] = YELLOW;
	}
	else {
		colors[i * SIZE + j] = GREEN;
	}
}
void changeLR(int board[SIZE][SIZE], int i, int j, int temp) {
	board[i][temp] = board[i][temp] + board[i][j]; 
	board[i][j] = 0;
	changeColor(board, i, temp);
	colors[i * SIZE + j] = WHITE;
}
void changeUD(int board[SIZE][SIZE], int i, int j, int temp) {
	board[temp][i] = board[temp][i] + board[j][i]; 
	board[j][i] = 0;
	changeColor(board, temp, i);
	colors[j * SIZE + i] = WHITE;
}
int moveLeft(int board[SIZE][SIZE]) {
	int m = 0;
	for (int i = 0; i < SIZE; i++) {
		int flag = 0;
		for (int j = 0; j < SIZE; j++) {
			if (board[i][j] != 0) {
				changeColor(board, i, j);
				int temp = j;
				for (int k = j - 1; k >= 0; k--) {
					if (board[i][k] == 0) { temp = k; m = 1; continue; }
					else if (board[i][k] == board[i][j] && !flag) {
						temp = k;
						//board[i][k] = board[i][k] + board[i][j];
						total += board[i][j];
						//board[i][j] = 0;
						flag = 1;
						m = 1;
						break;
					}
					else {
						flag = 0;
						break;
					}
				}
				/*if (temp != j && !flag) {
					board[i][temp] = board[i][j]; board[i][j] = 0; m = 1;
				}*/
				if (temp != j) {
					changeLR(board, i, j, temp);
				}
			}
		}
	}
	return m;
}
int moveRight(int board[SIZE][SIZE]) {
	int m = 0;
	for (int i = 0; i < SIZE; i++) {
		int flag = 0;
		for (int j = SIZE - 1; j >= 0; j--) {
			if (board[i][j] != 0) {
				changeColor(board, i, j);
				int temp = j;
				for (int k = j + 1; k < SIZE; k++) {
					if (board[i][k] == 0) { temp = k; m = 1; continue; }
					else if (board[i][k] == board[i][j] && !flag) {
						temp = k;
						//board[i][k] = board[i][k] + board[i][j];
						total += board[i][j];
						//board[i][j] = 0;
						flag = 1;
						m = 1;
						break;
					}
					else {
						flag = 0;
						break;
					}
				}
				/*if (temp != j && !flag) {
					board[i][temp] = board[i][j]; board[i][j] = 0; m = 1;
				}*/
				if (temp != j) {
					changeLR(board, i, j, temp);
				}
			}
		}
	}
	return m;
}

int moveUp(int board[SIZE][SIZE]) {
	int m = 0;
	for (int i = 0; i < SIZE; i++) {
		int flag = 0;
		for (int j = 0; j < SIZE; j++) {
			if (board[j][i] != 0) {
				changeColor(board, j, i);
				int temp = j;
				for (int k = j - 1; k >= 0; k--) {
					if (board[k][i] == 0) { temp = k; m = 1; continue; }
					else if (board[k][i] == board[j][i] && !flag) {
						temp = k;
						//board[k][i] = board[k][i] + board[j][i];
						total += board[j][i];
						//board[j][i] = 0;
						flag = 1;
						m = 1;
						break;
					}
					else {
						flag = 0;
						break;
					}
				}
				/*if (temp != j && !flag) {
					board[temp][i] = board[j][i]; board[j][i] = 0; m = 1;
				}*/
				if (temp != j) {
					changeUD(board, i, j, temp);
				}
			}
		}
	}
	return m;
}

int moveDown(int board[SIZE][SIZE]) {
	int m = 0;
	for (int i = 0; i < SIZE; i++) {
		int flag = 0;
		for (int j = SIZE - 1; j >= 0; j--) {
			if (board[j][i] != 0) {
				changeColor(board, j, i);
				int temp = j;
				for (int k = j + 1; k < SIZE; k++) {
					if (board[k][i] == 0) { temp = k; m = 1; continue; }
					else if (board[k][i] == board[j][i] && !flag) {
						temp = k;
						//board[k][i] = board[k][i] + board[j][i];
						total += board[j][i];
						//board[j][i] = 0;
						flag = 1;
						m = 1;
						break;
					}
					else {
						flag = 0;
						break;
					}
				}
				/*if (temp != j && !flag) {
					board[temp][i] = board[j][i]; board[j][i] = 0; m = 1;
				}*/
				if (temp != j) {
					changeUD(board, i, j, temp);
				}
			}
		}
	}
	return m;
}

int checkWin(int board[SIZE][SIZE]) {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (board[i][j] == 2048) {
				won = 1;
				return 1;
			}
		}
	}
	return 0;
}

int checkGameOver(int board[SIZE][SIZE]) {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (board[i][j] == 0 || (j > 0 && board[i][j - 1] == board[i][j]) || (j < SIZE - 1 && board[i][j + 1] == board[i][j])) {
				return 0;
			}
		}
		for (int k = 1; k < SIZE - 1; k++) {
			if (board[k][i] == board[k - 1][i] || board[k][i] == board[k + 1][i]) {
				return 0;
			}
		}
	}
	return 1;
}
