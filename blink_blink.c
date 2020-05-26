//Created: September 2018 by Fatin Sarker


#include "gpiolib_addr.h"
#include "gpiolib_reg.h"
#include "gpiolib_reg.c"

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <time.h>

int main(void)
{
	//Initialize the GPIO pins and check if initialize correctly
  
	GPIO_Handle gpio;
	gpio = gpiolib_init_gpio();
	if(gpio == NULL)
	{
		perror("Could not initialize GPIO");
	}
	
	//Set pin 4 as an output pin, same as what was done in the blink program
  
	uint32_t sel_reg = gpiolib_read_reg(gpio, GPFSEL(1));
	sel_reg |= 1  << 21;
	gpiolib_write_reg(gpio, GPFSEL(1), sel_reg);
	    
		/*
		  Declare a variable called level_reg of 32-bit size and 
		  assigned the value of the level register
		*/ 	
    
	sel_reg = gpiolib_read_reg(gpio, GPFSEL(1));
	sel_reg = 1 << 21;
	gpiolib_write_reg(gpio,GPFSEL(1));
  
	  /*
    Declare a variable called pin_state and assign the value of bit 4
    from the level_reg
    */ 
    
	int pin_state = level_reg & (1 << 4);
	int i = 0;
	int t = 0;
	while(1)
	{  
    //Turn the LED on
    
        gpiolib_write_reg(gpio, GPSET(0), 1 << 17);
		uint32_t level_reg = gpiolib_read_reg(gpio, GPLEV(0));
    
	//Button not pressed
  
	    while(pin_state) //if the pin is true
		{
			level_reg = gpiolib_read_reg(gpio, GPLEV(0));
			pin_state = level_reg & (1 << 4);
		}
		usleep(1000000);
	//Button is pressed	
		while (!pin_state) //if the pin is false
		{
			level_reg = gpiolib_read_reg (gpio, GPLEV(0));
			pin_state = level_reg & (1 << 4);
		}
		gpiolib_write_reg (gpio, GPCLR(0), 1 << 17);
		pin_state = 0;
		int p = 0;
		i = 0;
		t = 0;
		while (t<10000000)
		{
			usleep(1000);
			level_reg = gpiolib_read_reg(gpio, GPLEV (0));
			pin_state = level_reg & (1 << 4); 
			t+=1000;
			if (pin_state && !p)
			{
				i++;
			}
			p=pin_state;
		}
		
			int counter = 0; 


	//Loop to blink the LED i times for the button push
  
	while(counter < i)
	{
		//Turn on the LED by changing the 17th bit in the set register to 1
		gpiolib_write_reg(gpio, GPSET(0), 1 << 17);

		//Pause the program for 1000000 microseconds, i.e. 1 second
		usleep(1000000);

		//Turn the LED off by setting the 17th bit in the clear register to 1
		gpiolib_write_reg(gpio, GPCLR(0), 1 << 17);

		//Pause the program for 1000000 microseconds, i.e. 1 second
		usleep(1000000);

		counter ++;
		}
		usleep (5000000);
		
	}
