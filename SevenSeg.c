#include <DAQlib.h>
#include "SevenSeg.h"

//INPUT_Ap = 'A prime' = NOT(A) = ~INPUT_A
#define INPUT_A		((input >> 3) & 1)
#define INPUT_Ap	(~((input >> 3) & 1))
#define INPUT_B		((input >> 2) & 1)
#define INPUT_Bp	(~((input >> 2) & 1))
#define INPUT_C		((input >> 1) & 1)
#define INPUT_Cp	(~((input >> 1) & 1))
#define INPUT_D		((input) & 1)
#define INPUT_Dp	(~((input) & 1))


unsigned char getDigit(unsigned char input){
	unsigned char output,a,b,c,d,e,f,g;
	a = ((INPUT_A | INPUT_C | (INPUT_B&INPUT_D) | (INPUT_Bp&INPUT_Dp)) & 1) << 6;
	b = ((INPUT_Bp | (INPUT_Cp&INPUT_Dp) | (INPUT_C&INPUT_D)) & 1) << 5;
	c = ((INPUT_Cp | INPUT_D | INPUT_B) & 1) << 4;
	d = ((INPUT_A | (INPUT_Bp&INPUT_Dp) | (INPUT_Bp&INPUT_C) | (INPUT_C&INPUT_Dp) | (INPUT_B&INPUT_Cp&INPUT_D)) & 1) << 3;
	e = (((INPUT_Bp&INPUT_Dp) | (INPUT_C&INPUT_Dp)) & 1) << 2;
	f = ((INPUT_A | (INPUT_Cp&INPUT_Dp) | (INPUT_B&INPUT_Cp) | (INPUT_B&INPUT_Dp)) & 1) << 1;
	g = (INPUT_A | (INPUT_Bp&INPUT_C) | (INPUT_C&INPUT_Dp) | (INPUT_B&INPUT_Cp)) & 1;
#ifdef DEBUG
	printf("Output is %d,%d,%d,%d,%d,%d,%d\n", a, b, c, d, e, f, g);
#endif //DEBUG
	output = (a + b + c + d + e + f + g) << 1;
	return output;
}

void writeDigit(int digit, int position){
#ifdef DEBUG
	printf("Digit is %d, got %d, writing to position %d\n", digit, getDigit(digit), position);
#endif //DEBUG
	displayWrite(getDigit(digit), position);
	return;
}

void writeNumber(int number){
	clearDisplay();
	int work;
	int i = 0;
	int divide = 1;
	do{
		work = ((number % (divide * 10)) / divide);
#ifdef DEBUG
		printf("Writing work %d to position %d\n", work, i);
#endif //DEBUG
		writeDigit(work, i);
		i++;
		divide *= 10;
	} while (i < 8 && work < number);
}

void clearDisplay(){
	for (int i = 0; i < 8; i++)
		displayWrite(0, i);
	return;
}

#undef DEBUG
