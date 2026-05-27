#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* divide(int first, int second, size_t sequenceLength) {
    if (second == 0) {
        return NULL;
    }
    
    // Вычисляем целую часть
    int integerPart = first / second;
    int remainder = first % second;
    
    // Выделяем память под строку: целая часть + точка + sequenceLength цифр + '\0'
    char* result = (char*)malloc(sequenceLength + 20); // +20 для запаса
    if (result == NULL) {
        return NULL;
    }
    
    // Формируем целую часть с точкой
    sprintf(result, "%d.", integerPart);
    
    // Получаем указатель на позицию после точки
    char* ptr = result + strlen(result);
    
    // Генерируем дробную часть
    for (size_t i = 0; i < sequenceLength; i++) {
        remainder *= 10;
        int digit = remainder / second;
        ptr[i] = '0' + digit;
        remainder %= second;
    }
    ptr[sequenceLength] = '\0';
    
    return result;
}

int main() {
    FILE* inputFile = fopen("task16.txt", "r");
    if (inputFile == NULL) {
        printf("Ошибка: не удалось открыть файл task16.txt\n");
        return 1;
    }
    
    int first, second;
    size_t sequenceLength;
    
    if (fscanf(inputFile, "%d %d %zu", &first, &second, &sequenceLength) != 3) {
        printf("Ошибка: неверный формат данных в файле\n");
        fclose(inputFile);
        return 1;
    }
    fclose(inputFile);
    
    // Вызываем функцию деления
    char* result = divide(first, second, sequenceLength);
    if (result == NULL) {
        printf("Ошибка: деление на ноль или недостаточно памяти\n");
        return 1;
    }
    
    // Записываем результат в out.txt
    FILE* outputFile = fopen("out.txt", "w");
    if (outputFile == NULL) {
        printf("Ошибка: не удалось создать файл out.txt\n");
        free(result);
        return 1;
    }
    
    fprintf(outputFile, "%s\n", result);
    fclose(outputFile);
    
    // Освобождаем память
    free(result);
    
    printf("Результат успешно записан в файл out.txt\n");
    
    return 0;
}
