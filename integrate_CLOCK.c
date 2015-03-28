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

main() {
	int arr[] = { 1, 3, 6, 2, 4, 5, 2, 5, 0, 3, 1, 2, 5, 4, 1,0 };
	int i;
	int n = 3;
	intialize_linked_list(n);
	display_linked_list(n);
	for (i = 0; i < 16; i++) {
		insertFrame_clock(n, arr[i]);
		display_linked_list(n);
	}

	printf("END\n");
}

int getPointerLocation(int n){
    struct node *ptr = start;
    int i =0;
    int framePointer = -1;
    while(ptr != NULL)
    {
	if(i<n){
		if(ptr->flag == true){
			framePointer = i;
			break;
		}
		else{
			i = i + 1;
        		ptr = ptr->next;
		}
	}
	else break;
    }

return framePointer;
}

checkIfRefBitIsZero(int n){
   struct node *ptr = start;
    int i =0;
    int frameWithRefBitOne = -1;
    while(ptr != NULL)
    {
	if(i<n){
		if(ptr->ref_bit == 0){
			frameWithRefBitOne = i;
			break;
		}
		else{
			i = i + 1;
        		ptr = ptr->next;
		}
	}
	else break;
    }

return frameWithRefBitOne;

}


pageReplacement(int pagenumber,int n){
	printf("In PAGE REPLACEMENT!!!");
	struct node*ptr = start;
        int i=0;
	int framePointer = getPointerLocation(n);
	printf("Frame Points to %d \n",framePointer);

	int frameWithRefBitIsZero = checkIfRefBitIsZero(n);
	printf("Frame contains Reference Bit is ZERO? [%d]\n",frameWithRefBitIsZero);

	if(frameWithRefBitIsZero == -1){ //No frame contains a reference bit zero. Replace all 1->0.
		while(ptr != NULL)
   			{
				if(i<n){
				if(i==framePointer){
					int j=0;
					while(j<n){
					ptr->flag = false;
					ptr = ptr->next;
					ptr->ref_bit = 0;
					j = j+1;
					}
					ptr = ptr->next;
					ptr->ref_bit = 1;
					ptr->flag = true;
					ptr->data = pagenumber;
				}
				else{
					ptr = ptr->next;
					//DO NOTHING.
				}
				i = i+1;
				}
				else{
					break;
				}

    			}

	}
	else{    //There is a frame which has reference bit zero.framePointer=0
		while(ptr != NULL)
   			{
				if(i<n){
				if(i==framePointer){
					ptr = ptr->next;
					ptr->ref_bit = 1;
					ptr->flag = true;
					ptr->data = pagenumber;

				}
				else{
					ptr = ptr->next;
					ptr->flag = false;
					//DO NOTHING.
				}
				i=i+1;
				}
				else{
					break;
				}
			}
	}
/*
    while(ptr != NULL)
    {

    } */
	printf("Pointer Movements are [%d] \n",i+1);

}


insertFrame_clock(int totalPages, int pageNumber) {
	printf("Page Number = %d\n", pageNumber);
	int numberofEmptyFrames = emptyFrames(totalPages);
	printf("EMPTY=[%d]\n", numberofEmptyFrames);
	int hit = hitFault(pageNumber);
	printf("HIT=1;FAULT=0 :- [%d]\n", hit);
	struct node *new_node;
	new_node = start;
	if (!hit) {
		do {
			if (new_node->data == -1) {
				new_node->data = pageNumber;
				new_node->ref_bit = 1;
				new_node->flag = true;
				break;
			} else if (numberofEmptyFrames > 0) {
				new_node->flag = false;
				new_node = new_node->next;
			} else if (numberofEmptyFrames == 0) {
				printf("Clock-PageReplacement");
				pageReplacement(pageNumber,totalPages);
			}
		} while (new_node != start);
	} else {
		printf("HIT and incremented flag !");
	}
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

void display_linked_list(int n) {

	struct node *new_node = start;

	printf("\n ----[DISPLAY METHOD]---Printing list Start------- \n");
	int i = 0;

	do {
		if (i < n) {
			printf("VALUE = [%d] and FRAME [%d] and Reference Bit[%d] with POINTER[%d] \n",
					new_node->data, i, new_node->ref_bit,new_node->flag);
			i = i + 1;
			new_node = new_node->next;
		} else
			break;
	} while (new_node != NULL);

	printf("\n ----[DISPLAY METHOD]---Printing list End------- \n");

}
int hitFault(int pageNumber) {
	struct node *new_node = start;
	int hit = 0;

	do {
		if (new_node->data == pageNumber) {
			hit = 1;
			break;
		} else {
			new_node = new_node->next;
		}

	} while (new_node != start);

	return hit;
}

int emptyFrames(int n) {
	int count = 0;

	struct node *new_node = start;

	do {
		if (new_node->data == -1) {
			count = count + 1;
		}
		new_node = new_node->next;
	} while (new_node != start);

	return count;
}
