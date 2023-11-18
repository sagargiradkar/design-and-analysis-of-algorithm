#include <iostream>
#include <cstdlib>

using namespace std;

int board[20], count = 0;

int place(int row, int column) {
    for (int i = 1; i <= row - 1; i++) {
        if (board[i] == column || abs(board[i] - column) == abs(i - row))
            return 0;
    }
    return 1;
}
void Queen(int row, int n) {
    for (int column = 1; column <= n; column++) {
        if (place(row, column)) {
            board[row] = column;
            if (row == n)
                print_board(n);
            else
                Queen(row + 1, n);
        }
    }
}
void print_board(int n) {
    cout << "\nSolution " << ++count << ":\n";
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (board[i] == j)
                cout << "Q ";
            else
                cout << "- ";
        }
        cout << "\n";
    }
}

int main() {
    int n;
    cout << "Enter the number of queens: ";
    cin >> n;

    if (n <= 0) {
        cout << "Please enter a valid positive integer for the number of queens.\n";
        return 1;
    }

    Queen(1, n);
    if (count == 0)
        cout << "No solutions found for " << n << "-Queens problem.\n";

    return 0;
}
