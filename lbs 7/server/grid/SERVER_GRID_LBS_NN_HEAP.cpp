//
//  SERVER_GRID_LBS_NN_HEAP.cpp
//  
//
//  Created by Runze Chen on 2018/2/9.
//

#include <stdio.h>
#include <stdlib.h>
#include"SERVER_GRID_LBS_NN_HEAP.h"

int lbs_nnheap_init(lbs_nnheap_t* lbs_nnheap) {
    lbs_nnheap->capacity = 100;
    lbs_nnheap->size = 0;
    lbs_nnheap->heap_nodes = (lbs_heapnode_t*)malloc(sizeof(lbs_heapnode_t) * lbs_nnheap->capacity);
    return 0;
}

int lbs_nnheap_destroy(lbs_nnheap_t* lbs_nnheap) {
    free(lbs_nnheap->heap_nodes);
    lbs_nnheap->heap_nodes = NULL;
    lbs_nnheap->capacity = 0;
    lbs_nnheap->size = 0;
    return 0;
}

int lbs_nnheap_insert(lbs_nnheap_t* lbs_nnheap,
                      lbs_mov_node_t* lbs_mov_node,
                      int cell_id, uint8_t is_grid, double distance) {
    if (lbs_nnheap->size == lbs_nnheap->capacity) {
       lbs_nnheap->capacity *= 2;
       lbs_nnheap->heap_nodes = (lbs_heapnode_t*)realloc(lbs_nnheap->heap_nodes,
                                                         sizeof(lbs_heapnode_t) * lbs_nnheap->capacity);
    }

    lbs_nnheap->heap_nodes[lbs_nnheap->size].is_grid = is_grid;
    lbs_nnheap->heap_nodes[lbs_nnheap->size].distance = distance;
    lbs_nnheap->heap_nodes[lbs_nnheap->size].cell_id = cell_id;
    lbs_nnheap->heap_nodes[lbs_nnheap->size].node = lbs_mov_node;
    lbs_nnheap->size++;
    int i = lbs_nnheap->size;
    while(i > 1) {
        if(lbs_nnheap->heap_nodes[i - 1].distance < lbs_nnheap->heap_nodes[i/2 - 1].distance){
            lbs_heapnode_t a;
            a = lbs_nnheap->heap_nodes[i - 1];
            lbs_nnheap->heap_nodes[i - 1] = lbs_nnheap->heap_nodes[i/2 - 1];
            lbs_nnheap->heap_nodes[i/2 - 1] = a;
            i = i/2;
        } else {
          break;
        }
    }
    return 0;
}

lbs_heapnode_t* lbs_nnheap_top(lbs_nnheap_t* lbs_nnheap) {
    return &lbs_nnheap->heap_nodes[0];
}

void lbs_nnheap_pop(lbs_nnheap_t* lbs_nnheap) {
    int i =lbs_nnheap->size;
            lbs_nnheap->heap_nodes[0] = lbs_nnheap->heap_nodes[i - 1];
            lbs_nnheap->size = lbs_nnheap->size - 1;
            int a = 1;
            while(2*a <= i){
                int min = 2*a;
                if(2*a <= i - 1) {
                    if(lbs_nnheap->heap_nodes[2*a - 1].distance > lbs_nnheap->heap_nodes[2*a].distance) {
                        min = 2*a + 1;
                    }
                }
                if(lbs_nnheap->heap_nodes[a - 1].distance > lbs_nnheap->heap_nodes[min-1].distance) {
                    lbs_heapnode_t b;
                        b = lbs_nnheap->heap_nodes[min - 1];
                        lbs_nnheap->heap_nodes[min - 1] = lbs_nnheap->heap_nodes[a - 1];
                        lbs_nnheap->heap_nodes[a - 1] = b;
                        a = min;
                }
                else{
                    return;
                }
            }
}
                    
               /* if(lbs_nnheap->heap_nodes[a - 1].distance > lbs_nnheap->heap_nodes[2*a - 1].distance || lbs_nnheap->heap_nodes[a - 1].distance > lbs_nnheap->heap_nodes[2*a].distance){
                    lbs_heap_nodes b;
                    if(lbs_nnheap->heap_nodes[2*a - 1].distance > lbs_nnheap->heap_nodes[2*a].distance){
                    b = lbs_nnheap->heap_nodes[2*a];
                    lbs_nnheap->heap_nodes[2*a] = lbs_nnheap->heap_nodes[a - 1];
                    lbs_nnheap->heap_nodes[a - 1] = b;
                    a = 2*a;
                }
                    else {
                        b = lbs_nnheap->heap_nodes[2*a - 1];
                        lbs_nnheap->heap_nodes[2*a - 1] = lbs_nnheap->heap_nodes[a - 1];
                        lbs_nnheap->heap_nodes[a - 1] = b;
                        a = 2*a - 1;
                    }
                    
                    }
                else{
                    return 0;
                }
                }
                else{
                    if(lbs_nnheap->heap_nodes[a - 1].distance > lbs_nnheap->heap_nodes[2*a - 1].distance）{
                        b = lbs_nnheap->heap_nodes[2*a - 1];
                        lbs_nnheap->heap_nodes[2*a - 1] = lbs_nnheap->heap_nodes[a - 1];
                        lbs_nnheap->heap_nodes[a - 1] = b;
                        a = 2*a - 1;
                        else {
                            return 0;
                        }
                    }
                }
            }*/


