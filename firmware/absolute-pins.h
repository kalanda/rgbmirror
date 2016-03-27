#ifndef __ABSOLUTE_PINS_H_
#define __ABSOLUTE_PINS_H_

// Some fixed values
#define LOW 0
#define HIGH 1

#define PB 2
#define PC 3
#define PD 4

uint8_t digitalPinToPort[] = {
	PB, //0
	PB, //1
	PB, //2
	PB, //3
	PB, //4
	PB, //5
    PC, //6
	PC, //7
	PC, //8
	PC, //9
	PC, //10
	PC, //11
	PD, //12
	PD, //13
	PD, //14
	PD, //15
	PD, //16
	PD, //17
	PD, //18
	PD //19
};

uint8_t  digitalPinToBitMask[] = {
	32, //0
	16, //1
	8, //2
	4, //3
	2, //4
	1, //5
    32, //6
	16, //7
	8, //8
	4, //9
	2, //10
	1, //11
	128, //12
	64, //13
	32, //14
	16, //15
	8, //16
	4, //17
	2, //18
	1 //19
};

// digitalWrite from Arduino modified for use absolute pins

void digitalWrite(uint8_t pin, uint8_t val){

	uint8_t bit = digitalPinToBitMask[pin];
	uint8_t port = digitalPinToPort[pin];
	volatile uint8_t *out;

	if (port == PB) {
		 out = &PORTB; 
	} else
	if (port == PC) {
		 out = &PORTC; 
	} else  
	if (port == PD) { 
	     out = &PORTD; 
	}
	if (val == LOW) *out &= ~bit;
	else *out |= bit;
    
}
#endif /* __ABSOLUTE_PINS_H_ */
