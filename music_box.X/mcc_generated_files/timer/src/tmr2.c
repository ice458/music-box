/**
 * TMR2 Generated Driver File
 *
 * @file tmr2.c
 * 
 * @ingroup  tmr2
 * 
 * @brief API implementations for the TMR2 module.
 *
 * @version TMR2 Driver Version 3.0.1
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
  Section: Included Files
*/

#include <xc.h>
#include "../tmr2.h"

const struct TMR_INTERFACE ScoreTMR = {
    .Initialize = ScoreTMR_Initialize,
    .Start = ScoreTMR_Start,
    .Stop = ScoreTMR_Stop,
    .PeriodCountSet = ScoreTMR_PeriodCountSet,
    .TimeoutCallbackRegister = ScoreTMR_OverflowCallbackRegister,
    .Tasks = NULL
};

static void (*ScoreTMR_OverflowCallback)(void);
static void ScoreTMR_DefaultOverflowCallback(void);

/**
  Section: TMR2 APIs
*/

void ScoreTMR_Initialize(void){

    // Set TMR2 to the options selected in the User Interface
    // TCS LFINTOSC; 
    T2CLKCON = 0x4;
    // TMODE Software control; TCKSYNC Synchronized; TCKPOL Rising Edge; TPSYNC Not Synchronized; 
    T2HLT = 0x20;
    // TRSEL T2CKIPPS pin; 
    T2RST = 0x0;
    // PR 12; 
    T2PR = 0xC;
    // TMR 0x0; 
    T2TMR = 0x0;

    // Set default overflow callback
    ScoreTMR_OverflowCallbackRegister(ScoreTMR_DefaultOverflowCallback);

    // Clearing IF flag before enabling the interrupt.
     PIR3bits.TMR2IF = 0;
    // Enabling TMR2 interrupt.
     PIE3bits.TMR2IE = 1;
    // TCKPS 1:128; TMRON on; TOUTPS 1:2; 
    T2CON = 0xF1;
}

void ScoreTMR_ModeSet(ScoreTMR_HLT_MODE mode)
{
   // Configure different types HLT mode
    T2HLTbits.T2MODE = mode;
}

void ScoreTMR_ExtResetSourceSet(ScoreTMR_HLT_EXT_RESET_SOURCE reset)
{
    //Configure different types of HLT external reset source
    T2RSTbits.T2RSEL = reset;
}

void ScoreTMR_Start(void)
{
    // Start the Timer by writing to TMRxON bit
    T2CONbits.TMR2ON = 1;
}

void ScoreTMR_Stop(void)
{
    // Stop the Timer by writing to TMRxON bit
    T2CONbits.TMR2ON = 0;
}

uint8_t ScoreTMR_Read(void)
{
    uint8_t readVal;
    readVal = TMR2;
    return readVal;
}

void ScoreTMR_Write(uint8_t timerVal)
{
    // Write to the Timer2 register
    TMR2 = timerVal;;
}

void ScoreTMR_PeriodCountSet(size_t periodVal)
{
   PR2 = (uint8_t) periodVal;
}

void ScoreTMR_ISR(void)
{
    // clear the TMR2 interrupt flag
     PIR3bits.TMR2IF = 0;

    // ticker function call;
    // ticker is 1 -> Callback function gets called everytime this ISR executes
    ScoreTMR_OverflowCallback();
}

void ScoreTMR_OverflowCallbackRegister(void (* InterruptHandler)(void)){
    ScoreTMR_OverflowCallback = InterruptHandler;
}

static void ScoreTMR_DefaultOverflowCallback(void){
    // add your TMR2 interrupt custom code
    // or set custom function using ScoreTMR_OverflowCallbackRegister()
}

