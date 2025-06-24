#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Константы игры
const int BOARD_SIZE = 3;
const char EMPTY_CELL = ' ';
const char PLAYER_X = 'X';
const char PLAYER_O = 'O';

/* 
 * Инициализирует пустое игровое поле
 * @return Пустое поле размером BOARD_SIZE x BOARD_SIZE
 */
vector<vector<char>> InitializeGameBoard() {
    return vector<vector<char>>(BOARD_SIZE, vector<char>(BOARD_SIZE, EMPTY_CELL));
}

/*
 * Отображает текущее состояние игрового поля
 * @param board - текущее игровое поле
 */
void DisplayGameBoard(const vector<vector<char>>& board) {
    cout << "\nТекущее состояние поля:\n";
    for (int row = 0; row < BOARD_SIZE; ++row) {
        cout << " ";
        for (int col = 0; col < BOARD_SIZE; ++col) {
            cout << board[row][col];
            if (col < BOARD_SIZE - 1) cout << " | ";
        }
        cout << "\n";
        if (row < BOARD_SIZE - 1) cout << "-----------\n";
    }
    cout << endl;
}

/*
 * Проверяет, содержит ли линия 3 одинаковых символа (не EMPTY_CELL)
 * @param line - проверяемая линия (строка, столбец или диагональ)
 * @return true, если линия содержит 3 одинаковых символа
 */
bool IsLineCompleted(const vector<char>& line) {
    return (line[0] != EMPTY_CELL && line[0] == line[1] && line[1] == line[2]);
}

/*
 * Проверяет, выиграл ли текущий игрок
 * @param board - игровое поле
 * @param player - символ игрока (PLAYER_X или PLAYER_O)
 * @return true, если игрок выиграл
 */
bool CheckPlayerWin(const vector<vector<char>>& board, char player) {
    // Проверка строк и столбцов
    for (int i = 0; i < BOARD_SIZE; ++i) {
        // Проверка строки
        if (IsLineCompleted({board[i][0], board[i][1], board[i][2]})) 
            return true;
        
        // Проверка столбца
        if (IsLineCompleted({board[0][i], board[1][i], board[2][i]}))
            return true;
    }
    
    // Проверка диагоналей
    if (IsLineCompleted({board[0][0], board[1][1], board[2][2]}))
        return true;
    if (IsLineCompleted({board[0][2], board[1][1], board[2][0]}))
        return true;
        
    return false;
}

/*
 * Проверяет, наступила ли ничья
 * @param board - игровое поле
 * @return true, если нет свободных клеток
 */
bool IsGameDraw(const vector<vector<char>>& board) {
    for (const auto& row : board) {
        for (char cell : row) {
            if (cell == EMPTY_CELL)
                return false;
        }
    }
    return true;
}

/*
 * Получает и проверяет ход игрока
 * @param board - игровое поле
 * @param player - текущий игрок
 */
void ProcessPlayerMove(vector<vector<char>>& board, char player) {
    int row, col;
    while (true) {
        cout << "Игрок " << player << ", введите строку и столбец (1-" 
             << BOARD_SIZE << "): ";
        cin >> row >> col;
        
        // Преобразование в индексы массива
        row--;
        col--;
        
        // Проверка ввода
        if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
            cout << "Ошибка! Координаты должны быть от 1 до " << BOARD_SIZE << ".\n";
            continue;
        }
        
        if (board[row][col] != EMPTY_CELL) {
            cout << "Эта клетка уже занята! Выберите другую.\n";
            continue;
        }
        
        break;
    }
    
    board[row][col] = player;
}

/*
 * Определяет, хочет ли игрок сыграть снова
 * @return true, если игрок ввел 'Y' или 'y'
 */
bool AskToPlayAgain() {
    char choice;
    cout << "Хотите сыграть еще раз? (Y/N): ";
    cin >> choice;
    return (choice == 'Y' || choice == 'y');
}

// Основная функция игры
void RunGame() {
    do {
        vector<vector<char>> gameBoard = InitializeGameBoard();
        char currentPlayer = PLAYER_X;
        bool gameFinished = false;
        
        while (!gameFinished) {
            DisplayGameBoard(gameBoard);
            ProcessPlayerMove(gameBoard, currentPlayer);
            
            if (CheckPlayerWin(gameBoard, currentPlayer)) {
                DisplayGameBoard(gameBoard);
                cout << "Игрок " << currentPlayer << " победил!\n";
                gameFinished = true;
            } else if (IsGameDraw(gameBoard)) {
                DisplayGameBoard(gameBoard);
                cout << "Ничья!\n";
                gameFinished = true;
            } else {
                currentPlayer = (currentPlayer == PLAYER_X) ? PLAYER_O : PLAYER_X;
            }
        }
    } while (AskToPlayAgain());
    
    cout << "Спасибо за игру!\n";
}

int main() {
    cout << "Добро пожаловать в игру Крестики-нолики!\n";
    cout << "Для хода вводите номер строки и столбца (например, 1 2).\n";
    
    RunGame();
    
    return 0;
}