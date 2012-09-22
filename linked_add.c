#include <stdio.h>
#include <stdlib.h>

typedef struct node node;
struct node {
	node *next;
	int digit;
};


node *create_node(int digit)
{
	node *node = malloc(sizeof(node));
	node->next = NULL;
	node->digit = digit;

	return node;
}


node *add_lists(node *first, node *second, int carry)
{
	int added;
	if (first == NULL && second == NULL)
		return carry == 0 ? NULL : create_node(carry);
	else if (first == NULL && second != NULL)
		added = second->digit + carry;
	else if (first != NULL && second == NULL)
		added = first->digit + carry;
	else
		added = first->digit + second->digit + carry;

	int digit_value = added > 9 ? added - 10 : added;
	int to_carry = added > 9 ? 1 : 0;

	node *partial = create_node(digit_value);

	node *first_after = first == NULL ? NULL : first->next;
	node *second_after = second == NULL ? NULL : second->next;

	partial->next = add_lists(first_after, second_after, to_carry);

	return partial;
}


int main(int agc, char **argv)
{
	// 6 -> 8 -> 3 -> 7 + 0 -> 5 -> 7 == 7386 + 750 = 8136
	node *first = create_node(6);
	first->next = create_node(8);
	first->next->next = create_node(3);
	first->next->next->next = create_node(7);

	node *second = create_node(0);
	second->next = create_node(5);
	second->next->next = create_node(7);

	node *result = add_lists(first, second, 0);

	node *next = result;
	while (next != NULL) {
		printf("%d", next->digit);
		next = next->next;
	}
	printf("\n");
}




