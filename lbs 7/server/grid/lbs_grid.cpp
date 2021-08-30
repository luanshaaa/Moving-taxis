#include"server/grid/lbs_hashtable.h"
#include "server/grid/lbs_queue.h"
#include "server/grid/lbs_grid.h"

#include <stdlib.h>

//����ĳ�ʼ��
int lbs_grid_init(lbs_grid_t* lbs_grid, double lon1, double lon2, double lat1,double lat2, int row_num, int col_num)//����һ��lbs_grid_t���͵�lbs_grid 
{
	//lbs_grid_t����������һ���ṹ�壬��ʼ������ṹ��ĸ������������ԣ� 
	lbs_grid->row_num=row_num;
	lbs_grid->col_num=col_num ;
	lbs_grid->cell_width=(lon2-lon1)/col_num;
	lbs_grid->cell_height=(lat2-lat1)/row_num;
	lbs_grid->lon_min=lon1;
	lbs_grid->lat_min=lat1;
	lbs_hashtable_init(&(lbs_grid->hash_table)); 
	lbs_grid->cell=(lbs_cell_t*)malloc(row_num*col_num*sizeof(lbs_cell_t));//��ʼ��ͬʱ����ռ� 
	
	for(int i=0;i<row_num*col_num;i++)
	{   // ��ÿһ��cell��ʼ��ͷ��� 
		// p��prev nextָ��  queue�Ǳ��� 
		// ��ÿ��cell[i]��ͷ����queue�ĵ�ַ����pָ�� 
		lbs_queue_init(&(lbs_grid->cell[i].dammy_node.queue));		
	}
	return 0;
}

int lbs_grid_cell_row(lbs_grid_t* lbs_grid,double lat) {


	int cell_row;
	cell_row=(lat-lbs_grid->lat_min)/lbs_grid->cell_height;
	
	return cell_row;
}

//����Cell Col
int lbs_grid_cell_col(lbs_grid_t* lbs_grid,double lon)
{ 
	int cell_col;
	cell_col= (lon-lbs_grid->lon_min)/lbs_grid->cell_width;	
	return cell_col;
}
 
//����Cell Id
int lbs_grid_cell_id(lbs_grid_t* lbs_grid,int cell_row,int cell_col)
{	int cell_id;
	cell_id=  lbs_grid->col_num * cell_row + cell_col;
	return cell_id;
} 
//����row��col
void lbs_grid_cell_row_col(lbs_grid_t* lbs_grid,int cell_id,int*cell_row,int*cell_col)
{ 
	//ͨ��cell_id����С��У����� *row��*col (��row=ox0010,*row=3)
	*cell_row=cell_id/lbs_grid->col_num;
	*cell_col=cell_id%lbs_grid->col_num;
} 
//��ȡCell Id�����Cell  ������id���ͷ��� 
lbs_cell_t* lbs_grid_cell(lbs_grid_t* lbs_grid, int cell_id)
{
	return  lbs_grid->cell+cell_id;
}






