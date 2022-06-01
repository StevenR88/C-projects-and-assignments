#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MEMORY_ALLOC_ERROR_CODE 2
#define EMPTY_LIST_ERROR_CODE 3

/**
 * Struct to represent a memory block. Boolean parameter indicates whether
 * the struct is a process (true) or a hole (false).
 */
struct Node {
    bool isProcess;
    int processNumber;
    int base;
    int limit;
    struct Node *next;
};


/**
 * Redefined Node* as Link object.
 */
typedef struct Node* Link;

/**
 * Creates a new Node object.
 * @param isProcess as a bool
 * @param processNumber as an int
 * @param base as an int
 * @param limit as an int
 * @return Link to newly created Node object
 */
Link createNode(bool isProcess, int processNumber, int base, int limit) {
    Link link = (Link) malloc(sizeof(struct Node));
    if (!link) {
        perror("Memory allocation error.");
        exit(MEMORY_ALLOC_ERROR_CODE);
    }

    link->isProcess = isProcess;
    link->processNumber = processNumber;
    link->base = base;
    link->limit = limit;
    link->next = NULL;

    return link;
}

/**
 * Creates a new Node object, and sets next node to entered parameter.
 * @param isProcess as a bool
 * @param processNumber as an int
 * @param base as an int
 * @param limit as an int
 * @param next as the next node in list
 * @return Link to newly created Node object
 */
Link createNodeWithNextNode(bool isProcess, int processNumber, int base,
                            int limit, Link next) {
    Link link = createNode(isProcess, processNumber, base, limit);
    link->next = next;
    return link;
}

/**
 * Pushes a Node to the front of the specified linked list.
 * @param head as a Link
 * @param isProcess as a bool
 * @param processNumber as an int
 * @param base as an int
 * @param limit as an int
 */
void push(Link *head, bool isProcess, int processNumber, int base, int limit) {
    Link newHead = createNodeWithNextNode(isProcess, processNumber, base,
                                          limit, *head);
    *head = newHead;
}

/**
 * Removes a Node from the front of the specified linked list.
 * @param head as a Link
 */
void pop(Link *head) {
    if (!*head) {
        perror("Empty list.");
        exit(EMPTY_LIST_ERROR_CODE);
    }
    Link oldHead = *head;
    *head = (*head)->next;
    free(oldHead);
}

/**
 * Gets the tail of a linked list and returns pointer.
 * @param head
 * @return
 */
Link getTail(Link head) {
    if (!head) {
        return NULL;
    }
    if (!head->next) {
        return head;
    }
    return getTail(head->next);
}

/**
 * Adds a Node to the end of a linked list.
 * @param head as a Link
 * @param isProcess as a bool
 * @param processNumber as an int
 * @param base as an int
 * @param limit as an int
 */
void addLast(Link *head, bool isProcess, int processNumber, int base, int limit) {
    Link newTail = createNode(isProcess, processNumber, base, limit);
    if (!*head) {
        *head = newTail;
        return;
    }
    Link currentTail = getTail(*head);
    currentTail->next = newTail;
}

/**
 * Merges any consecutive holes (two or more) in memory into single blocks
 * for the specified linked list.
 * @param head  as a Link
 */
void mergeFreeBlocks(Link head) {
    Link previousNode = NULL;
    while (head) {
        if (previousNode && !head->isProcess
            && previousNode->isProcess == false) {
            previousNode->limit += head->limit;
            pop(&head);
            previousNode->next = head;
        } else {
            previousNode = head;
            head = head->next;
        }
    }
}

/**
 * Moves all allocated blocks of memory (processes) next to each other,
 * and moves any holes to end of the specified linked list.
 * @param head as a pointer to a Link
 */
void compaction (Link *head) {
    int nextHeadBase = 0;
    int holeNodeLimitCount = 0;
    Link previousNode = NULL;

    while (*head && !(*head)->isProcess) {
        holeNodeLimitCount += (*head)->limit;
        pop(head);
    }
    Link currentNode = *head;

    while(currentNode && *head) {
        if (!currentNode->isProcess) {
            holeNodeLimitCount += currentNode->limit;
            pop(&currentNode);
        } else {
            currentNode->base = nextHeadBase;
            nextHeadBase += currentNode->limit;
            previousNode = currentNode;
            currentNode = currentNode->next;
        }
        if (previousNode) {
            previousNode->next = currentNode;
        }
    }
    if (holeNodeLimitCount != 0) {
        addLast(head,false, 1, nextHeadBase, holeNodeLimitCount);
    }
}

/**
 * Prints each block of memory in a specified linked list to the console
 * (one line at a time).
 * @param head as a Link
 */
void printMemory(Link head) {
    int listCounter = 1;
    if (head == NULL) {
        printf("--Empty List--\n");
        return;
    }
    while (head) {
        if (head->isProcess) {
            printf("Node %d: P%d, base = %d, limit = %d", listCounter,
                   head->processNumber, head->base, head->limit);
            printf("\n");
        } else {
            printf("Node %d: H (Hole), base = %d, limit = %d", listCounter,
                   head->base, head->limit);
            printf("\n");
        }
        head = head->next;
        ++listCounter;
    }
}

/**
 * Frees memory from the specified linked list.
 * @param head as a link
 */
void freeLinkedList(Link *head) {
    while (*head) {
        pop(head);
    }
}

int main() {
    Link head = NULL;
    printf("\nmergeFreeBlocks Tests\n");
    printf("==================================================\n");
    printf("Test case: Empty list test\n");
    printMemory(head);
    mergeFreeBlocks(head);
    printf("After Merge:\n");
    printMemory(head);
    freeLinkedList(&head);


    printf("--------------------------------------------------");
    printf("\nTest case: One process test\n");
    push(&head, true, 1, 0, 10);
    printMemory(head);
    mergeFreeBlocks(head);
    printf("After Merge:\n");
    printMemory(head);
    freeLinkedList(&head);

    printf("--------------------------------------------------");
    printf("\nTest case: Multiple processes test\n");
    push(&head, true, 3, 12, 10);
    push(&head, true, 2, 10, 12);
    push(&head, true, 1, 0, 10);
    printMemory(head);
    mergeFreeBlocks(head);
    printf("After Merge:\n");
    printMemory(head);
    freeLinkedList(&head);

    printf("--------------------------------------------------");
    printf("\nTest case: One hole test\n");
    push(&head, false, 0, 0, 10);
    printMemory(head);
    mergeFreeBlocks(head);
    printf("After Merge:\n");
    printMemory(head);
    freeLinkedList(&head);

    printf("--------------------------------------------------");
    printf("\nTest case: Two adjacent holes test\n");
    push(&head, false, 0, 10, 12);
    push(&head, false, 0, 0, 10);
    printMemory(head);
    mergeFreeBlocks(head);
    printf("After Merge:\n");
    printMemory(head);
    freeLinkedList(&head);

    printf("--------------------------------------------------");
    printf("\nTest case: Three adjacent holes test\n");
    push(&head, false, 0, 22, 10);
    push(&head, false, 0, 10, 12);
    push(&head, false, 0, 0, 10);
    printMemory(head);
    mergeFreeBlocks(head);
    printf("After Merge:\n");
    printMemory(head);
    freeLinkedList(&head);

    printf("--------------------------------------------------");
    printf("\nTest case: No adjacent holes test\n");
    push(&head, false, 0, 29, 3);
    push(&head, true, 2, 27, 2);
    push(&head, false, 0, 22, 5);
    push(&head, true, 1, 10, 12);
    push(&head, false, 0, 0, 10);
    printMemory(head);
    mergeFreeBlocks(head);
    printf("After Merge:\n");
    printMemory(head);
    freeLinkedList(&head);

    printf("--------------------------------------------------");
    printf("\nTest case: Multiple holes in the middle test\n");
    push(&head, true, 5, 46, 1);
    push(&head, true, 4, 37, 9);
    push(&head, false, 0, 35, 2);
    push(&head, false, 0, 34, 1);
    push(&head, false, 0, 28, 6);
    push(&head, true, 3, 18, 10);
    push(&head, false, 0, 17, 1);
    push(&head, true, 2, 16, 1);
    push(&head, true, 1, 10, 6);
    push(&head, false, 0, 0, 10);
    printMemory(head);
    mergeFreeBlocks(head);
    printf("After Merge:\n");
    printMemory(head);
    freeLinkedList(&head);

    printf("--------------------------------------------------");
    printf("\nTest case: Multiple holes in the beginning and middle test\n");
    push(&head, false, 0, 47, 2);
    push(&head, true, 5, 46, 1);
    push(&head, true, 4, 37, 9);
    push(&head, false, 0, 35, 2);
    push(&head, false, 0, 34, 1);
    push(&head, false, 0, 28, 6);
    push(&head, false, 0, 18, 10);
    push(&head, false, 0, 17, 1);
    push(&head, true, 2, 16, 1);
    push(&head, true, 1, 10, 6);
    push(&head, false, 0, 6, 4);
    push(&head, false, 0, 4, 2);
    push(&head, false, 0, 0, 4);
    printMemory(head);
    mergeFreeBlocks(head);
    printf("After Merge:\n");
    printMemory(head);
    freeLinkedList(&head);

    printf("--------------------------------------------------");
    printf("\nTest case: Multiple holes in the beginning, middle, and end test\n");
    push(&head, false, 0, 49, 4);
    push(&head, true, 0, 47, 2);
    push(&head, true, 5, 46, 1);
    push(&head, true, 4, 37, 9);
    push(&head, false, 0, 35, 2);
    push(&head, false, 0, 34, 1);
    push(&head, false, 0, 28, 6);
    push(&head, true, 3, 18, 10);
    push(&head, false, 0, 17, 1);
    push(&head, true, 2, 16, 1);
    push(&head, true, 1, 10, 6);
    push(&head, false, 0, 6, 4);
    push(&head, false, 0, 4, 2);
    push(&head, false, 0, 0, 4);
    printMemory(head);
    mergeFreeBlocks(head);
    printf("After Merge:\n");
    printMemory(head);
    freeLinkedList(&head);

    printf("--------------------------------------------------");
    printf("\nTest case: Starting with process test\n");
    push(&head, false, 0, 49, 4);
    push(&head, false, 0, 47, 2);
    push(&head, true, 6, 46, 1);
    push(&head, true, 5, 37, 9);
    push(&head, false, 0, 35, 2);
    push(&head, false, 0, 34, 1);
    push(&head, false, 0, 28, 6);
    push(&head, true, 4, 18, 10);
    push(&head, false, 0, 17, 1);
    push(&head, true, 3, 16, 1);
    push(&head, true, 2, 10, 6);
    push(&head, true, 1, 0, 10);
    printMemory(head);
    mergeFreeBlocks(head);
    printf("After Merge:\n");
    printMemory(head);
    freeLinkedList(&head);


    //Compaction tests:
    printf("\n\n\ncompaction tests \n");
    printf("==================================================\n");
    printf("Test case: Empty list test\n");
    printMemory(head);
    compaction(&head);
    printf("After compaction:\n");
    printMemory(head);
    freeLinkedList(&head);


    printf("--------------------------------------------------");
    printf("\nTest case: One process test\n");
    push(&head, true, 1, 0, 10);
    printMemory(head);
    compaction(&head);
    printf("After compaction:\n");
    printMemory(head);
    freeLinkedList(&head);

    printf("--------------------------------------------------");
    printf("\nTest case: Two processes test\n");
    push(&head, true, 2, 10, 12);
    push(&head, true, 1, 0, 10);
    printMemory(head);
    compaction(&head);
    printf("After compaction:\n");
    printMemory(head);
    freeLinkedList(&head);

    printf("--------------------------------------------------");
    printf("\nTest case: Three processes test\n");
    push(&head, true, 3, 22, 10);
    push(&head, true, 2, 10, 12);
    push(&head, true, 1, 0, 10);
    printMemory(head);
    compaction(&head);
    printf("After compaction:\n");
    printMemory(head);
    freeLinkedList(&head);

    printf("--------------------------------------------------");
    printf("\nTest case: One hole test\n");
    push(&head, false, 0, 0, 10);
    printMemory(head);
    compaction(&head);
    printf("After compaction:\n");
    printMemory(head);
    freeLinkedList(&head);

    printf("--------------------------------------------------");
    printf("\nTest case: Two holes test\n");
    push(&head, false, 0, 10, 12);
    push(&head, false, 0, 0, 10);
    printMemory(head);
    compaction(&head);
    printf("After compaction:\n");
    printMemory(head);
    freeLinkedList(&head);


    printf("--------------------------------------------------");
    printf("\nTest case: Three holes test\n");
    push(&head, false, 0, 22, 3);
    push(&head, false, 0, 10, 12);
    push(&head, false, 0, 0, 10);
    printMemory(head);
    compaction(&head);
    printf("After compaction:\n");
    printMemory(head);
    freeLinkedList(&head);

    printf("--------------------------------------------------");
    printf("\nlist with all holes\n");
    push(&head, false, 0, 18, 10);
    push(&head, false, 0, 17, 1);
    push(&head, false, 0, 16, 1);
    push(&head, false, 0, 10, 6);
    push(&head, false, 0, 0, 10);
    printMemory(head);
    printf("\n");
    compaction(&head);
    printMemory(head);
    freeLinkedList(&head);

    printf("--------------------------------------------------");
    printf("\nTest case: Multiple holes in the beginning test\n");
    push(&head, true, 2, 31, 1);
    push(&head, true, 1, 25, 6);
    push(&head, false, 0, 22, 3);
    push(&head, false, 0, 10, 12);
    push(&head, false, 0, 0, 10);
    printMemory(head);
    compaction(&head);
    printf("After compaction:\n");
    printMemory(head);
    freeLinkedList(&head);

    printf("--------------------------------------------------");
    printf("\nTest case: Multiple holes in the end test\n");
    push(&head, false, 0, 25, 7);
    push(&head, false, 0, 22, 3);
    push(&head, false, 0, 10, 12);
    push(&head, true, 2, 4, 6);
    push(&head, true, 1, 0, 4);
    printMemory(head);
    compaction(&head);
    printf("After compaction:\n");
    printMemory(head);
    freeLinkedList(&head);

    printf("--------------------------------------------------");
    printf("\nTest case: Multiple holes in the middle test\n");
    push(&head, true, 4, 28, 4);
    push(&head, true, 3, 26, 2);
    push(&head, false, 0, 25, 1);
    push(&head, false, 0, 22, 3);
    push(&head, false, 0, 10, 12);
    push(&head, true, 2, 4, 6);
    push(&head, true, 1, 0, 4);
    printMemory(head);
    compaction(&head);
    printf("After compaction:\n");
    printMemory(head);
    freeLinkedList(&head);

    printf("--------------------------------------------------");
    printf("\nTest case: Starting with one hole and having adjacent in the middle test\n");
    push(&head, true, 5, 46, 1);
    push(&head, true, 4, 37, 9);
    push(&head, false, 0, 35, 2);
    push(&head, false, 0, 34, 1);
    push(&head, false, 0, 28, 6);
    push(&head, true, 3, 18, 10);
    push(&head, false, 0, 17, 1);
    push(&head, true, 2, 16, 1);
    push(&head, true, 1, 10, 6);
    push(&head, false, 0, 0, 10);
    printMemory(head);
    compaction(&head);
    printf("After compaction:\n");
    printMemory(head);
    freeLinkedList(&head);

    printf("--------------------------------------------------");
    printf("\nTest case: Starting with multiple holes test and having adjacent in the middle test\n");
    push(&head, false, 0, 47, 15);
    push(&head, true, 5, 46, 1);
    push(&head, true, 4, 37, 9);
    push(&head, false, 0, 35, 2);
    push(&head, false, 0, 34, 1);
    push(&head, false, 0, 28, 6);
    push(&head, true, 3, 18, 10);
    push(&head, false, 0, 17, 1);
    push(&head, true, 2, 16, 1);
    push(&head, true, 1, 10, 6);
    push(&head, false, 0, 6, 4);
    push(&head, false, 0, 4, 2);
    push(&head, false, 0, 0, 4);
    printMemory(head);
    compaction(&head);
    printf("After compaction:\n");
    printMemory(head);
    freeLinkedList(&head);

    printf("--------------------------------------------------");
    printf("\nTest case: Starting and Ending with multiple holes test\n");
    push(&head, false, 0, 49, 4);
    push(&head, false, 0, 47, 2);
    push(&head, true, 5, 46, 1);
    push(&head, true, 4, 37, 9);
    push(&head, false, 0, 35, 2);
    push(&head, false, 0, 34, 1);
    push(&head, false, 0, 28, 6);
    push(&head, true, 3, 18, 10);
    push(&head, false, 0, 17, 1);
    push(&head, true, 2, 16, 1);
    push(&head, true, 1, 10, 6);
    push(&head, false, 0, 6, 4);
    push(&head, false, 0, 4, 2);
    push(&head, false, 0, 0, 4);
    printMemory(head);
    compaction(&head);
    printf("After compaction:\n");
    printMemory(head);
    freeLinkedList(&head);

    printf("--------------------------------------------------");
    printf("\nTest case: Starting with multiple processes test\n");
    push(&head, false, 0, 49, 4);
    push(&head, false, 0, 47, 2);
    push(&head, true, 6, 46, 1);
    push(&head, true, 5, 37, 9);
    push(&head, false, 0, 35, 2);
    push(&head, false, 0, 34, 1);
    push(&head, false, 0, 28, 6);
    push(&head, true, 4, 18, 10);
    push(&head, false, 0, 17, 1);
    push(&head, true, 3, 16, 1);
    push(&head, true, 2, 10, 6);
    push(&head, true, 1, 0, 10);
    printMemory(head);
    compaction(&head);
    printf("After compaction:\n");
    printMemory(head);
    freeLinkedList(&head);

    printf("\nFinal test completed --> freeing memory --> next print should be empty.\n");
    printMemory(head);
    return 0;
}
