#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 100
#define MAX_QUEUE_SIZE 100

// 队列结构
typedef struct {
    int items[MAX_QUEUE_SIZE];
    int front;
    int rear;
} Queue;

// 图的邻接表节点
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// 图结构
typedef struct {
    Node* adjLists[MAX_VERTICES];
    int numVertices;
} Graph;

// 初始化队列
Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = -1;
    queue->rear = -1;
    return queue;
}

// 队列是否为空
int isEmpty(Queue* queue) {
    return queue->front == -1;
}

// 入队
void enqueue(Queue* queue, int value) {
    if (queue->rear == MAX_QUEUE_SIZE - 1) {
        printf("Queue is full\n");
        return;
    }
    if (isEmpty(queue)) {
        queue->front = 0;
    }
    queue->rear++;
    queue->items[queue->rear] = value;
}

// 出队
int dequeue(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return -1;
    }
    int item = queue->items[queue->front];
    queue->front++;
    if (queue->front > queue->rear) {
        queue->front = queue->rear = -1;
    }
    return item;
}

// 创建图
Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;
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

// 广度优先搜索
void bfs(Graph* graph, int startVertex) {
    // 初始化访问数组
    int visited[MAX_VERTICES] = {0};
    Queue* queue = createQueue();

    // 标记起始顶点为已访问并入队
    visited[startVertex] = 1;
    enqueue(queue, startVertex);

    printf("BFS traversal starting from vertex %d: ", startVertex);

    while (!isEmpty(queue)) {
        int currentVertex = dequeue(queue);
        printf("%d ", currentVertex);

        // 遍历当前顶点的邻接表
        Node* temp = graph->adjLists[currentVertex];
        while (temp) {
            int adjVertex = temp->vertex;
            if (!visited[adjVertex]) {
                visited[adjVertex] = 1;
                enqueue(queue, adjVertex);
            }
            temp = temp->next;
        }
    }
    printf("\n");

    free(queue);
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

    // 执行BFS
    bfs(graph, 0);

    // 释放内存
    freeGraph(graph);
    return 0;
}
