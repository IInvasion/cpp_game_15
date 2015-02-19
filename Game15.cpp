#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

int ** MatrixCreate(int rows, int columns)
{
	int **arr = new int *[rows];
	for (int i = 0; i < rows; i++)
		arr[i] = new int[columns];

	return arr;
}

void MatrixDelete(int** arr, int rows, int columns)
{
	for (int i = 0; i < rows; i++)
		delete[] arr[i];

	delete[] arr;
}

void FieldFilling(int **field, int rows, int cols){
	int mult = rows * cols;
	int *arr = new int[mult];
	for (int i = 0; i < mult; i++)
		arr[i] = i;
	srand(time(0));
	for (int i = 0; i < rows; i++){
		for (int j = 0; j < cols; j++) {
			int value;
			while (1) {
				int random = rand() % mult;
				if (arr[random] != -1) {
					value = arr[random];
					arr[random] = -1;
					break;
				}
			}
			field[i][j] = value;
		}
	}
	delete[] arr;
}

bool WinCheck(int **field, int rows, int cols){
	bool flag = true;
	for (int i = 0; i < rows; i++){
		for (int j = 0; j < cols; j++){
			if ((i == rows - 1) && (j == cols - 1))
				return flag;
			else
				if (field[i][j] != (4 * i + (j + 1)))
					flag = false;
		}
	}
	return flag;
}

void FieldPrint(int **field, int rows, int cols) {
	system("cls");
	cout << '\t' << "1\t" << "2\t" << "3\t" << "4\t";
	for (int i = 0; i < rows; i++){
		cout << endl;
		cout << i + 1 << "\t";
		for (int j = 0; j < cols; j++)
			cout << field[i][j] << "\t";
	}
	cout << endl << endl;
}

bool InputCheck(int rows, int cols, int row, int col) {
	return ((row >= 0) && (row < rows)) && ((col >= 0) && (col < cols));
}

bool EmptyNeighborCheck(int **field, int rows, int cols, int row, int col, int& zeroRow, int& zeroCol) {
	if (InputCheck(rows, cols, row - 1, col)) {
		if (field[row - 1][col] == 0) {
			zeroRow = row - 1;
			zeroCol = col;
			return true;
		}
		else {
			zeroRow = -1;
			zeroCol = -1;
		}
	}

	if (InputCheck(rows, cols, row + 1, col)) {
		if (field[row + 1][col] == 0) {
			zeroRow = row + 1;
			zeroCol = col;
			return true;
		}
		else {
			zeroRow = -1;
			zeroCol = -1;
		}
	}

	if (InputCheck(rows, cols, row, col - 1)) {
		if (field[row][col - 1] == 0) {
			zeroRow = row;
			zeroCol = col - 1;
			return true;
		}
		else {
			zeroRow = -1;
			zeroCol = -1;
		}
	}

	if (InputCheck(rows, cols, row, col + 1)) {
		if (field[row][col + 1] == 0) {
			zeroRow = row;
			zeroCol = col + 1;
			return true;
		}
		else {
			zeroRow = -1;
			zeroCol = -1;
		}
	}
	return false;
}

void MakeStep(int **field, int row, int col, int zeroRow, int zeroCol) {
	field[zeroRow][zeroCol] = field[row][col];
	field[row][col] = 0;
}

int main() {
	const int rows = 4;
	const int cols = 4;
	int counter = 0;
	int **field = MatrixCreate(rows, cols);
	FieldFilling(field, rows, cols);
	FieldPrint(field, rows, cols);
	cout << counter << " steps" << endl;
	while (!WinCheck(field, rows, cols)){
		int currentRow;
		int currentCol;
		int zeroRow = -1;
		int zeroCol = -1;
		while(true) {
			do {
				cout << "Enter coordinate (row col): ";
				cin >> currentRow >> currentCol;
				if (!InputCheck(rows, cols, currentRow - 1, currentCol - 1))
					cout << "Wrong coordinate!" << endl;
			} while (!InputCheck(rows, cols, currentRow - 1, currentCol - 1));
			if (EmptyNeighborCheck(field, rows, cols, currentRow - 1, currentCol - 1, zeroRow, zeroCol) == 1){
				MakeStep(field, currentRow - 1, currentCol - 1, zeroRow, zeroCol);
				counter++;
				break;
			}
			else
				cout << "Wrong step!" << endl;
		}
		FieldPrint(field, rows, cols);
		cout << counter << " steps" << endl;
	}
	cout << "Congratulations!" << endl;
	MatrixDelete(field, rows, cols);
}
