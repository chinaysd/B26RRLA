#ifndef _BSP_IO_DATA_H_
#define _BSP_IO_DATA_H_


#include "SC92F836xB_C.H"


#define 	true		       1
#define 	false		0


#define IO_DATA_PORT      P1
#define IO_DATA_PIN         P15
#define IO_DATA_SET(X)     ((X)?(IO_DATA_PIN=X):(IO_DATA_PIN=X))




void IO_Data_Send(void);
void IO_Data_Rev(void);


#endif



