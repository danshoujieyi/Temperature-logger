/******************** (C) COPYRIGHT 2010 Embest Info&Tech Co.,LTD. ************
* 文件名: core_cm0.h
* 作者  : Wuhan R&D Center, Embest
* 日期  : 01/18/2010
* 描述  : CMSIS Cortex-M0核外围访问层头文件
*******************************************************************************
*******************************************************************************
* 历史:
* 01/18/2010		 : V1.0		   初始版本
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/

#ifndef __CM0_CORE_H__
#define __CM0_CORE_H__

#ifdef __cplusplus
 extern "C" {
#endif 

#define __CM0_CMSIS_VERSION_MAIN  (0x01)                                                       /*!< [31:16] CMSIS HAL 主版本号 */
#define __CM0_CMSIS_VERSION_SUB   (0x20)                                                       /*!< [15:0]  CMSIS HAL 子版本号 */
#define __CM0_CMSIS_VERSION       ((__CM0_CMSIS_VERSION_MAIN << 16) | __CM0_CMSIS_VERSION_SUB) /*!< CMSIS HAL 版本号           */

#define __CORTEX_M                (0x00)                                                       /*!< Cortex 核                  */



#include <stdint.h>                           

#if defined (__ICCARM__)
  #include <intrinsics.h>                     /* IAR 内联  */
#endif


#ifndef __NVIC_PRIO_BITS
  #define __NVIC_PRIO_BITS    2               /*!< NVIC优先级位数定义*/
#endif




/**
 * IO 定义
 *
 * 定义外围寄存器访问权限
 */

#ifdef __cplusplus
#define     __I     volatile                  /*!< 'read only'允许             */
#else
#define     __I     volatile const            /*!< 'read only'允许             */
#endif
#define     __O     volatile                  /*!< 'write only'允许            */
#define     __IO    volatile                  /*!< 'read / write'可读写        */



/* Private typedef ------------------------------------------------------------*/
/* System Reset */
#define NVIC_VECTRESET              0         /*!< 向量表复位                  */
#define NVIC_SYSRESETREQ            2         /*!< 系统复位请求                */
#define NVIC_AIRCR_VECTKEY    (0x5FA << 16)   /*!< AIRCR Key用于写允许         */
#define NVIC_AIRCR_ENDIANESS        15        /*!< 端对齐                      */




/* 嵌套向量中断控制器(NVIC)寄存器映射 */
typedef struct
{
  __IO uint32_t ISER[1];                      /*!< 中断设置使能寄存器           */
       uint32_t RESERVED0[31];
  __IO uint32_t ICER[1];                      /*!< 中断清除使能寄存器           */
       uint32_t RSERVED1[31];
  __IO uint32_t ISPR[1];                      /*!< 中断设置悬起寄存器           */
       uint32_t RESERVED2[31];
  __IO uint32_t ICPR[1];                      /*!< 中断清除悬起寄存器           */
       uint32_t RESERVED3[31];
       uint32_t RESERVED4[64];
  __IO uint32_t IPR[8];                       /*!< 中断优先级寄存器             */
}  NVIC_Type;


/* 系统控制块寄存器映射 */
typedef struct
{
  __I  uint32_t CPUID;                        /*!< CPU ID基址寄存器              */
  __IO uint32_t ICSR;                         /*!< 中断控制状态寄存器            */
       uint32_t RESERVED0;
  __IO uint32_t AIRCR;                        /*!< 应用程序中断/复位控制寄存器   */
  __IO uint32_t SCR;                          /*!< 系统控制寄存器                */
  __IO uint32_t CCR;                          /*!< 配置控制寄存器                */
       uint32_t RESERVED1;
  __IO uint32_t SHP[2];                       /*!< 系统处理优先级寄存器，0位保留 */
  __IO uint32_t SHCSR;                        /*!< 系统处理控制和状态寄存器      */
       uint32_t RESERVED2[2];
  __IO uint32_t DFSR;                         /*!< 调试故障状态寄存器            */
} SCB_Type;


/* 系统滴答存储器映射 */
typedef struct
{
  __IO uint32_t CTRL;                         /*!< SysTick控制和状态寄存器       */
  __IO uint32_t LOAD;                         /*!< SysTick重装载值寄存器         */
  __IO uint32_t VAL;                          /*!< SysTick当前值寄存器           */
  __I  uint32_t CALIB;                        /*!< SysTick校验寄存器             */
} SysTick_Type;



/* 内核调试寄存器 */
typedef struct
{
  __IO uint32_t DHCSR;                        /*!< 调试停机控制和状态寄存器      */
  __O  uint32_t DCRSR;                        /*!< 调试内核寄存器选择寄存器      */
  __IO uint32_t DCRDR;                        /*!< 调试内核寄存器数据寄存器      */
  __IO uint32_t DEMCR;                        /*!< 调试异常和监控控制寄存器      */
} CoreDebug_Type;


/* Cortex-M0硬件存储器映射 */
#define SCS_BASE            (0xE000E000)                              /*!< 系统控制空间基地址  */
#define CoreDebug_BASE      (0xE000EDF0)                              /*!< 内核调试基地址      */
#define SysTick_BASE        (SCS_BASE +  0x0010)                      /*!< SysTick基地址       */
#define NVIC_BASE           (SCS_BASE +  0x0100)                      /*!< NVIC基地址          */
#define SCB_BASE            (SCS_BASE +  0x0D00)                      /*!< 系统控制块基地址    */

#define SCB                 ((SCB_Type *)           SCB_BASE)         /*!< SCB配置结构         */
#define SysTick             ((SysTick_Type *)       SysTick_BASE)     /*!< SysTick配置结构     */
#define NVIC                ((NVIC_Type *)          NVIC_BASE)        /*!< NVIC配置结构        */
#define CoreDebug           ((CoreDebug_Type *)     CoreDebug_BASE)   /*!< Core Debug配置结构  */


/*******************************************************************************
 *                硬件抽象层
 ******************************************************************************/


#if defined ( __CC_ARM   )
  #define __ASM            __asm                                      
  #define __INLINE         __inline                                  

#elif defined ( __ICCARM__ )
  #define __ASM           __asm                                      
  #define __INLINE        inline                                     

#elif defined   (  __GNUC__  )
  #define __ASM            __asm                                      
  #define __INLINE         inline                                     

#elif defined   (  __TASKING__  )
  #define __ASM            __asm                                      
  #define __INLINE         inline                                     

#endif


/* ###################  编译器特性相关  ########################### */

#if defined ( __CC_ARM   ) /*------------------RealView编译器 -----------------*/

#define __enable_fault_irq                __enable_fiq
#define __disable_fault_irq               __disable_fiq

#define __NOP                             __nop
#define __WFI                             __wfi
#define __WFE                             __wfe
#define __SEV                             __sev
#define __ISB()                           __isb(0)
#define __DSB()                           __dsb(0)
#define __DMB()                           __dmb(0)
#define __REV                             __rev


  /* intrinsic void __enable_irq();     */
  /* intrinsic void __disable_irq();    */



extern uint32_t __get_PSP(void);
extern void __set_PSP(uint32_t topOfProcStack);
extern uint32_t __get_MSP(void);
extern void __set_MSP(uint32_t topOfMainStack);
extern uint32_t __REV16(uint16_t value);
extern int32_t __REVSH(int16_t value);

#if (__ARMCC_VERSION < 400000)

extern uint32_t __get_PRIMASK(void);
extern void __set_PRIMASK(uint32_t priMask);
extern uint32_t __get_CONTROL(void);
extern void __set_CONTROL(uint32_t control);

#else  /* (__ARMCC_VERSION >= 400000)  */

 
/**
  * @函数名：__get_PRIMASK
  * @描述：获取优先级屏蔽状态
  * @参数： 无
  * @返回值：uint32_t PriMask
  */ 
static __INLINE uint32_t __get_PRIMASK(void)
{
  register uint32_t __regPriMask         __ASM("primask");
  return(__regPriMask);
}

/**
  * @函数名：__set_PRIMASK
  * @描述：配置优先级屏蔽寄存器
  * @参数： uint32_t PriMask
  * @返回值：无
  */
static __INLINE void __set_PRIMASK(uint32_t priMask)
{
  register uint32_t __regPriMask         __ASM("primask");
  __regPriMask = (priMask);
}


/**
  * @函数名：__get_CONTROL
  * @描述：返回控制寄存器值
  * @参数： 无
  * @返回值：uint32_t 控制寄存器值
  */
static __INLINE uint32_t __get_CONTROL(void)
{
  register uint32_t __regControl         __ASM("control");
  return(__regControl);
}


/**
  * @函数名：__set_CONTROL
  * @描述：设置控制寄存器
  * @参数： uint32_t 控制寄存器值
  * @返回值：无
  */ 
static __INLINE void __set_CONTROL(uint32_t control)
{
  register uint32_t __regControl         __ASM("control");
  __regControl = control;
}

#endif /* __ARMCC_VERSION  */ 



#elif (defined (__ICCARM__)) /*------------------ ICC编译器 -------------------*/

#define __enable_irq                              __enable_interrupt        /*!< 全局中断使能 */
#define __disable_irq                             __disable_interrupt       /*!< 全局中断除能 */

static __INLINE void __enable_fault_irq()         { __ASM ("cpsie f"); }
static __INLINE void __disable_fault_irq()        { __ASM ("cpsid f"); }

#define __NOP                                     __no_operation()          
static __INLINE  void __WFI()                     { __ASM ("wfi"); }
static __INLINE  void __WFE()                     { __ASM ("wfe"); }
static __INLINE  void __SEV()                     { __ASM ("sev"); }

/* intrinsic void __ISB(void)                                     */
/* intrinsic void __DSB(void)                                     */
/* intrinsic void __DMB(void)                                     */
/* intrinsic void __set_PRIMASK();                                */
/* intrinsic void __get_PRIMASK();                                */


/* intrinsic uint32_t __REV(uint32_t value);                      */
/* intrinsic uint32_t __REVSH(uint32_t value);                    */


extern uint32_t __get_PSP(void);
extern void __set_PSP(uint32_t topOfProcStack);
extern uint32_t __get_MSP(void);
extern void __set_MSP(uint32_t topOfMainStack);
extern uint32_t __REV16(uint16_t value);



#elif (defined (__GNUC__)) /*------------------ GNU编译器 ---------------------*/

static __INLINE void __enable_irq()               { __ASM volatile ("cpsie i"); }
static __INLINE void __disable_irq()              { __ASM volatile ("cpsid i"); }

static __INLINE void __enable_fault_irq()         { __ASM volatile ("cpsie f"); }
static __INLINE void __disable_fault_irq()        { __ASM volatile ("cpsid f"); }

static __INLINE void __NOP()                      { __ASM volatile ("nop"); }
static __INLINE void __WFI()                      { __ASM volatile ("wfi"); }
static __INLINE void __WFE()                      { __ASM volatile ("wfe"); }
static __INLINE void __SEV()                      { __ASM volatile ("sev"); }
static __INLINE void __ISB()                      { __ASM volatile ("isb"); }
static __INLINE void __DSB()                      { __ASM volatile ("dsb"); }
static __INLINE void __DMB()                      { __ASM volatile ("dmb"); }


extern uint32_t __get_PSP(void);
extern void __set_PSP(uint32_t topOfProcStack);
extern uint32_t __get_MSP(void);
extern void __set_MSP(uint32_t topOfMainStack);
extern uint32_t  __get_PRIMASK(void);
extern void __set_PRIMASK(uint32_t priMask);
extern uint32_t __get_CONTROL(void);
extern void __set_CONTROL(uint32_t control);
extern uint32_t __REV(uint32_t value);
extern uint32_t __REV16(uint16_t value);
extern int32_t __REVSH(int16_t value);


#elif (defined (__TASKING__)) /*------------------ TASKING 编译器 ---------------------*/

#endif



/* ##########################   NVIC 函数  #################################### */

#define _BIT_SHIFT(IRQn)         (  (((uint32_t)(IRQn)       )    &  0x03) * 8 )
#define _SHP_IDX(IRQn)           ( ((((uint32_t)(IRQn) & 0x0F)-8) >>    2)     )
#define _IP_IDX(IRQn)            (   ((uint32_t)(IRQn)            >>    2)     )



/**
  * @函数名：NVIC_EnableIRQ
  * @描述：使能NVIC中断控制寄存器中相应位
  * @参数： IRQn_Type IRQn指定中断号
  * @返回值：无
  */  
static __INLINE void NVIC_EnableIRQ(IRQn_Type IRQn)
{
  NVIC->ISER[0] = (1 << ((uint32_t)(IRQn) & 0x1F)); /* 使能中断 */
}

/**
  * @函数名：NVIC_DisableIRQ
  * @描述：除能一个具体设备外部中断
  * @参数： IRQn_Type IRQn外部中断号，正数
  * @返回值：无
  */  
static __INLINE void NVIC_DisableIRQ(IRQn_Type IRQn)
{
  NVIC->ICER[0] = (1 << ((uint32_t)(IRQn) & 0x1F)); /* 除能中断 */
}

/**
  * @函数名：NVIC_GetPendingIRQ
  * @描述：获取中断悬起状态
  * @参数： IRQn_Type  IRQn具体设备中断号
  * @返回值：uint32_t   如果中断悬起返回1，否则返回0
  */  
static __INLINE uint32_t NVIC_GetPendingIRQ(IRQn_Type IRQn)
{
  return((uint32_t) ((NVIC->ISPR[0] & (1 << ((uint32_t)(IRQn) & 0x1F)))?1:0)); 
}

/**
  * @函数名：NVIC_SetPendingIRQ
  * @描述：为外部中断设置悬起位
  * @参数： IRQn_Type IRQn中断号
  * @返回值：无
  */ 
static __INLINE void NVIC_SetPendingIRQ(IRQn_Type IRQn)
{
  NVIC->ISPR[0] = (1 << ((uint32_t)(IRQn) & 0x1F)); 
}
 
/**
  * @函数名：NVIC_ClearPendingIRQ
  * @描述：清除外部中断悬起位
  * @参数： IRQn_Type  IRQn为中断号
  * @返回值：无
  */  
static __INLINE void NVIC_ClearPendingIRQ(IRQn_Type IRQn)
{
  NVIC->ICPR[0] = (1 << ((uint32_t)(IRQn) & 0x1F)); 
}

/**
  * @函数名：NVIC_SetPriority
  * @描述：设置中断优先级
  * @参数： IRQn_Type  IRQn中断号
  * @返回值：无
  */ 
static __INLINE void NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority)
{
  if(IRQn < 0) {
    SCB->SHP[_SHP_IDX(IRQn)] = (SCB->SHP[_SHP_IDX(IRQn)] & ~(0xFF << _BIT_SHIFT(IRQn))) | 
        (((priority << (8 - __NVIC_PRIO_BITS)) & 0xFF) << _BIT_SHIFT(IRQn)); }
  else {
    NVIC->IPR[_IP_IDX(IRQn)] = (NVIC->IPR[_IP_IDX(IRQn)] & ~(0xFF << _BIT_SHIFT(IRQn))) |
        (((priority << (8 - __NVIC_PRIO_BITS)) & 0xFF) << _BIT_SHIFT(IRQn)); }
}

/**
  * @函数名：NVIC_GetPriority
  * @描述：获取中断优先级
  * @参数： IRQn_Type IRQn中断号
  * @返回值：priority中断优先级
  */ 
static __INLINE uint32_t NVIC_GetPriority(IRQn_Type IRQn)
{

  if(IRQn < 0) {
    return((uint32_t)((SCB->SHP[_SHP_IDX(IRQn)] >> _BIT_SHIFT(IRQn) ) >> (8 - __NVIC_PRIO_BITS)));  } 
  else {
    return((uint32_t)((NVIC->IPR[_IP_IDX(IRQn)] >> _BIT_SHIFT(IRQn) ) >> (8 - __NVIC_PRIO_BITS)));  } 
}



/* ##################################    SysTick函数 ############################################ */

#if (!defined (__Vendor_SysTickConfig)) || (__Vendor_SysTickConfig == 0)

/* SysTick 常量 */
#define SYSTICK_ENABLE              0                                          /* 配置第0位启动或停止滴答定时器      */
#define SYSTICK_TICKINT             1                                          /* 使能或除能滴答中断                 */
#define SYSTICK_CLKSOURCE           2                                          /* 滴答时钟源配置                     */
#define SYSTICK_MAXCOUNT       ((1<<24) -1)                                    /* 滴答最大记数                       */

 /** 
  * @函数名:	SysTick_Config
  * @描述:	初始化并启动滴答定时器，包括中断配置
  * @参数:	uint32_t ticks滴答中断周期
  * @返回值:	无
  */ 
static __INLINE uint32_t SysTick_Config(uint32_t ticks)
{ 
  if (ticks > SYSTICK_MAXCOUNT)  return (1);                                             /* 重装载除能               */

  SysTick->LOAD  =  (ticks & SYSTICK_MAXCOUNT) - 1;                                      /* 设置重装载寄存器         */
  NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);                            /* 设置滴答中断优先级       */
  SysTick->VAL   =  (0x00);                                                              /* 设置滴答计数器初始值     */
  SysTick->CTRL = (1 << SYSTICK_CLKSOURCE) | (1<<SYSTICK_ENABLE) | (1<<SYSTICK_TICKINT); /* 使能滴答定时器           */
  return (0);                                                                            /* 初始化成功 */
}

#endif





/* ##################################    Reset 函数  ############################################ */

 /** 
  * @函数名:	NVIC_SystemReset
  * @描述:	初始化一个系统复位，请求复位MCU
  * @参数:	无
  * @返回值:	无
  */
static __INLINE void NVIC_SystemReset(void)
{
  SCB->AIRCR  = (NVIC_AIRCR_VECTKEY | (1<<NVIC_SYSRESETREQ));                          /* 保持优先级分组不变   */
  __DSB();                                                                             /* 保证存储器访问已完成 */              
  while(1);                                                                            /* 等待直到复位完成     */
}


#ifdef __cplusplus
}
#endif

#endif

/**
  * @}
  */ 

/**
  * @}
  */ 

/************* (C) COPYRIGHT 2010 Wuhan R&D Center, Embest *****文件结束*******/






















