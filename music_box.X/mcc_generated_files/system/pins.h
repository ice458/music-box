/**
 * Generated Pins header File
 * 
 * @file pins.h
 * 
 * @defgroup  pinsdriver Pins Driver
 * 
 * @brief This is generated driver header for pins. 
 *        This header file provides APIs for all pins selected in the GUI.
 *
 * @version Driver Version  3.1.0
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

#ifndef PINS_H
#define PINS_H

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set RC2 aliases
#define SW_Next_TRIS                 TRISCbits.TRISC2
#define SW_Next_LAT                  LATCbits.LATC2
#define SW_Next_PORT                 PORTCbits.RC2
#define SW_Next_WPU                  WPUCbits.WPUC2
#define SW_Next_OD                   ODCONCbits.ODCC2
#define SW_Next_ANS                  ANSELCbits.ANSELC2
#define SW_Next_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define SW_Next_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define SW_Next_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define SW_Next_GetValue()           PORTCbits.RC2
#define SW_Next_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define SW_Next_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define SW_Next_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define SW_Next_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define SW_Next_SetPushPull()        do { ODCONCbits.ODCC2 = 0; } while(0)
#define SW_Next_SetOpenDrain()       do { ODCONCbits.ODCC2 = 1; } while(0)
#define SW_Next_SetAnalogMode()      do { ANSELCbits.ANSELC2 = 1; } while(0)
#define SW_Next_SetDigitalMode()     do { ANSELCbits.ANSELC2 = 0; } while(0)
#define RC2_SetInterruptHandler  SW_Next_SetInterruptHandler

// get/set RC3 aliases
#define IO_RC3_TRIS                 TRISCbits.TRISC3
#define IO_RC3_LAT                  LATCbits.LATC3
#define IO_RC3_PORT                 PORTCbits.RC3
#define IO_RC3_WPU                  WPUCbits.WPUC3
#define IO_RC3_OD                   ODCONCbits.ODCC3
#define IO_RC3_ANS                  ANSELCbits.ANSELC3
#define IO_RC3_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define IO_RC3_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define IO_RC3_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define IO_RC3_GetValue()           PORTCbits.RC3
#define IO_RC3_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define IO_RC3_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define IO_RC3_SetPullup()          do { WPUCbits.WPUC3 = 1; } while(0)
#define IO_RC3_ResetPullup()        do { WPUCbits.WPUC3 = 0; } while(0)
#define IO_RC3_SetPushPull()        do { ODCONCbits.ODCC3 = 0; } while(0)
#define IO_RC3_SetOpenDrain()       do { ODCONCbits.ODCC3 = 1; } while(0)
#define IO_RC3_SetAnalogMode()      do { ANSELCbits.ANSELC3 = 1; } while(0)
#define IO_RC3_SetDigitalMode()     do { ANSELCbits.ANSELC3 = 0; } while(0)

/**
 * @ingroup  pinsdriver
 * @brief GPIO and peripheral I/O initialization
 * @param none
 * @return none
 */
void PIN_MANAGER_Initialize (void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt on Change Handling routine
 * @param none
 * @return none
 */
void PIN_MANAGER_IOC(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt on Change Handler for the SW_Next pin functionality
 * @param none
 * @return none
 */
void SW_Next_ISR(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for SW_Next pin interrupt-on-change functionality.
 *        Allows selecting an interrupt handler for SW_Next at application runtime
 * @pre Pins intializer called
 * @param InterruptHandler function pointer.
 * @return none
 */
void SW_Next_SetInterruptHandler(void (* InterruptHandler)(void));

/**
 * @ingroup  pinsdriver
 * @brief Dynamic Interrupt Handler for SW_Next pin.
 *        This is a dynamic interrupt handler to be used together with the SW_Next_SetInterruptHandler() method.
 *        This handler is called every time the SW_Next ISR is executed and allows any function to be registered at runtime.
 * @pre Pins intializer called
 * @param none
 * @return none
 */
extern void (*SW_Next_InterruptHandler)(void);

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for SW_Next pin. 
 *        This is a predefined interrupt handler to be used together with the SW_Next_SetInterruptHandler() method.
 *        This handler is called every time the SW_Next ISR is executed. 
 * @pre Pins intializer called
 * @param none
 * @return none
 */
void SW_Next_DefaultInterruptHandler(void);


#endif // PINS_H
/**
 End of File
*/