 /******************************************************************************
 *
 * Project Name: Fan Controller
 *
 * File Name: Fan_Controller.h
 *
 * Description: Header file for the ATmega32 Fan Controller project
 *
 * Author: Misara Ahmed
 *
 *******************************************************************************/
#ifndef FAN_CONTROLLER_H_
#define FAN_CONTROLLER_H_

#include "lcd.h"
#include "lm35_sensor.h"
#include "dc_motor.h"
#include "adc.h"

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description :
 * Function to control the Fan speed according to the temperature.
 */
void Fan_status(uint8 temp);

#endif /* FAN_CONTROLLER_H_ */
