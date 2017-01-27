#ifndef SEVENSEG_H
#define SEVENSEG_H

#define DEBUG

#define PRECISION 3

#define MAXDISP 99999999
#define MINDISP -9999999

#define MAXDIV 1000000000000000000
#define MINDIV -1000000000000000000

#define DISPBEGIN 0 
#define DISPEND 7
#define DISPSIZE 8

#define NEGSYM 10
#define EXPSYM 11


//Simulates a decoder for a 7 segment display using K-Maps
//Use 10 for '-' and 11 for 'E'
unsigned char getDigit(unsigned char input);

int getLength(long long i);

//Writes a digit in the specified position
void writeDigit(int digit, int position);

//Writes a digit in the specified position with decimal point
void writeDecDigit(int digit, int position);

//General function for writing numbers to display, will 
//automatically call the right function
//Note: Calls to writeDouble() will have a default precision of 3 decimal places
void writeNumber(long double number);

void writeInt(int number);
void writeLongNum(long long number);
void writeDouble(double number, int precision);

//Trying to not use math.h
//Also needs to accomodate large numbers
long long longAbs(long long input);

#endif //SEVENSEG_H