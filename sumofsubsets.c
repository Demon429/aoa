#include <stdio.h>

#define MAX 20

int n;
int set[MAX];
int solution[MAX];

// Function to print the subset that sums up to the target
void printSubset(int index) {
    printf("Subset: ");
    for (int i = 0; i < index; i++) {
        printf("%d ", set[solution[i]]);
    }
    printf("\n");
}

// Recursive function to find subsets with sum equal to target
void sumOfSubset(int sum, int index, int target) {
    // Base case: if the current sum is equal to the target, print the subset
    if (sum == target) {
        printSubset(index);
        return;
    }

    // If the sum exceeds the target or we have processed all elements, return
    if (sum > target || index == n) {
        return;
    }

    // Include the current element in the subset and recurse
    solution[index] = index;
    sumOfSubset(sum + set[index], index + 1, target);

    // Exclude the current element from the subset and recurse
    sumOfSubset(sum, index + 1, target);
}

int main() {
    int target;

    // Input the number of elements in the set
    printf("Enter the number of elements in the set: ");
    scanf("%d", &n);

    // Input the elements of the set
    printf("Enter the elements of the set:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &set[i]);
    }

    // Input the target sum
    printf("Enter the target sum: ");
    scanf("%d", &target);

    // Find subsets with sum equal to target using backtracking
    printf("Subsets with sum equal to %d:\n", target);
    sumOfSubset(0, 0, target);

    return 0;
}
