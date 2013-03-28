#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#define MaxValue 1300
#define MinValue 0
#include "blaze.h"

using namespace std;
//-----------------------------------------------------------
int main(void)
{
  	InitBlaze("/dev/ttyACM1",B57600);
//	printf("LED_Y\n");
//	LED_Y(0);
//	printf("ult1 = %d\n",Ult(1));
/*	printf("ult2 = %d\n",Ult(2));
	printf("ult3 = %d\n",Ult(3));
	printf("ult4 = %d\n",Ult(4));
	printf("ult5 = %d\n",Ult(5));
*/
  //      printf("ReflexiveIR = %d\n",ReflexiveIR(1));
//	printf("Buttons = %d\n",Buttons());
//	int *i = LineIR();
//	for(int x = 0; x<9;x++)	printf("S%d = %d\n",x,i[x]);
	printf("%i\n",ReadPosition());

	return 0;
}
