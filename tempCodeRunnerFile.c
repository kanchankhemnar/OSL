#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void sort_array(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] > arr[j]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void print_array(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    pid_t pid;
    int numbers[] = {9, 2, 5, 3, 1};
    int n = sizeof(numbers) / sizeof(numbers[0]);

    // Create a child process
    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid == 0) {
        // Child process
        printf("Child: Sorting the array...\n");
        sort_array(numbers, n);
        printf("Child: Sorted array: ");
        print_array(numbers, n);
        exit(0);  // Exit child process
    } else {
        // Parent process
        printf("Parent: Sorting the array...\n");
        sort_array(numbers, n);
        printf("Parent: Sorted array: ");
        print_array(numbers, n);
        
        // Parent exits before child finishes, causing child to become orphan
        exit(0);  // Parent exits here before child finishes
    }

    return 0;
}
