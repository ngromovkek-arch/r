#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Функция создания динамической матрицы
int** create_matrix(int rows, int cols) {
    int** matrix = (int**)malloc(rows * sizeof(int*));
    if (matrix == NULL) return NULL;
    
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
        if (matrix[i] == NULL) {
            for (int j = 0; j < i; j++) free(matrix[j]);
            free(matrix);
            return NULL;
        }
    }
    return matrix;
}

// Функция освобождения памяти матрицы
void free_matrix(int** matrix, int rows) {
    if (matrix == NULL) return;
    for (int i = 0; i < rows; i++) free(matrix[i]);
    free(matrix);
}

// Функция заполнения матрицы случайными числами [-9, 9]
void fill_matrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() % 19 - 9; // от -9 до 9
        }
    }
}

// Функция вывода матрицы на экран
void print_matrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%3d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Функция записи матрицы в файл
void write_matrix_to_file(FILE* file, int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fprintf(file, "%3d ", matrix[i][j]);
        }
        fprintf(file, "\n");
    }
}

// Функция сложения матриц
int** add_matrices(int** A, int** B, int rows, int cols) {
    int** result = create_matrix(rows, cols);
    if (result == NULL) return NULL;
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = A[i][j] + B[i][j];
        }
    }
    return result;
}

// Функция вычитания матриц
int** subtract_matrices(int** A, int** B, int rows, int cols) {
    int** result = create_matrix(rows, cols);
    if (result == NULL) return NULL;
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = A[i][j] - B[i][j];
        }
    }
    return result;
}

int main(int argc, char* argv[]) {
    // Проверка количества аргументов
    if (argc != 5) {
        printf("Использование: %s n m a b\n", argv[0]);
        printf("n, m - размеры матрицы A\n");
        printf("a, b - размеры матрицы B\n");
        return 1;
    }
    
    // Парсинг аргументов командной строки
    int n = atoi(argv[1]);
    int m = atoi(argv[2]);
    int a = atoi(argv[3]);
    int b = atoi(argv[4]);
    
    // Проверка корректности размеров
    if (n <= 0 || m <= 0 || a <= 0 || b <= 0) {
        printf("Ошибка: размеры матриц должны быть натуральными числами\n");
        return 1;
    }
    
    // Инициализация генератора случайных чисел
    srand(time(NULL));
    
    // Создание матриц
    int** A = create_matrix(n, m);
    int** B = create_matrix(a, b);
    
    if (A == NULL || B == NULL) {
        printf("Ошибка выделения памяти\n");
        if (A) free_matrix(A, n);
        if (B) free_matrix(B, a);
        return 1;
    }
    
    // Заполнение матриц
    fill_matrix(A, n, m);
    fill_matrix(B, a, b);
    
    // Вывод матриц на экран
    printf("Матрица A (%dx%d):\n", n, m);
    print_matrix(A, n, m);
    printf("\nМатрица B (%dx%d):\n", a, b);
    print_matrix(B, a, b);
    printf("\n");
    
    // Открытие файла для результата сложения
    FILE* add_file = fopen("add.txt", "w");
    if (add_file == NULL) {
        printf("Ошибка создания файла add.txt\n");
        free_matrix(A, n);
        free_matrix(B, a);
        return 1;
    }
    
    // Сложение матриц
    fprintf(add_file, "add\n");
    if (n == a && m == b) {
        int** sum = add_matrices(A, B, n, m);
        if (sum != NULL) {
            write_matrix_to_file(add_file, sum, n, m);
            free_matrix(sum, n);
        } else {
            fprintf(add_file, "Операция невозможна\n");
        }
    } else {
        fprintf(add_file, "Операция невозможна\n");
    }
    fclose(add_file);
    
    // Открытие файла для результата вычитания
    FILE* sub_file = fopen("sub.txt", "w");
    if (sub_file == NULL) {
        printf("Ошибка создания файла sub.txt\n");
        free_matrix(A, n);
        free_matrix(B, a);
        return 1;
    }
    
    // Вычитание матриц
    fprintf(sub_file, "sub\n");
    if (n == a && m == b) {
        int** diff = subtract_matrices(A, B, n, m);
        if (diff != NULL) {
            write_matrix_to_file(sub_file, diff, n, m);
            free_matrix(diff, n);
        } else {
            fprintf(sub_file, "Операция невозможна\n");
        }
    } else {
        fprintf(sub_file, "Операция невозможна\n");
    }
    fclose(sub_file);
    
    // Освобождение памяти
    free_matrix(A, n);
    free_matrix(B, a);
    
    printf("Результаты записаны в файлы add.txt и sub.txt\n");
    
    return 0;
}
