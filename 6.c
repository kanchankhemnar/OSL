#include <stdio.h>

#define MAX_FRAMES 10
#define MAX_PAGES 20

// Function for FCFS page replacement algorithm
void fcfs(int pages[], int n, int frames, int page_reference[]) {
    int frame[MAX_FRAMES] = {-1}; // Initialize all frames to -1 (empty)
    int page_faults = 0;
    
    printf("\nFCFS Page Replacement Algorithm:\n");
    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;
        
        // Check if the page is already in any frame
        for (int j = 0; j < frames; j++) {
            if (frame[j] == page) {
                found = 1;
                break;
            }
        }
        
        if (!found) { // Page fault
            frame[page_faults % frames] = page;  // Replace page using FCFS
            page_faults++;
        }
        
        // Print the current frame status
        printf("Step %d: ", i + 1);
        for (int j = 0; j < frames; j++) {
            if (frame[j] != -1)
                printf("%d ", frame[j]);
            else
                printf("- ");
        }
        printf("\n");
    }
    printf("Total page faults: %d\n", page_faults);
}

// Function for LRU page replacement algorithm
void lru(int pages[], int n, int frames, int page_reference[]) {
    int frame[MAX_FRAMES] = {-1}; // Initialize all frames to -1 (empty)
    int page_faults = 0;
    
    printf("\nLRU Page Replacement Algorithm:\n");
    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;
        
        // Check if the page is already in any frame
        for (int j = 0; j < frames; j++) {
            if (frame[j] == page) {
                found = 1;
                break;
            }
        }
        
        if (!found) { // Page fault
            int lru_index = 0;
            for (int j = 1; j < frames; j++) {
                // Find the least recently used page
                if (frame[j] != -1) {
                    int recent_usage = -1;
                    for (int k = i - 1; k >= 0; k--) {
                        if (pages[k] == frame[j]) {
                            recent_usage = k;
                            break;
                        }
                    }
                    if (recent_usage == -1 || recent_usage < lru_index)
                        lru_index = j;
                }
            }
            frame[lru_index] = page; // Replace LRU page
            page_faults++;
        }
        
        // Print the current frame status
        printf("Step %d: ", i + 1);
        for (int j = 0; j < frames; j++) {
            if (frame[j] != -1)
                printf("%d ", frame[j]);
            else
                printf("- ");
        }
        printf("\n");
    }
    printf("Total page faults: %d\n", page_faults);
}

// Function for Optimal page replacement algorithm
void optimal(int pages[], int n, int frames, int page_reference[]) {
    int frame[MAX_FRAMES] = {-1}; // Initialize all frames to -1 (empty)
    int page_faults = 0;
    
    printf("\nOptimal Page Replacement Algorithm:\n");
    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;
        
        // Check if the page is already in any frame
        for (int j = 0; j < frames; j++) {
            if (frame[j] == page) {
                found = 1;
                break;
            }
        }
        
        if (!found) { // Page fault
            int farthest_index = -1, farthest_page = -1;
            
            // Find the page that is used farthest in the future
            for (int j = 0; j < frames; j++) {
                int future_usage = -1;
                for (int k = i + 1; k < n; k++) {
                    if (pages[k] == frame[j]) {
                        future_usage = k;
                        break;
                    }
                }
                if (future_usage == -1) {
                    farthest_index = j;
                    break;
                } else if (future_usage > farthest_page) {
                    farthest_page = future_usage;
                    farthest_index = j;
                }
            }
            frame[farthest_index] = page; // Replace farthest page
            page_faults++;
        }
        
        // Print the current frame status
        printf("Step %d: ", i + 1);
        for (int j = 0; j < frames; j++) {
            if (frame[j] != -1)
                printf("%d ", frame[j]);
            else
                printf("- ");
        }
        printf("\n");
    }
    printf("Total page faults: %d\n", page_faults);
}

int main() {
    int pages[MAX_PAGES], n, frames;
    
    // Accepting number of pages and frame size
    printf("Enter the number of pages: ");
    scanf("%d", &n);
    
    printf("Enter the page reference string: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }
    
    printf("Enter the number of frames (minimum 3): ");
    scanf("%d", &frames);
    
    if (frames < 3) {
        printf("Frame size must be at least 3!\n");
        return 1;
    }
    
    // Call the page replacement algorithms
    fcfs(pages, n, frames, pages);
    lru(pages, n, frames, pages);
    optimal(pages, n, frames, pages);
    
    return 0;
}
