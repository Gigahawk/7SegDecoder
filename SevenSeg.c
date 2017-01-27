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
	a = (((INPUT_Ap&INPUT_C) | (INPUT_B&INPUT_D) | (INPUT_A&INPUT_D)|(INPUT_Bp&INPUT_Cp&INPUT_Dp)) & 1) << 6;
	b = (((INPUT_Ap&INPUT_Bp) | (INPUT_Bp&INPUT_Cp) | (INPUT_Cp&INPUT_Dp) | (INPUT_Ap&INPUT_C&INPUT_D)) & 1) << 5;
	c = ((INPUT_Cp | INPUT_B | (INPUT_Ap&INPUT_D)) & 1) << 4;
	d = (((INPUT_A&INPUT_Cp) | (INPUT_Ap&INPUT_Bp&INPUT_Dp) | (INPUT_Ap&INPUT_C&INPUT_Dp) | (INPUT_Bp&INPUT_C&INPUT_D) |  (INPUT_B&INPUT_Cp&INPUT_D)) & 1) << 3;
	e = (((INPUT_Bp&INPUT_Cp&INPUT_Dp) | (INPUT_Ap&INPUT_C&INPUT_Dp) | (INPUT_A&INPUT_C&INPUT_D)) & 1) << 2;
	f = (((INPUT_Cp&INPUT_Dp) | (INPUT_B&INPUT_Cp) | (INPUT_B&INPUT_Dp) | (INPUT_A&INPUT_D)) & 1) << 1;
	g = (INPUT_A | (INPUT_Bp&INPUT_C) | (INPUT_C&INPUT_Dp) | (INPUT_B&INPUT_Cp)) & 1;
#ifdef DEBUG
	printf("Input is %d , output is %d,%d,%d,%d,%d,%d,%d\n", input, a, b, c, d, e, f, g);
#endif //DEBUG
	output = (a + b + c + d + e + f + g) << 1;
	return output;
}

long long longAbs(long long input){
	if (input < 0){
		input *= (-1);
	}
	return input;
}

double floatAbs(double input){
	if (input < 0){
		input *= (-1);
	}
	return input;
}

int getLength(long long i){
#ifdef DEBUG
	printf("getLength got %lld\n", i);
#endif //DEBUG
	i = longAbs(i);
	int length = 1; //minimum length of number is 1 digit
	if (i < 0)
		length++;

	while (i > 9){
		length++;
		i = i / 10;
	}
#ifdef DEBUG
	printf("length is %d\n", length);
#endif //DEBUG
	return length;
}

void writeDigit(int digit, int position){
	digit = getDigit(digit);
#ifdef DEBUG
	printf("Digit is %d, got %d, writing to position %d\n", digit, getDigit(digit), position);
#endif //DEBUG
	displayWrite(digit, position);
	return;
}

void writeDecDigit(int digit, int position){
	digit = getDigit(digit) + 1;
#ifdef DEBUG
	printf("Digit is %d, got %d, writing to position %d with decimal\n", digit, getDigit(digit), position);
#endif //DEBUG
	displayWrite(digit, position);
	return;
}

long long magnitude(int mg){
	long long out = 1;
	for (int i = 0; i < mg; i++){
		out *= 10;
	}
#ifdef DEBUG
	printf("magnitude of %d, returning %d\n", mg, out);
#endif //DEBUG
	return out;
}

void writeNumber(long double number){
	if (number > MAXDISP || number < MINDISP){
		writeLongNum((long long)number);
	}
	else if (number == (int)number){
		writeInt((int)number);
	}
	else {
		writeDouble((double)number, PRECISION);
	}
}

void writeLongNum(long long number){
	int end, magn;
	long long absNum, digit, divide;
	end = 7;
	magn = getLength(number) - 1;
	divide = magnitude(magn - 3);
	absNum = longAbs(number);
	 
	//Writes exponent out in first three spaces
	writeDigit((magn % 10), 0);
	writeDigit((magn / 10), 1);
	writeDigit(EXPSYM, 2);

	//Writes negative symbol and shifts display over
	if (number < 0){
		end = 6;
		divide *= 10;
		writeDigit(NEGSYM, 7);
	}

	//sets the head to the 4th spot
	int place = 3;


	do{
#ifndef DEBUG
		digit = ((absNum % (divide * 10)) / divide);
#else
		digit = (absNum % (divide));
		digit /= (divide/10);
#endif
		if (place == end){
			writeDecDigit(digit, place);
		}
		else {
			writeDigit(digit, place);
		}
		place++;
		divide *= 10;
	} while (place <= end);

	
	return;
}

void writeInt(int number){
	int divide, digit, absNum,magn,place;
	absNum = longAbs(number);
	divide = 1;
	place = DISPBEGIN;

	do{
		digit = ((absNum % (divide * 10)) / divide);
		writeDigit(digit,place);
		place++;
		divide *= 10;
	} while (divide < absNum);

	if (number < 0){
		writeDigit(NEGSYM, place);
		place++;
	}

	while (place <= DISPEND){
		displayWrite(0, place);
		place++;
	}
}

void writeDouble(double number){
	int place, length, declength, divide, multiply, absNum, digit;
	place = DISPEND;
	length = getLength((int)number);
	declength = DISPSIZE - length;
	divide = magnitude(length + declength - 1);
	
	if (number < 0)
	{
		writeDigit(NEGSYM, place);
		place--;
		length++;
	}

	multiply = magnitude(declength);

	absNum = floatAbs(multiply*number);

	do{
		digit = ((absNum % (divide * 10)) / divide);
		if ((DISPEND - place) == (length-1)){
			writeDecDigit(digit, place);
		}
		else{
			writeDigit(digit, place);
		}

		place--;
		divide /= 10;
	} while (divide > 0 && place >= 0);

}

#undef DEBUG