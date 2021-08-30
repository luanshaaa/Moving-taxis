#include "server/grid/lbs_index.h"

#include <stdio.h>
#include <stdlib.h>

#include "common/log.h"

#include "server/grid/lbs_distance.h"

#define LBS_LON_MIN 116
#define LBS_LON_MAX 117
#define LBS_LAT_MIN 39
#define LBS_LAT_MAX 41

#define LBS_ROW_NUM 200
#define LBS_COL_NUM 100

#include "lbs_grid.h"

#include "get_cell_id.h"
#include "calculate_distance.h"
#include "lbs_bitmap.h"
#include "SERVER_GRID_LBS_NN_HEAP.h"

static lbs_grid_t lbs_grid; 

// 初始化网格索引
int lbs_grid_index_init() {
  lbs_grid_init(&lbs_grid, LBS_LON_MIN, LBS_LON_MAX, LBS_LAT_MIN, LBS_LAT_MAX, LBS_ROW_NUM, LBS_COL_NUM);
  return 0;
}

// 更新接口[出租车位置更新]
int lbs_grid_index_update(double lon,
                           double lat,
                           uint64_t timestamp,
                           uint32_t id) {
  lbs_grid_update(&lbs_grid, lon, lat, timestamp, id);
  // TODO: by student
  return 0;
}

// 范围查询接口[查询某一范围内的所有出租车信息]
int lbs_grid_index_range_query(double lon1,
                               double lon2,
                               double lat1,
                               double lat2,
                               lbs_res_node_t* out) {
    int row1= lbs_grid_cell_row(&lbs_grid,lat1);
    int col1= lbs_grid_cell_col(&lbs_grid,lon1);
    int row2= lbs_grid_cell_row(&lbs_grid,lat2);
    int col2= lbs_grid_cell_col(&lbs_grid,lon2);
    for(int row=row1;row<=row2;row++)
    {
        for(int col=col1;col<=col2;col++)
        {
            int cell_id = lbs_grid_cell_id(&lbs_grid,row,col);
            lbs_mov_node_t *head = &(lbs_grid.cell[cell_id].dammy_node);
            lbs_mov_node_t *current = (lbs_mov_node_t *)head->queue.next;
            while(current!=head){
                if(current->lon>=lon1 && current->lon<=lon2 && current->lat>=lat1 && current->lat<=lat2){
                    lbs_res_node_t* node = (lbs_res_node_t*)malloc(sizeof(lbs_res_node_t));
                    node->lon= current->lon;
                    node->lat= current->lat;
                    lbs_queue_insert_head(&(out->queue), &(node->queue));
                }
            current = (lbs_mov_node_t*)current->queue.next;
              
            }
        }
    }
  // TODO: by student
    
  return 0;
}

// NN查询接口[查询离lon,lat最近的出租车]
int lbs_grid_index_nn_query(double lon, double lat, lbs_res_node_t* out) {
    // TODO: by student
    
    //计算查询q所在的网格
    int row=lbs_grid_cell_row(&lbs_grid,lat);
    int col=lbs_grid_cell_col(&lbs_grid,lon);
    int cell_id=lbs_grid_cell_id(&lbs_grid,row,col);
    //Mindist=0
    int Mindist=lbs_min_distance(&lbs_grid,cell_id,lon,lat);

    lbs_nnheap_t lbs_nnheap;
    lbs_bitmap_t lbs_bitmap;

    //创建小顶堆
    lbs_nnheap_init(&lbs_nnheap);
    lbs_bitmap_init(&lbs_bitmap, lbs_grid.row_num * lbs_grid.col_num);

    lbs_bitmap_setbit(&lbs_bitmap, cell_id);
    printf("start insert heap\n");
    lbs_nnheap_insert(&lbs_nnheap, NULL, cell_id, 1, Mindist);
    printf("end insert heap\n");
    
    while ((&lbs_nnheap)->heap_nodes[0].is_grid != 0) {
        int grid_cell_id = (&lbs_nnheap)->heap_nodes[0].cell_id;
        printf("start pop\n");
        lbs_nnheap_pop(&lbs_nnheap);
        printf("end pop\n");

        /// Step1: insert cars in cell
        lbs_cell_t* head =lbs_grid_cell(&lbs_grid, grid_cell_id);
        lbs_mov_node_t *cur = (lbs_mov_node_t*)head->dammy_node.queue.next;
        while(cur!= &(head->dammy_node))
        {    //q与空间点的距离
            double dis=lbs_distance(lon,lat, cur->lon, cur->lat) ;
            //将空间点插入小顶堆
            printf("start insert heap\n");
            lbs_nnheap_insert(&lbs_nnheap, cur, grid_cell_id, 0, dis);
            printf("end insert heap\n");
            cur= (lbs_mov_node_t*)cur->queue.next;
        }
        /*求周围的cell_id*/
        int a[8];
        lbs_get_cell_id(&lbs_grid, grid_cell_id, a);
        /*计算到周围格子的距离并放入堆*/
           
        for(int i=0; i<8; i++){
          double dis = lbs_min_distance(&lbs_grid,a[i],lon,lat);
          if(lbs_bitmap_isset(&lbs_bitmap, a[i]) == 0)    {
                    lbs_nnheap_insert(&lbs_nnheap, NULL,a[i],1, dis);
                    lbs_bitmap_setbit(&lbs_bitmap,a[i]);
            
          }    
        }
        printf("grid_cell_id=%d\n", grid_cell_id);
    }

    lbs_res_node_t* node = (lbs_res_node_t*)malloc(sizeof(lbs_res_node_t));
    node->lon = lbs_nnheap.heap_nodes[0].node->lon;
    node->lat = lbs_nnheap.heap_nodes[0].node->lat;
    lbs_queue_insert_head(&(out->queue), &(node->queue));
    
    return 0;
       //return &lbs_nnheap->heap_nodes[0];
}
    

