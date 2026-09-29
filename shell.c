#include <stdio.h>
#include <string.h>

#define MAX 100

/* ---------- FIFO ---------- */
void fifo(int pages[], int n, int frames) {
    int memory[MAX];
    int count = 0, pointer = 0;
    int pageFaults = 0, pageHits = 0;

    for (int i = 0; i < frames; i++)
        memory[i] = -1;

    printf("\n--- FIFO Page Replacement ---\n");

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;

        // Check whether page is already present
        for (int j = 0; j < frames; j++) {
            if (memory[j] == page) {
                found = 1;
                break;
            }
        }

        if (found) {
            pageHits++;
            printf("Page %d -> Hit\t\t", page);
        } else {
            pageFaults++;

            memory[pointer] = page;
            pointer = (pointer + 1) % frames;

            printf("Page %d -> Fault\t", page);
        }

        for (int j = 0; j < frames; j++) {
            if (memory[j] == -1)
                printf("- ");
            else
                printf("%d ", memory[j]);
        }

        printf("\n");
    }

    printf("\nPage Faults = %d\n", pageFaults);
    printf("Page Hits   = %d\n", pageHits);
}


/* ---------- LRU ---------- */
void lru(int pages[], int n, int frames) {
    int memory[MAX];
    int lastUsed[MAX];

    int pageFaults = 0, pageHits = 0;

    for (int i = 0; i < frames; i++) {
        memory[i] = -1;
        lastUsed[i] = -1;
    }

    printf("\n--- LRU Page Replacement ---\n");

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = -1;

        // Search for page
        for (int j = 0; j < frames; j++) {
            if (memory[j] == page) {
                found = j;
                break;
            }
        }

        if (found != -1) {
            // Page hit
            pageHits++;
            lastUsed[found] = i;

            printf("Page %d -> Hit\t\t", page);
        } else {
            // Page fault
            pageFaults++;

            int position = -1;

            // Find empty frame
            for (int j = 0; j < frames; j++) {
                if (memory[j] == -1) {
                    position = j;
                    break;
                }
            }

            // If no empty frame, find least recently used
            if (position == -1) {
                position = 0;

                for (int j = 1; j < frames; j++) {
                    if (lastUsed[j] < lastUsed[position])
                        position = j;
                }
            }

            memory[position] = page;
            lastUsed[position] = i;

            printf("Page %d -> Fault\t", page);
        }

        for (int j = 0; j < frames; j++) {
            if (memory[j] == -1)
                printf("- ");
            else
                printf("%d ", memory[j]);
        }

        printf("\n");
    }

    printf("\nPage Faults = %d\n", pageFaults);
    printf("Page Hits   = %d\n", pageHits);
}


/* ---------- LFU ---------- */
void lfu(int pages[], int n, int frames) {
    int memory[MAX];
    int frequency[MAX];
    int lastUsed[MAX];

    int pageFaults = 0, pageHits = 0;

    for (int i = 0; i < frames; i++) {
        memory[i] = -1;
        frequency[i] = 0;
        lastUsed[i] = -1;
    }

    printf("\n--- LFU Page Replacement ---\n");

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = -1;

        // Search for page
        for (int j = 0; j < frames; j++) {
            if (memory[j] == page) {
                found = j;
                break;
            }
        }

        if (found != -1) {
            // Page hit
            pageHits++;
            frequency[found]++;
            lastUsed[found] = i;

            printf("Page %d -> Hit\t\t", page);
        } else {
            // Page fault
            pageFaults++;

            int position = -1;

            // Find empty frame
            for (int j = 0; j < frames; j++) {
                if (memory[j] == -1) {
                    position = j;
                    break;
                }
            }

            // If no empty frame, find LFU page
            if (position == -1) {
                position = 0;

                for (int j = 1; j < frames; j++) {

                    // Lower frequency = replace
                    // If same frequency, replace least recently used
                    if (frequency[j] < frequency[position]) {
                        position = j;
                    }
                    else if (frequency[j] == frequency[position] &&
                             lastUsed[j] < lastUsed[position]) {
                        position = j;
                    }
                }
            }

            memory[position] = page;
            frequency[position] = 1;
            lastUsed[position] = i;

            printf("Page %d -> Fault\t", page);
        }

        for (int j = 0; j < frames; j++) {
            if (memory[j] == -1)
                printf("- ");
            else
                printf("%d ", memory[j]);
        }

        printf("\n");
    }

    printf("\nPage Faults = %d\n", pageFaults);
    printf("Page Hits   = %d\n", pageHits);
}


/* ---------- MAIN ---------- */
int main() {
    int pages[MAX];
    int n, frames;
    char algorithm[10];

    printf("=====================================\n");
    printf("   PAGE REPLACEMENT ALGORITHMS\n");
    printf("=====================================\n");

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter the page reference string:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    printf("\nEnter algorithm (FIFO / LRU / LFU): ");
    scanf("%s", algorithm);

    if (strcmp(algorithm, "FIFO") == 0 ||
        strcmp(algorithm, "fifo") == 0) {

        fifo(pages, n, frames);

    }
    else if (strcmp(algorithm, "LRU") == 0 ||
             strcmp(algorithm, "lru") == 0) {

        lru(pages, n, frames);

    }
    else if (strcmp(algorithm, "LFU") == 0 ||
             strcmp(algorithm, "lfu") == 0) {

        lfu(pages, n, frames);

    }
    else {
        printf("\nInvalid algorithm!\n");
        printf("Please enter FIFO, LRU, or LFU.\n");
    }

    return 0;
}
