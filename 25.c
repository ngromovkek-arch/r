#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

// Функция подсчета количества строк в файле
int count_lines(FILE *file) {
    int lines = 0;
    int ch;
    
    // Сохраняем текущую позицию в файле
    long pos = ftell(file);
    rewind(file);
    
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            lines++;
        }
    }
    
    // Если файл не заканчивается на '\n', последняя строка тоже считается
    if (lines > 0 || ftell(file) > 0) {
        // Перемещаемся на последний символ
        fseek(file, -1, SEEK_END);
        int last_char = fgetc(file);
        if (last_char != '\n') {
            lines++;
        }
    }
    
    // Возвращаемся к сохраненной позиции
    fseek(file, pos, SEEK_SET);
    return lines;
}

// Функция подсчета общего количества символов в файле
int count_characters(FILE *file) {
    int count = 0;
    int ch;
    
    // Сохраняем текущую позицию
    long pos = ftell(file);
    rewind(file);
    
    while ((ch = fgetc(file)) != EOF) {
        count++;
    }
    
    // Возвращаемся к сохраненной позиции
    fseek(file, pos, SEEK_SET);
    return count;
}

// Функция вычисления процента пробельных символов
double calculate_whitespace_percentage(FILE *file) {
    int total_chars = 0;
    int whitespace_chars = 0;
    int ch;
    
    // Сохраняем текущую позицию
    long pos = ftell(file);
    rewind(file);
    
    while ((ch = fgetc(file)) != EOF) {
        total_chars++;
        if (isspace(ch)) {
            whitespace_chars++;
        }
    }
    
    // Возвращаемся к сохраненной позиции
    fseek(file, pos, SEEK_SET);
    
    if (total_chars == 0) {
        return 0.0;
    }
    
    return (double)whitespace_chars / total_chars * 100.0;
}

// Функция записи результатов в файл out.txt
void write_results(const char *filename, int lines, int chars, double percentage) {
    FILE *out = fopen("out.txt", "w");
    if (out == NULL) {
        printf("Ошибка: не удалось создать файл out.txt\n");
        return;
    }
    
    fprintf(out, "%d\n", lines);
    fprintf(out, "%d\n", chars);
    fprintf(out, "%.2f%%\n", percentage);
    
    fclose(out);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Использование: %s <имя_файла>\n", argv[0]);
        return 1;
    }
    
    // Открываем файл для чтения
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Ошибка: не удалось открыть файл %s\n", argv[1]);
        return 1;
    }
    
    // Вызываем функции для подсчета
    int lines = count_lines(file);
    int chars = count_characters(file);
    double percentage = calculate_whitespace_percentage(file);
    
    // Выводим результаты на экран
    printf("Результаты обработки файла %s:\n", argv[1]);
    printf("Количество строк: %d\n", lines);
    printf("Количество символов: %d\n", chars);
    printf("Процент пробельных символов: %.2f%%\n", percentage);
    
    // Записываем результаты в файл out.txt
    write_results(argv[1], lines, chars, percentage);
    
    printf("\nРезультаты сохранены в файл out.txt\n");
    
    fclose(file);
    return 0;
}
