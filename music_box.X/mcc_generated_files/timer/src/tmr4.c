/**
 * TMR4 Generated Driver File
 *
 * @file tmr4.c
 * 
 * @ingroup  tmr4
 * 
 * @brief API implementations for the TMR4 module.
 *
 * @version TMR4 Driver Version 3.0.1
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
#include "../tmr4.h"

const struct TMR_INTERFACE FsTMR = {
    .Initialize = FsTMR_Initialize,
    .Start = FsTMR_Start,
    .Stop = FsTMR_Stop,
    .PeriodCountSet = FsTMR_PeriodCountSet,
    .TimeoutCallbackRegister = FsTMR_OverflowCallbackRegister,
    .Tasks = NULL
};

static void (*FsTMR_OverflowCallback)(void);
static void FsTMR_DefaultOverflowCallback(void);

/**
  Section: TMR4 APIs
*/

void FsTMR_Initialize(void){

    // Set TMR4 to the options selected in the User Interface
    // TCS FOSC/4; 
    T4CLKCON = 0x1;
    // TMODE Software control; TCKSYNC Not Synchronized; TCKPOL Rising Edge; TPSYNC Not Synchronized; 
    T4HLT = 0x0;
    // TRSEL T4CKIPPS pin; 
    T4RST = 0x0;
    // PR 124; 
    T4PR = 0x7C;
    // TMR 0x0; 
    T4TMR = 0x0;

    // Set default overflow callback
    FsTMR_OverflowCallbackRegister(FsTMR_DefaultOverflowCallback);

    // Clearing IF flag before enabling the interrupt.
     PIR11bits.TMR4IF = 0;
    // Enabling TMR4 interrupt.
     PIE11bits.TMR4IE = 1;
    // TCKPS 1:4; TMRON on; TOUTPS 1:1; 
    T4CON = 0xA0;
}

void FsTMR_ModeSet(FsTMR_HLT_MODE mode)
{
   // Configure different types HLT mode
    T4HLTbits.T4MODE = mode;
}

void FsTMR_ExtResetSourceSet(FsTMR_HLT_EXT_RESET_SOURCE reset)
{
    //Configure different types of HLT external reset source
    T4RSTbits.T4RSEL = reset;
}

void FsTMR_Start(void)
{
    // Start the Timer by writing to TMRxON bit
    T4CONbits.TMR4ON = 1;
}

void FsTMR_Stop(void)
{
    // Stop the Timer by writing to TMRxON bit
    T4CONbits.TMR4ON = 0;
}

uint8_t FsTMR_Read(void)
{
    uint8_t readVal;
    readVal = TMR4;
    return readVal;
}

void FsTMR_Write(uint8_t timerVal)
{
    // Write to the Timer4 register
    TMR4 = timerVal;;
}

void FsTMR_PeriodCountSet(size_t periodVal)
{
   PR4 = (uint8_t) periodVal;
}

void FsTMR_ISR(void)
{
    // clear the TMR4 interrupt flag
     PIR11bits.TMR4IF = 0;

    if(FsTMR_OverflowCallback)
    {
        FsTMR_OverflowCallback();
    }
}

void FsTMR_OverflowCallbackRegister(void (* InterruptHandler)(void)){
    FsTMR_OverflowCallback = InterruptHandler;
}

static void FsTMR_DefaultOverflowCallback(void){
    // add your TMR4 interrupt custom code
    // or set custom function using FsTMR_OverflowCallbackRegister()
}

