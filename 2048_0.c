#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#define SIZE 4
void initializeBoard(int board[SIZE][SIZE]);
void addRandomTile(int board[SIZE][SIZE]);
void printBoard(int board[SIZE][SIZE]);
void changeLR(int board[SIZE][SIZE], int i, int j, int temp);
void changeUD(int board[SIZE][SIZE], int i, int j, int temp);
int moveLeft(int board[SIZE][SIZE]);
int moveRight(int board[SIZE][SIZE]);
int moveUp(int board[SIZE][SIZE]);
int moveDown(int board[SIZE][SIZE]);
int checkWin(int board[SIZE][SIZE]);
int checkGameOver(int board[SIZE][SIZE]);
int total = 0;

int main() {
	int board[SIZE][SIZE];
	char command;
	int moved;

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
			continue;
		}

		if (moved) {
			addRandomTile(board);
		}

		if (checkWin(board)) {
			printBoard(board);
			printf("恭喜！你已经获得了2048！\n");
			break;
		}

		if (checkGameOver(board)) {
			printBoard(board);
			printf("Game Over. Try again!\n");
			break;
		}
	}

	return 0;
}

void initializeBoard(int board[SIZE][SIZE]) {
	total = 0;
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			board[i][j] = 0;
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
	}
}

void printBoard(int board[SIZE][SIZE]) {
	printf("\n");
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			printf("%5d", board[i][j]);
		}
		printf("\n");
	}
	printf("\n分数:%d\n\n", total);
}
void changeLR(int board[SIZE][SIZE], int i, int j, int temp) {
	board[i][temp] = board[i][temp] + board[i][j]; 
	board[i][j] = 0;
}
void changeUD(int board[SIZE][SIZE], int i, int j, int temp) {
	board[temp][i] = board[temp][i] + board[j][i]; 
	board[j][i] = 0;
}
int moveLeft(int board[SIZE][SIZE]) {
	int m = 0;
	for (int i = 0; i < SIZE; i++) {
		int flag = 0;
		for (int j = 0; j < SIZE; j++) {
			if (board[i][j] != 0) {
				int temp = j;
				for (int k = j - 1; k >= 0; k--) {
					if (board[i][k] == 0) { temp = k; m = 1; continue; }
					else if (board[i][k] == board[i][j] && !flag) {
						temp = k;
						total += board[i][j];
						flag = 1;
						m = 1;
						break;
					}
					else {
						flag = 0;
						break;
					}
				}
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
				int temp = j;
				for (int k = j + 1; k < SIZE; k++) {
					if (board[i][k] == 0) { temp = k; m = 1; continue; }
					else if (board[i][k] == board[i][j] && !flag) {
						temp = k;
						total += board[i][j];
						flag = 1;
						m = 1;
						break;
					}
					else {
						flag = 0;
						break;
					}
				}
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
				int temp = j;
				for (int k = j - 1; k >= 0; k--) {
					if (board[k][i] == 0) { temp = k; m = 1; continue; }
					else if (board[k][i] == board[j][i] && !flag) {
						temp = k;
						total += board[j][i];
						flag = 1;
						m = 1;
						break;
					}
					else {
						flag = 0;
						break;
					}
				}
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
				int temp = j;
				for (int k = j + 1; k < SIZE; k++) {
					if (board[k][i] == 0) { temp = k; m = 1; continue; }
					else if (board[k][i] == board[j][i] && !flag) {
						temp = k;
						total += board[j][i];
						flag = 1;
						m = 1;
						break;
					}
					else {
						flag = 0;
						break;
					}
				}
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
