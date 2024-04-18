#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};


struct Node* bst_construct(int in[], int* post, int inStart, int inEnd);
void bfsTraversal(struct Node* root);

int main() {
    int inOrder[] = {5, 10, 15, 20, 25, 30, 45};
    int postOrder[] = {5, 15, 10, 25, 45, 30, 20};
    int n = sizeof(inOrder) / sizeof(inOrder[0]);

    struct Node* root = bst_construct(inOrder, postOrder, 0, n - 1);

    printf("BFS Traversal: ");
    bfsTraversal(root);

    return 0;
}

// Function to construct the Binary Search Tree
struct Node* bst_construct(int in[], int* post, int inStart, int inEnd) {
    // Base case
    if (inStart > inEnd)
        return NULL;

    // Create a new node with the current element from post-order traversal
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = post[inEnd]; // Last element of post-order is the root
    node->left = NULL;
    node->right = NULL;

    // If the current node has no children, return it
    if (inStart == inEnd)
        return node;

    // Find the index of current node in in-order traversal
    int inIndex;
    for (inIndex = inStart; inIndex <= inEnd; inIndex++) {
        if (in[inIndex] == node->data)
            break;
    }

    // Recursively construct the right and left subtrees
    node->right = bst_construct(in, post, inIndex + 1, inEnd - 1); // Exclude root from post-order
    node->left = bst_construct(in, post, inStart, inIndex - 1);

    return node;
}

// Function to perform breadth-first-search traversal
void bfsTraversal(struct Node* root) {
    if (root == NULL)
        return;

    // Create a queue for BFS
    struct Node* queue[100];
    int front = -1, rear = -1;

    queue[++rear] = root;

    while (front != rear) {
        struct Node* temp = queue[++front];
        printf("%d ", temp->data);

        if (temp->left != NULL)
            queue[++rear] = temp->left;

        if (temp->right != NULL)
            queue[++rear] = temp->right;
    }
}

