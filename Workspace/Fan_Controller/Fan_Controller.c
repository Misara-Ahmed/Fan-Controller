/******************************************************************************
 *
 * Project Name: Fan Controller
 *
 * File Name: Fan_Controller.c
 *
 * Description: Source file for the ATmega32 Fan Controller project
 *
 * Author: Misara Ahmed
 *
 *******************************************************************************/
#include "Fan_Controller.h"

#include <avr/io.h>

/*
 * Creating an object from the the ADC_ConfigType struct to configure the prescaler & the reference voltage.
 */
ADC_ConfigType ADC_config = { 3 , 3 };

/*
 * Description :
 * Function to control the Fan speed according to the temperature.
 */
void Fan_status(uint8 temp)
{
	LCD_moveCursor(0,11);

	if (temp < 30)
	{
		/*
		 * If the temperature is less than 30 C turn off the fan.
		 */
		LCD_displayString("OFF");
		DcMotor_Rotate(STOP,0);
	}
	else if (temp >= 30 && temp < 60)
	{
		/*
		 * If the temperature is greater than or equal 30 C turn on the fan with 25% of its maximum speed.
		 */
		LCD_displayString("ON ");
		DcMotor_Rotate(CW,25);
	}
	else if (temp >= 60 && temp < 90)
	{
		/*
		 * If the temperature is greater than or equal 60 C turn on the fan with 50% of its maximum speed.
		 */
		LCD_displayString("ON ");
		DcMotor_Rotate(CW,50);
	}
	else if (temp >= 90 && temp < 120)
	{
		/*
		 * If the temperature is greater than or equal 90 C turn on the fan with 75% of its maximum speed.
		 */
		LCD_displayString("ON ");
		DcMotor_Rotate(CW,75);
	}
	else if (temp >= 120)
	{
		/*
		 * If the temperature is greater than or equal 120 C turn on the fan with 100% of its maximum speed.
		 */
		LCD_displayString("ON ");
		DcMotor_Rotate(CW,100);
	}
}

int main(void)
{
	/*
	 * Initializing the LCD & ADC & MOTOR.
	 */
	LCD_init();
	ADC_init( &ADC_config );
	DcMotor_Init();

	/*
	 * Local variable to store the temperature reading.
	 */
	uint8 temp;

	/*
	 * Setup the LCD cursor to display where you want.
	 */
	LCD_moveCursor(0,4);
	LCD_displayString("FAN is ");

	LCD_moveCursor(1,3);
	LCD_displayString("TEMP =    C");

	while(1)
	{

		temp = LM35_getTemperature();

		/*
		 * Displaying the temperature.
		 */
		Fan_status(temp);

		/* Display the temperature value every time at same position */
		LCD_moveCursor(1,10);

		if(temp >= 100)
		{
			LCD_intgerToString(temp);
		}
		else
		{
			LCD_intgerToString(temp);

			/* In case the digital value is two or one digits print space in the next digit place */
			LCD_displayCharacter(' ');
		}
	}
}
