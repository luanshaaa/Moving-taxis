#include<stdlib.h>
#include "server/grid/lbs_bitmap.h"

int arr[8]={128,64,32,16,8,4,2,1};

/** 初始化Bitmap **/
int lbs_bitmap_init(lbs_bitmap_t* lbs_bitmap, uint32_t bits_num)
{
	lbs_bitmap->bits_num=bits_num ;
	if(bits_num%8!=0) {
		lbs_bitmap->bits=(uint8_t *)calloc(1, (bits_num/8+1)*sizeof(uint8_t));
  } else {
		lbs_bitmap->bits=(uint8_t *)calloc(1, (bits_num/8)*sizeof(uint8_t));
  }
	return 0;
}

/** 销毁 **/
int lbs_bitmap_destroy(lbs_bitmap_t* lbs_bitmap) {
  free(lbs_bitmap->bits);
}
/** 设置Bit**/
int lbs_bitmap_setbit(lbs_bitmap_t* lbs_bitmap, uint32_t pos)
{
	int pos_num= pos/8;
	int pos_id=pos%8;
	
	lbs_bitmap->bits[pos_num]=lbs_bitmap->bits[pos_num]|arr[pos_id];
	
	
	return 0;
	}	


/** 取消设置Bit **/
int lbs_bitmap_unsetbit(lbs_bitmap_t* lbs_bitmap, uint32_t pos) { }
/** 判定是否设置Bit **/
int lbs_bitmap_isset(lbs_bitmap_t* lbs_bitmap, uint32_t pos)
{
	int pos_num= pos/8;
	int pos_id=pos%8;
	
	
	if((lbs_bitmap->bits[pos_num]&arr[pos_id])!=0)
	{
		return 1;
	}else
	{
		return 0;
	}
}





