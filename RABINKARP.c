#include <stdio.h>

#define d 256 // Number of characters in the input alphabet

// Function to perform the Rabin-Karp string matching algorithm
void rabinKarp(char* txt, char* pat, int q) {
    int M = 0;
    int N = 0;
    int i, j;
    int p = 0; // Hash value for pattern
    int t = 0; // Hash value for txt
    int h = 1;

    // Calculate lengths of the pattern and the text
    while (pat[M] != '\0') M++;
    while (txt[N] != '\0') N++;

    // Calculate h = pow(d, M-1) % q
    for (i = 0; i < M - 1; i++) {
        h = (h * d) % q;
    }

    // Calculate hash values for the pattern and the first window of text
    for (i = 0; i < M; i++) {
        p = (d * p + pat[i]) % q;
        t = (d * t + txt[i]) % q;
    }

    // Slide the pattern over the text one character at a time
    for (i = 0; i <= N - M; i++) {
        // Check if the hash values match
        if (p == t) {
            // Check the characters one by one if the hash values match
            for (j = 0; j < M; j++) {
                if (txt[i + j] != pat[j])
                    break;
            }

            if (j == M) {
                // Pattern found at index i
                printf("Pattern found at index %d\n", i);
            }
        }

        // Calculate hash value for the next window of text
        if (i < N - M) {
            t = (d * (t - txt[i] * h) + txt[i + M]) % q;

            // Make sure t is non-negative
            if (t < 0) {
                t = t + q;
            }
        }
    }
}

int main() {
    char txt[100], pat[100];
    int q = 101; // A prime number as the modulus

    // Input the text and the pattern
    printf("Enter the text: ");
    scanf("%s", txt);
    printf("Enter the pattern: ");
    scanf("%s", pat);

    // Perform Rabin-Karp string matching algorithm
    printf("Pattern matches found at the following indices:\n");
    rabinKarp(txt, pat, q);

    return 0;
}
