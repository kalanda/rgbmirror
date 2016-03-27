#ifndef __RGB_CONTROLLER_H_
#define __RGB_CONTROLLER_H_

#include "absolute-pins.h"
#include <util/delay.h>

// Color table 3 bits (rgb)
#define BLACK  0x00
#define GREEN  0x02 
#define BLUE   0x04
#define CYAN   0x06
#define VIOLET 0x05
#define WHITE  0x07
#define YELLOW 0x03
#define RED    0x01

// Absolute pins for each color channel
#define R_PIN  12
#define G_PIN  13
#define B_PIN  14

uint8_t speed = 10;

// Rainbow ordered palette of 3 bits of detph
uint8_t palette[8] = { BLACK,GREEN,BLUE,CYAN,VIOLET,RED,YELLOW,WHITE };

// Configuration to set relation between absolute pins of board an absolute columns (cols)
uint8_t cols[16] = {
9,  // col 0
10, // col 1
11, // col 2
0,  // col 3
1,  // col 4
2,  // col 5
3,  // col 6
4,  // col 7
8,  // col 8
7,  // col 9
6,  // col 10
19, // col 11
18, // col 12
17, // col 13
16, // col 14
15  // col 15
};

// Display buffer
uint8_t display_buffer[16];

void RGBController_init(){
  // setup all pins to outputs escept PORTB.0 for the switch
  DDRB  = 0xfe;
  DDRC  = 0xff;
  DDRD  = 0xff;
	
  // set all ports to low
  PORTB  =0x01;
  PORTC = 0x00;
  PORTD = 0x00;
}

// Set a pixel by the absolute pin number (value can be HIGH or LOW)
void RGBController_setPixel(uint8_t col, uint8_t color ){
		digitalWrite(R_PIN, !(color>>2 & 1));
		digitalWrite(G_PIN, !(color>>1 & 1));
		digitalWrite(B_PIN, !(color & 1));
		digitalWrite(cols[col],HIGH);
		_delay_ms(1);
		digitalWrite(cols[col],LOW);	
		digitalWrite(R_PIN,HIGH);
		digitalWrite(G_PIN,HIGH);
		digitalWrite(B_PIN,HIGH);
}

void RGBController_paint(){
uint8_t col,i;
  for (i=0;i<speed;i++){
	for(col=0;col<16;col++){
		RGBController_setPixel(col, display_buffer[col]);
	}	
  }
}
#endif /* __RGB_CONTROLLER_H_ */
