 //
//  Header.h
//  
//
//  Created by Runze Chen on 2018/2/9.
//

#ifndef Header_h
#define Header_h
#include "lbs_grid.h"
#include "lbs_distance.h"

inline double lbs_min_distance(lbs_grid_t* lbs_grid, int cell_id, double lon, double lat) {
    int cell_row, cell_col;
    lbs_grid_cell_row_col(lbs_grid, cell_id, &cell_row, &cell_col);
    
    double lat_min = lbs_grid->lat_min + cell_row * lbs_grid->cell_height;
    double lon_min = lbs_grid->lon_min + cell_col * lbs_grid->cell_width;
    double lat_max = lat_min + lbs_grid->cell_height;
    double lon_max = lon_min + lbs_grid->cell_width;
    
    if(lon > lon_max ) {
        if(lat > lat_max){
            return lbs_distance (lon, lat, lon_max, lat_max);
        }
        if(lat < lat_max && lat > lat_min){
            return lbs_distance(lon, lat, lon_max, lat);
        }
        else{
            return lbs_distance(lon, lat, lon_min, lat_min);
        }
    } if(lon < lon_max && lon > lon_min) {
        if(lat > lat_max){
            return lbs_distance(lon, lat, lon, lat_max);
        }
        if(lat < lat_max && lat > lat_min){
            return 0;
        }
        else{
            return lbs_distance(lon, lat, lon, lat_max);
        }
    } else {
        if(lat > lat_max){
            return lbs_distance (lon, lat, lon_min, lat_max);
        }
        if(lat < lat_max && lat > lat_min){
            return lbs_distance(lon, lat, lon_min, lat);
        }
        else{
            return lbs_distance (lon, lat, lon_min, lat_min);
            
        }
    }
}




#endif /* Header_h */
