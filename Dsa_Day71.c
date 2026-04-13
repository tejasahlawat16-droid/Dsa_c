/* Problem Statement
Implement a hash table using quadratic probing with formula:

h(k, i) = (h(k) + i*i) % m

Input Format
Same as previous.

Output Format
Result of SEARCH operations.

Sample Input
7
4
INSERT 49
INSERT 56
SEARCH 49
SEARCH 15

Sample Output
FOUND
NOT FOUND

Explanation
Collisions resolved using i² jumps.
*/
#include <stdio.h>

#define EMPTY -1

int hash(int key, int m) {
    return key % m;
}

// Insert using Quadratic Probing
void insert(int table[], int m, int key) {
    int h = hash(key, m);

    for (int i = 0; i < m; i++) {
        int idx = (h + i * i) % m;
        if (table[idx] == EMPTY) {
            table[idx] = key;
            return;
        }
    }
}

// Search using Quadratic Probing
int search(int table[], int m, int key) {
    int h = hash(key, m);

    for (int i = 0; i < m; i++) {
        int idx = (h + i * i) % m;

        if (table[idx] == EMPTY)
            return 0;   // NOT FOUND

        if (table[idx] == key)
            return 1;   // FOUND
    }
    return 0;
}

int main() {
    int m, q;

    // Table size
    scanf("%d", &m);

    int table[m];
    for (int i = 0; i < m; i++)
        table[i] = EMPTY;

    // Number of operations
    scanf("%d", &q);

    char op[10];
    int key;

    for (int i = 0; i < q; i++) {
        scanf("%s %d", op, &key);

        if (op[0] == 'I') {
            insert(table, m, key);
        } 
        else if (op[0] == 'S') {
            if (search(table, m, key))
                printf("FOUND\n");
            else
                printf("NOT FOUND\n");
        }
    }

    return 0;
}