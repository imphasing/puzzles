#include <stdlib.h>
#include <stdio.h>
#include "graph.h"

struct graph *create_graph()
{
	struct graph *created = malloc(sizeof(struct graph));
	created->vertices = NULL;

	return created;
}

struct vertex *add_vertex(struct graph *graph, int value)
{
	struct vertex **last = &graph->vertices;

	while (*last != NULL)
		last = &(*last)->next;

	*last = malloc(sizeof(struct vertex));
	(*last)->element = value;
	(*last)->next = NULL;
	(*last)->edges = NULL;

	return *last;
}

void add_edge(struct vertex *vertex1, struct vertex *vertex2)
{
	struct edge **last = &vertex1->edges;
	while (*last != NULL)
		last = &(*last)->next;
	
	*last = malloc(sizeof(struct edge));
	(*last)->connects_to = vertex2;
	(*last)->next = NULL;
}

void print_graph(struct graph *graph)
{
	struct vertex *last_vertex = graph->vertices;
	
	while (last_vertex != NULL) {
		printf("Vertex: %d connects to: ", last_vertex->element);

		struct edge *last_edge = last_vertex->edges;

		while (last_edge != NULL) {
			if (last_edge->connects_to != NULL)
				printf("%d, ", last_edge->connects_to->element);

			last_edge = last_edge->next;
		}

		printf("\n");

		last_vertex = last_vertex->next;
	}
}

