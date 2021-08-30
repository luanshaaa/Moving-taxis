#ifndef SERVER_FRID_LBS_BITMAP_h
#define SERVER_FRID_LBS_BITMAP_h

#include<stdint.h>
#include<stdlib.h>

typedef struct lbs_bitmap_s {
    uint8_t *bits;
    uint32_t bits_num;
} lbs_bitmap_t;

/** ��ʼ��Bitmap **/
int lbs_bitmap_init(lbs_bitmap_t* lbs_bitmap, uint32_t bits_num);
/** ���� **/
int lbs_bitmap_destroy(lbs_bitmap_t* lbs_bitmap);
/** ����Bit**/
int lbs_bitmap_setbit(lbs_bitmap_t* lbs_bitmap, uint32_t pos);
/** ȡ������Bit **/
int lbs_bitmap_unsetbit(lbs_bitmap_t* lbs_bitmap, uint32_t pos);
/** �ж��Ƿ�����Bit **/
int lbs_bitmap_isset(lbs_bitmap_t* lbs_bitmap, uint32_t pos);

#endif /* SERVER_FRID_LBS_BITMAP_h */


