/**
  * TMR3 Generated Driver File
  *
  * @file tmr3.c
  *
  * @ingroup tmr3
  *
  * @brief Driver implementation for the TMR3 driver
  *
  * @version TMR3 Driver Version 3.1.0
*/
/*
? [2024] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

/**
 * Section: Included Files
*/

#include <xc.h>
#include "../tmr3.h"

/**
 * Section: Global Variables Definitions
*/
volatile uint16_t timer3ReloadVal;
void (*EnvTMR_InterruptHandler)(void);

const struct TMR_INTERFACE EnvTMR = {
    .Initialize = EnvTMR_Initialize,
    .Start = EnvTMR_Start,
    .Stop = EnvTMR_Stop,
    .PeriodCountSet = EnvTMR_PeriodCountSet,
    .TimeoutCallbackRegister = EnvTMR_OverflowCallbackRegister,
    .Tasks = NULL
};
static void (*EnvTMR_OverflowCallback)(void);
static void EnvTMR_DefaultOverflowCallback(void);

void EnvTMR_Initialize(void)
{
    //TGGO done; TGSPM disabled; TGTM disabled; TGPOL low; TMRGE disabled; 
    T3GCON = 0x0;
    //TGSS T3G_pin; 
    T3GATE = 0x0;
    //TMRCS FOSC/4; 
    T3CLK = 0x1;
    //TMRH 5; 
    TMR3H = 0x5;
    //TMRL 255; 
    TMR3L = 0xFF;

    // Load the TMR3 value to reload variable
    timer3ReloadVal=(uint16_t)((TMR3H << 8) | TMR3L);

    //Set default callback for TMR3 overflow interrupt
    EnvTMR_OverflowCallbackRegister(EnvTMR_DefaultOverflowCallback);

    // Clearing TMRI IF flag before enabling the interrupt.
     PIR5bits.TMR3IF = 0;
    // Enabling TMRI interrupt.
     PIE5bits.TMR3IE = 1;
    
    //TMRON enabled; TRD16 disabled; nTSYNC synchronize; TCKPS 1:2; 
    T3CON = 0x11;
}

void EnvTMR_Start(void)
{
    // Start the Timer by writing to TMRxON bit
    T3CONbits.TMR3ON = 1;
}

void EnvTMR_Stop(void)
{
    // Stop the Timer by writing to TMRxON bit
    T3CONbits.TMR3ON = 0;
}

uint16_t EnvTMR_Read(void)
{
    uint16_t readVal;
    uint8_t readValHigh;
    uint8_t readValLow;
    
	
    readValLow = TMR3L;
    readValHigh = TMR3H;
    
    readVal = ((uint16_t)readValHigh << 8) | readValLow;

    return readVal;
}

void EnvTMR_Write(size_t timerVal)
{
    if (T3CONbits.nT3SYNC == 1)
    {
        // Stop the Timer by writing to TMRxON bit
        T3CONbits.TMR3ON = 0;

        // Write to the Timer3 register
        TMR3H = (uint8_t)(timerVal >> 8);
        TMR3L = (uint8_t)timerVal;

        // Start the Timer after writing to the register
        T3CONbits.TMR3ON = 1;
    }
    else
    {
        // Write to the Timer3 register
        TMR3H = (uint8_t)(timerVal >> 8);
        TMR3L = (uint8_t)timerVal;
    }
}

void EnvTMR_Reload(void)
{
    EnvTMR_Write(timer3ReloadVal);
}

void EnvTMR_PeriodCountSet(size_t periodVal)
{
   timer3ReloadVal = (uint16_t) periodVal;
}

void EnvTMR_StartSinglePulseAcquisition(void)
{
    T3GCONbits.T3GGO = 1;
}

uint8_t EnvTMR_CheckGateValueStatus(void)
{
    return (T3GCONbits.T3GVAL);
}

void EnvTMR_OverflowISR(void)
{

    // Clear the TMR3 interrupt flag
    PIR5bits.TMR3IF = 0;
    EnvTMR_Write(timer3ReloadVal);

    if(EnvTMR_OverflowCallback)
    {
        EnvTMR_OverflowCallback();
    }
}

void EnvTMR_OverflowCallbackRegister(void (* CallbackHandler)(void))
{
    EnvTMR_OverflowCallback = CallbackHandler;
}

static void EnvTMR_DefaultOverflowCallback(void)
{
    //Add your interrupt code here or
    //Use EnvTMR_OverflowCallbackRegister function to use Custom ISR
}

bool EnvTMR_HasOverflowOccured(void)
{
    return(PIR5bits.TMR3IF);
}

void EnvTMR_GateISR(void)
{
    // clear the TMR3 interrupt flag
    PIR5bits.TMR3GIF = 0;
}


/**
  End of File
*/