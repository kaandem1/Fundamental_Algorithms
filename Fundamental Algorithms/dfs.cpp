#include <stdio.h>
#include <stdlib.h>

/**
 * @author Demirezenler Bilge Kaan
 * @group 30421
 *
 * Assignment requirements: correctly and efficiently implement the depth first search algorithm (DFS)
 * THE TIME COMPLEXITY FOR DFS IS O(V+E)
 * 

 *
 */

enum {
    COLOR_WHITE = 0,
    COLOR_GRAY,
    COLOR_BLACK
};

typedef struct _Node {
    int value;
    int adjSize;
    struct _Node** adj;

    int color;
    int discover_time;
    int finish_time;
    struct _Node* parent;
}Node;

typedef struct {
    int nrNodes;
    Node** v;
}Graph;

int time;

void dfs_visit(Node* u) //FUNCTION TO VISIT NODES IN THE GRAP
{
    time++;
    u->discover_time = time;
    u->color = COLOR_GRAY;
    for (int i = 0; i < u->adjSize; i++)
    {
        Node* v = u->adj[i];
        if (v->color == COLOR_WHITE)
        {
            v->parent = u;
            dfs_visit(v);
        }

    }
    u->color = COLOR_BLACK;
    time++;
    u->finish_time = time;
}

void dfs(Graph* g) //THE DFS 
{   
    time = 0;
    for (int i = 0; i < g->nrNodes; i++)
    {
        Node* u = g->v[i];
        u->color = COLOR_WHITE;
        u->parent = NULL;
        u->discover_time = u->finish_time = 0;

    }
    for (int i = 0; i < g->nrNodes; i++)
    {
        Node* u = g->v[i];
        if (u->color == COLOR_WHITE)
        {
            dfs_visit(u);
        }

    }
}

Graph createG(int nrNodes) {
    Graph g;
    g.nrNodes = nrNodes;
    g.v = (Node**)malloc(nrNodes * sizeof(Node*));
    for (int i = 0; i < g.nrNodes; i++)
    {
        g.v[i] = (Node*)malloc(sizeof(Node));
        g.v[i]->value = i;
        g.v[i]->adjSize= 0;
        g.v[i]->adj = (Node**)malloc(nrNodes * sizeof(Node*));
    }

    return g;
}

void free_graph(Graph* g) {
    for (int i = 0; i < g->nrNodes; i++)
    {
        free(g->v[i]->adj);
        free(g->v[i]);
    }
    free(g->v);
}

void addEdge(Graph* g, int x, int y) { //ADD EDGES TO THE GRAPH
    g->v[x]->adj[g->v[x]->adjSize] = g->v[y];
    g->v[x]->adjSize++;
}



int main()
{
    Graph g = createG(5);
    addEdge(&g, 0, 1);
    addEdge(&g, 0, 3);
    addEdge(&g, 1, 2);
    addEdge(&g, 2, 3);
    addEdge(&g, 3, 1);
    addEdge(&g, 4, 3);
    for (int i = 0; i < g.nrNodes; i++){
        printf("%d: ", i);
        for (int j = 0; j < g.v[i]->adjSize; j++) {
            printf("%d ", g.v[i]->adj[j]->value);
        }
        printf("\n");
    }

    dfs(&g);
    for (int i = 0; i < g.nrNodes; i++) {
        printf("Node: %d, parent: %d\n", i, g.v[i]->parent ? g.v[i]->parent->value : -1);
    }

    free_graph(&g);
}
