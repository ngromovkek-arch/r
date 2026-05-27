#include <stdio.h>
#include <stdlib.h>

// Функция чтения данных из файла в динамический массив
int* getData(const char* fname, size_t* size) {
    FILE* file = fopen(fname, "r");
    if (file == NULL) {
        printf("Ошибка: не удалось открыть файл %s\n", fname);
        return NULL;
    }
    
    // Временный массив для хранения чисел
    int* temp = NULL;
    size_t capacity = 10;  // Начальная емкость
    size_t count = 0;
    
    temp = (int*)malloc(capacity * sizeof(int));
    if (temp == NULL) {
        printf("Ошибка: не удалось выделить память\n");
        fclose(file);
        return NULL;
    }
    
    int num;
    while (fscanf(file, "%d", &num) == 1) {
        // Если массив заполнен, увеличиваем его размер
        if (count >= capacity) {
            capacity *= 2;
            int* new_temp = (int*)realloc(temp, capacity * sizeof(int));
            if (new_temp == NULL) {
                printf("Ошибка: не удалось перевыделить память\n");
                free(temp);
                fclose(file);
                return NULL;
            }
            temp = new_temp;
        }
        temp[count++] = num;
    }
    
    *size = count;
    fclose(file);
    return temp;
}

// Функция вывода массива на экран
void print(const int* data, size_t size) {
    printf("Массив чисел: ");
    for (size_t i = 0; i < size; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");
}

// Функция записи чисел в файлы
void writeToFiles(const int* data, size_t size) {
    FILE* positiveFile = fopen("positive.txt", "w");
    FILE* negativeFile = fopen("negative.txt", "w");
    
    if (positiveFile == NULL) {
        printf("Ошибка: не удалось создать файл positive.txt\n");
        return;
    }
    if (negativeFile == NULL) {
        printf("Ошибка: не удалось создать файл negative.txt\n");
        fclose(positiveFile);
        return;
    }
    
    int firstPositive = 1;
    int firstNegative = 1;
    
    for (size_t i = 0; i < size; i++) {
        if (data[i] > 0) {
            if (!firstPositive) {
                fprintf(positiveFile, " ");
            }
            fprintf(positiveFile, "%d", data[i]);
            firstPositive = 0;
        } else if (data[i] < 0) {
            if (!firstNegative) {
                fprintf(negativeFile, " ");
            }
            fprintf(negativeFile, "%d", data[i]);
            firstNegative = 0;
        }
    }
    
    fclose(positiveFile);
    fclose(negativeFile);
    
    printf("Положительные числа записаны в positive.txt\n");
    printf("Отрицательные числа записаны в negative.txt\n");
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Использование: %s <имя_файла>\n", argv[0]);
        return 1;
    }
    
    const char* filename = argv[1];
    size_t size = 0;
    
    // Чтение данных из файла
    int* data = getData(filename, &size);
    
    if (data == NULL) {
        return 1;
    }
    
    // Вывод массива на экран
    print(data, size);
    
    // Запись в файлы
    writeToFiles(data, size);
    
    // Освобождение памяти
    free(data);
    
    return 0;
}
