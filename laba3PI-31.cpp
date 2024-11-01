#include <iostream>
#include <cstdio>

#define SIZE 9

class Grid {
private:
    char cells[SIZE][SIZE];

public:

    void printGrid() {
        std::cout << "+---+---+---+---+---+---+---+---+---+\n";
        for (int row = 0; row < SIZE; row++) {
            for (int col = 0; col < SIZE; col++) {
                std::cout << "|   ";
            }
            std::cout << "|\n";
            std::cout << "+---+---+---+---+---+---+---+---+---+\n";
        }
    }
};

int main() {
    Grid* dynamicGrid = new Grid(); // Создание одного динамического объекта Grid
    dynamicGrid->printGrid(); // Печать сетки
    delete dynamicGrid; // Освобождение памяти, занятой объектом Grid
    return 0;
}