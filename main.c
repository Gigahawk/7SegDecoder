#define _CRT_SECURE_NO_WARNINGS

#define A  ((input » 3) & 1)
#define Ap  (~((input » 3) & 1))
#define B  ((input » 2) & 1)
#define Bp  (~((input » 2) & 1))
#define C  ((input » 1) & 1)
#define Cp  (~((input » 1) & 1))
#define D  ((input) & 1)
#define Dp  (~((input) & 1))

#include <stdio.h>
#include <stdlib.h>

unsigned char getDigit(unsigned char input);

int main(){
  unsigned char input;

  printf("For inputs:\n");

  printf("{");
  for (int i = 0; i < 10; i++){
    printf("%3d", i);
    if (i != 9) printf(", ");
  }
  printf("}\n\nOuptuts are:\n");


  printf("{");
  for (input = 0; input < 10; input++){
    //printf("input is %d\n", input);
    printf("%3d", getDigit(input));
    if (input != 9) printf(", ");
  }
  printf("}\n");
  system("PAUSE");
  return 0;
}

unsigned char getDigit(unsigned char input){
  unsigned char output,a,b,c,d,e,f,g;
  a = ((A | C | (B&D) | (Bp&Dp)) & 1) « 6;
  b = ((Bp | (Cp&Dp) | (C&D)) & 1) « 5;
  c = ((Cp | D | B) & 1) « 4;
  d = ((A | (Bp&Dp) | (Bp&C) | (C&Dp) | (B&Cp&D)) & 1) « 3;
  e = (((Bp&Dp) | (C&Dp)) & 1) « 2;
  f = ((A | (Cp&Dp) | (B&Cp) | (B&Dp)) & 1) « 1;
  g = (A | (Bp&C) | (C&Dp) | (B&Cp)) & 1;
 
  output = (a + b + c + d + e + f + g) « 1;
  return output;
}
