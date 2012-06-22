
struct graph {
	struct vertex *vertices;
};

struct vertex {
	int element;
	struct edge *edges;
	struct vertex *next;
};


struct edge {
	struct vertex *connectsTo;
	struct edge *next;
};


struct graph *create_graph();
struct vertex *add_vertex(struct graph *graph, int value);
void add_edge(struct vertex *vertexA, struct vertex *vertexB);
void print_graph(struct graph *graph);
