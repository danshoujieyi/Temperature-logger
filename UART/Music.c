#include "Music.h"
#include "Delay.h"

#define Bass		0
#define	Alto		1
#define	Teble		2

#define	One_Beat				1
#define	One_TWO_Beat		2
#define	One_FOUR_Beat		4


/* USER CODE END Includes */
/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PT */
	uint16_t Tone_Index[8][3]={
		{0  ,0  ,0   },
		{262,523,1046},
		{294,587,1175},
		{330,659,1318},
		{349,698,1397},
		{392,784,1568},
		{440,880,1760},
		{494,988,1976}		
	};
//	
////中速代表乐曲速度术语里的Moderato，或称中板，每分钟在88到104拍。
////中速 每分钟100拍 一拍600ms
//两只老虎简谱，没有细调
	uint16_t Music_Two_Tigers[][3]={
		{0,0,570},
		{1,Alto,One_Beat},
		{2,Alto,One_Beat},
		{3,Alto,One_Beat},
		{1,Alto,One_Beat},
		
		{0,Alto,24},
		
		{1,Alto,One_Beat},
		{2,Alto,One_Beat},
		{3,Alto,One_Beat},
		{1,Alto,One_Beat},
		
		//{0,Alto,3},
		
		{3,Alto,One_Beat},
		{4,Alto,One_Beat},
		{5,Alto,One_Beat},
		{0,Alto,One_Beat},
		
		
		{3,Alto,One_Beat},
		{4,Alto,One_Beat},
		{5,Alto,One_Beat},
		{0,Alto,One_Beat},
		
		
		{5,Alto,One_TWO_Beat},
		{6,Alto,One_TWO_Beat},
		{5,Alto,One_TWO_Beat},
		{4,Alto,One_TWO_Beat},
		{3,Alto,One_Beat},
		{1,Alto,One_Beat},
		
		//{0,Alto,3},
		
		{5,Alto,One_TWO_Beat},
		{6,Alto,One_TWO_Beat},
		{5,Alto,One_TWO_Beat},
		{4,Alto,One_TWO_Beat},
		{3,Alto,One_Beat},
		{1,Alto,One_Beat},
		
		{0,Alto,24},
		
		{1,Alto,One_Beat},
		{5,Bass,One_Beat},
		{1,Alto,One_Beat},
		{0,Alto,One_Beat},
		
		
		{1,Alto,One_Beat},
		{5,Bass,One_Beat},
		{1,Alto,One_Beat},
		{0,Alto,One_Beat},
		

	};
//中速 每分钟65拍 一拍920ms
uint16_t Music_Lone_Brave[][3]={
	//曲信息
	{0,0,920},
	
//	#define Bass		0
//	#define	Alto		1
//	#define	Teble		2
	
//	#define	One_Beat				1
//	#define	One_TWO_Beat		2
//	#define	One_FOUR_Beat		4
	
	//第一小节
	{2,Alto,One_TWO_Beat}  ,{7,Bass,One_TWO_Beat}  ,{1,Alto,One_TWO_Beat}  ,{6,Bass,One_TWO_Beat}  ,
	{2,Alto,One_TWO_Beat}  ,{7,Bass,One_TWO_Beat}  ,{1,Alto,One_TWO_Beat}  ,{6,Bass,One_TWO_Beat}  ,
	
	//第二小节	
	{2,Alto,One_TWO_Beat}  ,{7,Bass,One_TWO_Beat}  ,{1,Alto,One_TWO_Beat}  ,{6,Bass,One_TWO_Beat}  ,
	{2,Alto,One_TWO_Beat}  ,{7,Bass,One_TWO_Beat}  ,{1,Alto,One_TWO_Beat}  ,{6,Bass,One_TWO_Beat}  ,
	
	//第三小节	
	{2,Alto,One_TWO_Beat}  ,{7,Bass,One_TWO_Beat}  ,{1,Alto,One_TWO_Beat}  ,{6,Bass,One_TWO_Beat}  ,
	{2,Alto,One_TWO_Beat}  ,{7,Bass,One_TWO_Beat}  ,{1,Alto,One_TWO_Beat}  ,{6,Bass,One_TWO_Beat}  ,
	
	//第四小节	
	{2,Alto,One_TWO_Beat}  ,{7,Bass,One_TWO_Beat}  ,{1,Alto,One_TWO_Beat}  ,{6,Bass,One_TWO_Beat}  ,
	{2,Alto,One_TWO_Beat}  ,{7,Bass,One_TWO_Beat}  ,{1,Alto,One_TWO_Beat}  ,{6,Bass,One_TWO_Beat}  ,
	
	//第五小节	
	{2,Alto,One_TWO_Beat}  ,{7,Bass,One_TWO_Beat}  ,{1,Alto,One_TWO_Beat}  ,{6,Bass,One_TWO_Beat}  ,
	{2,Alto,One_TWO_Beat}  ,{7,Bass,One_TWO_Beat}  ,{1,Alto,One_TWO_Beat}  ,{6,Bass,One_TWO_Beat}  ,
	
	//第六小节	
	{3,Alto,One_Beat}		   ,{3,Alto,One_Beat}		  ,{0,Alto,One_Beat}       ,{0,Alto,One_FOUR_Beat} ,
	{1,Alto,One_FOUR_Beat} ,{2,Alto,One_FOUR_Beat},{1,Alto,One_FOUR_Beat}  ,
	
	//第七小节
	{3,Alto,One_Beat}      ,{3,Alto,One_Beat}			,{0,Alto,One_TWO_Beat}	 ,{1,Alto,One_FOUR_Beat} ,
	{2,Alto,One_FOUR_Beat} ,{1,Alto,One_FOUR_Beat},{2,Alto,One_FOUR_Beat}  ,{3,Alto,One_FOUR_Beat} ,
	
	//第八小节
	{6,Bass,One_TWO_Beat}  ,{1,Alto,One_FOUR_Beat},{6,Bass,One_TWO_Beat}	 ,{1,Alto,One_FOUR_Beat} ,
	{6,Bass,One_TWO_Beat}  ,{1,Alto,One_FOUR_Beat},{2,Alto,One_TWO_Beat}   ,{1,Alto,One_TWO_Beat}  ,
	
	//第九小节
	{7,Bass,One_TWO_Beat}  ,{7,Bass,One_FOUR_Beat},{0,Alto,One_TWO_Beat}	 ,{0,Alto,One_FOUR_Beat} ,

	//第十小节
	{3,Alto,One_Beat}		   ,{3,Alto,One_Beat}		  ,{0,Alto,One_Beat}       ,{0,Alto,One_FOUR_Beat} ,
	{1,Alto,One_FOUR_Beat} ,{2,Alto,One_FOUR_Beat},{1,Alto,One_FOUR_Beat}  ,
	
	//第十一小节
	{3,Alto,One_Beat}      ,{3,Alto,One_Beat}			,{0,Alto,One_TWO_Beat}	 ,{1,Alto,One_FOUR_Beat} ,
	{2,Alto,One_FOUR_Beat} ,{1,Alto,One_FOUR_Beat},{2,Alto,One_FOUR_Beat}  ,{3,Alto,One_FOUR_Beat} ,
	
	//第十二小节
	{6,Bass,One_TWO_Beat}  ,{1,Alto,One_FOUR_Beat},{6,Bass,One_TWO_Beat}	 ,{1,Alto,One_FOUR_Beat} ,
	{6,Bass,One_TWO_Beat}  ,{1,Alto,One_FOUR_Beat},{3,Alto,One_TWO_Beat}   ,{2,Alto,One_TWO_Beat}  ,
		
	//第十三小节
	{7,Bass,One_TWO_Beat}  ,{7,Bass,One_FOUR_Beat},{0,Alto,One_TWO_Beat}	 ,{0,Alto,One_FOUR_Beat} ,
	
	//第十四小节
	{6,Bass,One_FOUR_Beat} ,{1,Alto,One_FOUR_Beat},{6,Alto,One_TWO_Beat}	 ,{6,Alto,One_FOUR_Beat} ,
	{0,Alto,20 /*小衔接*/} ,{6,Alto,One_FOUR_Beat},{6,Alto,One_FOUR_Beat}  ,{5,Alto,One_FOUR_Beat} ,
	{6,Alto,One_TWO_Beat}  ,{6,Alto,One_FOUR_Beat},{5,Alto,One_FOUR_Beat}  ,{6,Alto,One_FOUR_Beat} ,
	{5,Alto,One_FOUR_Beat} ,{6,Alto,One_FOUR_Beat},{5,Alto,One_FOUR_Beat}  ,
	
	//第十五小节
	{3,Alto,One_FOUR_Beat} ,{3,Alto,One_TWO_Beat} ,{3,Alto,One_Beat}	     ,{0,Alto,20 /*小衔接*/} ,
	{0,Alto,One_Beat}      ,{0,Alto,One_TWO_Beat} ,{6,Bass,One_FOUR_Beat}  ,{1,Alto,One_FOUR_Beat} ,
	
	//第十六小节
	{6,Alto,One_TWO_Beat}  ,{6,Alto,One_FOUR_Beat},{0,Alto,20 /*小衔接*/}  ,{6,Alto,One_FOUR_Beat} ,
	{5,Alto,One_FOUR_Beat} ,{6,Alto,One_FOUR_Beat},{5,Alto,One_FOUR_Beat}  ,{7,Alto,One_TWO_Beat}  ,
	{7,Alto,One_FOUR_Beat} ,{0,Alto,20 /*小衔接*/},{7,Alto,One_FOUR_Beat}  ,{6,Alto,One_FOUR_Beat} ,
	{7,Alto,One_TWO_Beat}  ,
	
	//第十七小节
	{7,Alto,One_FOUR_Beat} ,{6,Alto,One_TWO_Beat} ,{3,Alto,One_FOUR_Beat}  ,{3,Alto,One_TWO_Beat}  ,
	{3,Alto,One_TWO_Beat}  ,{0,Alto,One_FOUR_Beat},{3,Alto,One_FOUR_Beat}  ,{5,Alto,One_FOUR_Beat} ,
	{3,Alto,One_FOUR_Beat} ,

	//第十八小节
	{2,Alto,One_TWO_Beat}  ,{3,Alto,One_FOUR_Beat},{2,Alto,One_TWO_Beat}   ,{3,Alto,One_FOUR_Beat} ,
	{2,Alto,One_TWO_Beat}  ,{3,Alto,One_FOUR_Beat},{5,Alto,One_FOUR_Beat}  ,{3,Alto,One_FOUR_Beat} ,
	{5,Alto,One_FOUR_Beat} ,{3,Alto,One_FOUR_Beat},
	
	//第十九小节
	{2,Alto,One_TWO_Beat}  ,{3,Alto,One_FOUR_Beat},{2,Alto,One_TWO_Beat}   ,{3,Alto,One_FOUR_Beat} ,
	{2,Alto,One_Beat}      ,{0,Alto,One_TWO_Beat} ,{1,Alto,One_FOUR_Beat}  ,{2,Alto,One_FOUR_Beat} ,
	
	//第二十小节
	{3,Alto,One_TWO_Beat}  ,{6,Bass,One_TWO_Beat} ,{1,Alto,One_TWO_Beat}   ,{3,Alto,One_TWO_Beat}  ,
	{2,Alto,One_TWO_Beat}  ,{3,Alto,One_FOUR_Beat},{2,Alto,One_FOUR_Beat}  ,{1,Alto,One_FOUR_Beat} ,
	{1,Alto,One_TWO_Beat}  ,
	
	//第二十一小节
	{6,Bass,One_Beat}      ,{6,Bass,One_Beat} 	  ,{0,Alto,One_Beat}       ,{0,Alto,One_TWO_Beat}  ,
	{6,Alto,One_FOUR_Beat} ,{7,Alto,One_FOUR_Beat},
	
	//第二十二小节
	{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{7,Alto,One_FOUR_Beat} ,{1,Teble,One_FOUR_Beat},
	{0,Alto,306 /*小衔接*/},{1,Teble,One_TWO_Beat} ,{0,Alto,306 /*小衔接*/},{1,Teble,One_FOUR_Beat},
	{7,Alto,One_FOUR_Beat} ,{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{7,Alto,One_FOUR_Beat} ,
	{1,Teble,One_FOUR_Beat},{0,Alto,306 /*小衔接*/},{1,Teble,One_TWO_Beat} ,{0,Alto,306 /*小衔接*/},
	{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	
	//第二十三小节
	{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	{3,Teble,One_TWO_Beat} ,{0,Alto,306 /*小衔接*/},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	{3,Teble,One_TWO_Beat} ,{5,Teble,One_TWO_Beat} ,{3,Teble,One_TWO_Beat} ,{6,Alto,One_FOUR_Beat} ,
	{7,Alto,One_FOUR_Beat} ,
	
	//第二十四小节
	{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{7,Alto,One_FOUR_Beat} ,{1,Teble,One_FOUR_Beat},
	{0,Alto,306 /*小衔接*/},{1,Teble,One_TWO_Beat} ,{0,Alto,306 /*小衔接*/},{1,Teble,One_FOUR_Beat},
	{7,Alto,One_FOUR_Beat} ,{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{7,Alto,One_FOUR_Beat} ,
	{1,Teble,One_FOUR_Beat},{0,Alto,306 /*小衔接*/},{1,Teble,One_TWO_Beat} ,{0,Alto,306 /*小衔接*/},
	{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	
	//第二十五小节
	{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	{3,Teble,One_TWO_Beat} ,{0,Alto,306 /*小衔接*/},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	{3,Teble,One_TWO_Beat} ,{5,Teble,One_TWO_Beat} ,{3,Teble,One_TWO_Beat} ,{5,Teble,One_TWO_Beat} ,
	
	//第二十六小节
	{3,Teble,One_TWO_Beat} ,{5,Teble,One_FOUR_Beat},{3,Teble,One_TWO_Beat} ,{5,Teble,One_FOUR_Beat},
	{3,Teble,One_FOUR_Beat},{5,Teble,One_FOUR_Beat},{6,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},
	{5,Teble,One_TWO_Beat} ,{0,Alto,184 /*小衔接*/},{5,Teble,One_TWO_Beat} ,
	
	//第二十七小节
	{3,Teble,One_TWO_Beat} ,{5,Teble,One_FOUR_Beat},{3,Teble,One_TWO_Beat} ,{5,Teble,One_FOUR_Beat},
	{3,Teble,One_FOUR_Beat},{5,Teble,One_FOUR_Beat},{6,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},
	{5,Teble,One_TWO_Beat} ,{0,Alto,184 /*小衔接*/},{5,Teble,One_TWO_Beat} ,{0,Alto,184 /*小衔接*/},
	{5,Teble,One_TWO_Beat} ,
	
	//第二十八小节
	//{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{0,Alto,184 /*小衔接*/},{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*小衔接*/},{2,Teble,One_TWO_Beat} ,
	//{1,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{0,Alto,184 /*小衔接*/},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{0,Alto,184 /*小衔接*/},
	//{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*小衔接*/},{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},{0,Alto,184 /*小衔接*/},{1,Teble,One_FOUR_Beat},
	{3,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*小衔接*/},
	{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},
	{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*小衔接*/},{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},
	{0,Alto,184 /*小衔接*/},{1,Teble,One_FOUR_Beat},
	
	//第二十九小节
	{1,Teble,One_TWO_Beat}  ,{0,Alto,One_FOUR_Beat} ,{0,Alto,One_TWO_Beat}  ,{0,Alto,One_TWO_Beat}  ,
	{5,Teble,One_FOUR_Beat},{0,Alto,184 /*小衔接*/},{5,Teble,One_FOUR_Beat},
	
	//第三十小节
	//{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{0,Alto,184 /*小衔接*/},{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*小衔接*/},{2,Teble,One_TWO_Beat} ,
	//{1,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{0,Alto,184 /*小衔接*/},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{0,Alto,184 /*小衔接*/},
	//{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*小衔接*/},{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},{0,Alto,184 /*小衔接*/},{1,Teble,One_FOUR_Beat},
	{3,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*小衔接*/},
	{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},
	{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*小衔接*/},{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},
	{0,Alto,184 /*小衔接*/},{1,Teble,One_FOUR_Beat},
	
	//第三十一小节
	{1,Teble,One_TWO_Beat} ,{0,Alto,One_Beat}      ,{0,Alto,One_Beat}      ,{0,Alto,One_Beat}      ,
//	
//	//第三十二小节
//	{0,Alto,One_Beat}      ,{0,Alto,One_Beat}      ,{0,Alto,One_Beat}      ,{0,Alto,One_Beat}      ,
//	
//	//第三十三小节
//	{0,Alto,One_Beat}      ,{0,Alto,One_Beat}      ,{0,Alto,One_Beat}      ,{0,Alto,One_Beat}      ,
	
	//第三十四小节
	{0,Alto,One_Beat}      ,{0,Alto,One_Beat}      ,{0,Alto,One_Beat}      ,{0,Alto,One_TWO_Beat}  ,
	{6,Teble,One_FOUR_Beat},{5,Alto,One_FOUR_Beat} ,
	
	//第三十五小节
	{6,Alto,One_TWO_Beat}  ,{5,Alto,One_FOUR_Beat} ,{6,Alto,One_FOUR_Beat} ,{5,Alto,One_FOUR_Beat} ,
	{6,Alto,One_FOUR_Beat} ,{5,Alto,One_FOUR_Beat} ,{6,Alto,One_TWO_Beat}  ,{0,Alto,184 /*小衔接*/},
	{6,Alto,One_FOUR_Beat} ,{5,Alto,One_FOUR_Beat} ,{6,Alto,One_FOUR_Beat} ,{5,Alto,One_FOUR_Beat} ,
	{6,Alto,One_FOUR_Beat} ,{5,Alto,One_FOUR_Beat} ,
	
	//第三十六小节
//	{3,Alto,One_FOUR_Beat} ,{3,Alto,One_TWO_Beat}  ,{3,Alto,One_Beat}       ,{0,Alto,One_Beat}     ,
//	{0,Alto,One_TWO_Beat}  ,{6,Alto,One_FOUR_Beat} ,{5,Alto,One_FOUR_Beat}  ,
	{3,Alto,One_TWO_Beat}  ,{3,Alto,One_Beat}      ,{0,Alto,One_Beat}      ,
	{0,Alto,One_TWO_Beat}  ,{6,Alto,One_FOUR_Beat} ,{5,Alto,One_FOUR_Beat} ,
	
	//第三十七小节
	{6,Alto,One_TWO_Beat}  ,{5,Alto,One_FOUR_Beat} ,{6,Alto,One_FOUR_Beat} ,{5,Alto,One_FOUR_Beat} ,
	{6,Alto,One_FOUR_Beat} ,{5,Alto,One_FOUR_Beat} ,{7,Alto,One_TWO_Beat}  ,{0,Alto,184 /*小衔接*/} ,
	{7,Alto,One_FOUR_Beat} ,{0,Alto,184 /*小衔接*/} ,{7,Alto,One_FOUR_Beat} ,{6,Alto,One_FOUR_Beat} ,
	{7,Alto,One_FOUR_Beat} ,{6,Alto,One_FOUR_Beat} ,

	//第三十八小节
//	{3,Alto,One_FOUR_Beat} ,{3,Alto,One_TWO_Beat}  ,{3,Alto,One_Beat}  ,{0,Alto,One_Beat}  ,
//	{0,Alto,One_FOUR_Beat},{3,Alto,One_FOUR_Beat}  ,{5,Alto,One_FOUR_Beat} ,{3,Alto,One_FOUR_Beat} ,
	{3,Alto,One_TWO_Beat}  ,{3,Alto,One_Beat}  ,{0,Alto,One_Beat}  ,{0,Alto,One_FOUR_Beat},
	{3,Alto,One_FOUR_Beat}  ,{5,Alto,One_FOUR_Beat} ,{3,Alto,One_FOUR_Beat} ,
	
	
	//第三十九小节
	{2,Alto,One_TWO_Beat}  ,{3,Alto,One_FOUR_Beat},{2,Alto,One_TWO_Beat}   ,{3,Alto,One_FOUR_Beat} ,
	{2,Alto,One_TWO_Beat}  ,{3,Alto,One_FOUR_Beat},{5,Alto,One_FOUR_Beat}  ,{3,Alto,One_FOUR_Beat} ,
	{5,Alto,One_FOUR_Beat} ,{3,Alto,One_FOUR_Beat},
	
	//第四十小节
	{2,Alto,One_TWO_Beat}  ,{3,Alto,One_FOUR_Beat},{2,Alto,One_TWO_Beat}   ,{3,Alto,One_FOUR_Beat} ,
	{2,Alto,One_Beat}      ,{0,Alto,One_TWO_Beat} ,{1,Alto,One_FOUR_Beat}  ,{2,Alto,One_FOUR_Beat} ,
	
	
	//第四十一小节
	{3,Alto,One_TWO_Beat}  ,{6,Alto,One_TWO_Beat} ,{1,Teble,One_TWO_Beat}   ,{3,Teble,One_TWO_Beat}  ,
	{2,Teble,One_TWO_Beat}  ,{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat}  ,{1,Teble,One_FOUR_Beat} ,
	{1,Teble,One_TWO_Beat}  ,
	
	//第四十二小节
	{6,Alto,One_Beat}  ,{0,Alto,One_Beat} ,{0,Alto,One_Beat}   ,{0,Alto,One_TWO_Beat}  ,
	{6,Alto,One_FOUR_Beat}  ,{7,Alto,One_FOUR_Beat},
	
	
	//开始第一遍循环
	//第二十二小节
	{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{7,Alto,One_FOUR_Beat} ,{1,Teble,One_FOUR_Beat},
	{0,Alto,306 /*小衔接*/},{1,Teble,One_TWO_Beat} ,{0,Alto,306 /*小衔接*/},{1,Teble,One_FOUR_Beat},
	{7,Alto,One_FOUR_Beat} ,{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{7,Alto,One_FOUR_Beat} ,
	{1,Teble,One_FOUR_Beat},{0,Alto,306 /*小衔接*/},{1,Teble,One_TWO_Beat} ,{0,Alto,306 /*小衔接*/},
	{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	
	//第二十三小节
	{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	{3,Teble,One_TWO_Beat} ,{0,Alto,306 /*小衔接*/},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	{3,Teble,One_TWO_Beat} ,{5,Teble,One_TWO_Beat} ,{3,Teble,One_TWO_Beat} ,{6,Alto,One_FOUR_Beat} ,
	{7,Alto,One_FOUR_Beat} ,
	
	//第二十四小节
	{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{7,Alto,One_FOUR_Beat} ,{1,Teble,One_FOUR_Beat},
	{0,Alto,306 /*小衔接*/},{1,Teble,One_TWO_Beat} ,{0,Alto,306 /*小衔接*/},{1,Teble,One_FOUR_Beat},
	{7,Alto,One_FOUR_Beat} ,{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{7,Alto,One_FOUR_Beat} ,
	{1,Teble,One_FOUR_Beat},{0,Alto,306 /*小衔接*/},{1,Teble,One_TWO_Beat} ,{0,Alto,306 /*小衔接*/},
	{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	
	//第二十五小节
	{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	{3,Teble,One_TWO_Beat} ,{0,Alto,306 /*小衔接*/},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	{3,Teble,One_TWO_Beat} ,{5,Teble,One_TWO_Beat} ,{3,Teble,One_TWO_Beat} ,{5,Teble,One_TWO_Beat} ,
	
	//第二十六小节
	{3,Teble,One_TWO_Beat} ,{5,Teble,One_FOUR_Beat},{3,Teble,One_TWO_Beat} ,{5,Teble,One_FOUR_Beat},
	{3,Teble,One_FOUR_Beat},{5,Teble,One_FOUR_Beat},{6,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},
	{5,Teble,One_TWO_Beat} ,{0,Alto,184 /*小衔接*/},{5,Teble,One_TWO_Beat} ,
	
	//第二十七小节
	{3,Teble,One_TWO_Beat} ,{5,Teble,One_FOUR_Beat},{3,Teble,One_TWO_Beat} ,{5,Teble,One_FOUR_Beat},
	{3,Teble,One_FOUR_Beat},{5,Teble,One_FOUR_Beat},{6,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},
	{5,Teble,One_TWO_Beat} ,{0,Alto,184 /*小衔接*/},{5,Teble,One_TWO_Beat} ,{0,Alto,184 /*小衔接*/},
	{5,Teble,One_TWO_Beat} ,
	
	//第二十八小节
	//{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{0,Alto,184 /*小衔接*/},{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*小衔接*/},{2,Teble,One_TWO_Beat} ,
	//{1,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{0,Alto,184 /*小衔接*/},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{0,Alto,184 /*小衔接*/},
	//{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*小衔接*/},{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},{0,Alto,184 /*小衔接*/},{1,Teble,One_FOUR_Beat},
	{3,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*小衔接*/},
	{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},
	{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*小衔接*/},{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},
	{0,Alto,184 /*小衔接*/},{1,Teble,One_FOUR_Beat},
	
	//第二十九小节
	{1,Teble,One_TWO_Beat}  ,{0,Alto,One_FOUR_Beat} ,{0,Alto,One_TWO_Beat}  ,{0,Alto,One_TWO_Beat}  ,
	{5,Teble,One_FOUR_Beat},{0,Alto,184 /*小衔接*/},{5,Teble,One_FOUR_Beat},
	
	//第三十小节
	//{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{0,Alto,184 /*小衔接*/},{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*小衔接*/},{2,Teble,One_TWO_Beat} ,
	//{1,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{0,Alto,184 /*小衔接*/},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{0,Alto,184 /*小衔接*/},
	//{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*小衔接*/},{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},{0,Alto,184 /*小衔接*/},{1,Teble,One_FOUR_Beat},
	{3,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*小衔接*/},
	{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},
	{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*小衔接*/},{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},
	{0,Alto,184 /*小衔接*/},{1,Teble,One_FOUR_Beat},
	
	//第一遍循环结束
	
	//第四十三小节
	{6,Alto,One_TWO_Beat}  ,{6,Alto,One_TWO_Beat} ,{1,Alto,One_TWO_Beat}  ,{3,Alto,One_TWO_Beat}  ,
	{7,Alto,One_Beat},{0,Alto,184 /*小衔接*/},{7,Alto,One_TWO_Beat},{0,Alto,184 /*小衔接*/},
	{7,Alto,One_FOUR_Beat},{0,Alto,184 /*小衔接*/},{7,Alto,One_FOUR_Beat},
	
	//第四十四小节
	//{6,Alto,One_FOUR_Beat}  ,{6,Alto,One_TWO_Beat} ,{6,Alto,One_Beat}  ,{0,Alto,One_Beat}  ,
	//{0,Alto,One_Beat},{0,Alto,One_Beat},
	{6,Alto,One_TWO_Beat} ,{6,Alto,One_TWO_Beat} ,{6,Alto,One_TWO_Beat} ,{0,Alto,One_Beat}  ,
	{0,Alto,One_Beat},{0,Alto,One_Beat},
	
	//第四十五小节
	{6,Alto,One_TWO_Beat}  ,{6,Alto,One_TWO_Beat} ,{1,Alto,One_TWO_Beat}  ,{3,Alto,One_TWO_Beat}  ,
	{7,Alto,One_Beat},{0,Alto,184 /*小衔接*/},{7,Alto,One_TWO_Beat},{0,Alto,184 /*小衔接*/},
	{7,Alto,One_FOUR_Beat},{0,Alto,184 /*小衔接*/},{7,Alto,One_FOUR_Beat},
	
	//第四十六小节
	{7,Alto,One_FOUR_Beat},{6,Alto,One_TWO_Beat},{6,Alto,One_Beat} ,{0,Alto,One_Beat},
	{0,Alto,One_TWO_Beat},{6,Alto,One_FOUR_Beat} ,{7,Alto,One_FOUR_Beat},
	
	
	//第二次循环
	//第二十二小节
	{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{7,Alto,One_FOUR_Beat} ,{1,Teble,One_FOUR_Beat},
	{0,Alto,306 /*小衔接*/},{1,Teble,One_TWO_Beat} ,{0,Alto,306 /*小衔接*/},{1,Teble,One_FOUR_Beat},
	{7,Alto,One_FOUR_Beat} ,{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{7,Alto,One_FOUR_Beat} ,
	{1,Teble,One_FOUR_Beat},{0,Alto,306 /*小衔接*/},{1,Teble,One_TWO_Beat} ,{0,Alto,306 /*小衔接*/},
	{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	
	//第二十三小节
	{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	{3,Teble,One_TWO_Beat} ,{0,Alto,306 /*小衔接*/},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	{3,Teble,One_TWO_Beat} ,{5,Teble,One_TWO_Beat} ,{3,Teble,One_TWO_Beat} ,{6,Alto,One_FOUR_Beat} ,
	{7,Alto,One_FOUR_Beat} ,
	
	//第二十四小节
	{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{7,Alto,One_FOUR_Beat} ,{1,Teble,One_FOUR_Beat},
	{0,Alto,306 /*小衔接*/},{1,Teble,One_TWO_Beat} ,{0,Alto,306 /*小衔接*/},{1,Teble,One_FOUR_Beat},
	{7,Alto,One_FOUR_Beat} ,{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{7,Alto,One_FOUR_Beat} ,
	{1,Teble,One_FOUR_Beat},{0,Alto,306 /*小衔接*/},{1,Teble,One_TWO_Beat} ,{0,Alto,306 /*小衔接*/},
	{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	
	//第二十五小节
	{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	{3,Teble,One_TWO_Beat} ,{0,Alto,306 /*小衔接*/},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	{3,Teble,One_TWO_Beat} ,{5,Teble,One_TWO_Beat} ,{3,Teble,One_TWO_Beat} ,{5,Teble,One_TWO_Beat} ,
	
	//第二十六小节
	{3,Teble,One_TWO_Beat} ,{5,Teble,One_FOUR_Beat},{3,Teble,One_TWO_Beat} ,{5,Teble,One_FOUR_Beat},
	{3,Teble,One_FOUR_Beat},{5,Teble,One_FOUR_Beat},{6,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},
	{5,Teble,One_TWO_Beat} ,{0,Alto,184 /*小衔接*/},{5,Teble,One_TWO_Beat} ,
	
	//第二十七小节
	{3,Teble,One_TWO_Beat} ,{5,Teble,One_FOUR_Beat},{3,Teble,One_TWO_Beat} ,{5,Teble,One_FOUR_Beat},
	{3,Teble,One_FOUR_Beat},{5,Teble,One_FOUR_Beat},{6,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},
	{5,Teble,One_TWO_Beat} ,{0,Alto,184 /*小衔接*/},{5,Teble,One_TWO_Beat} ,{0,Alto,184 /*小衔接*/},
	{5,Teble,One_TWO_Beat} ,
	
	//第二十八小节
	//{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{0,Alto,184 /*小衔接*/},{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*小衔接*/},{2,Teble,One_TWO_Beat} ,
	//{1,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{0,Alto,184 /*小衔接*/},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{0,Alto,184 /*小衔接*/},
	//{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*小衔接*/},{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},{0,Alto,184 /*小衔接*/},{1,Teble,One_FOUR_Beat},
	{3,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*小衔接*/},
	{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},
	{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*小衔接*/},{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},
	{0,Alto,184 /*小衔接*/},{1,Teble,One_FOUR_Beat},
	
	//第二十九小节
	{1,Teble,One_TWO_Beat}  ,{0,Alto,One_FOUR_Beat} ,{0,Alto,One_TWO_Beat}  ,{0,Alto,One_TWO_Beat}  ,
	{5,Teble,One_FOUR_Beat},{0,Alto,184 /*小衔接*/},{5,Teble,One_FOUR_Beat},
	
	//第三十小节
	//{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{0,Alto,184 /*小衔接*/},{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*小衔接*/},{2,Teble,One_TWO_Beat} ,
	//{1,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{0,Alto,184 /*小衔接*/},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{0,Alto,184 /*小衔接*/},
	//{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*小衔接*/},{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},{0,Alto,184 /*小衔接*/},{1,Teble,One_FOUR_Beat},
	{3,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*小衔接*/},
	{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},
	{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*小衔接*/},{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},
	{0,Alto,184 /*小衔接*/},{1,Teble,One_FOUR_Beat},

	//第二次循环结束
	
	//第四十七小节
	{1,Teble,One_TWO_Beat} ,{0,Alto,One_Beat}      ,{0,Alto,One_Beat}      ,{0,Alto,One_Beat}      ,

	{0,Alto,One_Beat} ,
};


/* 初始化 16 位定时器1为 PWM 模式 */
void T16B1_PWM_init(void)  
{
    LPC_SYSCON->SYSAHBCLKCTRL |= (1UL << 8) | (1UL << 16); // 使能 16 位定时器1 和 IOCON 的时钟
    LPC_IOCON->PIO1_10 |= 0x02;  // 将 PIO1_10 复用为 MAT1（PWM 功能）
    LPC_TMR16B1->TCR = 0x02;  // 复位 16 位定时器1
    LPC_TMR16B1->PR = 0;  // 无分频, 设置为 1
    LPC_TMR16B1->PWMC = 0x02;  // 配置 MAT1 为 PWM 模式
    LPC_TMR16B1->MCR = (0x02 << 9);  // 设置匹配后 TC 复位且不中断
    LPC_TMR16B1->MR3 = SystemCoreClock / 1000;  // 设置 MR3 为 1ms
    LPC_TMR16B1->MR1 = LPC_TMR16B1->MR3; // MR0 用于 PWM 输出
    LPC_TMR16B1->TCR = 0x01;  // 使能 16 位定时器1
}

void PassiveBuzzer_Init(void)
{
    LPC_SYSCON->SYSAHBCLKCTRL |= (1UL << 6); // 使能 GPIO 时钟
    LPC_GPIO1->DIR |= (1UL << 10); // 设置 PIO1_10 为输出
	LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<16);   // 禁能GPIO时钟, 保证低功耗
}



void PassiveBuzzer_Set_Freq_Duty(int freq, int duty)
{
	
   LPC_TMR16B1->MR3 = SystemCoreClock / freq -1;  // 设置 MR3 为 1ms
   LPC_TMR16B1->MR1 = LPC_TMR16B1->MR3 * duty / 100;                // 在 PWM1 模式占空比
    
}

void PassiveBuzzer_OFF(void)
{
    LPC_SYSCON->SYSAHBCLKCTRL |= (1UL << 16); /* IOCON 时钟使能 */

    LPC_IOCON->PIO1_10 &= ~0x3F; 
	LPC_GPIO1->DIR &= ~(1UL << 10); // 
    LPC_TMR16B1->MR1 = 0; // MR0 用于 PWM 输出
	LPC_TMR16B1->TCR = 0x00; // 取消使能 16 位定时器1
	LPC_SYSCON->SYSAHBCLKCTRL &= ~(1UL << 8); /* 关闭定时器时钟 */   
	
	LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<16);   // 禁能GPIO时钟, 保证低功耗
}

void PassiveBuzzer_ON(void)
{
    LPC_SYSCON->SYSAHBCLKCTRL |= (1UL << 16); /* IOCON 时钟使能 */

    LPC_IOCON->PIO1_10 |= 0x02;  // 将 PIO1_10 复用为 MAT1（PWM 功能）
    
	LPC_TMR16B1->TCR = 0x01;  // 使能 16 位定时器1
	 LPC_SYSCON->SYSAHBCLKCTRL |= (1UL << 8);  
	LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<16);   // 禁能GPIO时钟, 保证低功耗
   LPC_TMR16B1->MR3 = SystemCoreClock / 1000 -1;  // 设置 MR3 为 1ms
   LPC_TMR16B1->MR1 = LPC_TMR16B1->MR3 * 50 / 100;                // 在 PWM1 模式占空比
	
}


		


/* USER CODE END PT */
/* Function definition -------------------------------------------------------*/
/* USER CODE BEGIN FD */
/**
  * @Function name  MUSIC_Begin
  * @Introduce  		开始播放音乐						
  * @Return 				NULL
  */
void MUSIC_Brave_Lone(void){
	uint16_t MusicBeatNum = ((((sizeof(Music_Lone_Brave))/2)/3)-1);
	
	uint16_t MusicSpeed = Music_Lone_Brave[0][2];
	for(uint16_t i = 1;i<=MusicBeatNum;i++){
		//BSP_Buzzer_SetFrequency(Tone_Index[Music_Lone_Brave[i][0]][Music_Lone_Brave[i][1]]);
		PassiveBuzzer_Set_Freq_Duty(Tone_Index[Music_Lone_Brave[i][0]][Music_Lone_Brave[i][1]], 50);
		//HAL_Delay(MusicSpeed/Music_Lone_Brave[i][2]);
		T16B0_delay_ms(MusicSpeed/Music_Lone_Brave[i][2]);
	}
}

void MUSIC_Two_Tigers(void){
	uint16_t MusicBeatNum = ((((sizeof(Music_Two_Tigers))/2)/3)-1);
	
	uint16_t MusicSpeed = Music_Two_Tigers[0][2];
	for(uint16_t i = 1;i<=MusicBeatNum;i++){
		//BSP_Buzzer_SetFrequency(Tone_Index[Music_Lone_Brave[i][0]][Music_Lone_Brave[i][1]]);
		PassiveBuzzer_Set_Freq_Duty(Tone_Index[Music_Two_Tigers[i][0]][Music_Two_Tigers[i][1]], 50);
		//HAL_Delay(MusicSpeed/Music_Lone_Brave[i][2]);
		T16B0_delay_ms(MusicSpeed/Music_Two_Tigers[i][2]);
	}
}
	
