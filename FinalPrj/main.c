#include "STD/STD_TYPES.h"
#include "STD/STD_MATH.h"
#include "DIO/DIO_INTERFACE.h"
#include "SPI/SPI_INTERFACE.h"
#include "GLCD/GLCD_INTERFACE.h"
#include "GIE/GIE_INTERFACE.h"
#include "ADC/ADC_INTERFACE.h"
#include "LM35/LM35_INTERFACE.h"
#include "LDR/LDR_INTERFACE.h"
#include "FLAME/FLAME_INTERFACE.h"
#include "UART/UART_INTERFACE.h"
#include <stdio.h>
#include <util/delay.h>

// Global variables
static uint8 current = 0; // Current menu state
static uint8 mode = 0; // System mode (Automatic or Manual)
static uint8 fanMode = 0; // Fan state (ON or OFF)
static uint8 fanSpeed = 1; // Fan speed (1, 2, 3)
static uint8 lightState = 0; // Light state (ON or OFF)

// Function prototypes
void mainMenuDisplay(); // Display the main menu
void statsMenuDisplay(); // Display the system status menu
void modifyMenuDisplay(); // Display the modify system menu
void modeMenuDisplay(); // Display the system mode menu
void settingsMenuDisplay(); // Display the settings menu
void fanStateMenuDisplay(); // Display the fan state menu
void fanSpeedMenuDisplay(); // Display the fan speed menu
void lightStateMenuDisplay(); // Display the light state menu
void handleUART(uint8 command); // Handle UART commands

int main(void)
{
    // Initialize hardware modules
    SPI_masterInit();
    UART_init(103);
    ADC_init();
    GLCD_init();
    mainMenuDisplay();

    // Set UART callback function for command handling
    UART_setCallBack(handleUART);

    // Enable global interrupts
    GIE();

    for (;;)
    {
        // Update sensor data
        LDR_init();
        LDR_calculate(2, mode);
        _delay_ms(10);
        LM35_init();
        LM35_calculate(0, mode);
        _delay_ms(10);
        FLAME_init();
        FLAME_calculate(1);
        _delay_ms(10);
    }

    return 0;
}

// Function to display the main menu
void mainMenuDisplay()
{
    current = 0;
    GLCD_clearLCD();
    GLCD_moveCursor(0, 35);
    GLCD_sendString("Main Menu");
    GLCD_moveCursor(3, 0);
    GLCD_sendString("1- Show System Status");
    GLCD_moveCursor(5, 0);
    GLCD_sendString("2- Modify System");
}

// Function to display the system status menu
void statsMenuDisplay()
{
    char LM35Str[25];
    char LDRStr[30];
    uint8 temperature = LM35_getTemperature();
    current = 1;
    GLCD_clearLCD();
    GLCD_moveCursor(0, 10);
    GLCD_sendString("System Status Menu");
    GLCD_moveCursor(2, 0);
    sprintf(LM35Str, "Temperature : %d C", LM35_getTemperature());
    GLCD_sendString(LM35Str);
    GLCD_moveCursor(3, 0);
    sprintf(LDRStr, "Light intensity : %d", LDR_getPercentage());
    GLCD_sendString(LDRStr);
    GLCD_moveCursor(4, 0);
    if (temperature <= 25)
    {
        GLCD_sendString("Fans are OFF");
    }
    else if (temperature > 25 && temperature <= 30)
    {
        GLCD_sendString("Fans are ON, Speed = 1");
    }
    else if (temperature > 30 && temperature <= 35)
    {
        GLCD_sendString("Fans are ON, Speed = 2");
    }
    else if (temperature > 35)
    {
        GLCD_sendString("Fans are ON, Speed = 3");
    }
    GLCD_moveCursor(6, 0);
    GLCD_sendString("Press r to Refresh");
    GLCD_moveCursor(7, 0);
    GLCD_sendString("Press m to go back");
}

// Function to display the modify system menu
void modifyMenuDisplay()
{
    // Logic to set initial fanMode, lightState, and fanSpeed
    if (mode == 0 && LM35_getTemperature() > 25)
    {
        fanMode = 1;
    }
    if (mode == 0 && LDR_getPercentage() <= 50)
    {
        lightState = 1;
    }
    uint8 temperature = LM35_getTemperature();
    if (temperature > 25 && temperature <= 30 && mode == 0)
    {
        fanSpeed = 1;
    }
    else if (temperature > 30 && temperature <= 35 && mode == 0)
    {
        fanSpeed = 2;
    }
    else if (temperature > 35 && mode == 0)
    {
        fanSpeed = 3;
    }

    current = 2;
    GLCD_clearLCD();
    GLCD_moveCursor(0, 9);
    GLCD_sendString("Modify System Menu");
    GLCD_moveCursor(3, 0);
    GLCD_sendString("1- Change System Mode");
    GLCD_moveCursor(5, 0);
    GLCD_sendString("2- Change Settings");
    GLCD_moveCursor(7, 0);
    GLCD_sendString("Press m to go back");
}

// Function to display the system mode menu
void modeMenuDisplay()
{
    current = 3;
    GLCD_clearLCD();
    GLCD_moveCursor(0, 13);
    GLCD_sendString("System Mode Menu");
    GLCD_moveCursor(3, 2);
    if (mode == 0)
    {
        GLCD_sendString("Automatic Mode is ON");
        GLCD_moveCursor(6, 0);
        GLCD_sendString("Press o to turn OFF");
    }
    else
    {
        GLCD_sendString("Automatic Mode is OFF");
        GLCD_moveCursor(6, 0);
        GLCD_sendString("Press o to turn ON");
    }
    GLCD_moveCursor(7, 0);
    GLCD_sendString("Press m to go back");
}

// Function to display the settings menu
void settingsMenuDisplay()
{
    current = 4;
    GLCD_clearLCD();
    if (mode == 1)
    {
        GLCD_moveCursor(0, 24);
        GLCD_sendString("Settings Menu");
        GLCD_moveCursor(2, 0);
        GLCD_sendString("1- Change Fan State");
        GLCD_moveCursor(3, 0);
        GLCD_sendString("2- Change Fan Speed");
        GLCD_moveCursor(4, 0);
        GLCD_sendString("3- Change Light State");
    }
    else
    {
        GLCD_moveCursor(3, 3);
        GLCD_sendString("Automatic Mode is ON");
    }
    GLCD_moveCursor(7, 0);
    GLCD_sendString("Press m to go back");
}

// Function to display the fan state menu
void fanStateMenuDisplay()
{
    current = 5;
    GLCD_clearLCD();
    GLCD_moveCursor(0, 20);
    GLCD_sendString("Fan State Menu");
    GLCD_moveCursor(2, 0);
    if (fanMode == 0)
    {
        GLCD_sendString("Fans are OFF");
        GLCD_moveCursor(6, 0);
        GLCD_sendString("Press f to turn ON");
    }
    else
    {
        GLCD_sendString("Fans are ON");
        GLCD_moveCursor(6, 0);
        GLCD_sendString("Press f to turn OFF");
    }
    GLCD_moveCursor(7, 0);
    GLCD_sendString("Press m to go back");
}

// Function to display the fan speed menu
void fanSpeedMenuDisplay()
{
    current = 6;
    char speed[30];
    GLCD_clearLCD();

    if (fanMode != 0)
    {
        GLCD_moveCursor(0, 20);
        GLCD_sendString("Fan Speed Menu");
        GLCD_moveCursor(2, 0);
        sprintf(speed, "Fan is at Speed : %d", fanSpeed);
        GLCD_sendString(speed);
        GLCD_moveCursor(6, 0);
        GLCD_sendString("Enter speed to Change");
    }
    else
    {
        GLCD_moveCursor(0, 20);
        GLCD_sendString("Fan Speed Menu");
        GLCD_moveCursor(3, 0);
        GLCD_sendString("Fan is OFF");
    }

    GLCD_moveCursor(7, 0);
    GLCD_sendString("Press m to go back");
}

// Function to display the light state menu
void lightStateMenuDisplay()
{
    current = 7;
    GLCD_clearLCD();
    GLCD_moveCursor(0, 18);
    GLCD_sendString("Light State Menu");
    GLCD_moveCursor(3, 2);
    if (lightState == 0)
    {
        GLCD_sendString("Light is OFF");
        GLCD_moveCursor(6, 0);
        GLCD_sendString("Press o to turn ON");
    }
    else
    {
        GLCD_sendString("Light is ON");
        GLCD_moveCursor(6, 0);
        GLCD_sendString("Press o to turn OFF");
    }
    GLCD_moveCursor(7, 0);
    GLCD_sendString("Press m to go back");
}

// Function to handle UART commands
void handleUART(uint8 command)
{
    switch (command)
    {
    case '1':
        if (current == 0)
        {
            statsMenuDisplay();
        }
        else if (current == 2)
        {
            modeMenuDisplay();
        }
        else if (current == 4)
        {
            fanStateMenuDisplay();
        }
        else if (current == 6)
        {
            SPI_transceive('1');
            fanSpeed = 1;
            fanSpeedMenuDisplay();
        }
        break;
    case '2':
        if (current == 0)
        {
            modifyMenuDisplay();
        }
        else if (current == 2)
        {
            settingsMenuDisplay();
        }
        else if (current == 4)
        {
            fanSpeedMenuDisplay();
        }
        else if (current == 6)
        {
            SPI_transceive('2');
            fanSpeed = 2;
            fanSpeedMenuDisplay();
        }
        break;
    case '3':
        if (current == 6)
        {
            SPI_transceive('3');
            fanSpeed = 3;
            fanSpeedMenuDisplay();
        }
        else if (current == 4)
        {
            lightStateMenuDisplay();
        }
        break;
    case 'm':
        mainMenuDisplay();
        break;
    case 'r':
        if (current == 1)
        {
            statsMenuDisplay();
        }
        break;
    case 'o':
        if (current == 3)
        {
            mode = !mode;
            modeMenuDisplay();
        }
        else if (current == 7)
        {
            lightState = !lightState;
            if (lightState == 0)
            {
                SPI_transceive('r');
            }
            else
            {
                SPI_transceive('R');
            }
            lightStateMenuDisplay();
        }
        break;
    case 'f':
        if (current == 5)
        {
            fanMode = !fanMode;
            if (fanMode == 0)
            {
                SPI_transceive('d');
            }
            else
            {
                SPI_transceive('D');
            }
            fanStateMenuDisplay();
        }
    default:
        break;
    }
}
