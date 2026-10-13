#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
int a = 0;
int b = 0;
int player_symbol = 1;   // чем ходит человек
int bot_symbol = 0;      // чем ходит робот

void display_field(int** point, int x, int y);
bool bot_turn(int** point, int x, int y);
void random_turn(int** arr, int a, int b, int x, int y);
void set_num(int** p);
bool win_or_not(int** point, int a, int b);
bool draw_or_not(int** point, int a, int b);
void vs_bot(int** arr, int a, int b);
void vs_player(int** arr, int a, int b);


int main(void) {
	int a1 = 0;
	scanf("%d", &a1);
	a = a1;
	b = a1;
	int** arr = malloc(a * sizeof(int*));
	for (int i = 0; i < a; i++) {
		arr[i] = malloc(b * sizeof(int));
	}
	set_num(arr);
	int mode = 0;
	printf("Chose: vs Bot = 1; vs player = 2\n");
	scanf("%d", &mode);
	switch (mode) {
		case 1: {
			vs_bot(arr, a, b);
			break;
		}
		case 2: {
			vs_player(arr, a, b);
			break;
		}
	}

	for (int i = 0; i < a; i++) {
		free(arr[i]);      
	}
	free(arr);             


	return 0;
}

void display_field(int** point, int x, int y) {
	for (int i = 0; i < y; ++i) {
		if (i == 0) printf("\t %d   ", i + 1);
		else if (i < 8) printf("%d   ", i + 1);
		else if (i >= 8) printf("%d  ", i + 1);
	}
	printf("\n");
	for (int i = 0; i < x; ++i) {
		printf(" %d\t", i + 1);
		for (int j = 0; j < y; ++j) {
			if (point[i][j] == 1) printf("[X] ");
			else if (point[i][j] == 0) printf("[0] ");
			else printf("[ ] ");
		}
		printf("\n");
	}
}

void set_num(int** p) {
	for (int i = 0; i < a; ++i) {
		for (int j = 0; j < b; ++j)
			p[i][j] = -1;
	}
}

void random_turn(int** arr, int a, int b, int x, int y) {

	int q = 0;
	while (1) {
		int count = 0;
		for (int i = -1; i < 2; ++i) {
			for (int j = -1; j < 2; ++j) {
				if (x + i >= 0 && x + i < a && y + j >= 0 && y + j < b && arr[x+i][y+j] == -1) {
					++count;
					if (count == q) {
						arr[x + i][y + j] = bot_symbol;
						return;
					}
				}
			}
		}
		if (count == 0) {
			for (int i = 0; i < a; i++) {
				for (int j = 0; j < b; j++) {
					if (arr[i][j] == -1) {
						arr[i][j] = bot_symbol;
						return;
					}
				}
			}
		}
		if (count != 0 )
			q = rand() % count + 1;
	}

	return;
}

bool bot_turn(int** point, int x, int y) {

	for (int i = 0; i < x; ++i) {
		int bots = 0;
		int empty_j = -1;
		for (int j = 0; j < y; ++j) {
			if (point[i][j] == bot_symbol) ++bots;
			else if (point[i][j] == -1)
				empty_j = j;
		}
		if (bots == y - 1 && empty_j != -1) {
			point[i][empty_j] = bot_symbol;
			return true;
		}
	}

	for (int j = 0; j < y; ++j) {
		int bots = 0;
		int empty_i = -1;
		for (int i = 0; i < x; ++i) {
			if (point[i][j] == bot_symbol) ++bots;
			else if (point[i][j] == -1)
				empty_i = i;
		}
		if (bots == x - 1 && empty_i != -1) {
			point[empty_i][j] = bot_symbol;
			return true;
		}
	}


	int bots = 0;
	int empty_i = -1;
	for (int i = 0; i < x; i++) {
		if (point[i][i] == bot_symbol)
			++bots;
		else if (point[i][i] == -1) 
			empty_i = i;
	} 
	if (bots == x - 1 && empty_i != -1) {
		point[empty_i][empty_i] = bot_symbol;
		return true;
	}

	bots = 0;
	empty_i = -1;

	for (int i = 0; i < x; ++i) {
		if (point[i][y - 1 - i] == bot_symbol) 
			++bots;
		else if (point[i][y - 1 - i] == -1)
			empty_i = i;
	}
	if (bots == x - 1 && empty_i != -1) {
		point[empty_i][y - 1 - empty_i] = bot_symbol;
		return true;
	}


	for (int i = 0; i < x; ++i) {
		int players = 0;
		int empty_j = -1;
		for (int j = 0; j < y; ++j) {
			if (point[i][j] == player_symbol) ++players;
			else if (point[i][j] == -1)
				empty_j = j;
		}
		if (players == y - 1 && empty_j != -1) {
			point[i][empty_j] = bot_symbol;
			return true;
		}
	}
	// 
	for (int j = 0; j < y; ++j) {
		int players = 0;
		int empty_i = -1;
		for (int i = 0; i < x; ++i) {
			if (point[i][j] == player_symbol) ++players;
			else if (point[i][j] == -1)
				empty_i = i;
		}
		if (players == x - 1 && empty_i != -1) {
			point[empty_i][j] = bot_symbol;
			return true;
		}
	}


	int players = 0;
	empty_i = -1;
	for (int i = 0; i < x; ++i) {
		if (point[i][i] == player_symbol) ++players;
		else if (point[i][i] == -1)
			empty_i = i;
	}
	if (players == x - 1 && empty_i != -1) {
		point[empty_i][empty_i] = bot_symbol;
		return true;
	}

	players = 0;
	empty_i = -1;
	for (int i = 0; i < x; ++i) {
		if (point[i][y - 1 - i] == player_symbol) 
			++players;
		else if (point[i][y - 1 - i] == -1)
			empty_i = i;
	}
	if (players == x - 1 && empty_i != -1) {
		point[empty_i][y - 1 - empty_i] = bot_symbol;
		return true;
	}

	return false;
}




bool win_or_not(int** point, int a, int b) {

	for (int i = 0; i < a; i++) { // для строк
		int player = 0;
		int bot = 0;
		for (int j = 0; j < b; j++) {
			if (point[i][j] == player_symbol)
				++player;
			else if (point[i][j] == bot_symbol)
				bot++;
		}
		if (bot == b) {
			printf("Bot - Winner!");
			return true;
		}
		else if (player == b) {
			printf("Player - Winner!");
			return true;
		}
	}


	// для столбцов
	for (int j = 0; j < b; j++) {
		int player = 0;
		int bot = 0;
		for (int i = 0; i < a; i++) {
			if (point[i][j] == player_symbol)
				++player;
			else if (point[i][j] == bot_symbol)
				bot++;
		}
		if (bot == a) {
			printf("Bot - Winner!");
			return true;
		}
		else if (player == a) {
			printf("Player - Winner!");
			return true;
		}
	}
	int player = 0;
	int bot = 0;
	// для главной диагонали
	for (int i = 0; i < a; i++) {
		if (point[i][i] == player_symbol)
			++player;
		else if (point[i][i] == bot_symbol)
			bot++;
		if (bot == a) {
			printf("Bot - Winner!");
			return true;
		}
		else if (player == b) {
			printf("Player - Winner!");
			return true;
		}
	}

	player = 0;
	bot = 0;
	//для побочной диагонали

	for (int i = 0; i < a; i++) {
		if (point[i][b - 1 - i] == player_symbol)
			++player;
		else if (point[i][b - 1 - i] == bot_symbol)
			bot++;
		if (bot == a) {
			printf("Bot - Winner!");
			return true;
		}
		else if (player == b) {
			printf("Player - Winner!");
			return true;
		}
	}
	return false;
}

void vs_bot(int** arr, int a, int b) {
	display_field(arr, a, b);
	while (1) {
		int x = 0;
		int y = 0;
		printf("Your turn: ");
		scanf("%d%d", &x, &y); //добавить проверку
		--x; --y;

		while (!(x >= 0 && x < a && y >= 0 && y < b) || arr[x][y] != -1) {
			printf("Cell is busy or out of bounds, try again\n");
			scanf("%d%d", &x, &y);
			--x; --y;
		}

		arr[x][y] = player_symbol;
		display_field(arr, a, b);

		if (win_or_not(arr, a, b)) break;
		if (draw_or_not(arr, a, b)) break;
		//Ход бота

		if (!bot_turn(arr, a, b)) {
			random_turn(arr, a, b, x, y);
		}

		printf("\n\n\n\n\n");
		display_field(arr, a, b);
		if (win_or_not(arr, a, b)) break;
		if (draw_or_not(arr, a, b)) break;
	}
}


void vs_player(int** arr, int a, int b) {
	display_field(arr, a, b);
	while (1) {
		int x = 0;
		int y = 0;
		printf("Player X turn: ");
		scanf("%d%d", &x, &y); 
		--x; --y;

		while (!(x >= 0 && x < a && y >= 0 && y < b) || arr[x][y] != -1) {
			printf("Cell is busy or out of bounds, try again\n");
			scanf("%d%d", &x, &y);
			--x; --y;
		}

		arr[x][y] = player_symbol;
		display_field(arr, a, b);

		if (win_or_not(arr, a, b)) break;
		if (draw_or_not(arr, a, b)) break;
		
		printf("Player 0 turn: ");
		scanf("%d%d", &x, &y); 
		--x; --y;

		while(!(x >= 0 && x < a && y >= 0 && y < b) || arr[x][y] != -1 ) {
			printf("Cell is busy or out of bounds, try again\n");
			scanf("%d%d", &x, &y);
			--x; --y;
		}

		arr[x][y] = bot_symbol;

		printf("\n\n\n\n\n");
		display_field(arr, a, b);
		if (win_or_not(arr, a, b)) break;
		if (draw_or_not(arr, a, b)) break;
	}
}

bool draw_or_not(int** point, int a, int b) {
	int sum = 0;
	for (int i = 0; i < a; ++i) {
		for (int j = 0; j < b; ++j) {
			if (point[i][j] != -1) ++sum;
		}
	}
	if (sum == a * b) { 
		printf("It's Draw!!");
		return true; 
	}
	else return false;
}