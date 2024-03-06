# PIC16_ADC_LED_Dimmer

This project implements an LED dimmer using an analog-to-digital converter (ADC) and pulse-width modulation (PWM) on a microcontroller. It is designed to control the brightness of an LED based on an analog input voltage.

## Microcontroller Used
This project is designed for the **PIC16F877A** microcontroller. 

## Project Overview
The project consists of two main components: ADC and PWM.

### ADC (Analog-to-Digital Converter)
The ADC module reads an analog input voltage from a sensor or potentiometer connected to one of the analog pins (AN0 in this case). It converts the analog voltage into a digital value, which is then used to determine the brightness of the LED.

### PWM (Pulse-Width Modulation)
The PWM module generates a pulse-width modulated signal that controls the brightness of the LED. The duty cycle of the PWM signal is determined by the digital value obtained from the ADC. 

## How to Use
1. **Setup**: Connect the microcontroller to the LED and the analog sensor/potentiometer.
2. **Compilation**: Compile the project using a suitable compiler (e.g., MPLAB XC8).
3. **Programming**: Program the microcontroller with the generated hex file.
4. **Operation**: Upon power-up, the LED will vary in brightness based on the input voltage from the analog sensor.

## Project Files
- **main.c**: Contains the main code for the project.
- **config.h**: Header file containing configuration settings for the microcontroller.
- **Makefile**: Makefile for compiling the project.

## Additional Notes
- The project is configured to use a 4 MHz crystal oscillator.
- Adjustments can be made to the PWM frequency and ADC settings as needed.
- This project serves as a basic example and can be extended for more complex applications.


