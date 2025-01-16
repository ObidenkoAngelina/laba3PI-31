﻿#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime> 
#include <string>

#define SIZE 9
#define TIME_LIMIT 300

class Grid {
protected:
    char cells[SIZE][SIZE];
    bool visible[SIZE][SIZE];
    static int gridCount;

public:

    Grid() {
        // Инициализация массива visible
        for (int row = 0; row < SIZE; row++) {
            for (int col = 0; col < SIZE; col++) {
                this->visible[row][col] = true; // Сначала все ячейки видимые
            }
        }
        gridCount++; // Увеличиваем счетчик при создании нового объекта
    }

    // Деструктор
    ~Grid() {
        gridCount--; // Уменьшаем счетчик при уничтожении объекта
    }

    // Статический метод для получения количества объектов Grid
    static int getGridCount() {
        return gridCount;
    }

    // Конструктор копирования
    Grid(const Grid& other) {
        for (int row = 0; row < SIZE; row++) {
            for (int col = 0; col < SIZE; col++) {
                this->cells[row][col] = other.cells[row][col];
                this->visible[row][col] = other.visible[row][col];
            }
        }
        gridCount++;
    }

    // Перегрузка оператора присваивания
    Grid& operator=(const Grid& other) {
        if (this != &other) { // Проверка на самоприсваивание
            for (int row = 0; row < SIZE; row++) {
                for (int col = 0; col < SIZE; col++) {
                    this->cells[row][col] = other.cells[row][col];
                    this->visible[row][col] = other.visible[row][col];
                }
            }
        }
        return *this;
    }

    virtual void initializeGrid() {
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
                this->cells[row][col] = '0' + value; // Преобразуем в символ
            }
        }
    }

    void hideNumbers(int row) {
        int hiddenCount = 0;
        while (hiddenCount < 1) { // Скрываем 4 числа
            int col = rand() % SIZE; // Генерируем случайный индекс колонки
            if (this->visible[row][col]) { // Проверяем, чтобы не скрыть уже скрытое
                this->visible[row][col] = false; // Скрыть это число
                hiddenCount++;
            }
        }
    }

    bool insertNumber(int row, int col, int number) {
        // Проверка корректности введенных индексов
        if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) {
            throw std::out_of_range("Некорректный выбор ячейки."); // Выбрасываем исключение
        }

        // Проверка, открыта ли ячейка
        if (visible[row][col]) {
            throw std::logic_error("Эта ячейка уже открыта."); // Выбрасываем исключение
        }

        // Проверка на корректность введенного числа
        if (number < 1 || number > 9) {
            throw std::invalid_argument("Неверное число. Пожалуйста, введите число от 1 до 9."); // Выбрасываем исключение
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
                if (!this->visible[row][col]) {
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

// Инициализация статического поля
int Grid::gridCount = 0;

class CustomGrid : public Grid {
public:
    // Перегрузка оператора присваивания
    CustomGrid& operator=(const CustomGrid& other) {
        if (this != &other) { // Проверка на самоприсваивание
            Grid::operator=(other); // Копируем базовую часть
            // Здесь можно добавить код для копирования специфичных для CustomGrid данных
        }
        return *this;
    }

    // Перегрузка метода initializeGrid без вызова базового метода
    void initializeGrid() override {
        std::cout << "Инициализация пользовательской сетки." << std::endl;
        for (int row = 0; row < SIZE; row++) {
            for (int col = 0; col < SIZE; col++) {
                // Заполнение сетки случайными числами от 1 до 9
                this->cells[row][col] = '0' + (rand() % 9 + 1);
                this->visible[row][col] = true; // Все ячейки видимы
            }
        }
    }

    // Перегрузка метода initializeGrid с вызовом базового метода
    void initializeGridWithBase() {
        Grid::initializeGrid(); // Вызов метода базового класса
        std::cout << "Дополнительная инициализация пользовательской сетки." << std::endl;
        // Дополнительная логика инициализации может быть добавлена здесь
    }
};

class Player {
private:
    Grid* grid; // Ссылка на объект Grid
    std::string name;

public:
    Player(Grid* grid, const std::string& name) : grid(grid), name(name) {}

    void play(time_t startTime) {
        std::cout << "Игрок " << this->name << " начинает игру...\n";
        while (!this->grid->allCellsVisible() && !Grid::isTimeUp(startTime)) {
            int row, col, number;
            try {
                std::cout << "Введите номер строки (0-8): ";
                std::cin >> row;

                std::cout << "Введите номер колонки (0-8): ";
                std::cin >> col;

                std::cout << "Введите число (1-9): ";
                std::cin >> number;

                bool result = this->grid->insertNumber(row, col, number);
                std::cout << *this->grid;

                if (!result) {
                    std::cout << "Попробуйте снова.\n";
                }
            }
            catch (const std::exception& e) { // Перехватываем исключения
                std::cout << "Ошибка: " << e.what() << "\n"; // Выводим сообщение об ошибке
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

    std::cout << "Всего создано объектов Grid: " << Grid::getGridCount() << std::endl;

    delete dynamicGrid; // Освобождение памяти, занятой объектом Grid
    return 0;

}