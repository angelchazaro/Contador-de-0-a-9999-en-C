/*
 * Contador con displays anodo comun.c
 *
 * Created: 03/02/2019 07:35:25 p. m.
 * Author : dx_ch
 */ 

#include <avr/io.h>
#include <util/delay.h>

#define SegOne   0x01	//Se realiza una macro para indicar el pin del puerto a ocupar.
#define SegTwo   0x02
#define SegThree 0x04
#define SegFour  0x08



int main() {
	char seg_code[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};	//Configuracion hexadecimal para los displays	//,0x88,0x83,0xc6,0xa1,0x86,0x8e};
	int cnt, num, temp,i;

	/* Configure the ports as output */
	DDRB = 0xff; // Data lines
	DDRD = 0xff; // Control signal PORTD0-PORTD3

	while (1)
	{
		for (cnt = 0x00; cnt <= 9999; cnt++) // Contador de 0 a 9999
		{
			for (i = 0; i < 50; i++)	//Controla la "velocidad" con la que hace el conteo
			{
				num = cnt;				//Se reasigna a una variable nueva
				temp = num / 1000;		//Se realiza la división para gestionar el cambio a cada display
				num = num % 1000;		//Se toma el residuo de la variable
				PORTD = SegOne;
				PORTB = seg_code[temp];
				_delay_ms(1);

				temp = num / 100;
				num = num % 100;
				PORTD = SegTwo;
				PORTB = seg_code[temp];
				_delay_ms(1);

				temp = num / 10;
				PORTD = SegThree;
				PORTB = seg_code[temp];
				_delay_ms(1);

				temp = num % 10;
				PORTD = SegFour;
				PORTB = seg_code[temp];
				_delay_ms(1);
			}
		}
	}
}