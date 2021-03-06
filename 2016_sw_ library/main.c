#include "main.h"
#include "uart.h"
#include "linear_ccd.h"
#include "pneumatic_control.h"
int stop_while = 1;
int delay_time = 100;
void listener(const uint8_t byte) {
	switch(byte) {
		case 'w':
			tft_prints(1,1,"Yay Forward LA");
			tft_update(); 
			motor_control(1,1,100);
			motor_control(2,1,100);
			_delay_ms(delay_time);
			motor_control(1, 1, 0); 
			motor_control(2, 1, 0); 
			break;
		
		case 'a': 
			tft_prints(1,1,"Yay Left LA");
			tft_update();
			motor_control(1, 1, 0); 
			motor_control(2, 1, 100);
	   	_delay_ms(delay_time);
			motor_control(1, 1, 0); 
			motor_control(2, 1, 0); 
			break; 
		
		case 'd':
			tft_prints(1, 1, "Yay Right LA");
			tft_update();
			motor_control(1,1,100);
			motor_control(2,1,0);
			_delay_ms(delay_time);
			motor_control(1, 1, 0); 
			motor_control(2, 1, 0); 
			break; 
		
		case 's': 
			tft_prints(1, 1, "Yay Stop La"); 
			tft_update(); 
			motor_control(1, 1, 0);
			motor_control(2, 1, 0);
			//stop_while = 0;
			break;
		
		case 'b':
			stop_while = 1; 
			break; 
		
		default:
			tft_prints(1, 1, "default la"); 
			break; 
		
	}
}
	
/*int main()
{
	LED_INIT(); 
	uart_init(COM3, 115200); 
	//uart_interrupt_init(COM3, &listener);  
	tft_init(0, WHITE, BLACK, GREEN);
	button_init(); 
	ticks_init(); 
	motor_init(); 
	pneumatic_init(); 
	int count = 0; 
	tft_init(0, WHITE, BLACK, GREEN);
	linear_ccd_init(); 
	adc_init(); 
	while(true) {
		if(count != get_ms_ticks()){
			count = get_ms_ticks();	
			if(count % 40 == 0){
				linear_ccd_clear(); 
				linear_ccd_read(); 
				linear_ccd_prints();
				if(find_white_line() != 0) {
					tft_prints(2, 1, "%3d", find_white_line());
					tft_update();
				}
		
				if(find_white_line() < 50) {
					motor_control(1,0,100);
						
				}
				else {
					motor_control(1,0,0);
						
				}
				//tft_update();
			}
		}
	}
	return 0;
}*/
int main(){
tft_init(0,WHITE,BLACK,RED);
linear_ccd_init();
ticks_init();
GPIO_switch_init();
pneumatic_init();
button_init();
LED_INIT();	
motor_init();
uart_init(COM3, 115200);
uart_interrupt_init(COM3,&listener);
	
while(true){
 //listener(const uint8_t byte);
 tft_clear();
 tft_prints(2,4,"okay la") ;
 tft_update();
	
 while(!read_button(1))
 { LED_ON(GPIOB, LED_M);
   motor_control(1,1,100);
 }
	 /*if(read_GPIO_switch(GPIOA,GPIO_Pin_9)==1&&!read_button(1))
 { tft_clear();
	 tft_prints(2,4,"grip");
	 tft_update();*/
 /*pneumatic_control(GPIOB,GPIO_Pin_13,1);}
  else
	{ tft_clear();
		tft_prints(2,4,"let it go~");
		tft_update();
	pneumatic_control(GPIOB,GPIO_Pin_13,0);}*/

int time = get_ms_ticks();
	if(time%40==0)
	{
	linear_ccd_clear();
	linear_ccd_read();
	linear_ccd_prints();
	 
	}
	//turnn(find_white_line());

}
}


	
/*
int main()
{ adc_init();
	ticks_init();
	linear_ccd_init();
	motor_init(); 
	pneumatic_init();
	tft_init(0,WHITE,BLACK,RED);
	uart_init(COM3, 115200);
	uart_interrupt_init(COM3,&listener);
	GPIO_ResetBits(GPIOA,GPIO_Pin_5);
  if(!read_button(2))
	{pneumatic_control(GPIOA,GPIO_Pin_5,1) ;}
	
	
	
	
	
	while(stop_while) {
		motor_control(1, 1, 100); 
		motor_control(2, 1, 100);
		
	}
	

	uint8_t *msg = "lo"; 
	uint8_t *a = "e";
	uart_tx(COM3, a);
	uart_tx(COM3, msg);
	
	
	
		
	//start();*/
		
	/*int main()
	{
	adc_init();
	ticks_init();
	linear_ccd_init();
	motor_init(); 
	pneumatic_init();
	tft_init(0,WHITE,BLACK,RED);
	uart_init(COM3, 115200);
	//uart_interrupt_init(COM3,&listener);
	while(1)
	{ 
	  int count=get_ms_ticks();
		if (count%40==0)
		{
	   linear_ccd_read();		
	   linear_ccd_prints();
		
		 //tft_prints(4,4,"%d",find_white_line());
	   linear_ccd_clear();
			tft_update(); 
			
		}
	}
}
	*/
	
	


	/*init();
	
	while (true)
	{
		if (!read_button(0))
		{
			while (!read_button(0));
			
			// ...
		}
		
		systemPolling();
	}*/
	
	


/*
void basemode()
{ 
	int y ;
	int x ;
	int max ;
	int sum=0 ;
	int avex;
  int count=0 ;	
		for(x=0;x<=127;x++)
		{ y= linear_ccd_buffer1[x];
		   if(y>max)
		    { count++;
		      sum+=x;
		    }
		}		
		avex= sum/count ;
		
		turnn(avex);
		*/
		
		/*
		if (avex>74)
		{
		 motor_control(2,0,80);
		 motor_control(1,0,100);
		}	
		else if (avex<54)
		{
		 motor_control(1,0,80);
		 motor_control(2,0,100);
		}	
		*/

	

