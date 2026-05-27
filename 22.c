#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    float x;
    float y;
} Complex;

// Вычитание комплексных чисел: a - b
Complex* subtraction(const Complex* a, const Complex* b) {
    Complex* result = (Complex*)malloc(sizeof(Complex));
    if (result != NULL) {
        result->x = a->x - b->x;
        result->y = a->y - b->y;
    }
    return result;
}

// Представление комплексного числа в алгебраической форме (a + b * i)
char* getStrrtAlg(const Complex* a) {
    char* str = (char*)malloc(100 * sizeof(char));
    if (str != NULL) {
        sprintf(str, "%.1f + %.1f * i", a->x, a->y);
    }
    return str;
}

int main(int argc, char* argv[]) {
    // Проверка аргументов командной строки
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    
    // Открытие входного файла
    FILE* inputFile = fopen(argv[1], "r");
    if (inputFile == NULL) {
        printf("Error: Cannot open file %s\n", argv[1]);
        return 1;
    }
    
    // Чтение количества строк
    int S;
    fscanf(inputFile, "%d", &S);
    
    // Открытие выходного файла
    FILE* outputFile = fopen("out.txt", "w");
    if (outputFile == NULL) {
        printf("Error: Cannot create out.txt\n");
        fclose(inputFile);
        return 1;
    }
    
    // Обработка каждой строки
    for (int i = 0; i < S; i++) {
        float rel1, im1, rel2, im2;
        fscanf(inputFile, "%f %f %f %f", &rel1, &im1, &rel2, &im2);
        
        Complex a = {rel1, im1};
        Complex b = {rel2, im2};
        
        // Вычисление разности
        Complex* diff = subtraction(&a, &b);
        
        // Получение строкового представления
        char* resultStr = getStrrtAlg(diff);
        
        // Запись в выходной файл
        fprintf(outputFile, "%s\n", resultStr);
        
        // Освобождение памяти
        free(diff);
        free(resultStr);
    }
    
    // Закрытие файлов
    fclose(inputFile);
    fclose(outputFile);
    
    printf("Results written to out.txt\n");
    
    return 0;
}
