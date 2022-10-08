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
	GPIO_setupPinDirection(DC_PORT,DC_FIRST_PIN,PIN_OUTPUT);
	GPIO_setupPinDirection(DC_PORT,DC_SECOND_PIN,PIN_OUTPUT);

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
#if DC_PORT == 0
		CLEAR_BIT(PORTA,DC_FIRST_PIN);
		CLEAR_BIT(PORTA,DC_SECOND_PIN);
		break;
#endif
#if DC_PORT == 1
		CLEAR_BIT(PORTB,DC_FIRST_PIN);
		CLEAR_BIT(PORTB,DC_SECOND_PIN);
		break;
#endif
#if DC_PORT == 2
		CLEAR_BIT(PORTC,DC_FIRST_PIN);
		CLEAR_BIT(PORTC,DC_SECOND_PIN);
		break;
#endif
#if DC_PORT == 3
		CLEAR_BIT(PORTD,DC_FIRST_PIN);
		CLEAR_BIT(PORTD,DC_SECOND_PIN);
		break;
#endif

	case CW :
		/*
		 * Configuring the motor to rotate clockwise by clearing the first pin and setting the second pin.
		 */
#if DC_PORT == 0
		CLEAR_BIT(PORTA,DC_FIRST_PIN);
		SET_BIT(PORTA,DC_SECOND_PIN);
		break;
#endif
#if DC_PORT == 1
		CLEAR_BIT(PORTB,DC_FIRST_PIN);
		SET_BIT(PORTB,DC_SECOND_PIN);
		break;
#endif
#if DC_PORT == 2
		CLEAR_BIT(PORTC,DC_FIRST_PIN);
		SET_BIT(PORTC,DC_SECOND_PIN);
		break;
#endif
#if DC_PORT == 3
		CLEAR_BIT(PORTD,DC_FIRST_PIN);
		SET_BIT(PORTD,DC_SECOND_PIN);
		break;
#endif

	case ACW :
		/*
		 * Configuring the motor to rotate anti-clockwise by setting the first pin and clearing the second pin.
		 */
#if DC_PORT == 0
		SET_BIT(PORTA,DC_FIRST_PIN);
		CLEAR_BIT(PORTA,DC_SECOND_PIN);
		break;
#endif
#if DC_PORT == 1
		SET_BIT(PORTB,DC_FIRST_PIN);
		CLEAR_BIT(PORTB,DC_SECOND_PIN);
		break;
#endif
#if DC_PORT == 2
		SET_BIT(PORTC,DC_FIRST_PIN);
		CLEAR_BIT(PORTC,DC_SECOND_PIN);
		break;
#endif
#if DC_PORT == 3
		SET_BIT(PORTD,DC_FIRST_PIN);
		CLEAR_BIT(PORTD,DC_SECOND_PIN);
		break;
#endif
	}

	/*
	 * starting the motor with the required speed.
	 */
	PWM_Timer0_Start(speed);
}
