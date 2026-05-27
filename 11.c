#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Функция 1: нахождение максимального из набора чисел
int find_max(const int *arr, int size) {
    if (size == 0) return INT_MIN;
    int max_val = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }
    return max_val;
}

// Функция 2: определить, сколько четных чисел содержится в файле
int count_even(const int *arr, int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] % 2 == 0) {
            count++;
        }
    }
    return count;
}

// Функция 3: определить, образуют ли эти числа возрастающую последовательность
int is_increasing(const int *arr, int size) {
    if (size <= 1) return 1; // пустая или из одного числа последовательность считается возрастающей
    for (int i = 1; i < size; i++) {
        if (arr[i] <= arr[i - 1]) {
            return 0;
        }
    }
    return 1;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    const char *input_filename = argv[1];
    const char *output_filename = "out.txt";

    FILE *input_file = fopen(input_filename, "r");
    if (!input_file) {
        fprintf(stderr, "Error: Cannot open file %s\n", input_filename);
        return 1;
    }

    // Динамическое выделение памяти для массива чисел
    int capacity = 10;
    int size = 0;
    int *numbers = (int*)malloc(capacity * sizeof(int));
    if (!numbers) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        fclose(input_file);
        return 1;
    }

    // Чтение чисел из файла
    int value;
    while (fscanf(input_file, "%d", &value) == 1) {
        if (size >= capacity) {
            capacity *= 2;
            int *temp = (int*)realloc(numbers, capacity * sizeof(int));
            if (!temp) {
                fprintf(stderr, "Error: Memory reallocation failed\n");
                free(numbers);
                fclose(input_file);
                return 1;
            }
            numbers = temp;
        }
        numbers[size++] = value;
    }

    fclose(input_file);

    if (size == 0) {
        fprintf(stderr, "Error: No numbers found in the file\n");
        free(numbers);
        return 1;
    }

    // Вычисление результатов
    int max_value = find_max(numbers, size);
    int even_count = count_even(numbers, size);
    int increasing = is_increasing(numbers, size);

    // Запись результатов в out.txt
    FILE *output_file = fopen(output_filename, "w");
    if (!output_file) {
        fprintf(stderr, "Error: Cannot create output file %s\n", output_filename);
        free(numbers);
        return 1;
    }

    fprintf(output_file, "Maximum number: %d\n", max_value);
    fprintf(output_file, "Count of even numbers: %d\n", even_count);
    fprintf(output_file, "Is increasing sequence: %s\n", increasing ? "yes" : "no");

    fclose(output_file);
    free(numbers);

    printf("Results successfully written to %s\n", output_filename);
    return 0;
}
