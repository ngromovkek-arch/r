#include <stdio.h>
#include <string.h>

int getCountSubstr(const char* str, const char* substr) {
    int count = 0;
    int len_str = strlen(str);
    int len_sub = strlen(substr);
    
    if (len_sub == 0) return 0;
    
    for (int i = 0; i <= len_str - len_sub; i++) {
        if (strncmp(&str[i], substr, len_sub) == 0) {
            count++;
            i += len_sub - 1; // Сдвиг для непересекающихся вхождений
            // Если нужны пересекающиеся вхождения, замените строку выше на:
            // (пусто, т.е. i++ будет автоматически)
        }
    }
    
    return count;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Использование: %s <имя_файла>\n", argv[0]);
        return 1;
    }
    
    const char* filename = argv[1];
    FILE* file = fopen(filename, "r");
    
    if (file == NULL) {
        printf("Ошибка: не удалось открыть файл %s\n", filename);
        return 1;
    }
    
    char str[1000];
    char substr[1000];
    
    // Читаем первую строку (текст, содержащий пробелы)
    if (fgets(str, sizeof(str), file) == NULL) {
        printf("Ошибка: не удалось прочитать первую строку\n");
        fclose(file);
        return 1;
    }
    
    // Удаляем символ новой строки, если он есть
    str[strcspn(str, "\n")] = '\0';
    
    // Читаем вторую строку (подстроку)
    if (fgets(substr, sizeof(substr), file) == NULL) {
        printf("Ошибка: не удалось прочитать вторую строку\n");
        fclose(file);
        return 1;
    }
    
    // Удаляем символ новой строки, если он есть
    substr[strcspn(substr, "\n")] = '\0';
    
    fclose(file);
    
    // Подсчитываем количество вхождений
    int result = getCountSubstr(str, substr);
    
    // Выводим результат
    printf("Строка: \"%s\"\n", str);
    printf("Подстрока: \"%s\"\n", substr);
    printf("Количество вхождений: %d\n", result);
    
    return 0;
}
