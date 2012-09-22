#include <stdio.h>

int main(int argc, char **argv)
{
	int array[][3] = { 
		{1, 2, 3},
		{4, 5, 6},
		{7, 8, 9}
	};

	int rotated[3][3];

	int size = 3;
	int i, j;
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			rotated[j][i] = array[i][j];
		}
	}

	for (i = 0; i < size; i++) {
		for (j = 0; j < size/2; j++) {
			int temp = rotated[i][j];
			rotated[i][j] = rotated[i][size - 1 - j];
			rotated[i][size - 1 - j] = temp;
		}
	}
			
			
	
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++)
			printf("%d, ", rotated[i][j]);

		printf("\n");
	}
}
