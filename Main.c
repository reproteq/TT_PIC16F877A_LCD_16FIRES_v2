
#include "Includes.h"

// Configuration word for PIC16F877A
__CONFIG(FOSC_XT & WDTE_OFF & PWRTE_ON & BOREN_ON & LVP_OFF & CPD_OFF & WRT_OFF & CP_OFF);
// Main Function
void main(void)
{
	unsigned char State = NORMAL_STATE;	// To store current state  
    unsigned char AuthorTT = Author;
    unsigned char Logo = MsgLogo;
    unsigned char MesaPrograma = MsgPrograma;
    unsigned char MesaDispara = MsgDispara;
    unsigned char BorrrMemo = MsgClear;
    unsigned char GuardarMemo = MsgRec;
    unsigned char DigitoSec = MsgSec;
    unsigned char DisgitoCsec = MsgCsec;
    unsigned char MesaFuego = MsgFuego;
    unsigned char MesaCompletado = MsgCompletado;
    unsigned char FireLine1 = Fire1;
    unsigned char FireLine2 = Fire2;
    unsigned char FireLine3 = Fire3;
    unsigned char FireLine4 = Fire4;
    unsigned char FireLine5 = Fire5;
    unsigned char FireLine6 = Fire6;
    unsigned char FireLine7 = Fire7;
    unsigned char FireLine8 = Fire8;
    unsigned char FireLine9 = Fire9;
    unsigned char FireLine10 = Fire10;
    unsigned char FireLine11 = Fire11;
    unsigned char FireLine12 = Fire12;
    unsigned char FireLine13 = Fire13;
    unsigned char FireLine14 = Fire14;
    unsigned char FireLine15 = Fire15;
    unsigned char FireLine16 = Fire16;
 
    TRISA =  0x3f;
    ADCON1 = 0x07;
    TRISC = 0;
    TRISD = 0;
    PORTC = 0;
    PORTD = 0;
    PORTA = 0;
	TRISD0 = 0;						// Make RD0 pin an output
	RD0	= 0;						// Make RD0 zero
    RD1 = 0;
    RD2 = 0;
    RD3 = 0;
    RD4 = 0;
    RD5 = 0;
    RD6 = 0;
    RD7 = 0;
    RC0 = 0;
    RC1 = 0;
    RC2 = 0;
    RC3 = 0;
    RC4 = 0;
    RC5 = 0;
    RC6 = 0;
    RC6 = 0;
	TRISE  = 0x07;					// PORTE is used for inputs
	ADCON1 = 0x07;					// Disable ADC to make PORTE pins 
									// as digital IO pins
	ReadEeprom();
   	InitLCD();
    Init1msecTimerInterrupt();		// Start 1 msec timer
    DisplayAuthorToLCD();
    __delay_ms(1000);
    DisplayMsgLogoToLCD();
    __delay_ms(1000);
	while(1)
	{
       
      
       if(RA0==0)	///////////////// MODO PROGRAMA SWICHT RA0 NIVEL  BAJO
		{ 
                  /// Msg Modo Dispara
           if (MesaPrograma == 1){DisplayMsgProgramaToLCD();  __delay_ms(300);} 
           
           UpdateTimeCounters(State); 
             
           /// borrado de memoria 
        if(RA2==1){ClearMemo();DisplayMsgClearToLCD();  __delay_ms(300); }
            
		if(State == NORMAL_STATE)
		{
			if(RE0==1)				// si se pulso grabando
			{   
                DisplayMsgRecToLCD(); __delay_ms(300); // mensaje recording
				State = CONFIG_SEC_STATE;	// cambio de estado para programar

				while(RE0==1)			//antirebote
                    
					UpdateTimeCounters(State);// actualizar counters
			}

			 
        }
		else					// If state is not NORMAL_STATE
		{
                       
			if(RE1==1)			// If Up button pressed
			{
               
				//while(RE1==1)		// antirebote
					//UpdateTimeCounters(State);//   updating   counters

				switch(State)	// Increment counter
				{
                    
                case CONFIG_CSEC_STATE: if(csCounter==99)
											csCounter = 0;
										else
											csCounter++;
										break;            
				case CONFIG_SEC_STATE:	if(secCounter==59)
											secCounter = 0;
										else
											secCounter++;
										break;

				}
			}
			else if(RE2==1)		// If Down button pressed
			{

				//while(RE2==1)		//  antirebote

					//UpdateTimeCounters(State);// Keep updating time counters

				switch(State)	// Decrement counter
				{
                case CONFIG_CSEC_STATE:	if(csCounter==0)
											csCounter = 99;
										else
											csCounter--;
                                        break;
				case CONFIG_SEC_STATE:	if(secCounter==0)
											secCounter = 59;
										else
											secCounter--;
										break;

				}
			}
			else if(RE0==1)		// If grabando se sigue pulsando
			{
             
                  
				while(RE0==1)		//antirebote
					UpdateTimeCounters(State);//   updating   counters

				switch(State)	// switch para los 2 digitos segundos decimas
				{ 
				case CONFIG_SEC_STATE:	State = CONFIG_CSEC_STATE;
                 DisplayMsgSecToLCD();  __delay_ms(300);   
                
                  break;
                  
                case CONFIG_CSEC_STATE: State = NORMAL_STATE;
                  DisplayMsgCsecToLCD(); __delay_ms(300);
                  break;
				}				              
                
			}	
		}
           
            // Update counters
		    UpdateTimeCounters(State);       	 
			// Display time  
			DisplayTimeToLCD( secCounter,csCounter, NORMAL_STATE);
            // escribe en la eeprom interna
		    WriteEeprom();
		    
           
           
           
        } //fin if programa
       
       if(RA0==1)	///////////////// MODO DISPARO 
		{ 
           
             DisplayMsgDisparoToLCD();
             __delay_ms(50);
             
             ReadEeprom();
             DisplayTimeToLCD( secCounter,csCounter, NORMAL_STATE); 
             __delay_ms(50);
             
         if (RA1)//pulso dispara secuencia
          {
             State = NORMAL_STATE;
             ReadEeprom();  

             while(State == NORMAL_STATE && RC0 == 0 && FireLine1 == 1)///linea1 puerto c
                {              
                RC0 = 1; __delay_ms(10);  RC0 = 0; FireLine1 = 0;State = NORMAL_STATE;  MesaCompletado = 1; ReadEeprom();  
				}
             
            while(State == NORMAL_STATE && RC1 == 0 && FireLine2 == 1)///linea2
                {              
                 msCounter = 10;
                 UpdateTimeCounters(State); 
                 DisplayTimeToLCD(secCounter,csCounter, State); 
                 if( csCounter == 0 && secCounter == 0  ) {RC1 = 1; __delay_ms(10);  RC1 = 0; FireLine2 = 0;State = NORMAL_STATE; ReadEeprom();   }
				}
                           
             while(State == NORMAL_STATE && RC2 == 0 && FireLine3 == 1)///linea3
                {              
                 msCounter = 10;
                 UpdateTimeCounters(State); 
                 DisplayTimeToLCD(secCounter,csCounter, State); 
                 if( csCounter == 0 && secCounter == 0  ) {RC2 = 1; __delay_ms(10);  RC2 = 0; FireLine3 = 0;State = NORMAL_STATE; ReadEeprom();   }
				}
                     
             while(State == NORMAL_STATE && RC3 == 0 && FireLine4 == 1)///linea4
                {              
                 msCounter = 10;
                 UpdateTimeCounters(State); 
                 DisplayTimeToLCD(secCounter,csCounter, State); 
                 if( csCounter == 0 && secCounter == 0  ) {RC3 = 1; __delay_ms(10);  RC3 = 0; FireLine4 = 0;State = NORMAL_STATE; ReadEeprom();   }
				}
             
             while(State == NORMAL_STATE && RC4 == 0 && FireLine5 == 1)///linea5
                {              
                 msCounter = 10;
                 UpdateTimeCounters(State); 
                 DisplayTimeToLCD(secCounter,csCounter, State); 
                 if( csCounter == 0 && secCounter == 0  ) {RC4 = 1; __delay_ms(10);  RC4 = 0; FireLine5 = 0;State = NORMAL_STATE; ReadEeprom();   }
				}             
             
             while(State == NORMAL_STATE && RC5 == 0 && FireLine6 == 1)///linea6
                {              
                 msCounter = 10;
                 UpdateTimeCounters(State); 
                 DisplayTimeToLCD(secCounter,csCounter, State); 
                 if( csCounter == 0 && secCounter == 0  ) {RC5 = 1; __delay_ms(10);  RC5 = 0; FireLine6 = 0;State = NORMAL_STATE; ReadEeprom();   }
				}

             while(State == NORMAL_STATE && RC6 == 0 && FireLine7 == 1)///linea7
                {              
                 msCounter = 10;
                 UpdateTimeCounters(State); 
                 DisplayTimeToLCD(secCounter,csCounter, State); 
                 if( csCounter == 0 && secCounter == 0  ) {RC6 = 1; __delay_ms(10);  RC6 = 0; FireLine7 = 0;State = NORMAL_STATE; ReadEeprom();   }
				}
             
             while(State == NORMAL_STATE && RC7 == 0 && FireLine8 == 1)///linea8
                {              
                 msCounter = 10;
                 UpdateTimeCounters(State); 
                 DisplayTimeToLCD(secCounter,csCounter, State); 
                 if( csCounter == 0 && secCounter == 0  ) {RC7 = 1; __delay_ms(10);  RC7 = 0; FireLine8 = 0;State = NORMAL_STATE; ReadEeprom();   }
				}
                          
             
             while(State == NORMAL_STATE && RD0 == 0 && FireLine9 == 1)///linea 9  cambio de puerto D
                {              
                 msCounter = 10;
                 UpdateTimeCounters(State); 
                 DisplayTimeToLCD(secCounter,csCounter, State); 
                 if( csCounter == 0 && secCounter == 0  ) {RD0 = 1; __delay_ms(10);  RD0 = 0; FireLine9 = 0;State = NORMAL_STATE; ReadEeprom();   }
				}             
             
             while(State == NORMAL_STATE && RD1 == 0 && FireLine10 == 1)///linea 10
                {              
                 msCounter = 10;
                 UpdateTimeCounters(State); 
                 DisplayTimeToLCD(secCounter,csCounter, State); 
                 if( csCounter == 0 && secCounter == 0  ) {RD1 = 1; __delay_ms(10);  RD1 = 0; FireLine10 = 0;State = NORMAL_STATE; ReadEeprom();   }
				}
             
             while(State == NORMAL_STATE && RD2 == 0 && FireLine11 == 1)///linea 11
                {              
                 msCounter = 10;
                 UpdateTimeCounters(State); 
                 DisplayTimeToLCD(secCounter,csCounter, State); 
                 if( csCounter == 0 && secCounter == 0  ) {RD2 = 1; __delay_ms(10);  RD2 = 0; FireLine11 = 0;State = NORMAL_STATE; ReadEeprom();   }
				}
             
             while(State == NORMAL_STATE && RD3 == 0 && FireLine12 == 1)///linea 12
                {              
                 msCounter = 10;
                 UpdateTimeCounters(State); 
                 DisplayTimeToLCD(secCounter,csCounter, State); 
                 if( csCounter == 0 && secCounter == 0  ) {RD3 = 1; __delay_ms(10);  RD3 = 0; FireLine12 = 0;State = NORMAL_STATE; ReadEeprom();   }
				}
             
             while(State == NORMAL_STATE && RD4 == 0 && FireLine13 == 1)///linea 13
                {              
                 msCounter = 10;
                 UpdateTimeCounters(State); 
                 DisplayTimeToLCD(secCounter,csCounter, State); 
                 if( csCounter == 0 && secCounter == 0  ) {RD4 = 1; __delay_ms(10);  RD4 = 0; FireLine13 = 0;State = NORMAL_STATE; ReadEeprom();   }
				}
             
             while(State == NORMAL_STATE && RD5 == 0 && FireLine14 == 1)///linea 14
                {              
                 msCounter = 10;
                 UpdateTimeCounters(State); 
                 DisplayTimeToLCD(secCounter,csCounter, State); 
                 if( csCounter == 0 && secCounter == 0  ) {RD5 = 1; __delay_ms(10);  RD5 = 0; FireLine14 = 0;State = NORMAL_STATE; ReadEeprom();   }
				}
             
             while(State == NORMAL_STATE && RD6 == 0 && FireLine15 == 1)///linea 15
                {              
                 msCounter = 10;
                 UpdateTimeCounters(State); 
                 DisplayTimeToLCD(secCounter,csCounter, State); 
                 if( csCounter == 0 && secCounter == 0  ) {RD6 = 1; __delay_ms(10);  RD6 = 0; FireLine15 = 0;State = NORMAL_STATE; ReadEeprom();   }
				}
             
             while(State == NORMAL_STATE && RD7 == 0 && FireLine16 == 1)///linea 16
                {              
                 msCounter = 10;
                 UpdateTimeCounters(State); 
                 DisplayTimeToLCD(secCounter,csCounter, State); 
                 if( csCounter == 0 && secCounter == 0  ) {RD7 = 1; __delay_ms(10);  RD7 = 0; FireLine16 = 0;State = NORMAL_STATE; ReadEeprom();   }
				}             
             
              while(State == NORMAL_STATE && MesaCompletado == 1)
                { 
                              
                 DisplayMsgCompletadoToLCD();
                 __delay_ms(1000);                 
                 MesaCompletado = 0;
                 FireLine1 = 1;
                 FireLine2 = 1;
                 FireLine3 = 1;
                 FireLine4 = 1;
                 FireLine5 = 1;
                 FireLine6 = 1;
                 FireLine7 = 1;
                 FireLine8 = 1;
                 FireLine9 = 1;
                 FireLine10 = 1;
                 FireLine11 = 1;
                 FireLine12 = 1;
                 FireLine13 = 1;
                 FireLine14 = 1;
                 FireLine15 = 1;
                 FireLine16 = 1;
                
				}     
             
          }
         
        } //fin if dispara
      
       
       
  	}//fin while(1)
}//fin void main

