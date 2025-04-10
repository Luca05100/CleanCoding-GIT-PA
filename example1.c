/*Determinati daca exista sau nu drum direct intre doua restaurante dintr-o retea de tip graf*/

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

    typedef struct Node
{
    int data;
    struct Node *next;
}
/// pentru simplitate, folosim numerele de la 0 la n-1 pentru a reprezenta restaurantele
/// ex: 1 - restaurantul 1; 2- restaurantul 2; 3 - restaurantul 3; ... n - restaurantul n
    /// pentru a reprezenta muchiile, folosim o lista inlantuita (linked list) pentru fiecare nod
    /// ex: 1 -> 2 -> 3 -> NULL (restaurantul 1 are muchii catre restaurantul 2 si restaurantul 3)

Node;

typedef struct Graph
{
    int numberOfNodes;
    int *visited;
    struct Node **adjacencyList;
} Graph;

typedef struct Stack
{
    int top;
    int capacity;
    int *arr;
} Stack;

Node *create_node(int numberOfNodes)
{
    Node *newNode = malloc(sizeof(Node));
    newNode->data = numberOfNodes;
    newNode->next = NULL;
    return newNode;
}

void add_edge(Graph *g, int sourceNode, int destinationNode)
{
    Node *newNode = create_node(destinationNode);
    newNode->next = g->adjacencyList[sourceNode];
    g->adjacencyList[sourceNode] = newNode;
    newNode = create_node(sourceNode);
    newNode->next = g->adjacencyList[destinationNode];
    g->adjacencyList[destinationNode] = newNode;
}

Graph *create_graph(int NumberOfNodes)
{
    int i;
    Graph *g = malloc(sizeof(Graph));
    g->numberOfNodes = NumberOfNodes;
    g->adjacencyList = malloc(NumberOfNodes * sizeof(Node *));
    g->visited = malloc(sizeof(int) * NumberOfNodes);

    for (int i = 0; i < NumberOfNodes; i++)
    {
        g->adjacencyList[i] = NULL;
        g->visited[i] = 0;
    }
    return g;
}

Stack *create_stack(int capacity)
{
    Stack *s = malloc(sizeof(Stack));
    s->arr = malloc(capacity * sizeof(int));
    s->top = -1;
    s->capacity = capacity;

    return s;
}

void push(int value, Stack *stack)
{
    stack->top = stack->top + 1; // stack->top++;
    stack->arr[stack->top] = value; // stack->arr[stack->top] = value(value);
}

void DFS_traverse(Graph *g, Stack *s, int currentNode)
{
    Node *adj_list = g->adjacencyList[currentNode];
    Node *aux = adj_list;
    g->visited[currentNode] = 1;
    printf("%d ", currentNode);
    push(currentNode, s);
    while (aux != NULL)
    {
        int con_ver = aux->data;
        if (g->visited[con_ver] == 0)
            DFS_traverse(g, s, con_ver);
        aux = aux->next;
    }
}

void insert_edges(Graph *g, int edgeNumber, int nrv)
{
    int sourceNode, destinationNode, i;
    printf("Adauga %d munchii (de la 1 la %d)\n", edgeNumber, nrv);
    for (i = 0; i < edgeNumber; i++)
    {
        scanf("%d%d", &sourceNode, &destinationNode);
        add_edge(g, sourceNode, destinationNode);
    }
}

void wipe(Graph *g, int nrv)
{
    for (int i = 0; i < nrv; i++)
    {
        g->visited[i] = 0;
    }
}

int canbe(Graph *g, int nrv, Stack *s1, Stack *s2) // 0 sau 1 daca poate fi sau nu ajuns
{
   for(int i = 0; i < nrv; i++)
   {
        s1->top = -1;
        wipe(g, nrv);
        DFS_traverse(g, s1, i);
        
        for(int j = 0; j < nrv; j++)
        {
            s2->top = -1;
            wipe(g, nrv);
            DFS_traverse(g, s2, j);

            for(int x = 0; x <= s1->top; x++)
            {
                for (int y = 0; y <= s2->top; y++)
                {
                    if(s1->arr[x] == s2->arr[y])
                    {
                        return 1;
                    }
                }
            }
        }
   }
    return 0;
}

//Am adaugat functia canbe_between pentru a verifica daca exista un drum intre 2 noduri start si end.
int canbe_between(Graph *g, int nrv, Stack *stack, int start, int end)
{
    stack->top = -1;
    wipe(g, nrv);
    DFS_traverse(g, stack, start);

    for (int i = 0; i <= stack->top; i++)
    {
        if (stack->arr[i] == end)
            return 1;
    }
    return 0;
}

int main()
{

    int nrv;
    int edgeNumber;
    int sourceNode, destinationNode;
    int i;
    int startNode;
    int endNode;
    int answer;

    printf("Cate noduri are graful? ");
    scanf("%d", &nrv);

    printf("Cate muchii are graful? ");
    scanf("%d", &edgeNumber);

    Graph *g = create_graph(nrv);

    Stack *s1 = create_stack(2 * nrv);
    Stack *s2 = create_stack(2 * nrv);

    insert_edges(g, edgeNumber, nrv);

    printf("Introdu cele doua loacatii(noduri) pe care vrei sa le verifici: ");
    scanf("%d %d", &startNode, &endNode);


    answer = canbe_between(g, nrv, s1, startNode, endNode);
    if(answer == 1)
    {
        printf("Exista drum direct intre cele doua locatii\n");
    }
    else
    {
        printf("Nu exista drum direct intre cele doua locatii\n");
    }

}