/*  This program calculates the yearly cost of gas based on the
 *  distance (km) travelled per week, the current price of gas ($/L),
 *  and the mileage of the vehicle.
 *
 *  Author: Shygaan Khalili
 *  Date: 2025-01-07
 *
 *  Capilano University
 *  COMP 120 01
 */

#include <stdio.h>

#define WEEKS 52

int main(void) {
    float kmPerWeek, pricePerLitre, kmPerLiter;

    printf("Distance (km) driven per week:\n");
    scanf("%f", &kmPerWeek);

    printf("Gas $/L:\n");
    scanf("%f", &pricePerLitre);

    printf("Distance (km) travelled per liter:\n");
    scanf("%f", &kmPerLiter);

    printf("$%.2f\n", (kmPerWeek * WEEKS) / kmPerLiter * pricePerLitre);

    return 0;
}
