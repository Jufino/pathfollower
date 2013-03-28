#include "blaze.h"
//--------------------------------------------------------
char *int2char(char *buffer,int i,bool newline){ 
  char *bufferx = (char*)malloc(strlen(buffer)*sizeof(char)+5);
  if (buffer != NULL && newline == false)	sprintf(bufferx,"%s%4d",buffer,i);
  else if(buffer == NULL && newline == false)  	sprintf(bufferx,"%4d",i);
  else if(buffer != NULL && newline == true)    sprintf(bufferx,"%s%4d\n",buffer,i);
  else						sprintf(bufferx,"%4d\n",i);
  unsigned char p=0;
  do{
        if (bufferx[p] == ' ') bufferx[p] = '0';
  }
  while(bufferx[p++] != '\0');
  return bufferx;
}

//-------------------------------------------------------
timeval startTime,endTime;
void tik(void){
	gettimeofday(&startTime, NULL);
}
void tok(void){
	long seconds, useconds;
	double duration;
        gettimeofday(&endTime, NULL);
        seconds  = endTime.tv_sec  - startTime.tv_sec;
        useconds = endTime.tv_usec - startTime.tv_usec;
        duration = seconds + useconds/1000000.0;
        printf("%5.6f seconds\n", duration);
}
//-------------------------------------------------------
int port;
void InitBlaze(const char *port_name,speed_t speed){
  port = SerialOpen(port_name,speed);
  SerialWrite(port,int2char("b",MaxValue,true));
}
char Ult(unsigned char i){
  switch(i){
    case 1: SerialWrite(port,"a\n");
            return SerialRead(port,1)[0];  break;
    case 2: SerialWrite(port,"s\n");
            return SerialRead(port,1)[0];  break;
    case 3: SerialWrite(port,"d\n");
            return SerialRead(port,1)[0];  break;
    case 4: SerialWrite(port,"f\n");
            return SerialRead(port,1)[0];  break;
    case 5: SerialWrite(port,"g\n");
            return SerialRead(port,1)[0];  break;
  }
}
char Buttons(void){
  SerialWrite(port,"h\n");
  return SerialRead(port,1)[0];
}
char ReflexiveIR(unsigned char i){
switch(i){
    case 1: SerialWrite(port,"j\n");
            return  SerialRead(port,1)[0]; break;
    case 2: SerialWrite(port,"k\n");
            return SerialRead(port,1)[0];  break;
    case 3: SerialWrite(port,"l\n");
            return SerialRead(port,1)[0];  break;
    case 4: SerialWrite(port,"q\n");
            return SerialRead(port,1)[0];  break;
    case 5: SerialWrite(port,"w\n");
            return SerialRead(port,1)[0];  break;
  }
}
int *LineSensors(void){
  SerialWrite(port,"e\n");
  char *datas =  SerialRead(port,18);
  int *i = (int*)malloc(sizeof(int)*9);
  i[0] = (((int)datas[0]<<8)+(int)datas[1])-MinValue;
  i[1] = (((int)datas[2]<<8)+(int)datas[3])-MinValue;
  i[2] = (((int)datas[4]<<8)+(int)datas[5])-MinValue;
  i[3] = (((int)datas[6]<<8)+(int)datas[7])-MinValue;
  i[4] = (((int)datas[8]<<8)+(int)datas[9])-MinValue;
  i[5] = (((int)datas[10]<<8)+(int)datas[11])-MinValue;
  i[6] = (((int)datas[12]<<8)+(int)datas[13])-MinValue;
  i[7] = (((int)datas[14]<<8)+(int)datas[15])-MinValue;
  i[8] = (((int)datas[16]<<8)+(int)datas[17])-MinValue;
  for (unsigned char a=0;a<9;a++){
	if (i[a] < 0)	i[a] = 0;
  }
  return i;
}
void LED_Y(bool status){
  if (status == 0)  SerialWrite(port,"0\n");
  else              SerialWrite(port,"1\n");
}
void LED_R(bool status){
  if (status == 0)  SerialWrite(port,"2\n");
  else              SerialWrite(port,"3\n");
}
void LED_G(bool status){
  if (status == 0)  SerialWrite(port,"4\n");
  else              SerialWrite(port,"5\n");
}
void LED_IR(bool status){
  if (status == 0)  SerialWrite(port,"6\n");
  else              SerialWrite(port,"7\n");
}
void InitMotors(char mode){
  if (mode == 'a')  SerialWrite(port,"8\n");
  else              SerialWrite(port,"9\n");
}
void MotorL(int speed){
  SerialWrite(port,int2char("i",speed,true));
}
void MotorR(int speed){
  SerialWrite(port,int2char("u",speed,true));
}
void SetMotors(int speedA,int speedB){
  
  char *buffer = int2char("y",speedA,false);
  SerialWrite(port,int2char(buffer,speedB,true));
}
unsigned int LinePosition(void){
    int *sensor_values = LineSensors();
    unsigned int sum = 	(unsigned int)sensor_values[0]+
			(unsigned int)sensor_values[1]+
			(unsigned int)sensor_values[2]+
			(unsigned int)sensor_values[3]+
			(unsigned int)sensor_values[4]+
			(unsigned int)sensor_values[5]+
			(unsigned int)sensor_values[6]+
			(unsigned int)sensor_values[7]+
			(unsigned int)sensor_values[8];   

    if (sum != 0){
        return ((unsigned int)sensor_values[1] * (MaxValue-MinValue)   + 
		(unsigned int)sensor_values[2] * (MaxValue-MinValue) *2 + 
		(unsigned int)sensor_values[3] * (MaxValue-MinValue) *3 + 
		(unsigned int)sensor_values[4] * (MaxValue-MinValue) *4 + 
		(unsigned int)sensor_values[5] * (MaxValue-MinValue) *5 + 
		(unsigned int)sensor_values[6] * (MaxValue-MinValue) *6 + 
		(unsigned int)sensor_values[7] * (MaxValue-MinValue) *7 + 
		(unsigned int)sensor_values[8] * (MaxValue-MinValue) *8)/sum;      
    }  
    else	return 0;
}
