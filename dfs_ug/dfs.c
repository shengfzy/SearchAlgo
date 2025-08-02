#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 100

// 图的邻接表节点
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// 图结构
typedef struct {
    Node* adjLists[MAX_VERTICES];
    int numVertices;
    int* visited; // 动态分配的访问数组
} Graph;

// 创建图
Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;
    graph->visited = (int*)calloc(vertices, sizeof(int)); // 初始化访问数组
    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
    }
    return graph;
}

// 添加边
void addEdge(Graph* graph, int src, int dest) {
    // 添加 src -> dest
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = dest;
    newNode->next = NULL;
    
    if (graph->adjLists[src] == NULL) {
        graph->adjLists[src] = newNode;
    } else {
        Node* temp = graph->adjLists[src];
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    // 添加 dest -> src（无向图）
    newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = src;
    newNode->next = NULL;
    
    if (graph->adjLists[dest] == NULL) {
        graph->adjLists[dest] = newNode;
    } else {
        Node* temp = graph->adjLists[dest];
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// 深度优先搜索（递归）
void dfsRecursive(Graph* graph, int vertex) {
    // 标记当前顶点为已访问
    graph->visited[vertex] = 1;
    printf("%d ", vertex);

    // 遍历当前顶点的邻接表
    Node* temp = graph->adjLists[vertex];
    while (temp) {
        int adjVertex = temp->vertex;
        if (!graph->visited[adjVertex]) {
            dfsRecursive(graph, adjVertex);
        }
        temp = temp->next;
    }
}

// 深度优先搜索（包装函数）
void dfs(Graph* graph, int startVertex) {
    // 重置访问数组
    for (int i = 0; i < graph->numVertices; i++) {
        graph->visited[i] = 0;
    }

    printf("DFS traversal starting from vertex %d: ", startVertex);
    dfsRecursive(graph, startVertex);
    printf("\n");
}

// 释放图的内存
void freeGraph(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        Node* temp = graph->adjLists[i];
        while (temp) {
            Node* next = temp->next;
            free(temp);
            temp = next;
        }
    }
    free(graph->visited);
    free(graph);
}

// 示例用法
int main() {
    // 创建一个有5个顶点的图
    Graph* graph = createGraph(5);

    // 添加边
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 2, 3);
    addEdge(graph, 2, 4);

    // 执行DFS
    dfs(graph, 0);

    // 释放内存
    freeGraph(graph);
    return 0;
}
