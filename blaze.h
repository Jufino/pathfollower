#ifndef _BLAZE_H
#define _BLAZE_H

#ifndef MaxValue
	#define MaxValue 1300
#endif
#ifndef MinValue
	#define MinValue 500
#endif

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include "libserial.h"

void InitBlaze(const char *port_name,speed_t speed);
char Ult(unsigned char i);
char Buttons(void);
char ReflexiveIR(unsigned char i);
int *LineSensors(void);
unsigned int LinePosition(void);
void LED_Y(bool status);
void LED_R(bool status);
void LED_G(bool status);
void LED_IR(bool status);
void InitMotors(char mode);
void MotorL(int speed);
void MotorR(int speed);
void SetMotors(int speedA,int speedB);
void tik(void);
void tok(void);
#endif
