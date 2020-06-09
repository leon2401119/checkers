#include <iostream>
#include <vector>


#include "STcpClient.h"

int Min(struct board_data*, bool, int);


struct board_data {
	std::vector<std::vector<int>> board;
	int level;
	int value;
	struct child_list* first_child;
	int child_count;
	std::vector<short> decision;
	std::vector<int> start_location;
};
struct child_list {
	struct board_data childboard;
	std::vector<short> dir;
	std::vector<int> piece;
	struct child_list* next_child;
};
struct root_node {
	struct board_data startboard;
};

struct root_node root;

bool bitmap[8][8];

std::vector<std::vector<int>> MyStep;


struct board_data* current_global;
std::vector<std::vector<int>> board;
std::vector<std::vector<int>> steps;
std::vector<short> dir;

void GetNextBoard(bool is_black) {
	bool done = true;
	std::vector<int> laststep;
	laststep.reserve(2);
	laststep = steps.back();
	std::vector<int> newstep;
	newstep.reserve(2);
	int column = laststep[0], row = laststep[1];
	if (column + 2 <= 7 && board[column + 2][row] == 0 && board[column + 1][row] != 0 && !bitmap[column + 2][row]) {
		newstep.clear();
		if (board[column + 1][row] == 1) {        //hopping over black
			if (!is_black) {
				board[column + 1][row] = 0;     //black captured
			}
			board[column + 2][row] = board[column][row];
			board[column][row] = 0;
			newstep.push_back(column + 2);
			newstep.push_back(row);
			steps.push_back(newstep);
			dir.push_back(4);
			bitmap[column + 2][row] = 1;
			GetNextBoard(is_black);
			board[column + 1][row] = 1;
			board[column][row] = board[column + 2][row];
			board[column + 2][row] = 0;
			steps.pop_back();
			dir.pop_back();
			bitmap[column + 2][row] = 0;
		}
		else if (board[column + 1][row] == 2) {   //hopping over white
			if (is_black) {
				board[column + 1][row] = 0;     //black captured
			}
			board[column + 2][row] = board[column][row];
			board[column][row] = 0;
			newstep.push_back(column + 2);
			newstep.push_back(row);
			steps.push_back(newstep);
			dir.push_back(4);
			bitmap[column + 2][row] = 1;
			GetNextBoard(is_black);
			board[column + 1][row] = 2;
			board[column][row] = board[column + 2][row];
			board[column + 2][row] = 0;
			steps.pop_back();
			dir.pop_back();
			bitmap[column + 2][row] = 0;
		}
		done = false;
	}
	if (column - 2 >= 0 && board[column - 2][row] == 0 && board[column - 1][row] != 0 && !bitmap[column - 2][row]) {
		newstep.clear();
		if (board[column - 1][row] == 1) {        //hopping over black
			if (!is_black) {
				board[column - 1][row] = 0;     //black captured
			}
			board[column - 2][row] = board[column][row];
			board[column][row] = 0;
			newstep.push_back(column - 2);
			newstep.push_back(row);
			steps.push_back(newstep);
			dir.push_back(2);
			bitmap[column - 2][row] = 1;
			GetNextBoard(is_black);
			board[column - 1][row] = 1;
			board[column][row] = board[column - 2][row];
			board[column - 2][row] = 0;
			steps.pop_back();
			dir.pop_back();
			bitmap[column - 2][row] = 0;
		}
		else if (board[column - 1][row] == 2) {   //hopping over white
			if (is_black) {
				board[column - 1][row] = 0;     //black captured
			}
			board[column - 2][row] = board[column][row];
			board[column][row] = 0;
			newstep.push_back(column - 2);
			newstep.push_back(row);
			steps.push_back(newstep);
			dir.push_back(2);
			bitmap[column - 2][row] = 1;
			GetNextBoard(is_black);
			board[column - 1][row] = 2;
			board[column][row] = board[column - 2][row];
			board[column - 2][row] = 0;
			steps.pop_back();
			dir.pop_back();
			bitmap[column - 2][row] = 0;
		}
		done = false;
	}
	if (row + 2 <= 7 && board[column][row + 2] == 0 && board[column][row + 1] != 0 && !bitmap[column][row + 2]) {
		newstep.clear();
		if (board[column][row + 1] == 1) {        //hopping over black
			if (!is_black) {
				board[column][row + 1] = 0;     //black captured
			}
			board[column][row + 2] = board[column][row];
			board[column][row] = 0;
			newstep.push_back(column);
			newstep.push_back(row + 2);
			steps.push_back(newstep);
			dir.push_back(1);
			bitmap[column][row + 2] = 1;
			GetNextBoard(is_black);
			board[column][row + 1] = 1;
			board[column][row] = board[column][row + 2];
			board[column][row + 2] = 0;
			steps.pop_back();
			dir.pop_back();
			bitmap[column][row + 2] = 0;
		}
		else if (board[column][row + 1] == 2) {   //hopping over white
			if (is_black) {
				board[column][row + 1] = 0;     //black captured
			}
			board[column][row + 2] = board[column][row];
			board[column][row] = 0;
			newstep.push_back(column);
			newstep.push_back(row + 2);
			steps.push_back(newstep);
			dir.push_back(1);
			bitmap[column][row + 2] = 1;
			GetNextBoard(is_black);
			board[column][row + 1] = 2;
			board[column][row] = board[column][row + 2];
			board[column][row + 2] = 0;
			steps.pop_back();
			dir.pop_back();
			bitmap[column][row + 2] = 0;
		}
		done = false;
	}
	if (row - 2 >= 0 && board[column][row - 2] == 0 && board[column][row - 1] != 0 && !bitmap[column][row - 2]) {
		newstep.clear();
		if (board[column][row - 1] == 1) {        //hopping over black
			if (!is_black) {
				board[column][row - 1] = 0;     //black captured
			}
			board[column][row - 2] = board[column][row];
			board[column][row] = 0;
			newstep.push_back(column);
			newstep.push_back(row - 2);
			steps.push_back(newstep);
			dir.push_back(3);
			bitmap[column][row - 2] = 1;
			GetNextBoard(is_black);
			board[column][row - 1] = 1;
			board[column][row] = board[column][row - 2];
			board[column][row - 2] = 0;
			steps.pop_back();
			dir.pop_back();
			bitmap[column][row - 2] = 0;
		}
		else if (board[column][row - 1] == 2) {   //hopping over white
			if (is_black) {
				board[column][row - 1] = 0;     //black captured
			}
			board[column][row - 2] = board[column][row];
			board[column][row] = 0;
			newstep.push_back(column);
			newstep.push_back(row - 2);
			steps.push_back(newstep);
			dir.push_back(3);
			bitmap[column][row - 2] = 1;
			GetNextBoard(is_black);
			board[column][row - 1] = 2;
			board[column][row] = board[column][row - 2];
			board[column][row - 2] = 0;
			steps.pop_back();
			dir.pop_back();
			bitmap[column][row - 2] = 0;
		}
		done = false;
	}
	if (done) {
		if (dir.empty())
			return;
		struct child_list* temp;
		std::vector<int> location;
		location = steps[0];
		if (current_global->first_child == NULL) {
			current_global->first_child = new struct child_list;
			temp = current_global->first_child;
		}
		else {
			temp = current_global->first_child;
			while (temp->next_child != NULL)
				temp = temp->next_child;
			temp->next_child = new struct child_list;
			temp = temp->next_child;
		}
		temp->childboard.board = board;
		temp->childboard.level = current_global->level + 1;
		temp->childboard.first_child = NULL;
		temp->childboard.child_count = 0;
		temp->piece = location;
		temp->dir = dir;
		temp->next_child = NULL;
		current_global->child_count++;
		return;
	}
}


int Max(struct board_data* current, bool is_black, int prune) {
	int max = -10000;
	struct child_list* temp = current->first_child;
	board = current->board;
	std::vector<int> newstep;
	std::vector<int> location;
	newstep.reserve(2);
	location.reserve(2);
	int i, j;

	//print board
	/*for(i=0;i<8;i++){
	for(j=0;j<8;j++)
	printf("%d",board[i][j]);
	printf("\n");
	}
	printf("\n");*/
	//

	if (current->level == 4) {                                   //reached leaves
		current->value = 0;
		int enemy = 0;
		for (i = 0; i < 8; i++) {
			for (j = 0; j < 8; j++) {
				if (current->board[i][j] == 1)
					current->value += 300;
				else if (current->board[i][j] == 2)
					current->value -= 300;
				if (current->board[i][j] == 1 && j < 6) {
					current->value -= (6 - j);
					/*if (i >= 1 && current->board[i - 1][j] == 2) {
						if(is_black)
							current->value -= 10;
						else
							current->value += 10;
					}

					if (j >= 1 && current->board[i][j-1] == 2) {
						if (is_black)
							current->value -= 10;
						else
							current->value += 10;
					}
					if (i <= 6 && current->board[i+1][j] == 2) {
						if (is_black)
							current->value -= 10;
						else
							current->value += 10;
					}
					if (j <= 6 && current->board[i][j+1] == 2) {
						if (is_black)
							current->value -= 10;
						else
							current->value += 10;
					}*/
				}
				else if (current->board[i][j] == 2 && j > 1) {
					current->value += (j - 1);
					//enemy++;
				}
			}
		}
		//current->value -= enemy*10;
		if (!is_black)
			current->value = -current->value;
		return current->value;
	}
	for (i = 0; i < 8; i++) {                                       //explore all child
		for (j = 0; j < 8; j++) {
			location.clear();
			location.push_back(i);
			location.push_back(j);
			if (is_black && board[i][j] == 1) {
				if (i + 1 <= 7 && board[i + 1][j] == 0) {
					board[i + 1][j] = 1;
					board[i][j] = 0;
					if (current->first_child == NULL) {
						current->first_child = new struct child_list;
						temp = current->first_child;
					}
					else {
						temp = current->first_child;
						while (temp->next_child != NULL)
							temp = temp->next_child;
						temp->next_child = new struct child_list;
						temp = temp->next_child;
					}
					temp->childboard.board = board;
					temp->childboard.level = current->level + 1;
					temp->childboard.first_child = NULL;
					temp->childboard.child_count = 0;
					temp->dir.push_back(8);
					temp->piece = location;
					temp->next_child = NULL;
					current->child_count++;
					board = current->board;
				}
				if (i - 1 >= 0 && board[i - 1][j] == 0) {
					board[i - 1][j] = 1;
					board[i][j] = 0;
					if (current->first_child == NULL) {
						current->first_child = new struct child_list;
						temp = current->first_child;
					}
					else {
						temp = current->first_child;
						while (temp->next_child != NULL)
							temp = temp->next_child;
						temp->next_child = new struct child_list;
						temp = temp->next_child;
					}
					temp->childboard.board = board;
					temp->childboard.level = current->level + 1;
					temp->childboard.first_child = NULL;
					temp->childboard.child_count = 0;
					temp->dir.push_back(6);
					temp->piece = location;
					temp->next_child = NULL;
					current->child_count++;
					board = current->board;
				}
				if (j + 1 <= 7 && board[i][j + 1] == 0) {
					board[i][j + 1] = 1;
					board[i][j] = 0;
					if (current->first_child == NULL) {
						current->first_child = new struct child_list;
						temp = current->first_child;
					}
					else {
						temp = current->first_child;
						while (temp->next_child != NULL)
							temp = temp->next_child;
						temp->next_child = new struct child_list;
						temp = temp->next_child;
					}
					temp->childboard.board = board;
					temp->childboard.level = current->level + 1;
					temp->childboard.first_child = NULL;
					temp->childboard.child_count = 0;
					temp->dir.push_back(5);
					temp->piece = location;
					temp->next_child = NULL;
					current->child_count++;
					board = current->board;
				}
				if (j - 1 >= 0 && board[i][j - 1] == 0) {
					board[i][j - 1] = 1;
					board[i][j] = 0;
					if (current->first_child == NULL) {
						current->first_child = new struct child_list;
						temp = current->first_child;
					}
					else {
						temp = current->first_child;
						while (temp->next_child != NULL)
							temp = temp->next_child;
						temp->next_child = new struct child_list;
						temp = temp->next_child;
					}
					temp->childboard.board = board;
					temp->childboard.level = current->level + 1;
					temp->childboard.first_child = NULL;
					temp->childboard.child_count = 0;
					temp->dir.push_back(7);
					temp->piece = location;
					temp->next_child = NULL;
					current->child_count++;
					board = current->board;
				}
				newstep.clear();
				newstep.push_back(i);
				newstep.push_back(j);
				steps.push_back(newstep);
				dir.clear();
				current_global = current;
				for (int ha = 0; ha < 8; ha++) {
					for (int he = 0; he < 8; he++)
						bitmap[ha][he] = false;
				}
				bitmap[i][j] = true;
				GetNextBoard(is_black);
				steps.pop_back();
			}
			else if (!is_black && board[i][j] == 2) {
				if (i + 1 <= 7 && board[i + 1][j] == 0) {
					board[i + 1][j] = 2;
					board[i][j] = 0;
					if (current->first_child == NULL) {
						current->first_child = new struct child_list;
						temp = current->first_child;
					}
					else {
						temp = current->first_child;
						while (temp->next_child != NULL)
							temp = temp->next_child;
						temp->next_child = new struct child_list;
						temp = temp->next_child;
					}
					temp->childboard.board = board;
					temp->childboard.level = current->level + 1;
					temp->childboard.first_child = NULL;
					temp->childboard.child_count = 0;
					temp->dir.push_back(8);
					temp->piece = location;
					temp->next_child = NULL;
					current->child_count++;
					board = current->board;
				}
				if (i - 1 >= 0 && board[i - 1][j] == 0) {
					board[i - 1][j] = 2;
					board[i][j] = 0;
					if (current->first_child == NULL) {
						current->first_child = new struct child_list;
						temp = current->first_child;
					}
					else {
						temp = current->first_child;
						while (temp->next_child != NULL)
							temp = temp->next_child;
						temp->next_child = new struct child_list;
						temp = temp->next_child;
					}
					temp->childboard.board = board;
					temp->childboard.level = current->level + 1;
					temp->childboard.first_child = NULL;
					temp->childboard.child_count = 0;
					temp->dir.push_back(6);
					temp->piece = location;
					temp->next_child = NULL;
					current->child_count++;
					board = current->board;
				}
				if (j + 1 <= 7 && board[i][j + 1] == 0) {
					board[i][j + 1] = 2;
					board[i][j] = 0;
					if (current->first_child == NULL) {
						current->first_child = new struct child_list;
						temp = current->first_child;
					}
					else {
						temp = current->first_child;
						while (temp->next_child != NULL)
							temp = temp->next_child;
						temp->next_child = new struct child_list;
						temp = temp->next_child;
					}
					temp->childboard.board = board;
					temp->childboard.level = current->level + 1;
					temp->childboard.first_child = NULL;
					temp->childboard.child_count = 0;
					temp->dir.push_back(5);
					temp->piece = location;
					temp->next_child = NULL;
					current->child_count++;
					board = current->board;
				}
				if (j - 1 >= 0 && board[i][j - 1] == 0) {
					board[i][j - 1] = 2;
					board[i][j] = 0;
					if (current->first_child == NULL) {
						current->first_child = new struct child_list;
						temp = current->first_child;
					}
					else {
						temp = current->first_child;
						while (temp->next_child != NULL)
							temp = temp->next_child;
						temp->next_child = new struct child_list;
						temp = temp->next_child;
					}
					temp->childboard.board = board;
					temp->childboard.level = current->level + 1;
					temp->childboard.first_child = NULL;
					temp->childboard.child_count = 0;
					temp->dir.push_back(7);
					temp->piece = location;
					temp->next_child = NULL;
					current->child_count++;
					board = current->board;
				}
				newstep.clear();
				newstep.push_back(i);
				newstep.push_back(j);
				steps.push_back(newstep);
				dir.clear();
				current_global = current;
				for (int ha = 0; ha < 8; ha++) {
					for (int he = 0; he < 8; he++)
						bitmap[ha][he] = false;
				}
				bitmap[i][j] = true;
				GetNextBoard(is_black);
				steps.pop_back();
			}
		}
	}
	temp = current->first_child;
	for (i = 0; i < current->child_count; i++) {
		Min(&(temp->childboard), is_black, max);
		if (temp->childboard.value > max) {
			max = temp->childboard.value;
			current->decision = temp->dir;
			current->start_location = temp->piece;
			current->value = max;
		}
		if (max > prune)
			return max;
		temp = temp->next_child;
	}
	return max;
}

int Min(struct board_data* current, bool is_black, int prune) {
	int min = 10000;
	struct child_list* temp = current->first_child;
	board = current->board;
	std::vector<int> newstep;
	std::vector<int> location;
	newstep.reserve(2);
	location.reserve(2);
	int i, j;

	//print board
	/*for(i=0;i<8;i++){
	for(j=0;j<8;j++)
	printf("%d",board[i][j]);
	printf("\n");
	}
	printf("\n");*/
	//

	bool black_gone = true, white_gone = true, black_fin = true, white_fin = true;
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			if (board[i][j] == 1) {
				black_gone = false;
				if (j < 6)
					black_fin = false;
			}
			else if (board[i][j] == 2) {
				white_gone = false;
				if (j > 1)
					white_fin = false;
			}
		}
	}
	if (is_black) {
		if (black_gone || white_fin)
			return -1000;
		else if (white_gone || black_fin)
			return 1000;
	}
	else {
		if (white_gone || black_fin)
			return -1000;
		else if (black_gone || white_fin)
			return 1000;
	}


	if (current->level == 4) {                                   //reached leaves
		current->value = 0;
		//int black_num;
		//int white_num;
		for (i = 0; i < 8; i++) {
			for (j = 0; j < 8; j++) {
				if (current->board[i][j] == 1) {
					if (i >= 1 && current->board[i - 1][j] == 2) {
						if (is_black)
							current->value -= 10;
						else
							current->value += 10;
					}
					else if (j >= 1 && current->board[i][j - 1] == 2) {
						if (is_black)
							current->value -= 10;
						else
							current->value += 10;
					}
					else if (i <= 6 && current->board[i + 1][j] == 2) {
						if (is_black)
							current->value -= 10;
						else
							current->value += 10;
					}
					else if (j <= 6 && current->board[i][j + 1] == 2) {
						if (is_black)
							current->value -= 10;
						else
							current->value += 10;
					}

					current->value += 25;
					current->value += (j*j);

					if (j >= 6)
						current->value += 50;
					//black_num++;
				}
				else if (current->board[i][j] == 2) {
					current->value -= 25;
					current->value -= (j - 7)*(j - 7);
					if (j <= 1)
						current->value -= 50;
				}
			}
		}
		if (!is_black)
			current->value = -current->value;
		return current->value;
	}
	for (i = 0; i < 8; i++) {                                       //explore all child
		for (j = 0; j < 8; j++) {
			location.clear();
			location.push_back(i);
			location.push_back(j);
			if (!is_black && board[i][j] == 1) {
				if (i + 1 <= 7 && board[i + 1][j] == 0) {
					board[i + 1][j] = 1;
					board[i][j] = 0;
					if (current->first_child == NULL) {
						current->first_child = new struct child_list;
						temp = current->first_child;
					}
					else {
						temp = current->first_child;
						while (temp->next_child != NULL)
							temp = temp->next_child;
						temp->next_child = new struct child_list;
						temp = temp->next_child;
					}
					temp->childboard.board = board;
					temp->childboard.level = current->level + 1;
					temp->childboard.first_child = NULL;
					temp->childboard.child_count = 0;
					temp->dir.push_back(8);
					temp->piece = location;
					temp->next_child = NULL;
					current->child_count++;
					board = current->board;
				}
				if (i - 1 >= 0 && board[i - 1][j] == 0) {
					board[i - 1][j] = 1;
					board[i][j] = 0;
					if (current->first_child == NULL) {
						current->first_child = new struct child_list;
						temp = current->first_child;
					}
					else {
						temp = current->first_child;
						while (temp->next_child != NULL)
							temp = temp->next_child;
						temp->next_child = new struct child_list;
						temp = temp->next_child;
					}
					temp->childboard.board = board;
					temp->childboard.level = current->level + 1;
					temp->childboard.first_child = NULL;
					temp->childboard.child_count = 0;
					temp->dir.push_back(6);
					temp->piece = location;
					temp->next_child = NULL;
					current->child_count++;
					board = current->board;
				}
				if (j + 1 <= 7 && board[i][j + 1] == 0) {
					board[i][j + 1] = 1;
					board[i][j] = 0;
					if (current->first_child == NULL) {
						current->first_child = new struct child_list;
						temp = current->first_child;
					}
					else {
						temp = current->first_child;
						while (temp->next_child != NULL)
							temp = temp->next_child;
						temp->next_child = new struct child_list;
						temp = temp->next_child;
					}
					temp->childboard.board = board;
					temp->childboard.level = current->level + 1;
					temp->childboard.first_child = NULL;
					temp->childboard.child_count = 0;
					temp->dir.push_back(5);
					temp->piece = location;
					temp->next_child = NULL;
					current->child_count++;
					board = current->board;
				}
				if (j - 1 >= 0 && board[i][j - 1] == 0) {
					board[i][j - 1] = 1;
					board[i][j] = 0;
					if (current->first_child == NULL) {
						current->first_child = new struct child_list;
						temp = current->first_child;
					}
					else {
						temp = current->first_child;
						while (temp->next_child != NULL)
							temp = temp->next_child;
						temp->next_child = new struct child_list;
						temp = temp->next_child;
					}
					temp->childboard.board = board;
					temp->childboard.level = current->level + 1;
					temp->childboard.first_child = NULL;
					temp->childboard.child_count = 0;
					temp->dir.push_back(7);
					temp->piece = location;
					temp->next_child = NULL;
					current->child_count++;
					board = current->board;
				}
				newstep.clear();
				newstep.push_back(i);
				newstep.push_back(j);
				steps.push_back(newstep);
				dir.clear();
				current_global = current;
				for (int ha = 0; ha < 8; ha++) {
					for (int he = 0; he < 8; he++)
						bitmap[ha][he] = false;
				}
				bitmap[i][j] = true;
				GetNextBoard(!is_black);
				steps.pop_back();
			}
			else if (is_black && board[i][j] == 2) {
				if (i + 1 <= 7 && board[i + 1][j] == 0) {
					board[i + 1][j] = 2;
					board[i][j] = 0;
					if (current->first_child == NULL) {
						current->first_child = new struct child_list;
						temp = current->first_child;
					}
					else {
						temp = current->first_child;
						while (temp->next_child != NULL)
							temp = temp->next_child;
						temp->next_child = new struct child_list;
						temp = temp->next_child;
					}
					temp->childboard.board = board;
					temp->childboard.level = current->level + 1;
					temp->childboard.first_child = NULL;
					temp->childboard.child_count = 0;
					temp->dir.push_back(8);
					temp->piece = location;
					temp->next_child = NULL;
					current->child_count++;
					board = current->board;
				}
				if (i - 1 >= 0 && board[i - 1][j] == 0) {
					board[i - 1][j] = 2;
					board[i][j] = 0;
					if (current->first_child == NULL) {
						current->first_child = new struct child_list;
						temp = current->first_child;
					}
					else {
						temp = current->first_child;
						while (temp->next_child != NULL)
							temp = temp->next_child;
						temp->next_child = new struct child_list;
						temp = temp->next_child;
					}
					temp->childboard.board = board;
					temp->childboard.level = current->level + 1;
					temp->childboard.first_child = NULL;
					temp->childboard.child_count = 0;
					temp->dir.push_back(6);
					temp->piece = location;
					temp->next_child = NULL;
					current->child_count++;
					board = current->board;
				}
				if (j + 1 <= 7 && board[i][j + 1] == 0) {
					board[i][j + 1] = 2;
					board[i][j] = 0;
					if (current->first_child == NULL) {
						current->first_child = new struct child_list;
						temp = current->first_child;
					}
					else {
						temp = current->first_child;
						while (temp->next_child != NULL)
							temp = temp->next_child;
						temp->next_child = new struct child_list;
						temp = temp->next_child;
					}
					temp->childboard.board = board;
					temp->childboard.level = current->level + 1;
					temp->childboard.first_child = NULL;
					temp->childboard.child_count = 0;
					temp->dir.push_back(5);
					temp->piece = location;
					temp->next_child = NULL;
					current->child_count++;
					board = current->board;
				}
				if (j - 1 >= 0 && board[i][j - 1] == 0) {
					board[i][j - 1] = 2;
					board[i][j] = 0;
					if (current->first_child == NULL) {
						current->first_child = new struct child_list;
						temp = current->first_child;
					}
					else {
						temp = current->first_child;
						while (temp->next_child != NULL)
							temp = temp->next_child;
						temp->next_child = new struct child_list;
						temp = temp->next_child;
					}
					temp->childboard.board = board;
					temp->childboard.level = current->level + 1;
					temp->childboard.first_child = NULL;
					temp->childboard.child_count = 0;
					temp->dir.push_back(7);
					temp->piece = location;
					temp->next_child = NULL;
					current->child_count++;
					board = current->board;
				}
				newstep.clear();
				newstep.push_back(i);
				newstep.push_back(j);
				steps.push_back(newstep);
				dir.clear();
				current_global = current;
				for (int ha = 0; ha < 8; ha++) {
					for (int he = 0; he < 8; he++)
						bitmap[ha][he] = false;
				}
				bitmap[i][j] = true;
				GetNextBoard(!is_black);
				steps.pop_back();
			}
		}
	}
	temp = current->first_child;
	for (i = 0; i < current->child_count; i++) {
		Max(&(temp->childboard), is_black, min);
		if (temp->childboard.value < min) {
			min = temp->childboard.value;
			current->decision = temp->dir;
			current->start_location = temp->piece;
			current->value = min;
		}
		if (min < prune)
			return min;
		temp = temp->next_child;
	}
	return min;
}

void Minimax(bool is_black) {
	Max(&(root.startboard), is_black, 10000);
	int i;
	MyStep.clear();
	std::vector<int> temp;
	temp.reserve(2);
	temp.push_back(root.startboard.start_location[0]);
	temp.push_back(root.startboard.start_location[1]);
	MyStep.push_back(temp);
	for (i = 0; i < root.startboard.decision.size(); i++) {
		if (root.startboard.decision[i] == 1) {
			temp[1] += 2;
		}
		else if (root.startboard.decision[i] == 2) {
			temp[0] -= 2;
		}
		else if (root.startboard.decision[i] == 3) {
			temp[1] -= 2;
		}
		else if (root.startboard.decision[i] == 4) {
			temp[0] += 2;
		}
		else if (root.startboard.decision[i] == 5) {
			temp[1] += 1;
		}
		else if (root.startboard.decision[i] == 6) {
			temp[0] -= 1;
		}
		else if (root.startboard.decision[i] == 7) {
			temp[1] -= 1;
		}
		else if (root.startboard.decision[i] == 8) {
			temp[0] += 1;
		}
		MyStep.push_back(temp);
	}
	for (i = 0; i < MyStep.size(); i++) {
		printf("(%d,%d)\n", MyStep[i][0], MyStep[i][1]);
	}
	return;
}

std::vector<std::vector<int>> GetStep(std::vector<std::vector<int>>& board, bool is_black) {
	std::vector<std::vector<int>> step;
	root.startboard.board = board;
	root.startboard.level = 0;
	root.startboard.child_count = 0;
	root.startboard.first_child = NULL;
	Minimax(is_black);
	step = MyStep;
	return step;
}


int main() {
	int id_package;
	std::vector<std::vector<int> > board, step;
	bool is_black;
	while (true) {
		if (GetBoard(id_package, board, is_black))
			break;

		step = GetStep(board, is_black);
		SendStep(id_package, step);
	}
}
