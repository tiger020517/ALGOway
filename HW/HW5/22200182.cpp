//Topological Sort를 제외한 모든 함수: 교수님이 주신 코드
// Topological Sort: 나.

#include <iostream>

using namespace std;

#define MAX_NODES 10

typedef enum {
    WHITE, // Not visited
    GRAY,  // Currently in recursion stack
    BLACK  // Finished processing
} COLOR;

typedef struct AdjListNode {
    char label;
    struct AdjListNode* next;
} AdjListNode;

typedef struct Graph {
    char nodeLabels[MAX_NODES]; 
    AdjListNode* adj[MAX_NODES];
    int numVertices;
} Graph;

void addVertex(Graph* graph, char label) {
    if (graph->numVertices < MAX_NODES) {
        // Check if the label already exists
        for (int i = 0; i < graph->numVertices; i++) {
            if (graph->nodeLabels[i] == label) {
                printf("Vertex %c already exists.\n", label);
                return;
            }
        }
        graph->nodeLabels[graph->numVertices] = label;
        graph->numVertices++;
    } else {
        printf("Maximum number of nodes reached.\n");
    }
}

int getVertexIndex(Graph* graph, char label) {
    for (int i = 0; i < graph->numVertices; i++) {
        if (graph->nodeLabels[i] == label) {
            //printf("index is %d\n", i);
            return i;
        }
    }
    return -1; // Not found
}

void addEdge(Graph* graph, char srcLabel, char destLabel) {
    int srcIndex = getVertexIndex(graph, srcLabel);
    int destIndex = getVertexIndex(graph, destLabel);

    if (srcIndex == -1 || destIndex == -1) {
        printf("Invalid vertex label.\n");
        return;
    }

    AdjListNode* newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    newNode->label = destLabel;
    newNode->next = graph->adj[srcIndex];
    graph->adj[srcIndex] = newNode;

	//alphabetically sort the adjacency list
	AdjListNode* current = graph->adj[srcIndex];
	if (current == NULL || current->next == NULL) return; 

	AdjListNode* next = current->next;
	while (next != NULL)
	{
		if (current->label > next->label) {
			char temp = current->label;
			current->label = next->label;
			next->label = temp;
		} else {
			current = next;
			next = next->next;
		}
	}
}
void DFS_VISIT(Graph* graph, int u, COLOR color[], int* time, int d[], int f[]) {
	if (color[u] == WHITE) {
        color[u] = GRAY; // Mark the vertex as GRAY (discovered)
        (*time)++; // Increment time
        d[u] = *time; // Set discovery time
        printf("Visiting %c, Discovery Time: %d\n", graph->nodeLabels[u], d[u]);

        AdjListNode* current = graph->adj[u];
        while (current != NULL) {
            int v = getVertexIndex(graph, current->label);
            if (color[v] == WHITE) {
                DFS_VISIT(graph, v, color, time, d, f); // Recursive call
            }
            current = current->next;
        }

        color[u] = BLACK; // Mark the vertex as BLACK (finished)
        (*time)++; // Increment time
        f[u] = *time; // Set finishing time
        printf("Finished %c, Finishing Time: %d\n", graph->nodeLabels[u], f[u]);
    }
  // Write code here
}

void DFS(Graph* graph, COLOR color[], int* time, int d[], int f[]) {
	for (int i = 0; i < graph->numVertices; i++) {
		color[i] = WHITE; // Initialize all vertices to WHITE
	}
	for (int i = 0; i < graph->numVertices; i++) {
		if (color[i] == WHITE) {
			DFS_VISIT(graph, i, color, time, d, f);
		}
	}
}

void TopologicalSort(Graph* graph, COLOR color[], int* time, int d[], int f[]) {
    int isPrinted[MAX_NODES] = {0};

    for (int i = 0; i < graph->numVertices; i++) {
        color[i] = WHITE; // Initialize all vertices to WHITE
    }
    for (int i = 0; i < graph->numVertices; i++) {
        if (color[i] == WHITE) {
            DFS_VISIT(graph, i, color, time, d, f);
        }
    }
    printf("Topological Sort Order:\n");
    for (int i = 0; i < graph->numVertices; i++) {
        int max = -1;

        for (int j = 0; j < graph->numVertices; j++) {
            if (isPrinted[j] == 0 && f[j] > f[max]) {
                max = j;
            }
        }

        if (max != -1) {
            printf("%c ", graph->nodeLabels[max]);
            isPrinted[max] = 1;
        }
        else 
            break ;
    }
    cout << endl;

}
void printGraph(Graph* graph) {
    printf("Adjacency List:\n");
    for (int i = 0; i < graph->numVertices; i++) {
        printf("%c: ", graph->nodeLabels[i]);
        AdjListNode* current = graph->adj[i];
        while (current != NULL) {
            printf("%c -> ", current->label);
            current = current->next;
        }
        printf("NULL\n");
    }
}

int	main(void)
{
	Graph* graph = new Graph;
	for (int i = 0; i < MAX_NODES; i++) {
		graph->adj[i] = NULL;
		graph->nodeLabels[i] = '\0';
	}
	graph->numVertices = 0;

	/*for (int i = 0; i < MAX_NODES; i++)
	{
		char label = 'A' + i;
		graph->nodeLabels[graph->numVertices] = label;
		graph->numVertices++;
		if (graph->numVertices >= MAX_NODES)
			break ;
	}*/

	while (true)
	{
		char choice;
		printf("'v' to add an vertex\t\t'a' to add an edge, \n'p' to print the graph, \t'd' to DFS, \n't' to Topological Sort or \t'q' to quit\n");
        printf("Enter your choice: ");
		cin >> choice;
		if (choice == 'q') {
			break;
		} else if (choice == 'a') {
			char srcLabel, destLabel;
			printf("Enter source and destination labels (e.g., A B): ");
			cin >> srcLabel >> destLabel;
			addEdge(graph, srcLabel, destLabel);
		} else if (choice == 'v') {
            char label;
            printf("Enter vertex label: ");
            cin >> label;
            addVertex(graph, label);
        }
        else if (choice == 'p') {
			printGraph(graph);
		} else if (choice == 'd') {
			COLOR color[MAX_NODES];
			int time = 0;
			int d[MAX_NODES] = {0};
			int f[MAX_NODES] = {0};
			DFS(graph, color, &time, d, f);
		} else if (choice == 't') {
            COLOR color[MAX_NODES];
            int time = 0;
            int d[MAX_NODES] = {0};
            int f[MAX_NODES] = {0};
            TopologicalSort(graph, color, &time, d, f);
        }
        else {
			printf("Invalid choice. Please try again.\n");
		}
        cout << endl;
	}

	delete graph;
	return 0;
}