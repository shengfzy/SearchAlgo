#include <stdio.h>
#include <stdlib.h>

// 颜色枚举
typedef enum { RED, BLACK } Color;

// 红黑树节点结构
typedef struct Node {
    int data;
    Color color;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
} Node;

// 红黑树结构
typedef struct RedBlackTree {
    Node* root;
    Node* nil; // 哨兵节点，表示空节点
} RedBlackTree;

// 创建新节点
Node* createNode(int data, Node* nil) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->color = RED; // 新节点默认红色
    node->left = nil;
    node->right = nil;
    node->parent = nil;
    return node;
}

// 创建红黑树
RedBlackTree* createRedBlackTree() {
    RedBlackTree* tree = (RedBlackTree*)malloc(sizeof(RedBlackTree));
    tree->nil = (Node*)malloc(sizeof(Node));
    tree->nil->color = BLACK;
    tree->nil->left = NULL;
    tree->nil->right = NULL;
    tree->nil->parent = NULL;
    tree->root = tree->nil;
    return tree;
}

// 左旋转
void leftRotate(RedBlackTree* tree, Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != tree->nil) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == tree->nil) {
        tree->root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

// 右旋转
void rightRotate(RedBlackTree* tree, Node* y) {
    Node* x = y->left;
    y->left = x->right;
    if (x->right != tree->nil) {
        x->right->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == tree->nil) {
        tree->root = x;
    } else if (y == y->parent->right) {
        y->parent->right = x;
    } else {
        y->parent->left = x;
    }
    x->right = y;
    y->parent = x;
}

// 修复红黑树性质
void fixInsert(RedBlackTree* tree, Node* z) {
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node* y = z->parent->parent->right; // 叔叔节点
            if (y->color == RED) {
                // 情况1：叔叔是红色
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                // 叔叔是黑色
                if (z == z->parent->right) {
                    // 情况2：z 是右孩子
                    z = z->parent;
                    leftRotate(tree, z);
                }
                // 情况3：z 是左孩子
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(tree, z->parent->parent);
            }
        } else {
            Node* y = z->parent->parent->left; // 叔叔节点
            if (y->color == RED) {
                // 情况1：叔叔是红色
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                // 叔叔是黑色
                if (z == z->parent->left) {
                    // 情况2：z 是左孩子
                    z = z->parent;
                    rightRotate(tree, z);
                }
                // 情况3：z 是右孩子
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(tree, z->parent->parent);
            }
        }
    }
    tree->root->color = BLACK; // 根节点始终黑色
}

// 插入节点
void insert(RedBlackTree* tree, int data) {
    Node* z = createNode(data, tree->nil);
    Node* y = tree->nil;
    Node* x = tree->root;

    // 找到插入位置
    while (x != tree->nil) {
        y = x;
        if (z->data < x->data) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    z->parent = y;
    if (y == tree->nil) {
        tree->root = z;
    } else if (z->data < y->data) {
        y->left = z;
    } else {
        y->right = z;
    }

    fixInsert(tree, z);
}

// 中序遍历（验证树结构）
void inorderTraversal(RedBlackTree* tree, Node* node) {
    if (node != tree->nil) {
        inorderTraversal(tree, node->left);
        printf("%d(%s) ", node->data, node->color == RED ? "RED" : "BLACK");
        inorderTraversal(tree, node->right);
    }
}

// 释放节点内存
void freeNode(RedBlackTree* tree, Node* node) {
    if (node != tree->nil) {
        freeNode(tree, node->left);
        freeNode(tree, node->right);
        free(node);
    }
}

// 释放红黑树
void freeRedBlackTree(RedBlackTree* tree) {
    freeNode(tree, tree->root);
    free(tree->nil);
    free(tree);
}

// 示例用法
int main() {
    RedBlackTree* tree = createRedBlackTree();

    // 插入示例数据
    int values[] = {7, 3, 18, 10, 22, 8, 11, 26, 2, 6};
    int n = sizeof(values) / sizeof(values[0]);
    for (int i = 0; i < n; i++) {
        insert(tree, values[i]);
    }

    // 中序遍历，验证树结构
    printf("Inorder traversal of the Red-Black Tree: ");
    inorderTraversal(tree, tree->root);
    printf("\n");

    // 释放内存
    freeRedBlackTree(tree);
    return 0;
}
