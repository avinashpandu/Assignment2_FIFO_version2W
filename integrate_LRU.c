#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

struct node {
	int data;
	int fix_count;
	bool dirty_bit;
	int originalval;
	int ref_bit;
	bool flag;
	struct node *next;
}*new_node, *current, *last, *temp;

struct node * start;

int position = 0;

main() {
	int arr[] = { 0, 1, 2, 3, 4, 3, 4, 0, 2, 1, 5, 6, 7, 8, 9 };
	//int arr[] = { 2,3,4,2,1,3,7,5,4,3};
	int i;
	int n = 5;
	intialize_linked_list(n);
	display_linked_list(n);
	for (i = 0; i < 15; i++) {
		insertFrame_lru(n, arr[i]);
		insertFrame_clock(n,arr[i]);
		display_linked_list(n);
	}
	printf("END\n");
}

insertFrame_lru(int totalPages, int pageNumber) {
	printf("Page Number = %d\n", pageNumber);
	int numberofEmptyFrames = emptyFrames(totalPages);
	printf("EMPTY=[%d]\n", numberofEmptyFrames);
	int hit = hitFault(pageNumber);
	printf("HIT=1;FAULT=0 :- [%d]\n",hit);
	struct node *new_node;
	new_node = start;
	if (!hit) {
		do {
			if (new_node->data == -1) {
				new_node->data = pageNumber;
				new_node->flag = 0;
				new_node->ref_bit = position;
				position = position + 1;
				break;
			} else if (numberofEmptyFrames > 0) {
				new_node = new_node->next;
			} else if (numberofEmptyFrames == 0) {
				printf("LRU-PageReplacement");
				int pagePositionToReplace = findNextVictim(pageNumber);
				if(new_node->ref_bit == pagePositionToReplace){
						new_node->data = pageNumber;
						new_node->ref_bit = position;
						position = position + 1;
						break;
				}
				new_node = new_node->next;
			}
		} while (new_node != start);
	} else {
		printf("HIT and incremented flag !");
	}
}

int findNextVictim(){
	struct node *new_node = start;
	int min = new_node->ref_bit;
	int victim ;
	do{
		if(new_node->ref_bit < min){
			min = new_node->ref_bit;
		}
		new_node= new_node->next;

	}while(new_node != start);

	return min;
}

int hitFault(int pageNumber) {
	struct node *new_node = start;
	int hit = 0;

	do {
		if (new_node->data == pageNumber) {
			new_node->flag = new_node->flag + 1;
			new_node->ref_bit = position;
			position = position + 1;
			hit = 1;
			break;
		} else {
			new_node = new_node->next;
		}

	} while (new_node != start);

	return hit;
}

intialize_linked_list(int n) {
	printf("In initialize method");
	struct node *new_node;
	int i;
	//start = NULL;
	for (i = 0; i < n; i++) {
		new_node = (struct node *) malloc(sizeof(struct node));
		if (new_node == NULL) {
			printf("Node creation failed");

		}
		new_node->data = -1;     // -99 = NULL or Empty Characcter
		new_node->next = NULL;
		//new_node->bm_ph.pageNum = -1;
		//new_node->bm_ph.data = NULL;
		new_node->fix_count = 0;
		new_node->dirty_bit = 0;
		if (start == NULL || start->data != -1) {
			start = new_node;
			current = new_node;
		} else {
			current->next = new_node;
			current = new_node;
		}
	}
	current->next = start;

}

int emptyFrames(int n) {
	int count = 0, i = 0;

	struct node *new_node = start;

	do {
		if (new_node->data == -1) {
			count = count + 1;
		}
		new_node = new_node->next;
	} while (new_node != start);

	return count;
}

void display_linked_list(int n) {

	struct node *new_node = start;

	printf("\n ----[DISPLAY METHOD]---Printing list Start------- \n");
	int i = 0;

	do {
		if (i < n) {
			printf(
					"VALUE = [%d] and FRAME [%d] and Fix Count [%d] and Count [%d] with position [%d] \n",
					new_node->data, i, new_node->fix_count, new_node->flag , new_node->ref_bit);
			i = i + 1;
			new_node = new_node->next;
		} else
			break;
	} while (new_node != NULL);

	printf("\n ----[DISPLAY METHOD]---Printing list End------- \n");

}
