/*
Matthew Kline
Lab1 CPSC 405
*/
#include <stdio.h>


struct LL{
	int data;
	struct LL *next;
};
typedef struct LL *node; //making a pointer

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
	return head;
}

int isEmpty(node head){
	if(head == NULL)
		return 1;
	else
		return 0;
}

node popNode(node head){
	node temp;
	if(head != NULL){
		temp = head;
		head = head->next;
	}
	else
		head = NULL;
	return head;
}


