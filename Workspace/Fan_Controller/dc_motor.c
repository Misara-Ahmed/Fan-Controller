/******************************************************************************
 *
 * Module: DC MOTOR
 *
 * File Name: dc_motor.c
 *
 * Description: Source file for the ATmega32 DC MOTOR driver
 *
 * Author: Misara Ahmed
 *
 *******************************************************************************/

#include "dc_motor.h"
#include <avr/io.h>

/*
 * Description :
 * Function responsible for setup the direction for the two motor pins and Stop the DC-Motor at the beginning.
 */
void DcMotor_Init(void)
{
	/*
	 * configuring the dc motor pins to be output pins.
	 */
	GPIO_setupPinDirection(DC_FIRST_PORT,DC_FIRST_PIN,PIN_OUTPUT);
	GPIO_setupPinDirection(DC_SECOND_PORT,DC_SECOND_PIN,PIN_OUTPUT);

	/*
	 * stopping the dc motor at the beginning.
	 */
	GPIO_writePin(DC_ENABLE_PORT, DC_ENABLE_PIN, LOGIC_LOW);

}

/*
 * Description :
 * Function responsible for rotate the DC Motor CW/ or A-CW or stop the motor based on the state input state value.
 * Function responsible for sending the required duty cycle to the PWM driver based on the required speed value.
 */
void DcMotor_Rotate(DcMotor_State state,uint8 speed)
{
	/*
	 * Configuring the states of the motor.
	 */
	switch (state)
	{
	case STOP :
		/*
		 * Stopping the motor by clearing both pins of it.
		 */
		CLEAR_BIT(DDRB,PIN0_ID);
		CLEAR_BIT(DDRB,PIN1_ID);
		break;
	case CW :
		/*
		 * Configuring the motor to rotate clockwise by setting the first pin and clearing the second pin.
		 */
		SET_BIT(DDRB,PIN0_ID);
		CLEAR_BIT(DDRB,PIN1_ID);
		break;
	case ACW :
		/*
		 * Configuring the motor to rotate anti-clockwise by clearing the first pin and setting the second pin.
		 */
		CLEAR_BIT(DDRB,PIN0_ID);
		SET_BIT(DDRB,PIN1_ID);
		break;
	}

	/*
	 * starting the motor with the required speed.
	 */
	PWM_Timer0_Start(speed);
}
