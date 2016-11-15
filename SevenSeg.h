#ifndef SEVENSEG_H
#define SEVENSEG_H

//#define DEBUG

//Simulates a decoder for a 7 segment display using K-Maps
unsigned char getDigit(unsigned char input);

//Writes a digit in the specified position
void writeDigit(int digit, int position);

//Writes a number to the display

void writeNumber(int number);

//Clears the display
void clearDisplay();

#endif //SEVENSEG_H
