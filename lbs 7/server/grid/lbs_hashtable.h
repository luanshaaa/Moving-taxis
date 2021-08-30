//
//  lbs_hashtable.h
//  
//
//  Created by Runze Chen on 2018/2/7.
//

#ifndef H_HASHTABLE_H_
#define H_HASHTABLE_H_

#include <pthread.h>//线程之间同步

#include "server/grid/lbs_defs.h"

typedef struct lbs_hashnode_s {
    //链表
    lbs_queue_t queue;
    //节点
    lbs_mov_node_t* mov_node;
    //cell id
    int cell_id;
    
} lbs_hashnode_t;

typedef struct lbs_hashtable_s {
    //锁
    pthread_mutex_t mutex;
    //已占用
    int size;
    //容量
    int capacity;
    //哈西-链地址
    lbs_hashnode_t* hash_nodes;
    
} lbs_hashtable_t;

//初始化
int lbs_hashtable_init(lbs_hashtable_t* lbs_hashtable);
//销毁
int lbs_hashtable_destory(lbs_hashtable_t* lbs_hash_table);
//设置
int lbs_hashtable_set(lbs_hashtable_t* lbs_hashtable, uint32_t id, lbs_mov_node_t* lbs_mov_node, int cell_id);
//提取
lbs_hashnode_t* lbs_hashtable_get(lbs_hashtable_t* lbs_hash_table, uint32_t id);

#endif
