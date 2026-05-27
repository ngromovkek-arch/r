#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Функция проверки счастливого билета
int isLuckyTicket(const char *number) {
    if (strlen(number) != 6) return 0;
    
    int sum1 = 0, sum2 = 0;
    
    // Сумма первых трёх цифр
    for (int i = 0; i < 3; i++) {
        if (number[i] < '0' || number[i] > '9') return 0;
        sum1 += number[i] - '0';
    }
    
    // Сумма последних трёх цифр
    for (int i = 3; i < 6; i++) {
        if (number[i] < '0' || number[i] > '9') return 0;
        sum2 += number[i] - '0';
    }
    
    return sum1 == sum2;
}

int main(int argc, char *argv[]) {
    // Проверка аргументов командной строки
    if (argc != 2) {
        printf("Использование: %s <имя_файла>\n", argv[0]);
        return 1;
    }
    
    const char *inputFilename = argv[1];
    const char *outputFilename = "out.txt";
    
    // Открытие входного файла
    FILE *inputFile = fopen(inputFilename, "r");
    if (inputFile == NULL) {
        printf("Ошибка: не удалось открыть файл %s\n", inputFilename);
        return 1;
    }
    
    // Открытие выходного файла
    FILE *outputFile = fopen(outputFilename, "w");
    if (outputFile == NULL) {
        printf("Ошибка: не удалось создать файл %s\n", outputFilename);
        fclose(inputFile);
        return 1;
    }
    
    char line[100];
    int firstTicket = 1;
    
    // Чтение файла построчно
    while (fgets(line, sizeof(line), inputFile) != NULL) {
        // Удаление символа новой строки
        line[strcspn(line, "\n")] = '\0';
        
        // Пропуск пустых строк
        if (strlen(line) == 0) continue;
        
        // Проверка длины строки
        if (strlen(line) != 6) {
            printf("Предупреждение: некорректный номер билета '%s' (должен быть 6 цифр)\n", line);
            continue;
        }
        
        // Проверка на счастливый билет
        int isLucky = isLuckyTicket(line);
        
        // Запись результата в выходной файл
        if (!firstTicket) {
            fprintf(outputFile, "\n");
        }
        fprintf(outputFile, "%s %s", line, isLucky ? "true" : "false");
        firstTicket = 0;
    }
    
    // Закрытие файлов
    fclose(inputFile);
    fclose(outputFile);
    
    printf("Результаты записаны в файл %s\n", outputFilename);
    
    return 0;
}
