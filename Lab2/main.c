/*  This program demonstrates the size (in bytes) of an integer,
 *  overflow and underflow in float and integer types respectively, and a Celsius to Fahrenheit conversion.
 *
 *  Author: Shygaan Khalili
 *  Date: 2025-01-07
 *
 *  Capilano University
 *  COMP 120 01
 */

#include <stdio.h>

int main(void) {

    printf("%i\n", (int) sizeof(int));

    float overFloat = 3.402823e+38f;
    printf("%f + 1 = %f\n", overFloat, overFloat * 2.0f);

    int underInt = -2147483648;
    printf("%i - 1 = %i\n", underInt, underInt - 1);


    float floatCastInt = 1.5f;
    printf("(int) %ff = %i\n", floatCastInt, (int) floatCastInt);


    double celsius; // Temperature in Celsius

    printf( "Please enter the temperature in celsius: ");
    scanf("%lf", &celsius);

    double fahrenheit = ( celsius / 5 ) * 9 + 32.0; // init and compute
    printf("\nThe temperature in fahrenheit is %lf.\n",fahrenheit);

    return 0;

}