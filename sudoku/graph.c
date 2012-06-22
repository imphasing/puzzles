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

void add_edge(struct vertex *vertexA, struct vertex *vertexB)
{
	struct edge **last = &vertexA->edges;
	while (*last != NULL)
		last = &(*last)->next;
	
	*last = malloc(sizeof(struct edge));
	(*last)->connectsTo = vertexB;
	(*last)->next = NULL;
}

void print_graph(struct graph *graph)
{
	struct vertex *lastVertex = graph->vertices;
	
	while (lastVertex != NULL)
	{
		printf("Vertex: %d connects to: ", lastVertex->element);

		struct edge *lastEdge = lastVertex->edges;

		while (lastEdge != NULL)
		{
			if (lastEdge->connectsTo != NULL)
				printf("%d, ", lastEdge->connectsTo->element);

			lastEdge = lastEdge->next;
		}

		puts("\n");

		lastVertex = lastVertex->next;
	}
}

