#include "sensor.h"

void HCSR04InitDist()
{
	DDRC|=(1<<PC6);
}

void HCSR04Init()
{
	DDRC|=(1<<PC0);
}

void HCSR04Init1()
{
	DDRC|=(1<<PC2);
}

void HCSR04Init2()
{
	DDRC|=(1<<PC4);
}


void HCSR04TriggerDist()
{
	//Send a 10uS pulse on trigger line

	PORTC|=(1<<PC6); //high

	_delay_us(215); //wait 15uS

	PORTC&=~(1<<PC6); //low
}

void HCSR04Trigger()
{
	//Send a 10uS pulse on trigger line

	PORTC|=(1<<PC0); //high

	_delay_us(215); //wait 15uS

	PORTC&=~(1<<PC0); //low
}

void HCSR04Trigger1()
{
	PORTC|=(1<<PC2); //high

	_delay_us(215); //wait 15uS

	PORTC&=~(1<<PC2); //low
}

void HCSR04Trigger2()
{
	//Send a 10uS pulse on trigger line

	PORTC|=(1<<PC4); //high

	_delay_us(215); //wait 15uS

	PORTC&=~(1<<PC4); //low
}

uint16_t GetPulseWidthDist()
{
	uint32_t i,result;

	for(i=0;i<100000;i++)
	{
		if(!(PINC & (1<<PC7)))
		continue;
		else
		break;
	}

	if(i==599999)
	return -1;
	
	TCCR1A=0X00;
	TCCR1B=(1<<CS11);
	TCNT1=0x00;

	for(i=0;i<100000;i++)
	{
		if(PINC & (1<<PC7))
		{
			if(TCNT1 > 10000)
			break;
			else
			continue;
		}
		else
		break;
	}

	if(i == 599999)
	return -2;

	result=TCNT1;

	TCCR1B=0x00;

	if(result > 10000)
	return -2;
	else
	return (result);
}


uint16_t GetPulseWidth()
{
	uint32_t i,result;

	for(i=0;i<100000;i++)
	{
		if(!(PINC & (1<<PC1)))
		continue;
		else
		break;
	}

	if(i==599999)
	return -1;
	
	TCCR1A=0X00;
	TCCR1B=(1<<CS11);
	TCNT1=0x00;

	for(i=0;i<100000;i++)
	{
		if(PINC & (1<<PC1))
		{
			if(TCNT1 > 10000)
			break;
			else
			continue;
		}
		else
		break;
	}

	if(i == 599999)
	return -2;

	result=TCNT1;

	TCCR1B=0x00;

	if(result > 10000)
	return -2;
	else
	return (result);
}

uint16_t GetPulseWidth1()
{
	uint32_t i,result;

	for(i=0;i<100000;i++)
	{
		if(!(PINC & (1<<PC3)))
		continue;
		else
		break;
	}

	if(i==599999)
	return -1;
	
	TCCR1A=0X00;
	TCCR1B=(1<<CS11);
	TCNT1=0x00;

	for(i=0;i<100000;i++)
	{
		if(PINC & (1<<PC3))
		{
			if(TCNT1 > 10000)
			break;
			else
			continue;
		}
		else
		break;
	}

	if(i == 599999)
	return -2;

	result=TCNT1;

	TCCR1B=0x00;

	if(result > 10000)
	return -2;
	else
	return (result);
}

uint16_t GetPulseWidth2()
{
	uint32_t i,result;

	for(i=0;i<100000;i++)
	{
		if(!(PINC & (1<<PC5)))
		continue;
		else
		break;
	}

	if(i==599999)
	return -1;
	
	TCCR1A=0X00;
	TCCR1B=(1<<CS11);
	TCNT1=0x00;

	for(i=0;i<100000;i++)
	{
		if(PINC & (1<<PC5))
		{
			if(TCNT1 > 10000)
			break;
			else
			continue;
		}
		else
		break;
	}

	if(i == 599999)
	return -2;

	result=TCNT1;

	TCCR1B=0x00;

	if(result > 10000)
	return -2;
	else
	return (result);
}
