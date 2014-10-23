#include "avr.h"

void
ini_avr(void)
{
	//WDTCR = 15;
}

void wait_avr(unsigned short msec)
{
	TCCR0 = 3;
	while (msec--) {
		TCNT0 = (unsigned char)(256 - (XTAL_FRQ / 64) * 0.001);
		SET_BIT(TIFR, TOV0);
		WDR();
		while (!GET_BIT(TIFR, TOV0));
	}
	TCCR0 = 0;
}

void wait_micSec(unsigned int micsec)
{
	TCCR0 = 3;
	while (micsec--) {
		TCNT0 = (unsigned char)(255 - (XTAL_FRQ / 31250));	//amount prefilled already
		SET_BIT(TIFR, TOV0);
		WDR();
		while (!GET_BIT(TIFR, TOV0));
	}
	TCCR0 = 0;
}

/*
256 - 131 = 125 cycles per milisecond
0.125 cycles per microsec 
8 micro sec per cycle 
255 - 
256 - (8000000 / 64) * 0.001 = 131
*/
