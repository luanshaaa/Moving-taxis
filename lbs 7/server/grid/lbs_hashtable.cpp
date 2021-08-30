//
//  lbs_hashtable.cpp
//  
//
//  Created by Runze Chen on 2018/2/7.
//

#include "lbs_hashtable.h"

#include <stdlib.h>

int lbs_hashtable_init(lbs_hashtable_t* lbs_hashtable) {
    lbs_hashtable->capacity = 20000;
    lbs_hashtable->size = 0;
    lbs_hashtable->hash_nodes = (lbs_hashnode_t*)malloc(sizeof(lbs_hashnode_t) * lbs_hashtable->capacity);
    for (int i = 0; i < lbs_hashtable->capacity; i++) {
        lbs_queue_init(&(lbs_hashtable->hash_nodes[i].queue));
    }
    return 0;
}

int lbs_hashtable_destory(lbs_hashtable_t* lbs_hashtable) {
    free (lbs_hashtable->hash_nodes);
    lbs_hashtable->hash_nodes = NULL;
    lbs_hashtable->capacity = 0;
    lbs_hashtable->size = 0;
    return 0;
}


int hash(uint32_t id) {
    return id%20000;
}

int lbs_hashtable_set(lbs_hashtable_t* lbs_hashtable, uint32_t id, lbs_mov_node_t* lbs_move_node, int cell_id) {
    int index = hash(id);
    
    lbs_hashnode_t* node = (lbs_hashnode_t*)malloc(sizeof(lbs_hashnode_t));
    node->cell_id = cell_id;
    node->mov_node = lbs_move_node;

    lbs_queue_insert_head(&(lbs_hashtable->hash_nodes[index].queue) , &(node->queue));
    return 0;
}

lbs_hashnode_t* lbs_hashtable_get(lbs_hashtable_t* lbs_hash_table, uint32_t id) {
    int index = hash(id);
    lbs_hashnode_t *head = (lbs_hashnode_t*)&(lbs_hash_table->hash_nodes[index].queue);
    lbs_hashnode_t *current = (lbs_hashnode_t*)head->queue.next;
    while(head != current) {
        if (current->mov_node->id == id) {
            return current;
        }
        current = (lbs_hashnode_t*)current->queue.next;
    }
    return NULL;
}

