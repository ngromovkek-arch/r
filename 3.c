#include <stdio.h>
#include <string.h>

void remove_char(char *str, char ch) {
    if (str == NULL) return;
    
    char *read_ptr = str;
    char *write_ptr = str;
    
    while (*read_ptr) {
        if (*read_ptr != ch) {
            *write_ptr = *read_ptr;
            write_ptr++;
        }
        read_ptr++;
    }
    *write_ptr = '\0';
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s \"string\" character\n", argv[0]);
        return 1;
    }
    
    char *str = argv[1];
    char ch = argv[2][0];
    
    // Создаем копию строки для обработки (argv[1] может быть read-only)
    char buffer[1024];
    strncpy(buffer, str, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';
    
    // Открываем файл для записи
    FILE *file = fopen("out.txt", "w");
    if (file == NULL) {
        fprintf(stderr, "Error opening file out.txt\n");
        return 1;
    }
    
    // Выводим исходную строку
    fprintf(file, "%s\n", buffer);
    
    // Удаляем символ
    remove_char(buffer, ch);
    
    // Выводим результат
    fprintf(file, "%s\n", buffer);
    
    fclose(file);
    
    return 0;
}
