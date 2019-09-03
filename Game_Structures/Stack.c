/*
 * Stack.c
 *
 *  Created on: Aug 7, 2019
 *      Author: Owner
 */
#include "../include_file.h"

void free_Stack_Node(Stack_Node* node) {
	free(node);
}

Stack* stack_generate() {
    /*
     * create Stack.
     * if malloc failed return NULL.
     */
	Stack* stack = malloc(sizeof(Stack));
	if (!stack) return NULL;
	stack->top = NULL;
	return stack;
}

int stack_is_empty(Stack* stack) {
	if (stack->top == NULL) return 1;
	return 0;
}
void* stack_pop(Stack* stack) {
	/*
	 * pop last element
	 * if empty - return NULL
	 */
	Stack_Node* out_node; void* result;
	if (stack->top == NULL) return NULL;
	out_node = stack->top;
	stack->top = out_node->prev;
	result = out_node->data;
	free_Stack_Node(out_node);
	return result;
}
int stack_push(Stack* stack, void* element) {
    /*
     * return 1 is succeed.
     * 0 if malloc failed.
     */
	Stack_Node* in_node = malloc(sizeof(Stack_Node));
	if (!in_node) return 0;
	in_node->data = element;
	in_node->prev = stack->top;
	stack->top = in_node;
	return 1;
}
void* stack_peek(Stack* stack) {
	if (stack->top == NULL) return NULL;
	return stack->top->data;
}

void stack_free(Stack* stack) {
	Stack_Node* node = stack->top;
	while (node!=NULL) {
		stack->top = node->prev;
		free(node); node = stack->top;
	}
	free(stack);
}
