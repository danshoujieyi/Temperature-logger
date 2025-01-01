/****************************************Copyright (c)****************************************************
**                            Guangzhou ZHIYUAN electronics Co.,LTD.
**
**                                 http://www.embedtools.com
**
**------File Info-----------------------------------------------------------------------------------------
** File name:               hz16.c
** Latest modified Date:    2007-12-12
** Latest Version:          1.0
** Descriptions:            ASCII码字库及汉字自定义字库的应用
**
**--------------------------------------------------------------------------------------------------------
** Created by:              张展威
** Created date:            2007-12-12
** Version:                 1.0
** Descriptions:
**
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Descriptions:
**
*********************************************************************************************************/
#include "hx16.h" 

/*********************************************************************************************************
** Function name:           findHzIndex
** Descriptions:            查找汉字在自定义字库中的索引
** input parameters:        hz 指向汉字(机内码)的指针
** output parameters:       无
** Returned value:          无
** Created By:              张展威
** Created date:            2007.12.12
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
unsigned int  findHzIndex(unsigned char *hz)                                           /* 在自定义汉字库在查找所要显示 */
                                                                        /* 的汉字的位置                 */
{
    unsigned int  i=0;
    
    FNT_GB16 *ptGb16 = (FNT_GB16 *)GBHZ_16;
    
    while(ptGb16[i].Index[0] > 0x80) {
        if ((*hz == ptGb16[i].Index[0]) && (*(hz+1) == ptGb16[i].Index[1])) {
            return i;
        }
        i++;
        //if(i > (sizeof(GBHZ_16) / sizeof(FNT_GB16) - 1)) {              /* 搜索下标约束                 */
        //    break;
       // }
    }
    return 0;
}

/*********************************************************************************************************
** End of File
*********************************************************************************************************/
