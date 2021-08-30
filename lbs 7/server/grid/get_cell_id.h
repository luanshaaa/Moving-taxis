//
//  get_cell_id.h
//  
//
//  Created by Runze Chen on 2018/2/10.
//

#ifndef get_cell_id_h
#define get_cell_id_h
#include "lbs_grid.h"

inline void lbs_get_cell_id(lbs_grid_t* lbs_grid,int cell_id, int a[8]) {
    a[0] = cell_id + lbs_grid->col_num + 1;
    a[1] = cell_id + lbs_grid->col_num;
    a[2] = cell_id + lbs_grid->col_num - 1;
    a[3] = cell_id + 1;
    a[4] = cell_id - 1;
    a[5] = cell_id - lbs_grid->col_num + 1;
    a[6] = cell_id - lbs_grid->col_num;
    a[7] = cell_id - lbs_grid->col_num - 1;
}

#endif /* get_cell_id_h */

