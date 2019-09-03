/*
 * Stack.h
 *
 *  Created on: Aug 7, 2019
 *      Author: Owner
 */

#ifndef GAME_STRUCTURES_STACK_H_
#define GAME_STRUCTURES_STACK_H_

struct Stack_Node {
  void* data;
  struct Stack_Node* prev;
};
typedef struct Stack_Node Stack_Node;

typedef struct {
	Stack_Node* top;
} Stack;

Stack* stack_generate();
int stack_is_empty(Stack* stack);
void* stack_pop(Stack* stack);
int stack_push(Stack* stack, void* element);
void* stack_peek(Stack* stack);
void stack_free(Stack* stack);


#endif /* GAME_STRUCTURES_STACK_H_ */
