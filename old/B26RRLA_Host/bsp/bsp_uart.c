#include "bsp_uart.h"


unsigned char Uart1SendFlag,Uart1ReceiveFlag;



void Uart1_Init(unsigned char Fsystem,unsigned int BaudRate_Count)
{
	P1CON &= 0xF3;   //TX/RX����Ϊ���������
	P1PH  |= 0x0C;
	
	SCON  |= 0X50;   //����ͨ�ŷ�ʽΪģʽһ���������
	TMCON |= 0X02;
	TMOD  |= 0X20;
	PCON  |= 0X80;	//SMOD=1
	TH1 = (Fsystem*1000000/BaudRate_Count)>>8;	  //������ΪT1�����ʱ�䣻
	TL1 = Fsystem*1000000/BaudRate_Count;
	TR1 = 0;
	ET1 = 0;
	EUART = 0;     //����Uart0�ж�
}

void Uart2_Init(unsigned char Freq,unsigned long int baud)
{
	P2CON &= 0xFC;   //TX/RX����Ϊ���������
	P2PH  |= 0x03;
	
	OTCON = 0xC0;    //���нӿ�SSIѡ��Uart1ͨ��
	SSCON0 = 0x50;   //����ͨ�ŷ�ʽΪģʽһ���������
	SSCON1 = Freq*1000000/baud;   //�����ʵ�λ����
	SSCON2 = (Freq*1000000/baud)>>8;   //�����ʸ�λ����
	IE1 = 0x01;      //����SSI�ж�
}

/******************************************************************************
*����:PETER
*����:190308
*����:����0���ͺ���
*����:��
*******************************************************************************/
static void UART_TX_byte(unsigned char DATA)
{
   TI = 0;
   SBUF = DATA;
   while(!TI);
}

static unsigned char  Uart1_SendData(PROTOCOL_TX *p)
{
	static unsigned char i;
	for(i = 0; i < UART1_BUF_SIZE; i ++)
	{
		UART_TX_byte(p->UART1_Buf[i]);
	}
	return 0;
}

unsigned char Protocol_Send(unsigned char addr,unsigned char id,unsigned int TX1_DATA)
{
	PROTOCOL_TX buf;
	memset(&buf,0,sizeof(buf));
	buf.Uart1_Format.ADDR = addr;
	buf.Uart1_Format.ID      = id;
	buf.Uart1_Format.DATA1 = Hight(TX1_DATA);
	buf.Uart1_Format.DATA2 = Low(TX1_DATA);
	buf.Uart1_Format.CHECKSUM = (unsigned char)(buf.Uart1_Format.ADDR+buf.Uart1_Format.ID+buf.Uart1_Format.DATA1+buf.Uart1_Format.DATA2);
	buf.Uart1_Format.STOP1 = 0x0d;
	buf.Uart1_Format.STOP2 = 0x0a;
	return Uart1_SendData(&buf);
}
/******************************************************************************
*����:PETER
*����:190308
*����:����1���ͺ���
*����:��
*******************************************************************************/

static void Uart1_Tx_Byte(unsigned char Uart1_Data)
{
	SSDAT = Uart1_Data;
	//while(!Uart1SendFlag);
	Uart1SendFlag = 0;
}

static unsigned char Send2_Data(PROTOCOL_TX2 *p)
{
	static unsigned char i;
	for(i = 0; i < UART2_BUF_SIZE; i ++)
	{
		Uart1_Tx_Byte(p->UART2_Buf[i]);
	}
	return 0;
}

unsigned char Protocol2_Send(unsigned char add2,unsigned char id2,unsigned int TX2_DATA)
{
	PROTOCOL_TX2 TX2_Buf;
	memset(&TX2_Buf,0,sizeof(TX2_Buf));
	TX2_Buf.Uart2_Format.TX2_ADDR = add2;
	TX2_Buf.Uart2_Format.TX2_ID = id2;
	TX2_Buf.Uart2_Format.TX2_DATA1 = TX2_Hight(TX2_DATA);
	TX2_Buf.Uart2_Format.TX2_DATA2 = TX2_Low(TX2_DATA);
	TX2_Buf.Uart2_Format.TX2_CHECKSUM = (unsigned char)(TX2_Buf.Uart2_Format.TX2_ADDR+TX2_Buf.Uart2_Format.TX2_ID+TX2_Buf.Uart2_Format.TX2_DATA1+TX2_Buf.Uart2_Format.TX2_DATA2);
	TX2_Buf.Uart2_Format.TX2_STOP1 = 0x0d;
	TX2_Buf.Uart2_Format.TX2_STOP2 = 0x0a;
       return Send2_Data(&TX2_Buf);
}


/******************************************************************************
*����:PETER
*����:190308
*����:����1���պ���
*����:��
*******************************************************************************/
unsigned char Rev_Data(unsigned char SLAVE)
{
    SLAVE = SSDAT;
    return SLAVE;
}

/******************************************************************************
*����:PETER
*����:190308
*����:����1�жϴ�����
*����:��
*******************************************************************************/

void Uart1_Int() interrupt 7   //Uart1�жϺ���
{
	if(SSCON0&0x02)    //���ͱ�־λ�ж�
	{
		SSCON0 &= 0xFD;
		Uart1SendFlag = 1;
	}
	if((SSCON0&0x01))  //���ձ�־λ�ж�
	{
		SSCON0 &= 0xFE;
		Uart1ReceiveFlag = 1;
	}	
}






