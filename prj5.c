#include <avr/io.h>
#include <avr/delay.h>

#include "avr.h"
#include "helper.h"
#include "lcd.h"
#include "sensor.h"

int flag = 1;

void main()
{
	//Activate PORT A for keyboard 
	DDRA = 0xF0;
	PORTA = 0x0F;
	
	uint16_t r,r1,r2,r4;

	_delay_ms(200); 
	
	ini_lcd();

    //distance sensor
	HCSR04InitDist();
	
    //volume sensor 1
	HCSR04Init();
	
	//volume sensor 2
    HCSR04Init1();
	
	//volume sensor 3
	HCSR04Init2();
	
	clr_lcd();
	
	pos_lcd(0,0);
	
	put_str_lcd("AZRET & ATSUHIRO");
	_delay_ms(4500);
	
	clr_lcd();
	//MENU : CHOSE 1 - DISTANCE  2 - VOLUME 
	while (keypressed()==' ')
	{
	 pos_lcd(0,0);
	 put_str_lcd("CHOSE ACTION");
	 pos_lcd(1,0);
	 put_str_lcd("1-DIST  2-VOLUME");
	}	

    //DISTANCE 
    if (keypressed()=='1')
	{
	  clr_lcd();
	 
	  HCSR04TriggerDist();
	 
	  pos_lcd(0,0);
	  put_str_lcd("Distance : ");
	 
	  while(1)
	  {
	   _delay_ms(100);
	  
	    unsigned int d4;
	   
	    HCSR04TriggerDist();
	    r4 = GetPulseWidthDist();
	   
	    if(r4==-1)
	    {
		   pos_lcd(1,0);
		   put_str_lcd("ERROR ERROR!");
	   }
	    else if(r4==-2)
	    {
		   pos_lcd(1,0);
		   //put_str_lcd("DISTANCE DIST!");
	    }
	    else
	    {
		   //Convert to cm
		   d4 = (r4/58.0);
		   char buffer[20];
		   sprintf(buffer, "%02dcm", d4);
		   pos_lcd(1,0);
		   put_str_lcd(buffer);
		   wait_avr(100);
	    }
	  }
	 }
    
	//VOLUME
	if (keypressed()=='2')
	{
		clr_lcd();
		pos_lcd(0,0);
		put_str_lcd("Place meter into");
		pos_lcd(1,0);
		put_str_lcd("your object 10sec");
		wait_avr(10000);
		clr_lcd();
	
	   unsigned int d,d1,d2;
	
  	 while(1)
	 {
       _delay_ms(200);
		
		//Send a trigger pulse
		HCSR04Trigger();
        HCSR04Trigger1();
		HCSR04Trigger2();
		
		//Measure the width of pulse
		if(flag == 1)
		{
			r = GetPulseWidth();
			flag = 2;
		} 
		else if(flag == 2)
		{
			r1 = GetPulseWidth1();
			flag = 3;
		}
		else if(flag == 3)
		{
			r2 = GetPulseWidth2();
			flag = 4;
		}
		
		//Handle Errors
		if(r==-1)
		{
			pos_lcd(1,0);
			put_str_lcd("ERROR ERROR!");
		}
		else if(r==-2)
		{
			pos_lcd(1,0);
		    //put_str_lcd("DISTANCE DIST!");
		}
		else
		{
			//Convert to cm
			d = (r/58.0); 
			d1 = (r1/58.0);
			d2 = (r2/58.0);
		}
		
		if(flag == 4)
		{
			char buffer[20];
			sprintf(buffer, "%02d %02d %02d  %02dcm", d,d1, d2,d*d1*d2);
			
			pos_lcd(0,0);
			put_str_lcd("L  W  H   VOLUME");
			
			pos_lcd(1,0);
			put_str_lcd(buffer);
		}
		
		//RESET VOLUME READER
		if(keypressed()=='A')
		{
			flag = 1;
		    clr_lcd();
		}
	 }
	}
}
