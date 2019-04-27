//*************************************************************************************************
//  Copyright (c) 	��������Ԫ΢�������޹�˾
//	�ļ�����	:  S_TouchKeyCFG.c
//	����		: 
//	ģ�鹦��	:  SC91F844���ؼ������ļ�
// 	�汾		:
// 	���ļ�¼	:
//	ע������	:  �û���Ҫ���õ��ļ���S_TouchKeyCFG.h��
//  ��汾���	: 
//************************************************************************************************
#include "lib\S_TouchKeyCFG.h"

//*************************************************************************************
//		844 �Ĵ�������
//*************************************************************************************
/*PSW*/
sfr 	TK_PSW	    = 	0xD0;	//����״̬��
sbit 	TK_CY		= 	TK_PSW^7;	//��λ  

sfr	    BTMCON      =   0XCE;   //��Ƶ��ʱ�����ƼĴ���
sfr 	TK_IE1	    = 	0xA9;								//�жϿ��ƼĴ�
/*system*/
sfr 	PCON	    =   0x87;		//��Դ�������ƼĴ���

sfr		TKCR	=	0xE8;								//TouchKey���ƼĴ���

sfr 	TKTMH	=	0xE7;								//����������ʱ�Ĵ���L
sfr 	TKTML	=	0xE6;								//����������ʱ�Ĵ���L
sfr16   TKTM    =   0xE6;

sfr		TKCNTH	=	0xE5;								//TouchKey������ֵ��7λ
sfr		TKCNTL	=	0xE4;								//TouchKey������ֵ��8λ
sfr16   TKCNT   =   0xE4;

sfr 	TKCFG2	=	0xE3;								//���������ο���ѹ���üĴ���
sfr		TKCFG1	=	0xE2;								//TouchKey���üĴ���2
sfr		TKCFG0	=	0xE1;								//TouchKey���üĴ���1

/*TKCR*/
sbit	ENTKS	=	TKCR^7;								//TouchKey���ص�Դ
sbit	TRIG	=	TKCR^6;								//TouchKey�������أ�д1��Ч������һ��keyɨ������
sbit	TRIF	=	TKCR^5;								//TouchKey�жϱ�־
//===========================================================================
//ȫ�ֱ�������
unsigned	char	xdata		SOCAPI_TouchKeyStatus;					//API�ӿ�״̬��bit7-һ��ɨ����ɱ�־  1:��� 	0��δ���
																	    //			   bit6-ͨ���������������־ 1:���	 0:δ���
//===============================================================================
//ȫ�ֱ��������������򲻿��޸�
unsigned 	int 	xdata		RawData [SOCAPI_SET_TOUCHKEY_TOTAL];			
unsigned 	int		xdata		BaseLine[SOCAPI_SET_TOUCHKEY_TOTAL];
unsigned    int	 	xdata		FilterData[SOCAPI_SET_TOUCHKEY_TOTAL];												
unsigned	char    xdata		RestAreaCnt[SOCAPI_SET_TOUCHKEY_TOTAL]; 			
unsigned	char    xdata		TouchCnt[SOCAPI_SET_TOUCHKEY_TOTAL];				
unsigned	char    xdata		NoTouchCnt[SOCAPI_SET_TOUCHKEY_TOTAL];  			
unsigned	char	xdata		CurrentChannel[SOCAPI_SET_TOUCHKEY_TOTAL];						     
unsigned    char    xdata 	    LowFingerDataCnt[SOCAPI_SET_TOUCHKEY_TOTAL];
unsigned	char    xdata		FloatAreaCnt[SOCAPI_SET_TOUCHKEY_TOTAL]; 
unsigned 	char 	xdata 	    BaseLineAdjusttmp[SOCAPI_SET_TOUCHKEY_TOTAL]; 	
int                 xdata 	    DifferAccum[SOCAPI_SET_TOUCHKEY_TOTAL]; 
char	            xdata		SetNoiseThreshold;
unsigned 	char	xdata		ConfirmTouchCnt;
unsigned 	char	xdata		MultipleDealTpye = 0; 

//�Զ������
unsigned 	int 	xdata  	    UpdateBaseLNum; 						// ��������������
unsigned 	int 	xdata  	    MultipleLNum;						// �ఴ�����ż���
bit  WakeUp_Flag = 0;
//�ⲿ�����ӿ�
extern 	unsigned	char	data		CurrentChannelMax;		//��ǰѡ�е�keysensor�ĸ���
extern  bit  bMultiple;	//�ఴ����־	
extern 	bit  GetIsNeedUpdateBaseline(void);
extern  void SetNeedUpdateBaseline(void);
extern  unsigned long int SensorKeyFlag(void);
extern  void MultipleDeal(unsigned char CycleCnt);
extern  void FilterDataDeal(unsigned char i);
extern unsigned 	int     xdata       ScanTime;


/***************���ɿ����***************/
#define		SOCAPI_SET_CS_FUNCTION						1		//0:��ʾ������CS����,1: ��ʾ����CS����,Ĭ��0
#define		SOCAPI_INHIBITION_ZONE					    8		//��������%�����÷�Χ5-10��Ĭ��7,����7*10��%=70% ����ˮʱ�Ӵ�ò���,�Խ�������С
#define		SOCAPI_MAX_KEY_MUTIPLE						300		//���ٴθ��Ÿ��»��ߣ�Ĭ��300*5=1500
#define		SOCAPI_MAX_KEY_NUM_INVALID					3		//ǿ�Ƹ��»��߰������Ƹ�����Ĭ��3
/****************************************/

#define	  	AppType			     			0
#define	  	IsDoubleKey			 			1
#define	  	AirSeparationDistance	 	    2
#define   	CONFIRMTOUCHCNT        	        3
#define   	INIT_AUTO_UPDATE_TIME	 	    4
#define   	SET_KEY_CONTI_TIME     	        5  
#define   	SET_SYNC_UPDATE 		 		6
#define   	SET_UPDATE_SPEED 		 		7	
#define   	AUTO_UPDATE_TIME	     	    8
#define	  	FilteredKValue		 			9
#define	  	SET_ANTIJAM		     			10
#define	  	BAUD		             		11
#define	  	DwellTime		         		12
#define   	SaveTime					    13
#define   	NOISE                  	        16

#define   	SET_TOUCH_FREQ		 			0
#define	  	SET_RESOLUTION		 			1
#define   	SET_GAIN_CFG			 		2
#define   	SCANTIME				 		3
#define   	SET_ICHA				 		4
#define   	FINGER_THRESHOLD_H	 		    6
#define   	FINGER_THRESHOLD_L	 		    7

//**********************************************************************************	
// 								�͹�������							  //
//**********************************************************************************

#define     TK_LowPowerMode                

#ifdef  TK_LowPowerMode
typedef enum
{
  BTM_TIMEBASE_15600US    = 0X00,		//��Ƶʱ���ж�ʱ��Ϊ15.6MS
  BTM_TIMEBASE_31300US    = 0X01,		//��Ƶʱ���ж�ʱ��Ϊ31.3MS
  BTM_TIMEBASE_62500US    = 0X02,		//��Ƶʱ���ж�ʱ��Ϊ62.5MS
  BTM_TIMEBASE_125MS  	  = 0X03,		//��Ƶʱ���ж�ʱ��Ϊ125MS
  BTM_TIMEBASE_250MS      = 0X04,		//��Ƶʱ���ж�ʱ��Ϊ250MS
  BTM_TIMEBASE_500MS      = 0X05,		//��Ƶʱ���ж�ʱ��Ϊ500MS
  BTM_TIMEBASE_1S         = 0X06,		//��Ƶʱ���ж�ʱ��Ϊ1S
  BTM_TIMEBASE_2S         = 0X07,		//��Ƶʱ���ж�ʱ��Ϊ2S
  BTM_TIMEBASE_4S         = 0X08    	//��Ƶʱ���ж�ʱ��Ϊ4S
} BTM_Timebase_TypeDef;


#include <intrins.h>

#define      WakeUpKeyNum                      1                    //�͹���ģʽ��ɨ�谴������     
#define      WakeUpKeyChannel                  0x00000200           //�͹�����ɨ�谴���Ķ�Ӧͨ��
#define      TK_SeepTimervSetting              BTM_TIMEBASE_125MS   //�͹����°���֮���ɨ����
#define      TK_WakeUpConfirmTouchCnt          8 					//�͹�����ȷ�ϰ�������
										   	
bit  LowPowerScan_Flag = 0;                                         //�͹���ɨ���־
bit  SingleKeyFastScan_Flag = 0;                                    //����������ɨ���־
bit  BTM_WakeUpFlag =0;
unsigned    char    idata       WakeUpKey_List[WakeUpKeyNum];
unsigned 	char 	idata  	    WakeUpKey_Index;
unsigned 	char 	idata  	    WakeUpThenScanCount = 0; 
extern void Customer_IntoLowPowerMode_Init(void);
extern void Customer_QuitLowPowerMode_Init(void);
extern void Customer_BTM_Dispose(void);
extern unsigned  long	int 	data 	  	KeyFlag;

//**********************************************************************************

/**************************************************
*�������ƣ�void BtmInit(void) 
*�������ܣ�
*��ڲ�����void 
*���ڲ�����void
**************************************************/
void BTM_Init(void)
{
    BTMCON = BTMCON & 0XF0 | TK_SeepTimervSetting;
	TK_IE1 |= 0X04;
}
/**************************************************
*�������ƣ�void BtmInit(void) interrupt	0
*�������ܣ�Btm�жϷ�����
*��ڲ�����void 
*���ڲ�����void
**************************************************/
void BtmInit(void) interrupt	9
{
   BTMCON &= (~0X40); 
   BTMCON &= (~0X80); 
   BTM_WakeUpFlag = 1;    
}
#endif


//**********************************************************************************	
// 								�����ӿڵ��ò���								  //
//**********************************************************************************
/**************************************************
*�������ƣ�unsigned int SetOneKeyPushResetTime(void) 
*�������ܣ�����������ʱ��
*��ڲ�����void
*���ڲ�����unsigned int SOCAPI_SET_KEY_CONTI_TIME
*��ע	 ���������ֵ�����ã� �Ǹ����ж೤ʱ������TouchKeyRestart����һ��
����10ms ����һ�Σ� ��SOCAPI_SET_KEY_CONTI_TIME*10ms������ʱ���˰�����Ч��
**************************************************/
unsigned int SetOneKeyPushResetTime(void)   
{	  
	return  TKCFG[SET_KEY_CONTI_TIME];
}
/**************************************************
*�������ƣ�unsignedint  GetBaselineUpdateThreshold(void)
*�������ܣ������ٶ� 
*��ڲ�����void
*���ڲ�����unsigned  int 
*��ע	 ��
**************************************************/
unsigned int  GetBaselineUpdateThreshold(void)
{
	return TKCFG[SET_UPDATE_SPEED]; 
}

/**************************************************
*�������ƣ�unsigned char GetInitAutoUpdateTime(void)
*�������ܣ���ʼ���Զ�У׼����
*��ڲ�����void
*���ڲ�����unsigned  char 
*��ע	 ��
**************************************************/
unsigned char GetInitAutoUpdateTime(void)
{
	return  TKCFG[INIT_AUTO_UPDATE_TIME];
}
/**************************************************
*�������ƣ�unsigned char GetCsFunction(void)
*�������ܣ�����CS ����
*��ڲ�����void
*���ڲ�����char SOCAPI_SET_CS_FUNCTION
*��ע	 ��
**************************************************/
unsigned char GetCsFunction(void)
{
	return SOCAPI_SET_CS_FUNCTION; 
}
/**************************************************
*�������ƣ�int  GetCurrFingerValue(unsigned char i)
*�������ܣ���ȡ��ǰ��finger ֵ
*��ڲ�����unsigned char
*���ڲ�����int 
*��ע	 ��
**************************************************/
unsigned int   GetCurrFingerValue(unsigned char i)
{ 
	return	TKChannelCfg[i][FINGER_THRESHOLD_H]*256+TKChannelCfg[i][FINGER_THRESHOLD_L] ;
}

/**************************************************
*�������ƣ�unsigned char  GetScanTimeValue(unsigned char i)
*�������ܣ���ȡ��ǰͨ����ɨ��ʱ��
*��ڲ�����unsigned char
*���ڲ�����unsigned char 
*��ע	 ��
**************************************************/
unsigned char  GetScanTimeValue(unsigned char i)
{ 
	return TKChannelCfg[i][SCANTIME];
}
/**************************************************
*�������ƣ�unsigned char IsDoubleKeyOrSlideKey(void)
*�������ܣ�����Ƿ��ǵ��ɻ�������˫��
*��ڲ�����void
*���ڲ�����unsigned char 
*��ע	 ��
**************************************************/
unsigned char IsDoubleKeyOrSlideKey(void)
{
    return TKCFG[IsDoubleKey];
}
/**************************************************
*�������ƣ�unsigned char  GetBaseLineAdjustValue(unsigned char i)
*�������ܣ���ȡ��ǰͨ���Ļ��ߵ���
j
*��ڲ�����unsigned char
*���ڲ�����unsigned char 
*��ע	 ��
**************************************************/
unsigned char  GetBaseLineAdjustValue(unsigned char i)
{	
    return BaseLineAdjusttmp[i]; 
}
/**************************************************
*�������ƣ�unsigned char GetUpConfirmCnt(void)
*�������ܣ���ⰴ���������
*��ڲ�����void
*���ڲ��������ذ�������ȷ�ϴ��� 
*��ע	 ��
**************************************************/
unsigned char GetUpConfirmCnt(void)
{
	return ConfirmTouchCnt>>1;
}
/**************************************************
*�������ƣ�unsigned char GetTKYzCnt(void)
*�������ܣ���ȡ��������ȷ�ϴ���
*��ڲ�����void
*���ڲ������������ƴ��� 
*��ע	 ��
**************************************************/
unsigned char GetTKYzCnt(void)
{
	return (ConfirmTouchCnt/3);
}

/**************************************************
*�������ƣ�int GetTKYzThreshold(unsigned char i)
*�������ܣ���ȡ������������
*��ڲ�����unsigned char i
*���ڲ�����������������
*��ע	 ��
**************************************************/
unsigned int GetTKYzThreshold(unsigned char i)
{	
	unsigned int SetFingerThresholdtmp; 
	
	SetFingerThresholdtmp = GetCurrFingerValue(i); 
    SetFingerThresholdtmp = SetFingerThresholdtmp*SOCAPI_INHIBITION_ZONE/10;

	return SetFingerThresholdtmp;
}
/**************************************************
*�������ƣ�void CurrentSensorChoose(void)
*�������ܣ���ǰͨ��ѡ��
*��ڲ�����void
*���ڲ�����void
*��ע	 ��
**************************************************/
void CurrentSensorChoose(void)
{
	unsigned char  	i ;
	unsigned char  	Ctk_Channel_mark = 0;
    unsigned char  	WakeUpKey_Channel_mark = 0;
	unsigned long int	CurrentSensorKey  ; 
	CurrentSensorKey = SOCAPI_SET_TOUCHKEY_CHANNEL; 
		
	for(i=0;i<23;i++)
	{
		CurrentSensorKey=CurrentSensorKey>>1;
		if(TK_CY)
		{
			CurrentChannel[Ctk_Channel_mark] = i;						//ѡ������ǰ��ͨ��
            #ifdef  TK_LowPowerMode
			if(WakeUpKey_Channel_mark<WakeUpKeyNum)
            {
                if((WakeUpKeyChannel&((unsigned long int)1<<i)))
                {
                    WakeUpKey_List[WakeUpKey_Channel_mark++] = Ctk_Channel_mark;
                }
            }
            #endif
			Ctk_Channel_mark++;
			if(Ctk_Channel_mark >= SOCAPI_SET_TOUCHKEY_TOTAL)
				break;
		}		
	}
	CurrentChannelMax = Ctk_Channel_mark;							//��ǰѡ��İ����� 
}

/**************************************************
*�������ƣ�unsigned char  GetCfgMsg(unsigned char i)
*�������ܣ���ȡTouch KEY ������Ϣ
*��ڲ�����void
*���ڲ�����int 
*��ע	 ��
**************************************************/
unsigned char  GetCfgMsg(unsigned char i)
{
	switch(i)
	{ 
		 case 0:  return TKChannelCfg[0][SET_TOUCH_FREQ];
		 case 1:  return TKChannelCfg[0][SET_RESOLUTION];
		 case 2:  return TKChannelCfg[0][SET_GAIN_CFG];
		 case 3:  return TKChannelCfg[0][SET_GAIN_CFG];
		 case 4:  return TKCFG[SET_ANTIJAM];
		 default:return 0; 	 	
	}
}

/**************************************************
*�������ƣ�void CurrentSensorChoose(void)
*�������ܣ���ʼ��TK�Ĵ���
*��ڲ�����void
*���ڲ�����void
*��ע	 ��
**************************************************/
void TouchKeyCFGInit(void)
{
	unsigned char  	i;
	ConfirmTouchCnt = TKCFG[CONFIRMTOUCHCNT];
	SetNoiseThreshold = TKCFG[NOISE];
	CurrentSensorChoose(); 
	for(i=0;i<CurrentChannelMax;i++)
	{
	  BaseLineAdjusttmp[i] =TKChannelCfg[i][SET_ICHA];;	
	} 
	UpdateBaseLNum = 0; 
    #ifdef  TK_LowPowerMode
    BTM_Init();
    #endif 
}

/**************************************************
*�������ƣ�unsigned int TouchKeyScan(void)
*�������ܣ���ⰴ���ӿ�
*��ڲ�����void
*���ڲ���������ͨ���� ���ص���һ��int , ͨ����
*��ע	 ��1,  ���ô��ؿ��⺯��SensorKeyFlag()
		   2,  �����ó�16��ͨ�����ĸ�ͨ���а��£�����bit λ����Ϊ1������Ϊ0
		   3,  ����Ƿ���Ҫ��������baseline:  ����MAX_KEY_RESET_BASELINE ����������ʱ��������baseline
		   4,  ˫�����ߵ�������ʱ�� ʱ�����SetOneKeyPushResetTime()���ʱ����baseline 
**************************************************/
unsigned long int TouchKeyScan(void)
{
	unsigned char t;
    unsigned char MultipleCnt = 0;//��������
	unsigned long int Keyvalue ; 
	unsigned long int KeyData = 0; 	
	if(WakeUp_Flag == 0)
	{
        if(GetIsNeedUpdateBaseline() == 0)				//����Ƿ���Ҫ����baseline 
        {
            Keyvalue = SensorKeyFlag();					//Sensor�ж�, �������bMultiple = 1 ��ʾ�м��и���	 //�����������ó���׼��16ͨ��bit λ                     							   
            for(t=0;t<CurrentChannelMax;t++)
            {
                Keyvalue = Keyvalue>>1;
                if(TK_CY)
                {
                    KeyData |= ((unsigned long int)0x01 << (CurrentChannel[t]));              
                    MultipleCnt++;							
                }
            }                
            if(MultipleCnt >= 2) 	 									//����ఴ������
            {			
                bMultiple = 1;			
                if(MultipleCnt >= SOCAPI_MAX_KEY_NUM_INVALID)
                {
                    SetNeedUpdateBaseline(); 							// ��������baseline ,�����ǿ��������ȥ
                }
                else
                {					
                    if(IsDoubleKeyOrSlideKey())
                    {
                        bMultiple = 0;
                    } 				 
                }			
            }			

            if(bMultiple == 0)							//���밴���ж�
            {		
                if(KeyData != 0x0)					    //���������ﵽ�೤ʱ���update baseline ,���ּ��
                {			
                    UpdateBaseLNum++; 
                }
                else	
                {
                    UpdateBaseLNum = 0;                            
                }                                  
            }	
            else
            {   
                //���ǻ��߸���		
                MultipleLNum++; 
                KeyData = 0x00;
            }

            if(UpdateBaseLNum > SetOneKeyPushResetTime())	  //������������ʱ����»���
            {
                SetNeedUpdateBaseline(); 
                UpdateBaseLNum = 0;
            }
                    
            if(MultipleLNum >SOCAPI_MAX_KEY_MUTIPLE)		  //���ż����������������»���
            {
                SetNeedUpdateBaseline(); 
                MultipleDealTpye = 1; 
                MultipleLNum = 0;
            }  
        }			
        else
        {
            MultipleDeal(TKCFG[AUTO_UPDATE_TIME]);										//���߸�λ����
        }  
    }
    else
    {
        #ifdef  TK_LowPowerMode
		Keyvalue = KeyFlag;
        for(t=0;t<CurrentChannelMax;t++)
        {  			
            FilterDataDeal(t);					//IIR�˲� 
            Keyvalue = Keyvalue>>1;
            if(TK_CY)
            {
                KeyData |= ((unsigned long int)0x01 << (CurrentChannel[t]));                           					
            }            
        }	       
        WakeUpThenScanCount++;
        if(WakeUpThenScanCount>5)
        {
            WakeUpThenScanCount = 0;
            for(t=0; t<CurrentChannelMax; t++)  //��ʼ��Filter�˲�
            {
                if(KeyFlag &((unsigned long int)1<<WakeUpKey_List[WakeUpKey_Index]))
                    continue;
                BaseLine[t] = RawData[t];
            }
            WakeUp_Flag = 0;
        }
		#endif
    }
	return KeyData;
}
/**************************************************
*�������ƣ�void TouchKey_IntoLowPowerMode(void)
*�������ܣd����͹���ģʽ
*��ڲ�����void
*���ڲ�����void  
**************************************************/
void TouchKey_IntoLowPowerMode(void)
{
    #ifdef  TK_LowPowerMode
    LowPowerScan_Flag = 1;
    WakeUp_Flag = 0;
    WakeUpKey_Index = 0;
    TK_IE1 = TK_IE1&(~0x10);    			//�ر�TK�ж�
    Customer_IntoLowPowerMode_Init();
    #endif
}

/**************************************************
*�������ƣ�void TouchKey_QuitLowPowerMode(void)
*�������ܣd�˳��͹���ģʽ
*��ڲ�����void
*���ڲ�����void  
**************************************************/
void TouchKey_QuitLowPowerMode(void)
{
    #ifdef  TK_LowPowerMode
     LowPowerScan_Flag = 0;
     WakeUp_Flag = 1;  
     TK_IE1 = TK_IE1|0x10;    			//ʹ�ܴ����ж�
     TKCR = 0x80|CurrentChannel[0]; 
     TRIG = 1; 
     Customer_QuitLowPowerMode_Init();
    #endif
}

/**************************************************
*�������ƣ�void TouchKey_LowPower_Scan(void)
*�������ܣd�͹���ɨ��
*��ڲ�����void
*���ڲ�����void  
**************************************************/
void TouchKey_LowPower_Scan(void)
{
    #ifdef  TK_LowPowerMode
    TKCFG0 =  GetCfgMsg(2)*16+0;
    TKTM = ScanTime*GetScanTimeValue(WakeUpKey_List[WakeUpKey_Index])>>2;
	TKCFG0 =  GetCfgMsg(2)*16+GetCfgMsg(0);
    TKCFG1 = (TKCFG1&0X80) | GetBaseLineAdjustValue(WakeUpKey_List[WakeUpKey_Index]);
    TKCR = 0x80|CurrentChannel[WakeUpKey_List[WakeUpKey_Index]]; 
    TRIG = 1;           
    #endif    
}

/**************************************************
*�������ƣ�void TouchKey_LowPower_Dispose(void)
*�������ܣd�͹���ɨ�����ݴ���
*��ڲ�����void
*���ڲ�����void  
**************************************************/
void TouchKey_LowPower_Dispose(void)
{  
     #ifdef  TK_LowPowerMode 
     int differData; 
     int SetFingerThresholdtmp;  
     while(TRIF == 0);  
     TRIF = 0; 
        
     RawData[WakeUpKey_List[WakeUpKey_Index]] = TKCNT<<2;
     FilterDataDeal(WakeUpKey_List[WakeUpKey_Index]);
     differData = RawData[WakeUpKey_List[WakeUpKey_Index]]-BaseLine[WakeUpKey_List[WakeUpKey_Index]] ;
     SetFingerThresholdtmp = GetCurrFingerValue(WakeUpKey_List[WakeUpKey_Index]);
     if(differData >= (SetFingerThresholdtmp ))
     {
         TouchCnt[WakeUpKey_List[WakeUpKey_Index]]++;        
         SingleKeyFastScan_Flag = 1;       
     } 
     else
     {      
          BaseLine[WakeUpKey_List[WakeUpKey_Index]] =BaseLine[WakeUpKey_List[WakeUpKey_Index]]-(BaseLine[WakeUpKey_List[WakeUpKey_Index]]>>5)+(RawData[WakeUpKey_List[WakeUpKey_Index]]>>5);          
     }
     #endif     
}

/**************************************************
*�������ƣ�void SingleKeyFastScan(void)
*�������ܣd����������ɨ��ģʽ
*��ڲ�����void
*���ڲ�����void  
**************************************************/
void SingleKeyFastScan(void)
{ 
    #ifdef  TK_LowPowerMode 
    unsigned char i;
    int differData; 
    int SetFingerThresholdtmp;
    
    SingleKeyFastScan_Flag = 0;  
    
    for(i=0;i<TK_WakeUpConfirmTouchCnt;i++)
    {
         TouchKey_LowPower_Scan();
         while(TRIF == 0);
         TRIF = 0;
         RawData[WakeUpKey_List[WakeUpKey_Index]] = TKCNT<<2;
         FilterDataDeal(WakeUpKey_List[WakeUpKey_Index]);
         differData = RawData[WakeUpKey_List[WakeUpKey_Index]]-BaseLine[WakeUpKey_List[WakeUpKey_Index]] ;
         SetFingerThresholdtmp = GetCurrFingerValue(WakeUpKey_List[WakeUpKey_Index]);
         if(differData >= (SetFingerThresholdtmp ))
         {   
            TouchCnt[WakeUpKey_List[WakeUpKey_Index]]++;  
         }             
    }
    if(TouchCnt[WakeUpKey_List[WakeUpKey_Index]]>=TK_WakeUpConfirmTouchCnt)
    {        
         KeyFlag |= ((unsigned long int)1<<WakeUpKey_List[WakeUpKey_Index]);      
		 TouchKey_QuitLowPowerMode();       
    }
    else
    {
        TouchCnt[WakeUpKey_List[WakeUpKey_Index]] = 0;;
    }
    #endif
}

/**************************************************
*�������ƣ�void  SleepMode(void)
*�������ܣd˯��ģʽ
*��ڲ�����void
*���ڲ�����void  
**************************************************/
void  SleepMode(void)
{   
    #ifdef  TK_LowPowerMode 
    BTMCON |= 0x80;
    BTM_WakeUpFlag = 0;
    PCON |= 0x02;	//PCON��bit1 STOPλд1������MCU����STOPģʽ
    _nop_();		//������Ҫ8��_nop_()
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    #endif
}

/**************************************************
*�������ƣ�void LowPower_Touchkey_Scan(void)
*�������ܣd�͹���ģʽTKɨ��
*��ڲ�����void
*���ڲ�����void  
**************************************************/
void LowPower_Touchkey_Scan(void)
{      					
    #ifdef  TK_LowPowerMode 
	//���û��Ѱ���ɨ��
    TouchKey_LowPower_Scan(); 

	//����STOPģʽ                  
    SleepMode();    
	                            
	//���а�������
    TouchKey_LowPower_Dispose();  	   //��ⰴ��
    if( SingleKeyFastScan_Flag == 1)
    {
        SingleKeyFastScan();		   //���а�����Ϣ���뵥�������ٶ��ɨ��ȷ�������Ƿ���ʵ�źš�
    }
    if(LowPowerScan_Flag == 1)
    {        
        WakeUpKey_Index++; 
        if(WakeUpKey_Index>=WakeUpKeyNum)
        {
           WakeUpKey_Index = 0; 
        }
    }	

	// �û�BTM���Ѻ�Ĵ�������
	Customer_BTM_Dispose();  
	      
    #endif    
}