#include "linear_ccd.h"

void moving_adverage(){
	for(int i =0;i<128;i++){
	if(i==0 || i == 127){
		
	}
		else{linear_ccd_buffer1[i] = (u32)((linear_ccd_buffer1[i-1] + linear_ccd_buffer1[i] + linear_ccd_buffer1[i+1])/3.0f);
		}
	}
}
	

void CLK(u8 state){//self make clock to control two ccd

		if (state == 1){
	GPIO_SetBits(CLK_PORT, CLK_PIN);
		state=0;
	}
	else if (state == 0){
	GPIO_ResetBits(CLK_PORT,CLK_PIN);
		state=1;
	}
}


void SI(u8 bit){ //controlling Linear_ccd 1  and 2 si1 si2

	if(bit==1){
	GPIO_SetBits(SI1_PORT,SI1_PIN);
	//GPIO_SetBits(SI2_PORT,SI2_PIN);
	}

	else{
		GPIO_ResetBits(SI1_PORT,SI1_PIN);
		//GPIO_ResetBits(SI2_PORT,SI2_PIN);
	}
}

	


u32 AO1(){  // getting data from ccd1 ao1
	u32 temp;
	int get_times = 200;
for(u8 i=0;i<get_times;i++){
temp += get_adc(1);
}
temp=(u32)(temp/get_times);
return temp;
}

u32 AO2(){  // getting data from ccd1 ao1
	u32 temp;
	int get_times = 10;
for(u8 i=0;i<get_times;i++){
temp += get_adc(2);
}
temp=(u32)(temp/get_times);
return temp;
}

u32 linear_ccd_buffer1[128];
u32 linear_ccd_buffer2[128];
u8 flag = 0;
void linear_ccd_read(){
	SI(0);
	CLK(0);
	_delay_us(1);
	SI(1);
	for(u8 n=0;n<128;n++)
	{
		_delay_us(1);
		CLK(1);		
		SI(0);
		_delay_us(1);
		linear_ccd_buffer1[n]=AO1();
		//linear_ccd_buffer2[n]=AO2();
		CLK(0);
	}
	
	
	

	for(u8 y=0;y<128;y++)
	{
		linear_ccd_buffer1[y] = (linear_ccd_buffer1[y])*160 / 4095;
	 if(linear_ccd_buffer1[y] >= 160){
		linear_ccd_buffer1[y] = 159;
	}
}
	 moving_adverage();
	//putting pixel on the monitor
	for(u8 y=0;y<128;y +=1)
	{
	
	 
		tft_put_pixel(y,linear_ccd_buffer1[y],GREEN);//put linear ccd1 pixels
		//tft_put_pixel(y,(linear_ccd_buffer2[y]*80 / 4095)+80,GREEN);//put linear ccd2 pixels
	
	}
		for(u8 y=0;y<128;y+=1 )
	{
	
	
		tft_put_pixel(y,linear_ccd_buffer1[y],BLACK);//clear linear ccd1 pixels
		//tft_put_pixel(y,(linear_ccd_buffer2[y]*80 / 4095)+80,BLACK);//clear linear ccd2 pixels
	
	
	}

	
	
	
}





void linear_ccd_init()
{//initialization of clk 
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = CLK_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(CLK_PORT, &GPIO_InitStructure);
	
//initialization of si1
	GPIO_InitStructure.GPIO_Pin = SI1_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(SI1_PORT, &GPIO_InitStructure);

//initialization of si2
	GPIO_InitStructure.GPIO_Pin = SI2_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(SI2_PORT, &GPIO_InitStructure);
}
void linear_ccd_prints()
	{ int y ;
		int x ;
		for(x=0;x<=127;x++)
		{y= linear_ccd_buffer1[x];
		tft_put_pixel(x,y, BLACK);}
		tft_prints(2,4,"%d",find_white_line());
		tft_update();
		
	}

/*void linear_ccd_prints()
	{ int y ;
		int x ;
		int max=0;
		int min=159;
		int avex ;
		int count;
		int sum=0;
		for(x=0;x<=127;x++)
		{y= linear_ccd_buffer1[x];
		tft_put_pixel(x,linear_ccd_buffer1[x], BLACK);
		if (y>100)
		{count=count+1;
		 sum+=x;}
		if(y>max)
		{max=y;
		}
		//tft_prints(4,4,"%d-%d",sum,count);
		if(y<min)
		{min=y;}
		
		}
		avex=sum/count ;
		tft_prints(0,0 ,"%d-%d",min,max);
		tft_update();
		
	}*/
	void linear_ccd_clear()
{   int y ;
		int x ;
		
		for(x=0;x<=127;x++)
		{y= linear_ccd_buffer1[x];
		tft_put_pixel(x,y, WHITE);}
		tft_clear();
		
		
}	
int whiteexists(int max, int min){
    if((max-min) > 120){
        return 1;
    }
    return 0;
}



void turnn(int x){
    if (x>0 && x<20){
        motor_control(1, 0, 0);  //left motor
        motor_control(2, 0, 100); //right motor
        tft_prints(5,5,"Turn left");
        tft_update();
    }else if(x>20 && x<40){
        motor_control(1, 0, 0);
        motor_control(2, 0, 75);
        tft_prints(5,5,"Turn left");
        tft_update();
    }else if(x>40 && x<54){
        motor_control(1, 0, 0);
        motor_control(2, 0, 70);
        tft_prints(5,5,"Turn left");
        tft_update();
    }
    if(x>74 && x<100){
        motor_control(1, 0, 100);   //left motor
        motor_control(2, 0, 0);
        tft_prints(5,5,"Turn right");
        tft_update();
    }else if(x<100 && x>120){
        motor_control(1,0, 75);
        motor_control(2,0, 0);
        tft_prints(5,5,"Turn right");
        tft_update();
    }else if (x>120){
        motor_control(1,0,70);
        motor_control(2,0, 0);
        tft_prints(5,5,"Turn right");
        tft_update();
    }
}
void start()
{ 
	
	 motor_control(1,0,100);
   motor_control(2,0,100);
	 _delay_ms(2000);
	 motor_control(1,0,0);
   motor_control(2,0,100);
	_delay_ms(2000);
	 motor_control(1,0,100);
   motor_control(2,0,100);
	 _delay_ms(4000);
	motor_control(1,0,0);
  motor_control(2,0,0);
	
}
void checkendstage(int max, int min)
	{
    
    if((max-min)<30){   //if y fall in small range stop the car in 1 sec
        motor_control(1,0,50);
        motor_control(2,0,50);
        _delay_ms(1000);
        motor_control(1,0,0);
        motor_control(2,0,0);
    }	
	}


void print_ccd()
	{
    int y;
    int x;
    int avex;
    int sum;
    int max=0;
    int min=159;
    int mmin;
    int mmax;
    int count;

    for(int i=0; i<128; ++i){
        tft_put_pixel(i, linear_ccd_buffer1[i], BLACK);
        x=i;
        y=linear_ccd_buffer1[i];
        max= (y>max)? y: max;
        min = (y<min)? y :min;

        /*if(whiteexists(max,min)){
            sum+=i;
            count=count+1;
            tft_prints(1,1,"whiteline=1");
            tft_update();
        }else{
            tft_prints(1,1,"whiteline=0");
            tft_update();
            //checkendstage(max,min);
        }
        //checkendstage(max,min);
    }
    tft_prints(2,2,"max=%d",max);
    tft_update();
    tft_prints(2,3,"min=%d",min);
    tft_update();
    avex=sum/count;
    tft_prints(7,7,"avex=%d",avex);
    tft_update();
    //turnn(avex);*/
}
}
	int find()
  { int x ;
		int r=127;
		int y[128];
	  int r1=128;
		int remain[r1] ;
		int maxNum=10;
		int maxy[maxNum] ;
		int maxx[maxNum];
		int maxy1=0 ;
		int maxx1;
	
		
		for(int i=0;i<128;i++)
		{ y[i]=linear_ccd_buffer1[i] ;}
		
	for(int i=0;i<10;i++)	
		{
			for(x=0;x<r+1;x++)
		   { if(y[x]>maxy1)
		     { maxy1=y[x];
					 maxx1=x;
				 }
		   }
		y[127]= maxy1;
		maxy[i]= maxy1;
		maxx[i]=maxx1;	 
	   for(int i=0;i<r;i++)
		  { r1--;
			remain[i]=y[i];}
		 r--;
		 i++;
	 } 
		int minInMaxY=160 ;
		for(int i=0;i<maxNum;i++)
		{if(maxy[i]<minInMaxY)
		    {minInMaxY=maxy[i];}
		}
		int sum=0;
		if (minInMaxY>100)
		{ for(int i=0;i<maxNum;i++)
		       {sum+=maxx[i];}
		}
		int avex=sum/maxNum ;
		
		
	}
 
	
	 	 
		
	
	int find_white_line() {
		
    int targetNumber = 10;
    int arrayLength = 128;
    int sortedArray[128];
    //int sortedArray[100]; 
    //Only make it 
    for (int h = 0; h < 128; ++h) {
        sortedArray[h] = linear_ccd_buffer1[h];
    }
    
    int swap;

    for (int i = 0; i < arrayLength; ++i) {
        for (int j = 0; j < arrayLength - i - 1; ++j) {
            if (sortedArray[j] < sortedArray[j+1]) {
                swap = sortedArray[j];
                sortedArray[j] = sortedArray[j+1];
                sortedArray[j+1] = swap;
            }
        }
    }

    int xvalues[targetNumber];
    int index = 0;
    int target = sortedArray[targetNumber];
    for (int i = 0; i < arrayLength; ++i) {
        if (linear_ccd_buffer1[i] > target) {
            xvalues[index] = i;
            index +=1;
        }
    }
    int averagex = 0;
    int sum = 0;
    for(int i = 0; i < targetNumber; i++) {
        sum += xvalues[i];
    }
		if(target>110)
		{
    averagex = sum/targetNumber;

    return averagex;
		}
		else
		{return 64 ;}
}
	void turn(int x){
	if (x>0 && x<20){
		motor_control(1, 0, 20);
		motor_control(2, 0, 165);
	}else if(x>20 && x<40){
		motor_control(1, 0, 20);
		motor_control(2, 0, 140);
	}else if(x>40 && x<54){
		motor_control(1, 0, 50);
		motor_control(2, 0, 110);
	}
	if(x>74 && x<100){
		motor_control(1, 0, 110);	//left motor
		motor_control(2, 0, 50);
	}else if(x<100 && x>120){
		motor_control(1,0, 140);
		motor_control(2,0, 20);
	}else if (x>120){
		motor_control(1,0,165);
		motor_control(2,0, 20);
	}
	
}
