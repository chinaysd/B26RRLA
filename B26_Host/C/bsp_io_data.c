#include "bsp_io_data.h"
#include "833X_IO.H"



void IO_Data_Send(void)
{
	P1CON |= 0X20;
	P1PH   &= ~0X20;
	IO_DATA_SET(0);
}

void IO_Data_Rev(void)
{
	P15IH;
}

