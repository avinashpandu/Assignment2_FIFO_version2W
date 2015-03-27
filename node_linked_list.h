/*
 * node_linked_list.h
 *
 *  Created on: Mar 23, 2015
 *      Author: vjonnala and team
 */

#ifndef NODE_LINKED_LIST_H_
#define NODE_LINKED_LIST_H_

#include<stdio.h>
#include<stdlib.h>
#include "buffer_mgr.h"
//#include "storage_mgr.h"


struct node {
	int data;
	BM_PageHandle bm_ph;
	int fix_count;
	bool dirty_bit;
	int originalval;
	int ref_bit;
	bool flag;
	struct node *next;
}*new_node, *current, *last, *temp;

struct BM_statistics {

	PageNumber *frameContents;
	bool *dirty_bit_stats;
	int *fix_count_stats;
	int numReadIO ;
	int numWriteIO ;

}stats_data;

RC intialize_linked_list(int n);

void display_linked_list(int n);

struct node* return_frame_linked_list(int pageNumber,int n);

int search_linked_list(int pageNumber,int n);

void insertFrame_linked_list(BM_BufferPool * const bm, int pageNumber);//fifo


#endif

/* NODE_LINKED_LIST_H_ */
