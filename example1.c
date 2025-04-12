#include <stdio.h>
#include <stdlib.h>

// Structura pentru nodul din lista de adiacență
typedef struct Node {
    int value;
    struct Node *next;
} Node;

// Structura pentru graf
typedef struct Graph {
    int num_vertices;
    Node **adjacency_list;
} Graph;

// Creează un nou nod în lista de adiacență
Node *create_node(int value) {
    Node *new_node = malloc(sizeof(Node));
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

// Creează un graf cu un număr specificat de noduri
Graph *create_graph(int num_vertices) {
    Graph *graph = malloc(sizeof(Graph));
    graph->num_vertices = num_vertices;
    graph->adjacency_list = malloc(sizeof(Node *) * num_vertices);
    for (int i = 0; i < num_vertices; i++) {
        graph->adjacency_list[i] = NULL;
    }
    return graph;
}

// Adaugă o muchie (legătură directă) între două restaurante
void add_edge(Graph *graph, int source, int destination) {
    Node *new_node = create_node(destination);
    new_node->next = graph->adjacency_list[source];
    graph->adjacency_list[source] = new_node;

    // Deoarece graful este neorientat, adăugăm și invers
    new_node = create_node(source);
    new_node->next = graph->adjacency_list[destination];
    graph->adjacency_list[destination] = new_node;
}

// Afișează lista de adiacență (opțional, pentru verificare)
void print_graph(Graph *graph) {
    for (int i = 0; i < graph->num_vertices; i++) {
        printf("Restaurant %d este conectat cu: ", i);
        Node *current = graph->adjacency_list[i];
        while (current) {
            printf("%d ", current->value);
            current = current->next;
        }
        printf("\n");
    }
}

// Verifică dacă două restaurante sunt conectate direct
int are_directly_connected(Graph *graph, int a, int b) {
    Node *current = graph->adjacency_list[a];
    while (current != NULL) {
        if (current->value == b)
            return 1; // există legătură directă
        current = current->next;
    }
    return 0; // nu există legătură directă
}

int main() {
    int num_vertices, num_edges;

    printf("Cate noduri are graful? ");
    scanf("%d", &num_vertices);

    printf("Cate muchii are graful? ");
    scanf("%d", &num_edges);

    Graph *graph = create_graph(num_vertices);

    // Citim muchiile dintre restaurante
    printf("Introdu %d perechi de noduri (numerotate de la 0 la %d):\n", num_edges, num_vertices - 1);
    for (int i = 0; i < num_edges; i++) {
        int a, b;
        printf("Legatura %d:", i + 1);
        scanf("%d %d", &a, &b);
        add_edge(graph, a, b);
    }

    int r1, r2;
    printf("Introdu doua restaurante pentru a verifica daca sunt conectate direct: ");
    scanf("%d %d", &r1, &r2);

    if (are_directly_connected(graph, r1, r2))
        printf("Exista drum direct intre restaurantul %d si restaurantul %d.\n", r1, r2);
    else
        printf("NU exista drum direct intre restaurantul %d si restaurantul %d.\n", r1, r2);

    return 0;
}
