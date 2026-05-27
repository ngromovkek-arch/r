#include <stdio.h>
#include <stdlib.h>

// Определение перечисления для форматов вывода
enum E_Type {
    FORMAT_DD_MM_YY = 1,   // dd.mm.yy
    FORMAT_DD_MM_YYYY = 2, // dd.mm.yyyy
    FORMAT_YYYY_MM_DD = 3  // yyyy/mm/dd
};

// Функция проверки корректности даты
int is_valid_date(int d, int m, int y) {
    // Проверка месяца
    if (m < 1 || m > 12) return 0;
    
    // Проверка дня в зависимости от месяца
    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    // Проверка високосного года
    int is_leap = (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
    if (is_leap && m == 2) {
        days_in_month[1] = 29;
    }
    
    if (d < 1 || d > days_in_month[m - 1]) return 0;
    
    return 1;
}

// Функция вывода даты в нужном формате
void print_date(int d, int m, int y, enum E_Type k, FILE *output) {
    // Проверка на валидность даты
    if (!is_valid_date(d, m, y)) {
        fprintf(output, "Ошибка: Неверная дата (%d.%d.%d)\n", d, m, y);
        return;
    }
    
    // Вывод в зависимости от формата
    switch (k) {
        case FORMAT_DD_MM_YY:
            fprintf(output, "%02d.%02d.%02d\n", d, m, y % 100);
            break;
            
        case FORMAT_DD_MM_YYYY:
            fprintf(output, "%02d.%02d.%04d\n", d, m, y);
            break;
            
        case FORMAT_YYYY_MM_DD:
            fprintf(output, "%04d/%02d/%02d\n", y, m, d);
            break;
            
        default:
            fprintf(output, "Ошибка: Неверный формат вывода (k = %d)\n", k);
            break;
    }
}

int main(int argc, char *argv[]) {
    FILE *input_file, *output_file;
    char filename[256];
    int d, m, y, k;
    int line_num = 1;
    
    // Проверка аргументов командной строки
    if (argc != 2) {
        printf("Использование: %s <имя_файла>\n", argv[0]);
        return 1;
    }
    
    // Открытие входного файла
    input_file = fopen(argv[1], "r");
    if (input_file == NULL) {
        printf("Ошибка: Не удалось открыть файл %s\n", argv[1]);
        return 1;
    }
    
    // Открытие выходного файла
    output_file = fopen("out.txt", "w");
    if (output_file == NULL) {
        printf("Ошибка: Не удалось создать файл out.txt\n");
        fclose(input_file);
        return 1;
    }
    
    // Чтение данных из файла и обработка
    while (fscanf(input_file, "%d %d %d %d", &d, &m, &y, &k) == 4) {
        fprintf(output_file, "Строка %d: ", line_num);
        print_date(d, m, y, (enum E_Type)k, output_file);
        line_num++;
    }
    
    // Закрытие файлов
    fclose(input_file);
    fclose(output_file);
    
    printf("Обработка завершена. Результат записан в файл out.txt\n");
    
    return 0;
}
