/*
 * Sorting Algorithm Visualizer
 * A complete console-based application for visualizing sorting algorithms
 * using ASCII vertical bars with ANSI color coding
 * 
 * Author: Sorting Visualizer
 * Date: October 29, 2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
    #include <windows.h>
    #define CLEAR_SCREEN "cls"
    #define SLEEP_MS(x) Sleep(x)
#else
    #include <unistd.h>
    #define CLEAR_SCREEN "clear"
    #define SLEEP_MS(x) usleep((x) * 1000)
#endif

// ANSI Color Codes
#define RESET "\033[0m"
#define WHITE "\033[37m"
#define RED "\033[31m"
#define BLUE "\033[34m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define CYAN "\033[36m"
#define BOLD "\033[1m"

// Constants
#define MAX_SIZE 50
#define MIN_VALUE 1
#define MAX_VALUE 50
#define DELAY_MS 100  // Delay in milliseconds for smooth animation

// Windows ANSI support
#ifdef _WIN32
    #ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
        #define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
    #endif
#endif

// Global variables for visualization
int arr[MAX_SIZE];
int n;
unsigned long long comparisons = 0;
unsigned long long swaps = 0;

// Function Prototypes
void clearScreen();
void displayArray(int highlight1, int highlight2, char* color1, char* color2);
void generateRandomArray(int size);
void printTimeComplexity(char* algorithm);
void resetCounters();

// Sorting Algorithm Prototypes
void bubbleSort();
void selectionSort();
void insertionSort();
void mergeSort(int left, int right);
void quickSort(int low, int high);

// Helper functions for Merge Sort and Quick Sort
void merge(int left, int mid, int right);
int partition(int low, int high);

/*
 * clearScreen - Clears the console screen using ANSI escape codes
 */
void clearScreen() {
    // Use ANSI escape codes for instant clearing
    // \033[H moves cursor to home position (0,0)
    // \033[J clears from cursor to end of screen
    printf("\033[H\033[J");
    fflush(stdout);
}

/*
 * displayArray - Displays the array as ASCII vertical bars with colors
 * @highlight1: First index to highlight (or -1 for none)
 * @highlight2: Second index to highlight (or -1 for none)
 * @color1: Color for first highlighted element
 * @color2: Color for second highlighted element
 */
void displayArray(int highlight1, int highlight2, char* color1, char* color2) {
    clearScreen();
    
    printf(BOLD CYAN "\n╔════════════════════════════════════════════════════════════╗\n");
    printf("║          SORTING ALGORITHM VISUALIZER                    ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n" RESET);
    
    printf("\nComparisons: %llu | Swaps/Shifts: %llu\n\n", comparisons, swaps);
    
    // Find max value for scaling
    int maxVal = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] > maxVal) maxVal = arr[i];
    }
    
    // Display bars from top to bottom (draw complete vertical bars)
    for (int level = maxVal; level > 0; level--) {
        for (int i = 0; i < n; i++) {
            if (arr[i] >= level) {
                // Determine color for this bar segment
                if (i == highlight1 && color1 != NULL) {
                    // CHANGE THIS LINE - Replace █ with ##
                    printf("%s##" RESET, color1);
                } else if (i == highlight2 && color2 != NULL) {
                    // CHANGE THIS LINE - Replace █ with ##
                    printf("%s##" RESET, color2);
                } else {
                    // CHANGE THIS LINE - Replace █ with ##
                    printf(WHITE "##" RESET);
                }
            } else {
                printf("  "); // Changed from single space to double space
            }
            printf(" "); // Add space between bars for clarity
        }
        printf("\n");
    }
    
    // Display values at the bottom
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("%2d ", arr[i]);
    }
    printf("\n");
    fflush(stdout); // Ensure output is displayed immediately
}

/*
 * generateRandomArray - Generates random array values
 * @size: Number of elements to generate
 */
void generateRandomArray(int size) {
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        arr[i] = (rand() % MAX_VALUE) + MIN_VALUE;
    }
}

/*
 * resetCounters - Resets comparison and swap counters
 */
void resetCounters() {
    comparisons = 0;
    swaps = 0;
}

/*
 * printTimeComplexity - Displays time complexity for the algorithm
 * @algorithm: Name of the sorting algorithm
 */
void printTimeComplexity(char* algorithm) {
    printf(BOLD YELLOW "\n╔════════════════════════════════════════════════════════════╗\n" RESET);
    printf(BOLD YELLOW "║  Time Complexity Analysis for %s\n" RESET, algorithm);
    printf(BOLD YELLOW "╚════════════════════════════════════════════════════════════╝\n" RESET);
    
    if (strcmp(algorithm, "Bubble Sort") == 0) {
        printf(GREEN "Best Case:    " RESET "O(n)   - When array is already sorted\n");
        printf(YELLOW "Average Case: " RESET "O(n²)  - Random arrangement\n");
        printf(RED "Worst Case:   " RESET "O(n²)  - When array is reverse sorted\n");
    } else if (strcmp(algorithm, "Selection Sort") == 0) {
        printf(GREEN "Best Case:    " RESET "O(n²)  - Always performs same comparisons\n");
        printf(YELLOW "Average Case: " RESET "O(n²)  - Random arrangement\n");
        printf(RED "Worst Case:   " RESET "O(n²)  - Always performs same comparisons\n");
    } else if (strcmp(algorithm, "Insertion Sort") == 0) {
        printf(GREEN "Best Case:    " RESET "O(n)   - When array is already sorted\n");
        printf(YELLOW "Average Case: " RESET "O(n²)  - Random arrangement\n");
        printf(RED "Worst Case:   " RESET "O(n²)  - When array is reverse sorted\n");
    } else if (strcmp(algorithm, "Merge Sort") == 0) {
        printf(GREEN "Best Case:    " RESET "O(n log n) - Consistent performance\n");
        printf(YELLOW "Average Case: " RESET "O(n log n) - Consistent performance\n");
        printf(RED "Worst Case:   " RESET "O(n log n) - Consistent performance\n");
    } else if (strcmp(algorithm, "Quick Sort") == 0) {
        printf(GREEN "Best Case:    " RESET "O(n log n) - Good pivot selection\n");
        printf(YELLOW "Average Case: " RESET "O(n log n) - Random pivot\n");
        printf(RED "Worst Case:   " RESET "O(n²)      - Poor pivot selection\n");
    }
    
    printf("\nTotal Comparisons: %llu\n", comparisons);
    printf("Total Swaps/Shifts: %llu\n", swaps);
}

/*
 * bubbleSort - Implements Bubble Sort with visualization
 * Repeatedly swaps adjacent elements if they are in wrong order
 */
void bubbleSort() {
    resetCounters();
    
    for (int i = 0; i < n - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < n - i - 1; j++) {
            comparisons++;
            displayArray(j, j + 1, RED, RED);
            SLEEP_MS(DELAY_MS);
            
            if (arr[j] > arr[j + 1]) {
                // Swap elements
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swaps++;
                swapped = 1;
                
                displayArray(j, j + 1, BLUE, BLUE);
                SLEEP_MS(DELAY_MS);
            }
        }
        if (!swapped) break; // Optimization: exit if no swaps occurred
    }
    
    // Display final sorted array
    displayArray(-1, -1, GREEN, GREEN);
    printTimeComplexity("Bubble Sort");
}

/*
 * selectionSort - Implements Selection Sort with visualization
 * Finds minimum element and places it at the beginning
 */
void selectionSort() {
    resetCounters();
    
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        
        for (int j = i + 1; j < n; j++) {
            comparisons++;
            displayArray(minIdx, j, RED, YELLOW);
            SLEEP_MS(DELAY_MS);
            
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        
        if (minIdx != i) {
            // Swap minimum element with first element
            int temp = arr[i];
            arr[i] = arr[minIdx];
            arr[minIdx] = temp;
            swaps++;
            
            displayArray(i, minIdx, BLUE, BLUE);
            SLEEP_MS(DELAY_MS);
        }
    }
    
    // Display final sorted array
    displayArray(-1, -1, GREEN, GREEN);
    printTimeComplexity("Selection Sort");
}

/*
 * insertionSort - Implements Insertion Sort with visualization
 * Builds sorted array one element at a time
 */
void insertionSort() {
    resetCounters();
    
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        
        displayArray(i, -1, RED, NULL);
        SLEEP_MS(DELAY_MS);
        
        while (j >= 0 && arr[j] > key) {
            comparisons++;
            arr[j + 1] = arr[j];
            swaps++;
            
            displayArray(j, j + 1, BLUE, BLUE);
            SLEEP_MS(DELAY_MS);
            
            j--;
        }
        if (j >= 0) comparisons++;
        
        arr[j + 1] = key;
    }
    
    // Display final sorted array
    displayArray(-1, -1, GREEN, GREEN);
    printTimeComplexity("Insertion Sort");
}

/*
 * merge - Helper function for Merge Sort
 * Merges two sorted subarrays
 */
void merge(int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    int L[n1], R[n2];
    
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    
    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) {
        comparisons++;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        swaps++;
        displayArray(k, -1, BLUE, NULL);
        SLEEP_MS(DELAY_MS);
        k++;
    }
    
    while (i < n1) {
        arr[k] = L[i];
        swaps++;
        displayArray(k, -1, BLUE, NULL);
        SLEEP_MS(DELAY_MS);
        i++;
        k++;
    }
    
    while (j < n2) {
        arr[k] = R[j];
        swaps++;
        displayArray(k, -1, BLUE, NULL);
        SLEEP_MS(DELAY_MS);
        j++;
        k++;
    }
}

/*
 * mergeSort - Implements Merge Sort with visualization
 * Divides array into halves, sorts them and merges
 */
void mergeSort(int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        mergeSort(left, mid);
        mergeSort(mid + 1, right);
        merge(left, mid, right);
    }
}

/*
 * partition - Helper function for Quick Sort
 * Places pivot element at correct position
 */
int partition(int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        comparisons++;
        displayArray(j, high, RED, YELLOW);
        SLEEP_MS(DELAY_MS);
        
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            swaps++;
            
            displayArray(i, j, BLUE, BLUE);
            SLEEP_MS(DELAY_MS);
        }
    }
    
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    swaps++;
    
    displayArray(i + 1, high, BLUE, BLUE);
    SLEEP_MS(DELAY_MS);
    
    return i + 1;
}

/*
 * quickSort - Implements Quick Sort with visualization
 * Selects pivot and partitions array around it
 */
void quickSort(int low, int high) {
    if (low < high) {
        int pi = partition(low, high);
        
        quickSort(low, pi - 1);
        quickSort(pi + 1, high);
    }
}

/*
 * main - Entry point of the program
 */
int main() {
    int choice;
    
    // Enable ANSI colors on Windows
    #ifdef _WIN32
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD dwMode = 0;
        GetConsoleMode(hOut, &dwMode);
        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hOut, dwMode);
    #endif
    
    clearScreen();
    
    printf(BOLD CYAN "\n");
    printf("╔════════════════════════════════════════════════════════════╗\n");
    printf("║                                                            ║\n");
    printf("║          SORTING ALGORITHM VISUALIZER                     ║\n");
    printf("║          ASCII-Based Console Application                  ║\n");
    printf("║                                                            ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n");
    printf(RESET "\n");
    
    // Get array size from user
    do {
        printf("Enter the number of elements (1-%d): ", MAX_SIZE);
        scanf("%d", &n);
        if (n < 1 || n > MAX_SIZE) {
            printf(RED "Invalid input! Please enter a number between 1 and %d.\n" RESET, MAX_SIZE);
        }
    } while (n < 1 || n > MAX_SIZE);
    
    // Generate random array
    generateRandomArray(n);
    
    printf(GREEN "\n✓ Random array of %d elements generated!\n" RESET, n);
    SLEEP_MS(1000);
    
    // Display menu
    while (1) {
        clearScreen();
        
        printf(BOLD CYAN "\n╔════════════════════════════════════════════════════════════╗\n");
        printf("║          SELECT SORTING ALGORITHM                        ║\n");
        printf("╚════════════════════════════════════════════════════════════╝\n" RESET);
        
        printf(WHITE "\n  Current Array (%d elements):\n  ", n);
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n\n" RESET);
        
        printf(YELLOW "  1. " RESET "Bubble Sort\n");
        printf(YELLOW "  2. " RESET "Selection Sort\n");
        printf(YELLOW "  3. " RESET "Insertion Sort\n");
        printf(YELLOW "  4. " RESET "Merge Sort\n");
        printf(YELLOW "  5. " RESET "Quick Sort\n");
        printf(YELLOW "  6. " RESET "Generate New Random Array\n");
        printf(YELLOW "  0. " RESET "Exit\n");
        
        printf("\n  Enter your choice: ");
        scanf("%d", &choice);
        
        if (choice == 0) {
            printf(BOLD GREEN "\n\n  Thank you for using Sorting Algorithm Visualizer!\n" RESET);
            printf(CYAN "  Goodbye!\n\n" RESET);
            break;
        }
        
        if (choice == 6) {
            generateRandomArray(n);
            printf(GREEN "\n✓ New random array generated!\n" RESET);
            SLEEP_MS(1000);
            continue;
        }
        
        printf(BOLD "\n  Starting visualization...\n" RESET);
        SLEEP_MS(1500);
        
        switch (choice) {
            case 1:
                bubbleSort();
                break;
            case 2:
                selectionSort();
                break;
            case 3:
                insertionSort();
                break;
            case 4:
                resetCounters();
                mergeSort(0, n - 1);
                displayArray(-1, -1, GREEN, GREEN);
                printTimeComplexity("Merge Sort");
                break;
            case 5:
                resetCounters();
                quickSort(0, n - 1);
                displayArray(-1, -1, GREEN, GREEN);
                printTimeComplexity("Quick Sort");
                break;
            default:
                printf(RED "\n  Invalid choice! Please try again.\n" RESET);
                SLEEP_MS(1500);
                continue;
        }
        
        printf(BOLD GREEN "\n✓ Sorting complete!\n" RESET);
        printf("\nPress Enter to continue...");
        getchar(); // Clear buffer
        getchar(); // Wait for Enter
        
        // Generate new random array for next iteration
        generateRandomArray(n);
    }
    
    return 0;
}
