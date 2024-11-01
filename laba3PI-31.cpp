#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime> 

#define SIZE 9

class Grid {
private:
    char cells[SIZE][SIZE];
    bool visible[SIZE][SIZE];

public:

    Grid() {
        // Инициализация массива visible
        for (int row = 0; row < SIZE; row++) {
            for (int col = 0; col < SIZE; col++) {
                visible[row][col] = true; // Сначала все ячейки видимые
            }
        }
    }

    void initializeGrid() {
        for (int row = 0; row < SIZE; row++) {
            for (int col = 0; col < SIZE; col++) {
                // Определяем начальное значение для каждой строки
                int startValue;
                if (row == 6) {
                    startValue = 3; // Шестая строка (индекс 6) должна начинаться с 3
                }
                else if (row == 7) {
                    startValue = 6; // Седьмая строка (индекс 7) должна начинаться с 6
                }
                else if (row == 8) {
                    startValue = 9; // Восьмая строка (индекс 8) должна начинаться с 9
                }
                else {
                    startValue = (row < 3) ? (row * 3 + 1) : (2 + (row - 3) * 3);
                }
                // Используем формулу для заполнения ячеек
                int value = (startValue + col - 1) % 9 + 1;
                cells[row][col] = '0' + value; // Преобразуем в символ
            }
        }
    }

    void hideNumbers(int row) {
        int hiddenCount = 0;
        while (hiddenCount < 4) { // Скрываем 4 числа
            int col = rand() % SIZE; // Генерируем случайный индекс колонки
            if (visible[row][col]) { // Проверяем, чтобы не скрыть уже скрытое
                visible[row][col] = false; // Скрыть это число
                hiddenCount++;
            }
        }
    }

    void printGrid() {
        std::cout << "+---+---+---+---+---+---+---+---+---+\n";
        for (int row = 0; row < SIZE; row++) {
            for (int col = 0; col < SIZE; col++) {
                if (visible[row][col]) {
                    std::cout << "| " << cells[row][col] << " "; // Печать видимых значений
                }
                else {
                    std::cout << "|   "; // Печать скрытых значений
                }
            }
            std::cout << "|\n";
            std::cout << "+---+---+---+---+---+---+---+---+---+\n";
        }
    }

    void insertNumber() {
        int row, col, number;

        // Запрос ввода номера строки
        std::cout << "Введите номер строки (0-8): ";
        std::cin >> row;

        // Запрос ввода номера колонки
        std::cout << "Введите номер колонки (0-8): ";
        std::cin >> col;

        // Проверка корректности введенных индексов
        if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) {
            std::cout << "Некорректный выбор ячейки.\n";
            return;
        }

        // Проверка, открыта ли ячейка
        if (visible[row][col]) {
            std::cout << "Эта ячейка уже открыта.\n";
            return;
        }

        // Запрос ввода числа
        std::cout << "Введите число (1-9): ";
        std::cin >> number;

        // Проверка на корректность введенного числа
        if (number < 1 || number > 9) {
            std::cout << "Неверное число. Пожалуйста, введите число от 1 до 9.\n";
            return;
        }

        // Сравнение введенного числа с фактическим значением ячейки
        if (cells[row][col] == '0' + number) {
            visible[row][col] = true; // Открываем ячейку
            std::cout << "Правильное число! Ячейка открыта.\n";
        }
        else {
            std::cout << "Неправильное число!\n";
        }
    }
};

int main() {
    setlocale(LC_ALL, "Rus");
    srand(static_cast<unsigned int>(time(0))); // Инициализация генератора случайных чисел
    Grid* dynamicGrid = new Grid(); // Создание одного динамического объекта Grid
    dynamicGrid->initializeGrid(); // Инициализация сетки
    for (int row = 0; row < SIZE; row++) {
        dynamicGrid->hideNumbers(row);
    }
    dynamicGrid->printGrid();
    dynamicGrid->insertNumber();
    dynamicGrid->printGrid();
    delete dynamicGrid; // Освобождение памяти, занятой объектом Grid
    return 0;
}