/*parcurgerge  graf cu DFS/BFS*/

//Imi cer scuze in avans


//Am schimbat numele variabilelor, am rezolvat erorile si am facut codul mai usor de citit

#include <stdlib.h>
#include <stdio.h>


typedef struct Node
{
    int data;
    struct Node *next;
} NODE;

typedef struct Graph
{ 
    int node_count;
    int *visited;
    struct Node **adjacency_lists;
} GPH;


NODE *create_node(int v)
{ 
    NODE *new_node = malloc(sizeof(NODE)); 
    new_node->data = v;
    new_node->next = NULL;
    return new_node;
}



GPH *create_graph(int node_count)
{
    GPH *graph = malloc(sizeof(GPH));
    graph->node_count = node_count;
    graph->adjacency_lists = malloc(node_count * sizeof(NODE *));
    graph->visited = malloc(sizeof(int) * node_count);
    
    for (int i = 0; i < node_count; i++)
    {
        graph->adjacency_lists[i] = NULL;
        graph->visited[i] = 0;
    } 
    return graph;
}

void add_edge(GPH *graph, int src, int dest)
{
    NODE *new_node = create_node(dest);
    new_node->next = graph->adjacency_lists[src];
    graph->adjacency_lists[src] = new_node;

    new_node = create_node(src);
    new_node->next = graph->adjacency_lists[dest];
    graph->adjacency_lists[dest] = new_node;
}


int read_edges(int nr_of_node_count, int nr_of_edges, GPH *graph)
{
    int src, dest;
    printf("Adauga %d muchii (de la 0 la %d):\n", nr_of_edges, nr_of_node_count - 1);
    for (int i = 0; i < nr_of_edges; i++)
    {
        scanf("%d%d", &src, &dest);
        add_edge(graph, src, dest);
    }
}

int is_empty(NODE *queue)
{
    return queue == NULL;
}

void enqueue(NODE **queue, int data)
{
    NODE *new_node = create_node(data);

    if (is_empty(*queue))
        *queue = new_node;
    else
    {
        NODE *temp = *queue;
        while (temp->next)
        {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

int dequeue(NODE **queue)
{
     int data = (*queue)->data;
     NODE *temp = *queue;
     *queue = (*queue)->next;
     return data;
}

void print_graph(GPH *graph)
{
    int i; for (i = 0; i < graph->node_count; i++)
    {
        NODE *temp = graph->adjacency_lists[i];

        while (temp) 
        {
            printf("%d", temp->data);
            temp = temp->next; 
        }
    printf("\n");
    }
}

void print_queue(NODE *queue)
{
    while (queue != NULL)
    {
        printf("%d ", queue->data);
        queue = queue->next;
    }
}


void reset_visited(GPH *graph, int nr_of_node_count)
{
    for (int i = 0; i < nr_of_node_count; i++)
    graph->visited[i] = 0;
}

void DFS(GPH *graph, int vertex_nr)
{
    NODE *adj_list = graph->adjacency_lists[vertex_nr];
    NODE *temp = adj_list;

    graph->visited[vertex_nr] = 1;
    printf("%d ", vertex_nr);

    while (temp != NULL)
    {
        int connected_vertex = temp->data;
        if (graph->visited[connected_vertex] == 0)
        {
            DFS(graph, connected_vertex);
        }
        temp = temp->next;
    }
}

void BFS(GPH *graph, int start)
{
    NODE *queue = NULL;

    graph->visited[start] = 1;
    enqueue(&queue, start);

    while (!is_empty(queue))
    {
        int current = dequeue(&queue);
        printf("%d ", current);

        NODE *temp = graph->adjacency_lists[current];
        while (temp)
        {
            int adj_vertex = temp->data;
            if (graph->visited[adj_vertex] == 0)
            {
                graph->visited[adj_vertex] = 1;
                enqueue(&queue, adj_vertex);
            }
        temp = temp->next;
        }
    }
}

int main()
{

    int nr_of_node_count;
    int nr_of_edges;
    int starting_vertex;
   
    printf("Cate noduri are graful? ");
    scanf("%d", &nr_of_node_count);
    
    printf("Cate muchii are graful? ");
    scanf("%d", &nr_of_edges);
    
    GPH *graph = create_graph(nr_of_node_count);

    read_edges(nr_of_node_count, nr_of_edges, graph);

    printf("De unde plecam in DFS? ");
    scanf("%d", &starting_vertex); 
    printf("Parcurgere cu DFS: ");
    DFS(graph, starting_vertex);
    printf("\n");

    reset_visited(graph, nr_of_node_count);


    printf("De unde plecam in BFS? ");
    scanf("%d", &starting_vertex);

    printf("Parcurgere cu BFS: ");
    BFS(graph, starting_vertex);


return 0;
}
