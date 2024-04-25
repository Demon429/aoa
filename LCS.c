#include <stdio.h>
#include <string.h>

// Function to calculate the longest common subsequence using dynamic programming
void lcs(char* str1, char* str2, int len1, int len2, char* lcs) {
    int dp[len1 + 1][len2 + 1];

    // Initialize the dp array
    for (int i = 0; i <= len1; i++) {
        for (int j = 0; j <= len2; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            } else if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = (dp[i - 1][j] > dp[i][j - 1])? dp[i - 1][j] : dp[i][j - 1];
            }
        }
    }

    // Construct the LCS by backtracking
    int i = len1, j = len2;
    while (i > 0 && j > 0) {
        if (str1[i - 1] == str2[j - 1]) {
            lcs[dp[len1][len2] - 1] = str1[i - 1];
            i--;
            j--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    // Print the LCS
    printf("Longest Common Subsequence (LCS): ");
    for (int k = 0; k < dp[len1][len2]; k++) {
        printf("%c", lcs[k]);
    }
    printf("\n");
}

int main() {
    char str1[100], str2[100];
    char lcs[100];

    // Input the first and second strings
    printf("Enter the first string: ");
    scanf("%s", str1);
    printf("Enter the second string: ");
    scanf("%s", str2);

    int len1 = strlen(str1);
    int len2 = strlen(str2);

    // Calculate and print the length of the LCS
    lcs(str1, str2, len1, len2, lcs);

    return 0;
}