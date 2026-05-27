#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define ALPHABET_SIZE 26

// Функция для подсчета букв в тексте
void countLetters(const char *filename, int *counts) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Ошибка открытия файла %s\n", filename);
        exit(1);
    }
    
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        if (isalpha(ch)) {  // Проверяем, является ли символ буквой
            char lower = tolower(ch);  // Приводим к нижнему регистру
            counts[lower - 'a']++;  // Увеличиваем счетчик для соответствующей буквы
        }
    }
    
    fclose(file);
}

// Функция для вывода результатов в файл
void writeResults(const char *filename, const int *counts) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Ошибка открытия файла %s\n", filename);
        exit(1);
    }
    
    // Выводим буквы, которые встретились хотя бы раз
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (counts[i] > 0) {
            fprintf(file, "%c - %d\n", 'a' + i, counts[i]);
        }
    }
    
    fclose(file);
}

int main(int argc, char *argv[]) {
    // Проверяем аргументы командной строки
    if (argc != 2) {
        printf("Использование: %s <имя_файла>\n", argv[0]);
        return 1;
    }
    
    // Массив для подсчета букв (a-z)
    int letterCounts[ALPHABET_SIZE] = {0};
    
    // Подсчитываем буквы из входного файла
    countLetters(argv[1], letterCounts);
    
    // Выводим результаты в выходной файл
    writeResults("out.txt", letterCounts);
    
    printf("Результат записан в файл out.txt\n");
    
    return 0;
}
