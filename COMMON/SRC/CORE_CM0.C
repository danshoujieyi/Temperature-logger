/******************** (C) COPYRIGHT 2010 Embest Info&Tech Co.,LTD. ************
* 文件名: core_cm0.c
* 作者  : Wuhan R&D Center, Embest
* 日期  : 01/18/2010
* 描述  : CMSIS Cortex-M0核外围访问层源文件
*******************************************************************************
*******************************************************************************
* 历史:
* 01/18/2010		 : V1.0		   初始版本
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/* 编译器的特性符号定义 */
#if defined ( __CC_ARM   )
  #define __ASM            __asm           /*!< armcc编译器asm关键字          */
  #define __INLINE         __inline        /*!< armcc编译器inline关键字       */

#elif defined ( __ICCARM__ )
  #define __ASM           __asm            /*!< iarcc编译器asm关键字          */
  #define __INLINE        inline           /*!< iarcc编译器inline关键字       */
  #define __nop           __no_operation   /*!< 无操作 */

#elif defined   (  __GNUC__  )
  #define __ASM             asm            /*!< gcc编译器asm关键字            */
  #define __INLINE          inline         /*!< gcc编译器inline关键字         */
#endif


#if (defined (__ARMCC_VERSION)) && (__ARMCC_VERSION < 400000)


/**
  * @函数名：uint32_t __get_PSP
  * @描述：返回进程堆栈指针
  * @参数： 无
  * @返回值：uint32_t 进程堆栈指针
  *          返回一个具体的进程堆栈指针
  */
__ASM uint32_t __get_PSP(void)
{
  mrs r0, psp
  bx lr
}


/**
  * @函数名：__set_PSP 
  * @描述：设置进程堆栈指针
  * @参数： uint32_t 进程堆栈指针
  * @返回值：无
  *          分配一个进程堆栈指针值给Cortex-M0核PSP寄存器 
  */
__ASM void __set_PSP(uint32_t topOfProcStack)
{
  msr psp, r0
  bx lr
}


/**
  * @函数名：__get_MSP
  * @描述：返回主堆栈指针
  * @参数： 无
  * @返回值：uint32_t 主程堆栈指针
  */
__ASM uint32_t __get_MSP(void)
{
  mrs r0, msp
  bx lr
}


/**
  * @函数名：__set_MSP
  * @描述：设置主堆栈指针
  * @参数：uint32_t 主程堆栈指针
  * @返回值：无
  *          分配一个具体值给MSP主堆栈指针寄存器
  */
__ASM void __set_MSP(uint32_t mainStackPointer)
{
  msr msp, r0
  bx lr
}


/**
  * @函数名：__get_BASEPRI
  * @描述：返回基优先级值
  * @参数：无
  * @返回值：uint32_t 基优先级
  */
__ASM uint32_t  __get_BASEPRI(void)
{
  mrs r0, basepri
  bx lr
}


/**
  * @函数名：__set_BASEPRI
  * @描述：设置基优先级值
  * @参数：uint32_t 基优先级
  * @返回值：无
  */
__ASM void __set_BASEPRI(uint32_t basePri)
{
  msr basepri, r0
  bx lr
}


/**
  * @函数名: __get_PRIMASK
  * @描述：返回优先级屏蔽值
  * @参数：无
  * @返回值：uint32_t 优先级屏蔽值
  */
__ASM uint32_t __get_PRIMASK(void)
{
  mrs r0, primask
  bx lr
}


/**
  * @函数名：__set_PRIMASK
  * @描述：设置优先级屏蔽寄存器
  * @参数：uint32_t 优先级屏蔽值
  * @返回值：无           
  */
__ASM void __set_PRIMASK(uint32_t priMask)
{
  msr primask, r0
  bx lr
}


/**
  * @函数名：__get_FAULTMASK 
  * @描述：返回故障屏蔽寄存器值
  * @参数：无
  * 返回值：uint32_t 故障屏蔽值           
  */
__ASM uint32_t  __get_FAULTMASK(void)
{
  mrs r0, faultmask
  bx lr
}


/**
 * @函数名：__set_FAULTMASK
 * @描述：设置故障屏蔽寄存器
 * @参数：uint32_t 故障屏蔽值
 * @返回值：无         
 */
__ASM void __set_FAULTMASK(uint32_t faultMask)
{
  msr faultmask, r0
  bx lr
}


/**
  * 函数名：__get_CONTROL
  * @描述：返回控制寄存器值
  * @参数: 无
  * @返回值: uint32_t 控制寄存器值
  */
__ASM uint32_t  __get_CONTROL(void)
{
  mrs r0, control
  bx lr
}

/**
 * @函数名：__set_CONTROL
 * @描述：设置控制寄存器
 * @参数：uint32_t 控制寄存器值
 * @返回值：无
 */
__ASM void __set_CONTROL(uint32_t control)
{
  msr control, r0
  bx lr
}


/**
  * @函数名：__REV16
  * @描述：反转unsigned short类型字节顺序
  * @参数：uint16_t value 待转换值
  * @返回值：uint32_t 转换后的值
  */
__ASM uint32_t __REV16(uint16_t value)
{
  rev16 r0, r0
  bx lr
}


/**
  * @函数名：__REVSH
  * @描述：反转signed short类型值字节顺序并进行符号扩展
  * @参数：int16_t value待转换值
  * @返回值：int32_t 转换后的值
  */
__ASM int32_t __REVSH(int16_t value)
{
  revsh r0, r0
  bx lr
}



#elif (defined (__ICCARM__))
#pragma diag_suppress=Pe940

/**
  * @函数名：__get_PSP
  * @描述：返回进程堆栈指针
  * @参数：无
  * @返回值：uint32_t 进程堆栈指针
  */
uint32_t __get_PSP(void)
{
  __ASM("mrs r0, psp");
  __ASM("bx lr");
}

/**
  * @函数名：__set_PSP
  * @描述：设置进程堆栈指针
  * @参数：uint32_t 进程堆栈指针
  * @返回值：无
  *          为PSP堆栈指针寄存器分配一个值
  */
void __set_PSP(uint32_t topOfProcStack)
{
  __ASM("msr psp, r0");
  __ASM("bx lr");
}

/**
  * @函数名：__get_MSP
  * @描述：返回主堆栈指针
  * @参数：无
  * @返回值： uint32_t 主堆栈指针
  */
uint32_t __get_MSP(void)
{
  __ASM("mrs r0, msp");
  __ASM("bx lr");
}

/**
  * @函数名：__set_MSP
  * @描述：设置主堆栈指针
  * @参数：uint32_t 主堆栈指针
  * @返回值：无
  *         为MSP主堆栈指针寄存器分配一个值
  */
void __set_MSP(uint32_t topOfMainStack)
{
  __ASM("msr msp, r0");
  __ASM("bx lr");
}


/**
  * @函数名：__REV16
  * @描述：反转unsigned short类型值字节顺序
  * @参数：uint16_t value等转换值
  * @返回值：uint32_t 转换后的值
  */
uint32_t __REV16(uint16_t value)
{
  __ASM("rev16 r0, r0");
  __ASM("bx lr");
}


/**
  * @函数名：__RBIT
  * @描述：反转一个值二进制位顺序
  * @参数：uint32_t value待转换值
  * @返回值：uint32_t 转换后的值
  */
uint32_t __RBIT(uint32_t value)
{
  __ASM("rbit r0, r0");
  __ASM("bx lr");
}

/**
  * @函数名：__LDREXB
  * @描述： LDR Exclusive
  * @参数： uint8_t* address
  * @返回值： uint8_t (*address)值
  */
uint8_t __LDREXB(uint8_t *addr)
{
  __ASM("ldrexb r0, [r0]");
  __ASM("bx lr"); 
}

/**
  * @函数名：__LDREXH
  * @描述：LDR Exclusive
  * @参数： uint16_t* address
  * @返回值：uint16_t (*address)值
  *          Exclusive LDR 指令
  */
uint16_t __LDREXH(uint16_t *addr)
{
  __ASM("ldrexh r0, [r0]");
  __ASM("bx lr");
}


/**
  * @函数名：__LDREXW
  * @描述：LDR Exclusive
  * @参数： uint32_t* address
  * @返回值：uint32_t (*address)值
  * Exclusive LDR 指令
  */
uint32_t __LDREXW(uint32_t *addr)
{
  __ASM("ldrex r0, [r0]");
  __ASM("bx lr");
}


/**
  * @函数名：__STREXB
  * @描述：STR Exclusive
  * @参数：uint8_t *address
  * @参数： uint8_t value待存储值
  * @返回值：uint32_t 成功/失败
  *          Exclusive STR 指令
  */
uint32_t __STREXB(uint8_t value, uint8_t *addr)
{
  __ASM("strexb r0, r0, [r1]");
  __ASM("bx lr");
}


/**
  * @函数名：__STREXH
  * @描述： STR Exclusive
  * @参数： uint16_t *address
  * @参数： uint16_t value待存储值
  * @返回值：uint32_t 成功/失败
  *          Exclusive STR 指令
  */
uint32_t __STREXH(uint16_t value, uint16_t *addr)
{
  __ASM("strexh r0, r0, [r1]");
  __ASM("bx lr");
}


/**
  * @函数名：__STREXW
  * @描述：STR Exclusive
  * @参数：uint32_t *address
  * @参数：uint32_t value待存储值
  * @返回值：uint32_t 成功/失败
  *          Exclusive STR 指令
  */
uint32_t __STREXW(uint32_t value, uint32_t *addr)
{
  __ASM("strex r0, r0, [r1]");
  __ASM("bx lr");
}




#pragma diag_default=Pe940




#elif (defined (__GNUC__))

/**
  * @函数名：__get_CONTROL
  * @描述：获取控制寄存器值
  * @参数：无
  * @返回值：uint32_t 控制寄存器值
  *          返回控制寄存器内容
  */
uint32_t __get_CONTROL(void)
{
  uint32_t result=0;
  __ASM volatile ("MRS %0, control" : "=r" (result) );
  return(result);
}

/**
  * @函数名：__set_CONTROL
  * @描述：设置控制寄存器
  * @参数： uint32_t 控制寄存器值
  * @返回值：无
  *          设置控制寄存器
  */
void __set_CONTROL(uint32_t control)
{
  __ASM volatile ("MSR control, %0" : : "r" (control) );
}

/**
  * @函数名：__get_PSP
  * @描述：返回进程堆栈指针
  * @参数：无
  * @返回值：uint32_t 进程堆栈指针
  *          返回进程堆栈指针
  */
uint32_t __get_PSP(void)
{
  uint32_t result=0;
  
  __ASM volatile ("MRS %0, psp" : "=r" (result) );
  return(result);
}

/**
  * @函数名：__set_PSP
  * @描述：设置进程堆栈指针
  * @参数：uint32_t P进程堆栈指针
  * @返回值：无
  *          分配一个进程堆栈指针给MSP主堆栈指针寄存器
  */
void __set_PSP(uint32_t topOfProcStack)
{
  __ASM volatile ("MSR psp, %0" : : "r" (topOfProcStack) );
}

/**
  * @函数名：__get_MSP
  * @描述：获取主堆栈指针
  * @参数：无
  * @返回值：uint32_t 主堆栈指针
  *          返回主堆栈指针寄存器的值
  */
uint32_t __get_MSP(void)
{
  uint32_t result=0;

  __ASM volatile ("MRS %0, msp" : "=r" (result) );
  return(result);
}

/**
  * @函数名：__set_MSP
  * @描述：设置主堆栈指针
  * @参数：uint32_t 主堆栈指针
  * @返回值：无
  *          分配一个主堆栈指针给MSP主堆栈指针寄存器
  */
void __set_MSP(uint32_t topOfMainStack)
{
  __ASM volatile ("MSR msp, %0" : : "r" (topOfMainStack) );
}

/**
  * @函数名：__get_BASEPRI
  * @描述：返回基优先级值
  * @参数：无
  * @返回值：uint32_t 基优先级
  *          返回基优先级寄存器值
  */
uint32_t __get_BASEPRI(void)
{
  uint32_t result=0;
  
  __ASM volatile ("MRS %0, basepri_max" : "=r" (result) );
  return(result);
}

/**
  * @函数名：__set_BASEPRI
  * @描述：设置基优先级寄存器
  * @参数：uint32_t 基优先级
  * @返回值：无
  *          设置基优先级寄存器
  */
void __set_BASEPRI(uint32_t value)
{
  __ASM volatile ("MSR basepri, %0" : : "r" (value) );
}

/**
  * @函数名：__get_PRIMASK
  * @描述：获取优先级屏蔽值
  * @参数：无
  * @返回值：uint32_t PriMask
  *          返回优先级屏蔽寄存器屏蔽状态
  */
uint32_t __get_PRIMASK(void)
{
  uint32_t result=0;
  
  __ASM volatile ("MRS %0, primask" : "=r" (result) );
  return(result);
}

/**
  * @函数名： __set_PRIMASK
  * @描述：设置优先级屏蔽位
  * @参数：uint32_t PriMask
  * @返回值：无
  *          配置优先级屏蔽寄存器
  */
void __set_PRIMASK(uint32_t priMask)
{
  __ASM volatile ("MSR primask, %0" : : "r" (priMask) );
}

/**
  * @函数名：__get_FAULTMASK
  * @描述：返回故障屏蔽状态
  * @参数：无
  * @返回值：uint32_t FaultMask
  *          返回故障屏蔽寄存器值
  */
uint32_t __get_FAULTMASK(void)
{
  uint32_t result=0;
  
  __ASM volatile ("MRS %0, faultmask" : "=r" (result) );
  return(result);
}

/**
  * @函数名：__set_FAULTMASK
  * @描述：设置故障屏蔽位
  * @参数：uint32_t 故障屏蔽值
  * @返回值：无
  *          设置故障屏蔽寄存器
  */
void __set_FAULTMASK(uint32_t faultMask)
{
  __ASM volatile ("MSR faultmask, %0" : : "r" (faultMask) );
}

/**
  * @函数名：__REV
  * @描述：反转整型值字节顺序
  * @参数：uint32_t value待转换值
  * @返回值：uint32_t 转换后的值
  *          反转整型值字节顺序
  */
uint32_t __REV(uint32_t value)
{
  uint32_t result=0;
  
   __ASM volatile ("rev %0, %1" : "=r" (result) : "r" (value) );
   return(result);
}

/**
  * @函数名：  __REV16
  * @描述：反转unsigned short类型值字节顺序
  * @参数：uint16_t value待转换值
  * @返回值：uint32_t 转换后的值
  *          反转unsigned short类型值字节顺序
  */
uint32_t __REV16(uint16_t value)
{
  uint32_t result=0;
  
   __ASM volatile ("rev16 %0, %1" : "=r" (result) : "r" (value) );
   return(result);
}


/**
  * @函数名：__REVSH
  * @描述：反转signed short类型值并进行符号扩展
  * @参数： int32_t value待转换值
  * @返回值：int32_t 转换后的值 
  *          反转signed short类型值并进行符号扩展
  */
int32_t __REVSH(int16_t value)
{
  uint32_t result=0;
  
   __ASM volatile ("revsh %0, %1" : "=r" (result) : "r" (value) );
   return(result);
}


/**
  * @函数名：__RBIT
  * @描述：反转位序
  * @参数： uint32_t value待转换值
  * @返回值：uint32_t 转换后的值
  *          反转位序
  */
uint32_t __RBIT(uint32_t value)
{
  uint32_t result=0;
  
   __ASM volatile ("rbit %0, %1" : "=r" (result) : "r" (value) );
   return(result);
}


/**
  * @函数名：__LDREXB
  * @描述：LDR Exclusive
  * @参数： uint8_t* address
  * @返回值：uint8_t (*address)值
  *          Exclusive LDR 指令
  */
uint8_t __LDREXB(uint8_t *addr)
{
    uint8_t result=0;
  
   __ASM volatile ("ldrexb %0, [%1]" : "=r" (result) : "r" (addr) );
   return(result);
}

/**
  * @函数名：__LDREXH
  * @描述：LDR Exclusive
  * @参数： uint16_t* address
  * @返回值：uint16_t (*address)值
  *          Exclusive LDR 指令
  */
uint16_t __LDREXH(uint16_t *addr)
{
    uint16_t result=0;
  
   __ASM volatile ("ldrexh %0, [%1]" : "=r" (result) : "r" (addr) );
   return(result);
}


/**
  * @函数名：__LDREXW
  * @描述：LDR Exclusive
  * @参数：uint32_t* address
  * @返回值：uint32_t (*address)值
  *          Exclusive LDR 指令
  */
uint32_t __LDREXW(uint32_t *addr)
{
    uint32_t result=0;
  
   __ASM volatile ("ldrex %0, [%1]" : "=r" (result) : "r" (addr) );
   return(result);
}


/**
  * @函数名：__STREXB
  * @描述：STR Exclusive
  * @参数：uint8_t *address
  * @参数：uint8_t value待存储值
  * @返回值：uint32_t 成功/失败
  *          Exclusive STR 指令
  */
uint32_t __STREXB(uint8_t value, uint8_t *addr)
{
   uint32_t result=0;
  
   __ASM volatile ("strexb %0, %2, [%1]" : "=r" (result) : "r" (addr), "r" (value) );
   return(result);
}


/**
  * @函数名：__STREXH
  * @描述：STR Exclusive
  * @参数： uint16_t *address
  * @参数： uint16_t value待存储值
  * @返回值：uint32_t 成功/失败
  *          Exclusive STR 指令
  */
uint32_t __STREXH(uint16_t value, uint16_t *addr)
{
   uint32_t result=0;
  
   __ASM volatile ("strexh %0, %2, [%1]" : "=r" (result) : "r" (addr), "r" (value) );
   return(result);
}


/**
  * @函数名：__STREXW
  * @描述：STR Exclusive
  * @参数：uint32_t *address
  * @参数：uint32_t value待存储值
  * @返回值：uint32_t 成功/失败
  *          Exclusive STR 指令
  */
uint32_t __STREXW(uint32_t value, uint32_t *addr)
{
   uint32_t result=0;
  
   __ASM volatile ("strex %0, %2, [%1]" : "=r" (result) : "r" (addr), "r" (value) );
   return(result);
}




#endif
/**
  * @}
  */ 

/**
  * @}
  */ 
/************* (C) COPYRIGHT 2010 Wuhan R&D Center, Embest *****文件结束*******/
















