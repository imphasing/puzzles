#include <stdio.h>
#include <malloc.h>
#include "graph.h"

// first 3 3x3 groups, in a row
int initial_groups[3][9] = {
	{0,1,2, 9,10,11, 18,19,20},
	{27,28,29, 36,37,38, 45,46,47},
	{54,55,56, 63,64,65, 72,73,74}
};

struct graph *load_initial()
{
	// load sudoku puzzle in from stdin
	int puzzle_size = 9;
	int num_chars = (puzzle_size * puzzle_size) + 1;
	int num_boxes = puzzle_size * puzzle_size;

	char *buffer = malloc(sizeof(char) * num_chars);
	fgets(buffer, num_chars, stdin);


	struct graph *graph = create_graph();
	struct vertex **vertices = malloc(sizeof(void *) * num_boxes);

	// set up the graph with the vertices
	int i = 0;
	int j = 0;
	for (i = 0; i < num_boxes; i++)
		vertices[i] = add_vertex(graph, buffer[i] - '0');

	// generate 3x3 groups from initial data
	int three_groups[9][9];
	for (i = 0; i < 9; i++) {
		int factor = 0;
		if (i > 2 && i < 6)
			factor = 1;
		else if (i > 5)
			factor = 2;

		for (j = 0; j < 9; j++) {
			three_groups[i][j] = initial_groups[i % 3][j] + (factor * 3);
		}
	}

	// generate row and column groups
	int row_groups[9][9];
	int col_groups[9][9];
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {
			row_groups[i][j] = (i * 9) + j;
			col_groups[i][j] = (j * 9) + i;
		}
	}

	return graph;
}
		

int main(int argc, char **argv)
{
	load_initial(9);
}
