#include "project.h"

//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************

#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}
#endif

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_gpio.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "driverlib/pwm.h"


int main(void)
{    
	
unsigned long Period;
	

    //Set system clock
   SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC |   SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

   //Configure PWM Clock
   SysCtlPWMClockSet(SYSCTL_PWMDIV_1);

   // Enable the peripherals 
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1); 
    Period = SysCtlClockGet() / 200;             //PWM frequency 200Hz

    //Configure PF1,PF2,PF3 Pins as PWM
    GPIOPinConfigure(GPIO_PF1_M1PWM5);
    GPIOPinConfigure(GPIO_PF2_M1PWM6);
    GPIOPinConfigure(GPIO_PF3_M1PWM7);
    GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);

    //Configure PWM Options
    //PWM_GEN_2 --> M1PWM4 and M1PWM5
    //PWM_GEN_3 --> M1PWM6 and M1PWM7
    PWMGenConfigure(PWM1_BASE, PWM_GEN_2, PWM_GEN_MODE_UP_DOWN | PWM_GEN_MODE_NO_SYNC); 
    PWMGenConfigure(PWM1_BASE, PWM_GEN_3, PWM_GEN_MODE_UP_DOWN | PWM_GEN_MODE_NO_SYNC); 

    //Set the Period
    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_2, Period);
    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_3, Period);

    //Set PWM duty-50% 
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5,Period/2);
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6,Period/2);
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_7,Period/2);

    // Enable the PWM Gen
    PWMGenEnable(PWM1_BASE, PWM_GEN_2);
    PWMGenEnable(PWM1_BASE, PWM_GEN_3);

    // Turn on the Output pins
    PWMOutputState(PWM1_BASE, PWM_OUT_5_BIT |PWM_OUT_6_BIT|PWM_OUT_7_BIT, true);

   
 while (1)
 {

}}
