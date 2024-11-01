#include <iostream>
#include <cstdio>

#define SIZE 9

class Grid {
private:
    char cells[SIZE][SIZE];

public:

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
                int value = (startValue + col - 1) % 9 + 1; // Модуль 9 и плюс 1 для диапазона от 1 до 9
                cells[row][col] = '0' + value; // Преобразуем в символ
            }
        }
    }

    void printGrid() {
        std::cout << "+---+---+---+---+---+---+---+---+---+\n";
        for (int row = 0; row < SIZE; row++) {
            for (int col = 0; col < SIZE; col++) {
                std::cout << "| " << cells[row][col] << " ";
            }
            std::cout << "|\n";
            std::cout << "+---+---+---+---+---+---+---+---+---+\n";
        }
    }
};

int main() {
    Grid* dynamicGrid = new Grid(); // Создание одного динамического объекта Grid
    dynamicGrid->initializeGrid(); // Инициализация сетки
    dynamicGrid->printGrid(); // Печать сетки
    delete dynamicGrid; // Освобождение памяти, занятой объектом Grid
    return 0;
}