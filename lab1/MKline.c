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
//node *head = NULL;
node createNode(){
	node temp;
	temp = (malloc(sizeof(struct LL)));
	temp->next = NULL;
	return temp;
}

void addNode(node head, int x){
	node temp;
	node p;
	temp = createNode();
	temp->data = x;
	if(head == NULL){
		head = temp;
	}
	else{
		/*p = head;
		while(p->next != NULL){
			p = p->next; //makes current Node last node
		}
		p->next = temp; */
		p = head;
		head = temp;
		head->next = p;
	}
	//return head;
}

int isEmpty(node head){
	if(head == NULL)
		return 1;
	else
		return 0;
}

void popNode(node head){
	node temp;
	if(head != NULL){
		temp = head;
		head = head->next;
	}
	else
		head = NULL;
	//return head;
}

int main(){
	int x = 0;
	int y;
	struct LL *head;
	head = NULL;
	printf("This program allows you to add, remove, and check to see if a linked list is empty.\n");
	while(x != 4){
		printf(" To add a number to the list press 1 \n To remove the top node from the list press 2 \n To check if the list is empty press 3 \n To exit this program press 4.\n");
 		scanf("%d",&x);
		if(x == 1){
			printf("What number would you like to add to the list?\n");
			scanf("%d",&y);
			addNode(&head, y);
		}
		else if(x == 2){
			popNode(&head);
		}
		else if(x == 3){
			int b;
			b = isEmpty(&head);
			printf("%d\n",b);
			if(b == 1){
				printf("The list is empty\n");
			}
			else{
				printf("The list has at least 1 item\n");
			}
		}
		else if(x == 4){
			printf("Goodbye\n");
		}
		else{
			printf("You failed to input a correct option.\n");
		}


	}
	return 0; 
}
