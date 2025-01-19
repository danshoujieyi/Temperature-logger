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
////���ٴ��������ٶ��������Moderato������а壬ÿ������88��104�ġ�
////���� ÿ����100�� һ��600ms
//��ֻ�ϻ����ף�û��ϸ��
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
//���� ÿ����65�� һ��920ms
uint16_t Music_Lone_Brave[][3]={
	//����Ϣ
	{0,0,920},
	
//	#define Bass		0
//	#define	Alto		1
//	#define	Teble		2
	
//	#define	One_Beat				1
//	#define	One_TWO_Beat		2
//	#define	One_FOUR_Beat		4
	
	//��һС��
	{2,Alto,One_TWO_Beat}  ,{7,Bass,One_TWO_Beat}  ,{1,Alto,One_TWO_Beat}  ,{6,Bass,One_TWO_Beat}  ,
	{2,Alto,One_TWO_Beat}  ,{7,Bass,One_TWO_Beat}  ,{1,Alto,One_TWO_Beat}  ,{6,Bass,One_TWO_Beat}  ,
	
	//�ڶ�С��	
	{2,Alto,One_TWO_Beat}  ,{7,Bass,One_TWO_Beat}  ,{1,Alto,One_TWO_Beat}  ,{6,Bass,One_TWO_Beat}  ,
	{2,Alto,One_TWO_Beat}  ,{7,Bass,One_TWO_Beat}  ,{1,Alto,One_TWO_Beat}  ,{6,Bass,One_TWO_Beat}  ,
	
	//����С��	
	{2,Alto,One_TWO_Beat}  ,{7,Bass,One_TWO_Beat}  ,{1,Alto,One_TWO_Beat}  ,{6,Bass,One_TWO_Beat}  ,
	{2,Alto,One_TWO_Beat}  ,{7,Bass,One_TWO_Beat}  ,{1,Alto,One_TWO_Beat}  ,{6,Bass,One_TWO_Beat}  ,
	
	//����С��	
	{2,Alto,One_TWO_Beat}  ,{7,Bass,One_TWO_Beat}  ,{1,Alto,One_TWO_Beat}  ,{6,Bass,One_TWO_Beat}  ,
	{2,Alto,One_TWO_Beat}  ,{7,Bass,One_TWO_Beat}  ,{1,Alto,One_TWO_Beat}  ,{6,Bass,One_TWO_Beat}  ,
	
	//����С��	
	{2,Alto,One_TWO_Beat}  ,{7,Bass,One_TWO_Beat}  ,{1,Alto,One_TWO_Beat}  ,{6,Bass,One_TWO_Beat}  ,
	{2,Alto,One_TWO_Beat}  ,{7,Bass,One_TWO_Beat}  ,{1,Alto,One_TWO_Beat}  ,{6,Bass,One_TWO_Beat}  ,
	
	//����С��	
	{3,Alto,One_Beat}		   ,{3,Alto,One_Beat}		  ,{0,Alto,One_Beat}       ,{0,Alto,One_FOUR_Beat} ,
	{1,Alto,One_FOUR_Beat} ,{2,Alto,One_FOUR_Beat},{1,Alto,One_FOUR_Beat}  ,
	
	//����С��
	{3,Alto,One_Beat}      ,{3,Alto,One_Beat}			,{0,Alto,One_TWO_Beat}	 ,{1,Alto,One_FOUR_Beat} ,
	{2,Alto,One_FOUR_Beat} ,{1,Alto,One_FOUR_Beat},{2,Alto,One_FOUR_Beat}  ,{3,Alto,One_FOUR_Beat} ,
	
	//�ڰ�С��
	{6,Bass,One_TWO_Beat}  ,{1,Alto,One_FOUR_Beat},{6,Bass,One_TWO_Beat}	 ,{1,Alto,One_FOUR_Beat} ,
	{6,Bass,One_TWO_Beat}  ,{1,Alto,One_FOUR_Beat},{2,Alto,One_TWO_Beat}   ,{1,Alto,One_TWO_Beat}  ,
	
	//�ھ�С��
	{7,Bass,One_TWO_Beat}  ,{7,Bass,One_FOUR_Beat},{0,Alto,One_TWO_Beat}	 ,{0,Alto,One_FOUR_Beat} ,

	//��ʮС��
	{3,Alto,One_Beat}		   ,{3,Alto,One_Beat}		  ,{0,Alto,One_Beat}       ,{0,Alto,One_FOUR_Beat} ,
	{1,Alto,One_FOUR_Beat} ,{2,Alto,One_FOUR_Beat},{1,Alto,One_FOUR_Beat}  ,
	
	//��ʮһС��
	{3,Alto,One_Beat}      ,{3,Alto,One_Beat}			,{0,Alto,One_TWO_Beat}	 ,{1,Alto,One_FOUR_Beat} ,
	{2,Alto,One_FOUR_Beat} ,{1,Alto,One_FOUR_Beat},{2,Alto,One_FOUR_Beat}  ,{3,Alto,One_FOUR_Beat} ,
	
	//��ʮ��С��
	{6,Bass,One_TWO_Beat}  ,{1,Alto,One_FOUR_Beat},{6,Bass,One_TWO_Beat}	 ,{1,Alto,One_FOUR_Beat} ,
	{6,Bass,One_TWO_Beat}  ,{1,Alto,One_FOUR_Beat},{3,Alto,One_TWO_Beat}   ,{2,Alto,One_TWO_Beat}  ,
		
	//��ʮ��С��
	{7,Bass,One_TWO_Beat}  ,{7,Bass,One_FOUR_Beat},{0,Alto,One_TWO_Beat}	 ,{0,Alto,One_FOUR_Beat} ,
	
	//��ʮ��С��
	{6,Bass,One_FOUR_Beat} ,{1,Alto,One_FOUR_Beat},{6,Alto,One_TWO_Beat}	 ,{6,Alto,One_FOUR_Beat} ,
	{0,Alto,20 /*С�ν�*/} ,{6,Alto,One_FOUR_Beat},{6,Alto,One_FOUR_Beat}  ,{5,Alto,One_FOUR_Beat} ,
	{6,Alto,One_TWO_Beat}  ,{6,Alto,One_FOUR_Beat},{5,Alto,One_FOUR_Beat}  ,{6,Alto,One_FOUR_Beat} ,
	{5,Alto,One_FOUR_Beat} ,{6,Alto,One_FOUR_Beat},{5,Alto,One_FOUR_Beat}  ,
	
	//��ʮ��С��
	{3,Alto,One_FOUR_Beat} ,{3,Alto,One_TWO_Beat} ,{3,Alto,One_Beat}	     ,{0,Alto,20 /*С�ν�*/} ,
	{0,Alto,One_Beat}      ,{0,Alto,One_TWO_Beat} ,{6,Bass,One_FOUR_Beat}  ,{1,Alto,One_FOUR_Beat} ,
	
	//��ʮ��С��
	{6,Alto,One_TWO_Beat}  ,{6,Alto,One_FOUR_Beat},{0,Alto,20 /*С�ν�*/}  ,{6,Alto,One_FOUR_Beat} ,
	{5,Alto,One_FOUR_Beat} ,{6,Alto,One_FOUR_Beat},{5,Alto,One_FOUR_Beat}  ,{7,Alto,One_TWO_Beat}  ,
	{7,Alto,One_FOUR_Beat} ,{0,Alto,20 /*С�ν�*/},{7,Alto,One_FOUR_Beat}  ,{6,Alto,One_FOUR_Beat} ,
	{7,Alto,One_TWO_Beat}  ,
	
	//��ʮ��С��
	{7,Alto,One_FOUR_Beat} ,{6,Alto,One_TWO_Beat} ,{3,Alto,One_FOUR_Beat}  ,{3,Alto,One_TWO_Beat}  ,
	{3,Alto,One_TWO_Beat}  ,{0,Alto,One_FOUR_Beat},{3,Alto,One_FOUR_Beat}  ,{5,Alto,One_FOUR_Beat} ,
	{3,Alto,One_FOUR_Beat} ,

	//��ʮ��С��
	{2,Alto,One_TWO_Beat}  ,{3,Alto,One_FOUR_Beat},{2,Alto,One_TWO_Beat}   ,{3,Alto,One_FOUR_Beat} ,
	{2,Alto,One_TWO_Beat}  ,{3,Alto,One_FOUR_Beat},{5,Alto,One_FOUR_Beat}  ,{3,Alto,One_FOUR_Beat} ,
	{5,Alto,One_FOUR_Beat} ,{3,Alto,One_FOUR_Beat},
	
	//��ʮ��С��
	{2,Alto,One_TWO_Beat}  ,{3,Alto,One_FOUR_Beat},{2,Alto,One_TWO_Beat}   ,{3,Alto,One_FOUR_Beat} ,
	{2,Alto,One_Beat}      ,{0,Alto,One_TWO_Beat} ,{1,Alto,One_FOUR_Beat}  ,{2,Alto,One_FOUR_Beat} ,
	
	//�ڶ�ʮС��
	{3,Alto,One_TWO_Beat}  ,{6,Bass,One_TWO_Beat} ,{1,Alto,One_TWO_Beat}   ,{3,Alto,One_TWO_Beat}  ,
	{2,Alto,One_TWO_Beat}  ,{3,Alto,One_FOUR_Beat},{2,Alto,One_FOUR_Beat}  ,{1,Alto,One_FOUR_Beat} ,
	{1,Alto,One_TWO_Beat}  ,
	
	//�ڶ�ʮһС��
	{6,Bass,One_Beat}      ,{6,Bass,One_Beat} 	  ,{0,Alto,One_Beat}       ,{0,Alto,One_TWO_Beat}  ,
	{6,Alto,One_FOUR_Beat} ,{7,Alto,One_FOUR_Beat},
	
	//�ڶ�ʮ��С��
	{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{7,Alto,One_FOUR_Beat} ,{1,Teble,One_FOUR_Beat},
	{0,Alto,306 /*С�ν�*/},{1,Teble,One_TWO_Beat} ,{0,Alto,306 /*С�ν�*/},{1,Teble,One_FOUR_Beat},
	{7,Alto,One_FOUR_Beat} ,{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{7,Alto,One_FOUR_Beat} ,
	{1,Teble,One_FOUR_Beat},{0,Alto,306 /*С�ν�*/},{1,Teble,One_TWO_Beat} ,{0,Alto,306 /*С�ν�*/},
	{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	
	//�ڶ�ʮ��С��
	{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	{3,Teble,One_TWO_Beat} ,{0,Alto,306 /*С�ν�*/},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	{3,Teble,One_TWO_Beat} ,{5,Teble,One_TWO_Beat} ,{3,Teble,One_TWO_Beat} ,{6,Alto,One_FOUR_Beat} ,
	{7,Alto,One_FOUR_Beat} ,
	
	//�ڶ�ʮ��С��
	{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{7,Alto,One_FOUR_Beat} ,{1,Teble,One_FOUR_Beat},
	{0,Alto,306 /*С�ν�*/},{1,Teble,One_TWO_Beat} ,{0,Alto,306 /*С�ν�*/},{1,Teble,One_FOUR_Beat},
	{7,Alto,One_FOUR_Beat} ,{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{7,Alto,One_FOUR_Beat} ,
	{1,Teble,One_FOUR_Beat},{0,Alto,306 /*С�ν�*/},{1,Teble,One_TWO_Beat} ,{0,Alto,306 /*С�ν�*/},
	{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	
	//�ڶ�ʮ��С��
	{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	{3,Teble,One_TWO_Beat} ,{0,Alto,306 /*С�ν�*/},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	{3,Teble,One_TWO_Beat} ,{5,Teble,One_TWO_Beat} ,{3,Teble,One_TWO_Beat} ,{5,Teble,One_TWO_Beat} ,
	
	//�ڶ�ʮ��С��
	{3,Teble,One_TWO_Beat} ,{5,Teble,One_FOUR_Beat},{3,Teble,One_TWO_Beat} ,{5,Teble,One_FOUR_Beat},
	{3,Teble,One_FOUR_Beat},{5,Teble,One_FOUR_Beat},{6,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},
	{5,Teble,One_TWO_Beat} ,{0,Alto,184 /*С�ν�*/},{5,Teble,One_TWO_Beat} ,
	
	//�ڶ�ʮ��С��
	{3,Teble,One_TWO_Beat} ,{5,Teble,One_FOUR_Beat},{3,Teble,One_TWO_Beat} ,{5,Teble,One_FOUR_Beat},
	{3,Teble,One_FOUR_Beat},{5,Teble,One_FOUR_Beat},{6,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},
	{5,Teble,One_TWO_Beat} ,{0,Alto,184 /*С�ν�*/},{5,Teble,One_TWO_Beat} ,{0,Alto,184 /*С�ν�*/},
	{5,Teble,One_TWO_Beat} ,
	
	//�ڶ�ʮ��С��
	//{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{0,Alto,184 /*С�ν�*/},{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*С�ν�*/},{2,Teble,One_TWO_Beat} ,
	//{1,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{0,Alto,184 /*С�ν�*/},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{0,Alto,184 /*С�ν�*/},
	//{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*С�ν�*/},{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},{0,Alto,184 /*С�ν�*/},{1,Teble,One_FOUR_Beat},
	{3,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*С�ν�*/},
	{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},
	{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*С�ν�*/},{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},
	{0,Alto,184 /*С�ν�*/},{1,Teble,One_FOUR_Beat},
	
	//�ڶ�ʮ��С��
	{1,Teble,One_TWO_Beat}  ,{0,Alto,One_FOUR_Beat} ,{0,Alto,One_TWO_Beat}  ,{0,Alto,One_TWO_Beat}  ,
	{5,Teble,One_FOUR_Beat},{0,Alto,184 /*С�ν�*/},{5,Teble,One_FOUR_Beat},
	
	//����ʮС��
	//{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{0,Alto,184 /*С�ν�*/},{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*С�ν�*/},{2,Teble,One_TWO_Beat} ,
	//{1,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{0,Alto,184 /*С�ν�*/},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{0,Alto,184 /*С�ν�*/},
	//{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*С�ν�*/},{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},{0,Alto,184 /*С�ν�*/},{1,Teble,One_FOUR_Beat},
	{3,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*С�ν�*/},
	{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},
	{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*С�ν�*/},{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},
	{0,Alto,184 /*С�ν�*/},{1,Teble,One_FOUR_Beat},
	
	//����ʮһС��
	{1,Teble,One_TWO_Beat} ,{0,Alto,One_Beat}      ,{0,Alto,One_Beat}      ,{0,Alto,One_Beat}      ,
//	
//	//����ʮ��С��
//	{0,Alto,One_Beat}      ,{0,Alto,One_Beat}      ,{0,Alto,One_Beat}      ,{0,Alto,One_Beat}      ,
//	
//	//����ʮ��С��
//	{0,Alto,One_Beat}      ,{0,Alto,One_Beat}      ,{0,Alto,One_Beat}      ,{0,Alto,One_Beat}      ,
	
	//����ʮ��С��
	{0,Alto,One_Beat}      ,{0,Alto,One_Beat}      ,{0,Alto,One_Beat}      ,{0,Alto,One_TWO_Beat}  ,
	{6,Teble,One_FOUR_Beat},{5,Alto,One_FOUR_Beat} ,
	
	//����ʮ��С��
	{6,Alto,One_TWO_Beat}  ,{5,Alto,One_FOUR_Beat} ,{6,Alto,One_FOUR_Beat} ,{5,Alto,One_FOUR_Beat} ,
	{6,Alto,One_FOUR_Beat} ,{5,Alto,One_FOUR_Beat} ,{6,Alto,One_TWO_Beat}  ,{0,Alto,184 /*С�ν�*/},
	{6,Alto,One_FOUR_Beat} ,{5,Alto,One_FOUR_Beat} ,{6,Alto,One_FOUR_Beat} ,{5,Alto,One_FOUR_Beat} ,
	{6,Alto,One_FOUR_Beat} ,{5,Alto,One_FOUR_Beat} ,
	
	//����ʮ��С��
//	{3,Alto,One_FOUR_Beat} ,{3,Alto,One_TWO_Beat}  ,{3,Alto,One_Beat}       ,{0,Alto,One_Beat}     ,
//	{0,Alto,One_TWO_Beat}  ,{6,Alto,One_FOUR_Beat} ,{5,Alto,One_FOUR_Beat}  ,
	{3,Alto,One_TWO_Beat}  ,{3,Alto,One_Beat}      ,{0,Alto,One_Beat}      ,
	{0,Alto,One_TWO_Beat}  ,{6,Alto,One_FOUR_Beat} ,{5,Alto,One_FOUR_Beat} ,
	
	//����ʮ��С��
	{6,Alto,One_TWO_Beat}  ,{5,Alto,One_FOUR_Beat} ,{6,Alto,One_FOUR_Beat} ,{5,Alto,One_FOUR_Beat} ,
	{6,Alto,One_FOUR_Beat} ,{5,Alto,One_FOUR_Beat} ,{7,Alto,One_TWO_Beat}  ,{0,Alto,184 /*С�ν�*/} ,
	{7,Alto,One_FOUR_Beat} ,{0,Alto,184 /*С�ν�*/} ,{7,Alto,One_FOUR_Beat} ,{6,Alto,One_FOUR_Beat} ,
	{7,Alto,One_FOUR_Beat} ,{6,Alto,One_FOUR_Beat} ,

	//����ʮ��С��
//	{3,Alto,One_FOUR_Beat} ,{3,Alto,One_TWO_Beat}  ,{3,Alto,One_Beat}  ,{0,Alto,One_Beat}  ,
//	{0,Alto,One_FOUR_Beat},{3,Alto,One_FOUR_Beat}  ,{5,Alto,One_FOUR_Beat} ,{3,Alto,One_FOUR_Beat} ,
	{3,Alto,One_TWO_Beat}  ,{3,Alto,One_Beat}  ,{0,Alto,One_Beat}  ,{0,Alto,One_FOUR_Beat},
	{3,Alto,One_FOUR_Beat}  ,{5,Alto,One_FOUR_Beat} ,{3,Alto,One_FOUR_Beat} ,
	
	
	//����ʮ��С��
	{2,Alto,One_TWO_Beat}  ,{3,Alto,One_FOUR_Beat},{2,Alto,One_TWO_Beat}   ,{3,Alto,One_FOUR_Beat} ,
	{2,Alto,One_TWO_Beat}  ,{3,Alto,One_FOUR_Beat},{5,Alto,One_FOUR_Beat}  ,{3,Alto,One_FOUR_Beat} ,
	{5,Alto,One_FOUR_Beat} ,{3,Alto,One_FOUR_Beat},
	
	//����ʮС��
	{2,Alto,One_TWO_Beat}  ,{3,Alto,One_FOUR_Beat},{2,Alto,One_TWO_Beat}   ,{3,Alto,One_FOUR_Beat} ,
	{2,Alto,One_Beat}      ,{0,Alto,One_TWO_Beat} ,{1,Alto,One_FOUR_Beat}  ,{2,Alto,One_FOUR_Beat} ,
	
	
	//����ʮһС��
	{3,Alto,One_TWO_Beat}  ,{6,Alto,One_TWO_Beat} ,{1,Teble,One_TWO_Beat}   ,{3,Teble,One_TWO_Beat}  ,
	{2,Teble,One_TWO_Beat}  ,{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat}  ,{1,Teble,One_FOUR_Beat} ,
	{1,Teble,One_TWO_Beat}  ,
	
	//����ʮ��С��
	{6,Alto,One_Beat}  ,{0,Alto,One_Beat} ,{0,Alto,One_Beat}   ,{0,Alto,One_TWO_Beat}  ,
	{6,Alto,One_FOUR_Beat}  ,{7,Alto,One_FOUR_Beat},
	
	
	//��ʼ��һ��ѭ��
	//�ڶ�ʮ��С��
	{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{7,Alto,One_FOUR_Beat} ,{1,Teble,One_FOUR_Beat},
	{0,Alto,306 /*С�ν�*/},{1,Teble,One_TWO_Beat} ,{0,Alto,306 /*С�ν�*/},{1,Teble,One_FOUR_Beat},
	{7,Alto,One_FOUR_Beat} ,{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{7,Alto,One_FOUR_Beat} ,
	{1,Teble,One_FOUR_Beat},{0,Alto,306 /*С�ν�*/},{1,Teble,One_TWO_Beat} ,{0,Alto,306 /*С�ν�*/},
	{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	
	//�ڶ�ʮ��С��
	{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	{3,Teble,One_TWO_Beat} ,{0,Alto,306 /*С�ν�*/},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	{3,Teble,One_TWO_Beat} ,{5,Teble,One_TWO_Beat} ,{3,Teble,One_TWO_Beat} ,{6,Alto,One_FOUR_Beat} ,
	{7,Alto,One_FOUR_Beat} ,
	
	//�ڶ�ʮ��С��
	{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{7,Alto,One_FOUR_Beat} ,{1,Teble,One_FOUR_Beat},
	{0,Alto,306 /*С�ν�*/},{1,Teble,One_TWO_Beat} ,{0,Alto,306 /*С�ν�*/},{1,Teble,One_FOUR_Beat},
	{7,Alto,One_FOUR_Beat} ,{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{7,Alto,One_FOUR_Beat} ,
	{1,Teble,One_FOUR_Beat},{0,Alto,306 /*С�ν�*/},{1,Teble,One_TWO_Beat} ,{0,Alto,306 /*С�ν�*/},
	{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	
	//�ڶ�ʮ��С��
	{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	{3,Teble,One_TWO_Beat} ,{0,Alto,306 /*С�ν�*/},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	{3,Teble,One_TWO_Beat} ,{5,Teble,One_TWO_Beat} ,{3,Teble,One_TWO_Beat} ,{5,Teble,One_TWO_Beat} ,
	
	//�ڶ�ʮ��С��
	{3,Teble,One_TWO_Beat} ,{5,Teble,One_FOUR_Beat},{3,Teble,One_TWO_Beat} ,{5,Teble,One_FOUR_Beat},
	{3,Teble,One_FOUR_Beat},{5,Teble,One_FOUR_Beat},{6,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},
	{5,Teble,One_TWO_Beat} ,{0,Alto,184 /*С�ν�*/},{5,Teble,One_TWO_Beat} ,
	
	//�ڶ�ʮ��С��
	{3,Teble,One_TWO_Beat} ,{5,Teble,One_FOUR_Beat},{3,Teble,One_TWO_Beat} ,{5,Teble,One_FOUR_Beat},
	{3,Teble,One_FOUR_Beat},{5,Teble,One_FOUR_Beat},{6,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},
	{5,Teble,One_TWO_Beat} ,{0,Alto,184 /*С�ν�*/},{5,Teble,One_TWO_Beat} ,{0,Alto,184 /*С�ν�*/},
	{5,Teble,One_TWO_Beat} ,
	
	//�ڶ�ʮ��С��
	//{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{0,Alto,184 /*С�ν�*/},{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*С�ν�*/},{2,Teble,One_TWO_Beat} ,
	//{1,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{0,Alto,184 /*С�ν�*/},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{0,Alto,184 /*С�ν�*/},
	//{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*С�ν�*/},{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},{0,Alto,184 /*С�ν�*/},{1,Teble,One_FOUR_Beat},
	{3,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*С�ν�*/},
	{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},
	{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*С�ν�*/},{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},
	{0,Alto,184 /*С�ν�*/},{1,Teble,One_FOUR_Beat},
	
	//�ڶ�ʮ��С��
	{1,Teble,One_TWO_Beat}  ,{0,Alto,One_FOUR_Beat} ,{0,Alto,One_TWO_Beat}  ,{0,Alto,One_TWO_Beat}  ,
	{5,Teble,One_FOUR_Beat},{0,Alto,184 /*С�ν�*/},{5,Teble,One_FOUR_Beat},
	
	//����ʮС��
	//{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{0,Alto,184 /*С�ν�*/},{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*С�ν�*/},{2,Teble,One_TWO_Beat} ,
	//{1,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{0,Alto,184 /*С�ν�*/},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{0,Alto,184 /*С�ν�*/},
	//{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*С�ν�*/},{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},{0,Alto,184 /*С�ν�*/},{1,Teble,One_FOUR_Beat},
	{3,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*С�ν�*/},
	{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},
	{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*С�ν�*/},{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},
	{0,Alto,184 /*С�ν�*/},{1,Teble,One_FOUR_Beat},
	
	//��һ��ѭ������
	
	//����ʮ��С��
	{6,Alto,One_TWO_Beat}  ,{6,Alto,One_TWO_Beat} ,{1,Alto,One_TWO_Beat}  ,{3,Alto,One_TWO_Beat}  ,
	{7,Alto,One_Beat},{0,Alto,184 /*С�ν�*/},{7,Alto,One_TWO_Beat},{0,Alto,184 /*С�ν�*/},
	{7,Alto,One_FOUR_Beat},{0,Alto,184 /*С�ν�*/},{7,Alto,One_FOUR_Beat},
	
	//����ʮ��С��
	//{6,Alto,One_FOUR_Beat}  ,{6,Alto,One_TWO_Beat} ,{6,Alto,One_Beat}  ,{0,Alto,One_Beat}  ,
	//{0,Alto,One_Beat},{0,Alto,One_Beat},
	{6,Alto,One_TWO_Beat} ,{6,Alto,One_TWO_Beat} ,{6,Alto,One_TWO_Beat} ,{0,Alto,One_Beat}  ,
	{0,Alto,One_Beat},{0,Alto,One_Beat},
	
	//����ʮ��С��
	{6,Alto,One_TWO_Beat}  ,{6,Alto,One_TWO_Beat} ,{1,Alto,One_TWO_Beat}  ,{3,Alto,One_TWO_Beat}  ,
	{7,Alto,One_Beat},{0,Alto,184 /*С�ν�*/},{7,Alto,One_TWO_Beat},{0,Alto,184 /*С�ν�*/},
	{7,Alto,One_FOUR_Beat},{0,Alto,184 /*С�ν�*/},{7,Alto,One_FOUR_Beat},
	
	//����ʮ��С��
	{7,Alto,One_FOUR_Beat},{6,Alto,One_TWO_Beat},{6,Alto,One_Beat} ,{0,Alto,One_Beat},
	{0,Alto,One_TWO_Beat},{6,Alto,One_FOUR_Beat} ,{7,Alto,One_FOUR_Beat},
	
	
	//�ڶ���ѭ��
	//�ڶ�ʮ��С��
	{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{7,Alto,One_FOUR_Beat} ,{1,Teble,One_FOUR_Beat},
	{0,Alto,306 /*С�ν�*/},{1,Teble,One_TWO_Beat} ,{0,Alto,306 /*С�ν�*/},{1,Teble,One_FOUR_Beat},
	{7,Alto,One_FOUR_Beat} ,{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{7,Alto,One_FOUR_Beat} ,
	{1,Teble,One_FOUR_Beat},{0,Alto,306 /*С�ν�*/},{1,Teble,One_TWO_Beat} ,{0,Alto,306 /*С�ν�*/},
	{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	
	//�ڶ�ʮ��С��
	{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	{3,Teble,One_TWO_Beat} ,{0,Alto,306 /*С�ν�*/},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	{3,Teble,One_TWO_Beat} ,{5,Teble,One_TWO_Beat} ,{3,Teble,One_TWO_Beat} ,{6,Alto,One_FOUR_Beat} ,
	{7,Alto,One_FOUR_Beat} ,
	
	//�ڶ�ʮ��С��
	{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{7,Alto,One_FOUR_Beat} ,{1,Teble,One_FOUR_Beat},
	{0,Alto,306 /*С�ν�*/},{1,Teble,One_TWO_Beat} ,{0,Alto,306 /*С�ν�*/},{1,Teble,One_FOUR_Beat},
	{7,Alto,One_FOUR_Beat} ,{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{7,Alto,One_FOUR_Beat} ,
	{1,Teble,One_FOUR_Beat},{0,Alto,306 /*С�ν�*/},{1,Teble,One_TWO_Beat} ,{0,Alto,306 /*С�ν�*/},
	{1,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	
	//�ڶ�ʮ��С��
	{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	{3,Teble,One_TWO_Beat} ,{0,Alto,306 /*С�ν�*/},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},
	{3,Teble,One_TWO_Beat} ,{5,Teble,One_TWO_Beat} ,{3,Teble,One_TWO_Beat} ,{5,Teble,One_TWO_Beat} ,
	
	//�ڶ�ʮ��С��
	{3,Teble,One_TWO_Beat} ,{5,Teble,One_FOUR_Beat},{3,Teble,One_TWO_Beat} ,{5,Teble,One_FOUR_Beat},
	{3,Teble,One_FOUR_Beat},{5,Teble,One_FOUR_Beat},{6,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},
	{5,Teble,One_TWO_Beat} ,{0,Alto,184 /*С�ν�*/},{5,Teble,One_TWO_Beat} ,
	
	//�ڶ�ʮ��С��
	{3,Teble,One_TWO_Beat} ,{5,Teble,One_FOUR_Beat},{3,Teble,One_TWO_Beat} ,{5,Teble,One_FOUR_Beat},
	{3,Teble,One_FOUR_Beat},{5,Teble,One_FOUR_Beat},{6,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},
	{5,Teble,One_TWO_Beat} ,{0,Alto,184 /*С�ν�*/},{5,Teble,One_TWO_Beat} ,{0,Alto,184 /*С�ν�*/},
	{5,Teble,One_TWO_Beat} ,
	
	//�ڶ�ʮ��С��
	//{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{0,Alto,184 /*С�ν�*/},{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*С�ν�*/},{2,Teble,One_TWO_Beat} ,
	//{1,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{0,Alto,184 /*С�ν�*/},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{0,Alto,184 /*С�ν�*/},
	//{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*С�ν�*/},{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},{0,Alto,184 /*С�ν�*/},{1,Teble,One_FOUR_Beat},
	{3,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*С�ν�*/},
	{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},
	{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*С�ν�*/},{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},
	{0,Alto,184 /*С�ν�*/},{1,Teble,One_FOUR_Beat},
	
	//�ڶ�ʮ��С��
	{1,Teble,One_TWO_Beat}  ,{0,Alto,One_FOUR_Beat} ,{0,Alto,One_TWO_Beat}  ,{0,Alto,One_TWO_Beat}  ,
	{5,Teble,One_FOUR_Beat},{0,Alto,184 /*С�ν�*/},{5,Teble,One_FOUR_Beat},
	
	//����ʮС��
	//{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{0,Alto,184 /*С�ν�*/},{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*С�ν�*/},{2,Teble,One_TWO_Beat} ,
	//{1,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{0,Alto,184 /*С�ν�*/},{3,Teble,One_FOUR_Beat},{2,Teble,One_FOUR_Beat},{0,Alto,184 /*С�ν�*/},
	//{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*С�ν�*/},{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},{0,Alto,184 /*С�ν�*/},{1,Teble,One_FOUR_Beat},
	{3,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*С�ν�*/},
	{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},{3,Teble,One_FOUR_Beat},
	{2,Teble,One_TWO_Beat} ,{0,Alto,184 /*С�ν�*/},{2,Teble,One_TWO_Beat} ,{1,Teble,One_FOUR_Beat},
	{0,Alto,184 /*С�ν�*/},{1,Teble,One_FOUR_Beat},

	//�ڶ���ѭ������
	
	//����ʮ��С��
	{1,Teble,One_TWO_Beat} ,{0,Alto,One_Beat}      ,{0,Alto,One_Beat}      ,{0,Alto,One_Beat}      ,

	{0,Alto,One_Beat} ,
};


/* ��ʼ�� 16 λ��ʱ��1Ϊ PWM ģʽ */
void T16B1_PWM_init(void)  
{
    LPC_SYSCON->SYSAHBCLKCTRL |= (1UL << 8) | (1UL << 16); // ʹ�� 16 λ��ʱ��1 �� IOCON ��ʱ��
    LPC_IOCON->PIO1_10 |= 0x02;  // �� PIO1_10 ����Ϊ MAT1��PWM ���ܣ�
    LPC_TMR16B1->TCR = 0x02;  // ��λ 16 λ��ʱ��1
    LPC_TMR16B1->PR = 0;  // �޷�Ƶ, ����Ϊ 1
    LPC_TMR16B1->PWMC = 0x02;  // ���� MAT1 Ϊ PWM ģʽ
    LPC_TMR16B1->MCR = (0x02 << 9);  // ����ƥ��� TC ��λ�Ҳ��ж�
    LPC_TMR16B1->MR3 = SystemCoreClock / 1000;  // ���� MR3 Ϊ 1ms
    LPC_TMR16B1->MR1 = LPC_TMR16B1->MR3; // MR0 ���� PWM ���
    LPC_TMR16B1->TCR = 0x01;  // ʹ�� 16 λ��ʱ��1
}

void PassiveBuzzer_Init(void)
{
    LPC_SYSCON->SYSAHBCLKCTRL |= (1UL << 6); // ʹ�� GPIO ʱ��
    LPC_GPIO1->DIR |= (1UL << 10); // ���� PIO1_10 Ϊ���
	LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<16);   // ����GPIOʱ��, ��֤�͹���
}



void PassiveBuzzer_Set_Freq_Duty(int freq, int duty)
{
	
   LPC_TMR16B1->MR3 = SystemCoreClock / freq -1;  // ���� MR3 Ϊ 1ms
   LPC_TMR16B1->MR1 = LPC_TMR16B1->MR3 * duty / 100;                // �� PWM1 ģʽռ�ձ�
    
}

void PassiveBuzzer_OFF(void)
{
    LPC_SYSCON->SYSAHBCLKCTRL |= (1UL << 16); /* IOCON ʱ��ʹ�� */

    LPC_IOCON->PIO1_10 &= ~0x3F; 
	LPC_GPIO1->DIR &= ~(1UL << 10); // 
    LPC_TMR16B1->MR1 = 0; // MR0 ���� PWM ���
	LPC_TMR16B1->TCR = 0x00; // ȡ��ʹ�� 16 λ��ʱ��1
	LPC_SYSCON->SYSAHBCLKCTRL &= ~(1UL << 8); /* �رն�ʱ��ʱ�� */   
	
	LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<16);   // ����GPIOʱ��, ��֤�͹���
}

void PassiveBuzzer_ON(void)
{
    LPC_SYSCON->SYSAHBCLKCTRL |= (1UL << 16); /* IOCON ʱ��ʹ�� */

    LPC_IOCON->PIO1_10 |= 0x02;  // �� PIO1_10 ����Ϊ MAT1��PWM ���ܣ�
    
	LPC_TMR16B1->TCR = 0x01;  // ʹ�� 16 λ��ʱ��1
	 LPC_SYSCON->SYSAHBCLKCTRL |= (1UL << 8);  
	LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<16);   // ����GPIOʱ��, ��֤�͹���
   LPC_TMR16B1->MR3 = SystemCoreClock / 1000 -1;  // ���� MR3 Ϊ 1ms
   LPC_TMR16B1->MR1 = LPC_TMR16B1->MR3 * 50 / 100;                // �� PWM1 ģʽռ�ձ�
	
}


		


/* USER CODE END PT */
/* Function definition -------------------------------------------------------*/
/* USER CODE BEGIN FD */
/**
  * @Function name  MUSIC_Begin
  * @Introduce  		��ʼ��������						
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
	
