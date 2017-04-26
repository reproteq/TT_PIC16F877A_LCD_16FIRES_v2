
#ifndef __INCLUDES_H
#define __INCLUDES_H

// Define CPU Frequency
// This must be defined, if __delay_ms() or 
// __delay_us() functions are used in the code
#define _XTAL_FREQ   4000000  

// Define stats
#define NORMAL_STATE		0
#define CONFIG_SEC_STATE	1
#define CONFIG_CSEC_STATE	2

//variables de estado
#define Author           	1 
#define MsgLogo         	1 
#define MsgClear        	1  
#define MsgRec          	1 
#define MsgSec          	1 
#define MsgCsec         	1 
#define MsgFuego         	1 
#define MsgCompletado      	1 
#define MsgPrograma      	1
#define MsgDispara       	1
#define Fire1               1
#define Fire2               1
#define Fire3               1
#define Fire4               1
#define Fire5               1
#define Fire6               1
#define Fire7               1
#define Fire8               1
#define Fire9               1
#define Fire10              1
#define Fire11              1
#define Fire12              1
#define Fire13              1
#define Fire14              1
#define Fire15              1
#define Fire16              1
#include <htc.h> 
#include "LCD.h"
#include "Timer.h"
#include "ESTADO.c"

#endif