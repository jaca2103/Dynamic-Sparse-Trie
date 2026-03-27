#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define DEFAULT_KEY_VALUE -1

typedef struct Trie {
    int key;
    struct Trie **children;
} Trie;

Trie *createTrie() {
    Trie *trie = (Trie *)malloc(sizeof(Trie));
    trie->key = DEFAULT_KEY_VALUE;
    trie->children = NULL;
    return trie;
}

void allocateChildren(Trie *trie, int size) {
    if (!trie->children) {
        trie->children = (Trie **)calloc(size, sizeof(Trie *));
    }
}

int divCalculate(int key, int n, int k, int *x, bool isRoot) {
    if (isRoot) {
        return key % n;
    }
    int div = *x % k;
    *x = *x / k;
    return div;
}

//DODAWANIE
void insertTrie(Trie *trie, int key, int n, int k) {
    Trie *current = trie;
    bool isRoot = true;
    int x = key / n;

    while (1) {
        if (current->key == key) {
            printf("%d exist\n", key);
            return;
        }

        if (current->key == DEFAULT_KEY_VALUE) {
            current->key = key;
            return;
        }

        int div = divCalculate(key, n, k, &x, isRoot);
        if (isRoot) {
            allocateChildren(current, n);
            isRoot = false;
        } else {
            allocateChildren(current, k);
        }

        if (!current->children[div] || current->children[div]->key == DEFAULT_KEY_VALUE) {
            current->children[div] = createTrie();
            current->children[div]->key = key;
            return;
        }
        current = current->children[div];
    }
}

//WYPISYWANIE
void printTrie(Trie* trie, int n, int k, bool isRoot) {
    if (trie->key != DEFAULT_KEY_VALUE) {
        printf("%d ", trie->key);
    }

    if (!trie->children) {
        return;
    }

    int y = isRoot ? n : k;
    for (int i = 0; i < y; i++) {
        if (trie->children[i]) {
            printTrie(trie->children[i], n, k, false);
        }
    }
}

//SPRAWDZANIE
void lookTrie(Trie* trie, int key, int n, int k, int x, bool isRoot) {
    if (!trie) {
        printf("%d not exist\n", key);
        return;
    }

    if (trie->key == key) {
        printf("%d exist\n", key);
        return;
    }

    if (!trie->children) {
        printf("%d not exist\n", key);
        return;
    }

    int div = divCalculate(key, n, k, &x, isRoot);

    if (trie->children[div]) {
        lookTrie(trie->children[div], key, n, k, x, false);
    } else {
        printf("%d not exist\n", key);
    }
}

//USUWANIE
bool hasLeaf(Trie* trie, int k) {
    if (!trie->children) {
        return false;
    }

    for (int i = 0; i < k; i++) {
        if (trie->children[i] && trie->children[i]->key != DEFAULT_KEY_VALUE) {
            return true;
        }
    }
    return false;
}

Trie *findLeftLeaf(Trie* trie, int k) {
    if (!trie || !trie->children) {
        return trie;
    }

    for (int i = 0; i < k; i++) {
        if (trie->children[i] && trie->children[i]->key != DEFAULT_KEY_VALUE) {
            return findLeftLeaf(trie->children[i], k);
        }
    }
    return trie;
}

void deleteTrie(Trie* trie, int key, int n, int k) {
    Trie *current = trie;
    bool isRoot = true;
    int x = key / n;

    while (trie != NULL) {
        if (current->key == key) {
            if (!hasLeaf(current, k)) {
                current->key = DEFAULT_KEY_VALUE;
            } else {
                Trie *leaf = findLeftLeaf(current, k);
                if (current == leaf) {
                    current->key = DEFAULT_KEY_VALUE;
                } else {
                    current->key = leaf->key;
                    leaf->key = DEFAULT_KEY_VALUE;
                }
            }
            return;
        }

        int div = divCalculate(key, n, k, &x, isRoot);
        isRoot = false;

        if (!current->children || !current->children[div]) {
            printf("%d not exist\n", key);
            return;
        }
        current = current->children[div];
    }
}

void freeMemory(Trie* trie, int n, int k) {
    if (trie->children) {
        for (int i = 0; i < n; i++) {
            if (trie->children[i]) {
                freeMemory(trie->children[i], k, k);
            }
        }
        free(trie->children);
    }
    free(trie);
}

int main() {
    int count, min, max, n, k, key;
    char ch;
    scanf("%d %d %d %d %d", &count, &min, &max, &n, &k);
    Trie *trie = createTrie();
    for (int i = 0; i < count; i++) {
        scanf(" %c", &ch);
        switch (ch) {
            case 'I':
                scanf("%d", &key);
                insertTrie(trie, key, n, k);
                break;
            case 'P':
                printTrie(trie, n, k, true);
                printf("\n");
                break;
            case 'L':
                scanf("%d", &key);
                lookTrie(trie, key, n, k, key/n, true);
                break;
            case 'D':
                scanf("%d", &key);
                deleteTrie(trie, key, n, k);
                break;
        }
    }
    freeMemory(trie, n, k);
    return 0;
}