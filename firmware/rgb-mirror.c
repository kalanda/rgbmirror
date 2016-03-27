// Library includes
#include <stdlib.h> 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "rgb-controller.h"

uint8_t rainbow[16] = { 
	GREEN,CYAN,BLUE,BLUE,VIOLET,RED,RED,YELLOW,YELLOW,RED, RED, VIOLET, BLUE, BLUE,CYAN,GREEN
};

uint8_t time;
uint8_t frame;
uint8_t run_mode;
uint8_t button_release;

void show_clear(){
  uint8_t col;
  for (col=0;col<16;col++) {
	display_buffer[col] = 0;
  }
}
void show_rainbow(){
  uint8_t col;
  for (col=0;col<16;col++) {
	display_buffer[col] = rainbow[col];
  }
}
void show_rainbow_offset(){
  uint8_t col;
  if (frame>=16) frame = 0;
  for (col=0;col<16;col++) {
  	if (col+frame<16) display_buffer[col] = rainbow[col+frame];
	else display_buffer[col] = rainbow[col+frame-16];	
  }
}

// Here is the main 
int main (void)
{ 
	RGBController_init();
  
  	run_mode = 0;
	frame = 0;
	time = 0;
    button_release = 0;
	for(;;) {
	
		//  run_mode: detect button push
		if(button_release==0 && bit_is_clear(PINB,PB0) ) {  
		    button_release = 1;
			run_mode++;
			_delay_us(10);
	    } else if (!bit_is_clear(PINB,PB0)) button_release = 0; 

	    // handle actions within a state
	    switch(run_mode) { 
		    case 0:
			    speed = 5;
			    show_rainbow();
	            break;
	        case 1:
			    speed = 30;
			    show_rainbow_offset();
	            break;
			case 2:
			    speed = 20;
			    show_rainbow_offset();
	            break;
			case 3:
			    speed = 10;
			    show_rainbow_offset();
	            break;
            case 4:
			    speed = 5;
			    show_rainbow_offset();
	            break;
            case 5:
			    show_clear();
	            break;
	    }
		
	    RGBController_paint();
		frame++;
		//if (++time > 16) { run_mode++; time = 0;}
		if (run_mode > 5) run_mode = 0;
	}
}
