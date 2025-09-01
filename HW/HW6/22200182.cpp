//강의 자료: Graph 관련 된 코드: 교수님이 주신 코드
//블로그: 플로이드 워셜 알고리즘: https://ansohxxn.github.io/algorithm/floyd/
//블로그: 다익스트라 알고리즘: https://yabmoons.tistory.com/364
//블로그: 다익스트라 알고리즘: https://meojiktard.tistory.com/13

#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

#define MAX_NODES 10
#define INFI 999999999

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

	ifstream InputFile("homework6.data");
	if (!InputFile.is_open()) {
		cout << "파일 읽기 오류" << endl;
		return 1;
	}
	int matrix[10][10] = {0};
	string cities[10];
	int cityCount = 0;
	while (!InputFile.eof()) {
		string in;
		InputFile >> in;
		if (in == "") 
			break ;
		cities[cityCount] = in;
		for (int i = 0; i < 10; i++)
		{
			InputFile >> in;
			if (in == "INF")
				matrix[cityCount][i] = INFI;
			else
				matrix[cityCount][i] = stoi(in);
		}
		cityCount++;
	}
	for (int i = 0; i < cityCount; i++) {
		addVertex(graph, 'a' + i);
	}
	for (int i = 0; i < cityCount; i++) {
		for (int j = 0; j < cityCount; j++) {
			if (matrix[i][j] != INFI && matrix[i][j] != 0) {
				addEdge(graph, 'a' + i, 'a' + j);
			}
		}
	}
	int daikstra[10][10];
	int visited[10][10];
	//다익스트라 시작
	for (int start = 0; start < cityCount; start++) {
		for (int j = 0; j < cityCount; j++) {
            daikstra[start][j] = INFI;
            visited[start][j] = 0;  
        }
		daikstra[start][start] = 0;
		for (int i = 0; i < cityCount - 1; i++) {
			int minIndex = -1;
			int minValue = INFI;
			for (int j = 0; j < cityCount; j++) {
				if (!visited[start][j] && daikstra[start][j] < minValue) {
					minValue = daikstra[start][j];
					minIndex = j;
				}
			}
			if (minIndex == -1) break ;
			visited[start][minIndex] = 1;
			for (int j = 0; j < cityCount; j++) {
				if (!visited[start][j] && matrix[minIndex][j] != INFI) {
					if (daikstra[start][minIndex] + matrix[minIndex][j] < daikstra[start][j]) {
						daikstra[start][j] = daikstra[start][minIndex] + matrix[minIndex][j];
					}
				}
			}
		}
	}
	/*
	cout << "행렬 출력" << endl;
	for (int i = 0; i < cityCount; i++) 
		cout << "\t" << cities[i];
	cout << endl;
	for (int i = 0; i < cityCount; i++) {
		cout << cities[i] << "\t";
		for (int j = 0; j < cityCount; j++) {
			if (matrix[i][j] == INFI)
				cout << "INF\t";
			else
				cout << matrix[i][j] << "\t";
		}
		cout << endl;
	}
	*/
	cout << "다익스트라 결과" << endl;
	for (int i = 0; i < cityCount; i++) 
		cout << "\t" << cities[i];
	cout << endl;
	for (int i = 0; i < cityCount; i++) {
		cout << cities[i] << "\t";
		for (int j = 0; j < cityCount; j++) {
			if (daikstra[i][j] == INFI)
				cout << "INF\t";
			else
				cout << daikstra[i][j] << "\t";
		}
		cout << endl;
	}
	/*
	cout << "행렬 출력" << endl;
	for (int i = 0; i < cityCount; i++) 
		cout << "\t" << cities[i];
	cout << endl;
	for (int i = 0; i < cityCount; i++) {
		cout << cities[i] << "\t";
		for (int j = 0; j < cityCount; j++) {
			if (matrix[i][j] == INFI)
				cout << "INF\t";
			else
				cout << matrix[i][j] << "\t";
		}
		cout << endl;
	}
	*/
	//플로이드 워셜 시작
	for (int k = 0; k < cityCount; k++) {
		for (int i = 0; i < cityCount; i++) {
			for (int j = 0; j < cityCount; j++) {
				if (matrix[i][j] > matrix[i][k] + matrix[k][j]) {
					matrix[i][j] = matrix[i][k] + matrix[k][j];
				}
			}
		}
	}
	cout << "플로이드 워셜 결과" << endl;
	for (int i = 0; i < cityCount; i++) 
		cout << "\t" << cities[i];
	cout << endl;
	for (int i = 0; i < cityCount; i++) {
		cout << cities[i] << "\t";
		for (int j = 0; j < cityCount; j++) {
			if (matrix[i][j] == INFI)
				cout << "INF\t";
			else
				cout << matrix[i][j] << "\t";
		}
		cout << endl;
	}
	
	
	
	
	
	
	
	
	
	

	delete graph;
	return 0;
}

/*
	for (int i = 0; i < cityCount; i++) 
		cout << "\t" << cities[i];
	cout << endl;
	for (int i = 0; i < cityCount; i++) {
		cout << cities[i] << "\t";
		for (int j = 0; j < cityCount; j++) {
			if (matrix[i][j] == INFI)
				cout << "INF\t";
			else
				cout << matrix[i][j] << "\t";
		}
		cout << endl;
	}
	*/