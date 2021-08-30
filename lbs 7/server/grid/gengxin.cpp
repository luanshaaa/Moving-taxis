//
//  asd.cpp
//  
//
//  Created by apple on 2018/2/8.
//
#include"lbs_grid.h"

#include <stdlib.h>

int lbs_grid_update(lbs_grid_t* lbs_grid,double lon,double lat,uint64_t timestamp,uint32_t id)
{
    lbs_hashnode_t* p;
    lbs_mov_node_t* q;

    //计算lon lat对应的col row
    int row1 = lbs_grid_cell_row(lbs_grid, lat);
    int col1 = lbs_grid_cell_col(lbs_grid, lon);
    //算出lon lat对应的cell id
    int cell_id=lbs_grid_cell_id(lbs_grid, row1, col1);
    //遍历hash表
    p = lbs_hashtable_get(&lbs_grid->hash_table, id);
    
    if (p)
    {
        //修改数据
        p->mov_node->lon=lon;
        p->mov_node->lat=lat;
        p->mov_node->timestamp=timestamp;
        
        if (p->cell_id != cell_id)
        {
          lbs_queue_remove(&p->mov_node->queue);
          lbs_queue_insert_head(&lbs_grid->cell[cell_id].dammy_node.queue,
                                &p->mov_node->queue);
          p->cell_id = cell_id;
        }
    }
    else//没找到就执行5
    {
        q=(lbs_mov_node_t*)malloc(sizeof(lbs_mov_node_t));

        q->lon=lon;
        q->lat=lat;
        q->id=id;
        q->timestamp=timestamp;
        
        lbs_queue_insert_head(&lbs_grid->cell[cell_id].dammy_node.queue,
                                &q->queue);
        
        lbs_hashtable_set(&lbs_grid->hash_table, id, q, cell_id);
    }
    return 0;
}
    
