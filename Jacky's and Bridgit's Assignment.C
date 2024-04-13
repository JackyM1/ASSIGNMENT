#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// Function to create a new node
TreeNode* createNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode == NULL) {
        printf("Memory allocation error!\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to find index of a value in an array
int findIndex(int arr[], int start, int end, int value) {
    int i;
    for (i = start; i <= end; i++) {
        if (arr[i] == value) {
            return i;
        }
    }
    return -1;  // Value not found
}

// Recursive function to construct BST from in-order and post-order traversals
TreeNode* constructBST(int inorder[], int postorder[], int inStart, int inEnd, int* postIndex) {
    if (inStart > inEnd) {
        return NULL;
    }

    // Create a new node with the current postorder element
    TreeNode* root = createNode(postorder[*postIndex]);
    (*postIndex)--;

    // If the node has no children, return it
    if (inStart == inEnd) {
        return root;
    }

    // Find index of current node in inorder traversal
    int inIndex = findIndex(inorder, inStart, inEnd, root->data);

    // Recursively construct right subtree
    root->right = constructBST(inorder, postorder, inIndex + 1, inEnd, postIndex);
    // Recursively construct left subtree
    root->left = constructBST(inorder, postorder, inStart, inIndex - 1, postIndex);

    return root;
}

// Function to traverse BST in breadth-first-search (DFS) traversal
void breadthFirstSearch(TreeNode* root) {
    if (root == NULL) {
        return;
    }

    // Create a queue for BFS traversal
    TreeNode* queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        TreeNode* current = queue[front++];
        printf("%d ", current->data);

        if (current->left != NULL) {
            queue[rear++] = current->left;
        }
        if (current->right != NULL) {
            queue[rear++] = current->right;
        }
    }
}

// Function to construct BST using in-order and post-order traversals
TreeNode* hst_construct(int inorder[], int postorder[], int n) {
    int postIndex = n - 1;
    return constructBST(inorder, postorder, 0, n - 1, &postIndex);
}

int main() {
    int inOrder[] = {5, 10, 15, 20, 25, 30, 45};
    int postOrder[] = {5, 15, 10, 25, 45, 30, 20};
    int n = sizeof(inOrder) / sizeof(inOrder[0]);

    TreeNode* root = hst_construct(inOrder, postOrder, n);
    printf("Breadth-First Search (DFS) Traversal:\n");
    breadthFirstSearch(root);
    printf("\n");

    return 0;
}
