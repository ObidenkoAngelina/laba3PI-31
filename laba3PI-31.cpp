#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime> 
#include <string>

#define SIZE 9
#define TIME_LIMIT 300

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

    // Конструктор копирования
    Grid(const Grid& other) {
        for (int row = 0; row < SIZE; row++) {
            for (int col = 0; col < SIZE; col++) {
                cells[row][col] = other.cells[row][col];
                visible[row][col] = other.visible[row][col];
            }
        }
    }

    // Перегрузка оператора присваивания
    Grid& operator=(const Grid& other) {
        if (this != &other) { // Проверка на самоприсваивание
            for (int row = 0; row < SIZE; row++) {
                for (int col = 0; col < SIZE; col++) {
                    cells[row][col] = other.cells[row][col];
                    visible[row][col] = other.visible[row][col];
                }
            }
        }
        return *this;
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
        while (hiddenCount < 1) { // Скрываем 4 числа
            int col = rand() % SIZE; // Генерируем случайный индекс колонки
            if (visible[row][col]) { // Проверяем, чтобы не скрыть уже скрытое
                visible[row][col] = false; // Скрыть это число
                hiddenCount++;
            }
        }
    }

    bool insertNumber(int row, int col, int number) {
        // Проверка корректности введенных индексов
        if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) {
            std::cout << "Некорректный выбор ячейки.\n";
            return false;
        }

        // Проверка, открыта ли ячейка
        if (visible[row][col]) {
            std::cout << "Эта ячейка уже открыта.\n";
            return false;
        }

        // Проверка на корректность введенного числа
        if (number < 1 || number > 9) {
            std::cout << "Неверное число. Пожалуйста, введите число от 1 до 9.\n";
            return false;
        }

        // Сравнение введенного числа с фактическим значением ячейки
        if (cells[row][col] == '0' + number) {
            visible[row][col] = true; // Открываем ячейку
            std::cout << "Правильное число! Ячейка открыта.\n";
            return true;
        }
        else {
            std::cout << "Неправильное число!\n";
            return false;
        }
    }

    void insertNumber(int row, int col, int number, bool* result) {
        *result = insertNumber(row, col, number);
    }

    bool allCellsVisible() {
        for (int row = 0; row < SIZE; row++) {
            for (int col = 0; col < SIZE; col++) {
                if (!visible[row][col]) {
                    return false; // Если найдена закрытая ячейка
                }
            }
        }
        return true; // Все ячейки открыты
    }

    static bool isTimeUp(time_t startTime) {
        return difftime(time(NULL), startTime) >= TIME_LIMIT; // Возвращает true, если время истекло
    }

    // Перегрузка оператора вывода
    friend std::ostream& operator<<(std::ostream& os, const Grid& grid) {
        os << "+---+---+---+---+---+---+---+---+---+\n";
        for (int row = 0; row < SIZE; row++) {
            for (int col = 0; col < SIZE; col++) {
                if (grid.visible[row][col]) {
                    os << "| " << grid.cells[row][col] << " "; // Печать видимых значений
                }
                else {
                    os << "|   "; // Печать скрытых значений
                }
            }
            os << "|\n";
            os << "+---+---+---+---+---+---+---+---+---+\n";
        }
        return os;
    }

};

class Player {
private:
    Grid* grid; // Ссылка на объект Grid
    std::string name;

public:
    Player(Grid* grid, const std::string& name) : grid(grid), name(name) {}

    void play(time_t startTime) {
        std::cout << "Игрок " << name << " начинает игру...\n";
        while (!grid->allCellsVisible() && !Grid::isTimeUp(startTime)) {
            int row, col, number;

            // Запрос ввода номера строки
            std::cout << "Введите номер строки (0-8): ";
            std::cin >> row;

            // Запрос ввода номера колонки
            std::cout << "Введите номер колонки (0-8): ";
            std::cin >> col;

            // Запрос ввода числа
            std::cout << "Введите число (1-9): ";
            std::cin >> number;

            bool result = grid->insertNumber(row, col, number); // Получаем результат
            std::cout << *grid; // Используем перегруженный оператор для отображения сетки

            if (!result) {
                std::cout << "Попробуйте снова.\n";
            }
        }

        if (Grid::isTimeUp(startTime)) { // Проверка на истечение времени
            std::cout << "Ваше время вышло! Игрок " << name << " проиграл!\n";
        }
        else {
            std::cout << "Все ячейки открыты! Игрок " << name << " победил!\n"; // Сообщение о победе
        }
    }
};

int main() {
    setlocale(LC_ALL, "Rus");
    srand(static_cast<unsigned int>(time(0))); // Инициализация генератора случайных чисел
    time_t startTime = time(NULL);

    Grid* dynamicGrid = new Grid(); // Создание одного динамического объекта Grid
    dynamicGrid->initializeGrid(); // Инициализация сетки
    for (int row = 0; row < SIZE; row++) {
        dynamicGrid->hideNumbers(row);
    }

    // Начальное состояние сетки
    std::cout << *dynamicGrid; // Вызов перегруженного оператора для отображения сетки

    std::string playerName;
    std::cout << "Введите имя игрока: ";
    std::getline(std::cin, playerName);

    // Создаем игрока и начинаем игру
    Player player(dynamicGrid, playerName);
    player.play(startTime);

    delete dynamicGrid; // Освобождение памяти, занятой объектом Grid
    return 0;
}