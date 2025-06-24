#include <iostream>
#include <vector>

using namespace std;

// Функция для отображения игрового поля
void displayBoard(const vector<vector<char>>& board) {
    cout << "\n";
    for (int i = 0; i < 3; ++i) {
        cout << " ";
        for (int j = 0; j < 3; ++j) {
            cout << board[i][j];
            if (j < 2) cout << " | ";
        }
        cout << "\n";
        if (i < 2) cout << "-----------\n";
    }
    cout << "\n";
}

// Функция для проверки победы
bool checkWin(const vector<vector<char>>& board, char player) {
    // Проверка строк и столбцов
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            return true;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
            return true;
    }
    
    // Проверка диагоналей
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
        return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
        return true;
    
    return false;
}

// Функция для проверки ничьей
bool checkDraw(const vector<vector<char>>& board) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == ' ')
                return false;
        }
    }
    return true;
}

int main() {
    vector<vector<char>> board(3, vector<char>(3, ' '));
    char currentPlayer = 'X';
    int row, col;
    bool gameOver = false;
    
    cout << "Добро пожаловать в игру Крестики-нолики!\n";
    cout << "Игрок X ходит первым, затем игрок O.\n";
    cout << "Введите номер строки (1-3) и столбца (1-3) для вашего хода.\n";
    
    while (!gameOver) {
        displayBoard(board);
        cout << "Игрок " << currentPlayer << ", ваш ход: ";
        cin >> row >> col;
        
        // Проверка корректности ввода
        if (row < 1 || row > 3 || col < 1 || col > 3) {
            cout << "Неверные координаты. Попробуйте снова.\n";
            continue;
        }
        
        // Переход к индексам массива (0-2)
        row--;
        col--;
        
        // Проверка, свободна ли клетка
        if (board[row][col] != ' ') {
            cout << "Эта клетка уже занята. Попробуйте другую.\n";
            continue;
        }
        
        // Делаем ход
        board[row][col] = currentPlayer;
        
        // Проверка на победу
        if (checkWin(board, currentPlayer)) {
            displayBoard(board);
            cout << "Игрок " << currentPlayer << " победил! Поздравляем!\n";
            gameOver = true;
        } 
        // Проверка на ничью
        else if (checkDraw(board)) {
            displayBoard(board);
            cout << "Ничья! Игра окончена.\n";
            gameOver = true;
        } 
        // Смена игрока
        else {
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
    }
    
    cout << "Хотите сыграть еще раз? (y/n): ";
    char playAgain;
    cin >> playAgain;
    
    if (playAgain == 'y' || playAgain == 'Y') {
        // Очищаем доску и начинаем заново
        board = vector<vector<char>>(3, vector<char>(3, ' '));
        main(); // Рекурсивный вызов main (не лучшая практика, но для простоты)
    } else {
        cout << "Спасибо за игру! До свидания!\n";
    }
    
    return 0;
}