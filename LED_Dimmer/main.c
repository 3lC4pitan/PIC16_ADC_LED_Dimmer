/*
 * ADC LED Dimmer
 * Author:   Amine NAOUR 
 */

#include <xc.h>
#include "config.h" // Include configuration header file
#include <stdint.h>

// Define oscillator frequency
#define _XTAL_FREQ 4000000

// Function prototypes
void PWM1_Init();
void PWM1_Set_Duty(uint16_t);
void ADC_Init();
uint16_t ADC_Read(uint8_t);

// Main function
void main(void) 
{
    // Initialize PWM and ADC modules
    PWM1_Init();
    ADC_Init();
    
    // Main loop
    while(1)
    {
        // Read analog input and set PWM duty cycle accordingly
        PWM1_Set_Duty(ADC_Read(0)); 
        __delay_ms(1); // Delay for stability
    }
    return;
}

// Initialize PWM module
void PWM1_Init()
{
    // Configure CCP module for PWM mode
    CCP1M3 = 1;
    CCP1M2 = 1;
    TRISC2 = 0; // Set CCP1 output pin (PWM)
    
    // Set PWM frequency (~1kHz)
    PR2 = 255;
    
    // Set prescaler for Timer2 (1:4 ratio)
    T2CKPS0 = 1;
    T2CKPS1 = 0;
    
    // Start PWM
    TMR2ON = 1;
}

// Set PWM duty cycle
void PWM1_Set_Duty(uint16_t DC)
{
    // Ensure DC value is within 10-bit range
    if(DC < 1024)
    {
        // Set CCP1Y and CCP1X based on lower bits of DC
        CCP1Y = DC & 1;
        CCP1X = DC & 2;
        // Set CCPR1L based on upper bits of DC
        CCPR1L = DC >> 2;
    }
}

// Initialize ADC module
void ADC_Init()
{
    // Turn ADC ON, select AN0 channel, ADC clock = Fosc/8
    ADCON0 = 0x41;
    // All 8 channels are analog, result is "Right-Justified",
    // ADC clock = Fosc/8
    ADCON1 = 0x80;
}

// Read analog value from specified channel
uint16_t ADC_Read(uint8_t ANC)
{
    // Check channel number validity
    if(ANC < 0 || ANC > 7)    
    { 
        return 0;
    }
    
    // Clear channel selection bits
    ADCON0 &= 0b11000101;
    // Select the required channel (ANC)
    ADCON0 |= ANC << 3;
    // Wait for acquisition time
    __delay_us(30); // Minimum Tacq = 20us
    // Start A/D conversion
    GO_DONE = 1;
    // Wait until conversion is complete
    while(ADCON0bits.GO_DONE); 
    // Return the right-justified 10-bit result
    return ((ADRESH << 8) + ADRESL); 
}
