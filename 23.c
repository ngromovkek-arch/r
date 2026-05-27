#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int r;
    int g;
    int b;
} Color;

// Функция преобразования HEX в RGB
Color *getColorFromHex(const char *str) {
    // Проверка на корректность входной строки
    if (str == NULL || str[0] != '#' || strlen(str) != 7) {
        return NULL;
    }
    
    // Проверка, что все символы после # являются шестнадцатеричными цифрами
    for (int i = 1; i < 7; i++) {
        if (!isxdigit(str[i])) {
            return NULL;
        }
    }
    
    // Выделение памяти для структуры Color
    Color *color = (Color *)malloc(sizeof(Color));
    if (color == NULL) {
        return NULL;
    }
    
    // Преобразование HEX в RGB
    char hex[3];
    
    // Красный компонент (2 символа)
    hex[0] = str[1];
    hex[1] = str[2];
    hex[2] = '\0';
    color->r = (int)strtol(hex, NULL, 16);
    
    // Зеленый компонент (2 символа)
    hex[0] = str[3];
    hex[1] = str[4];
    hex[2] = '\0';
    color->g = (int)strtol(hex, NULL, 16);
    
    // Синий компонент (2 символа)
    hex[0] = str[5];
    hex[1] = str[6];
    hex[2] = '\0';
    color->b = (int)strtol(hex, NULL, 16);
    
    return color;
}

int main(int argc, char *argv[]) {
    // Проверка наличия аргумента командной строки
    if (argc != 2) {
        printf("использование: %s <HEX-цвет>\n", argv[0]);
        return 1;
    }
    
    // Получение цвета из HEX строки
    Color *color = getColorFromHex(argv[1]);
    
    // Вывод результата
    if (color == NULL) {
        printf("невозможно преобразовать\n");
    } else {
        printf("%d %d %d\n", color->r, color->g, color->b);
        free(color); // Освобождение выделенной памяти
    }
    
    return 0;
}
