/*
Matthew Kline
Lab1 CPSC 405
*/
#include <stdio.h>


struct LL{
	int x;
	struct LL *next;
};
typedef struct LL *node; //making a pointer
node top; // public node to save and call through out program

node createNode(){
	node temp;
	temp = node(malloc(sizeof(struct LL));
	temp->next = NULL;
	return temp;
}

node addNode(node head, int x){
	node temp;
	node p;
	temp = createNode();
	temp->data = value;
	if(head == NULL){
		head = temp;
	}
	else{
		p = head;
		while(p->next != NULL){
			p = p->next; //makes current Node last node
		}
		p->next = temp;
	}
	top = head; //Makes the top node stored
	return head;
}


