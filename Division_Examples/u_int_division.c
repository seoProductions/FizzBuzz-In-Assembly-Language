// This program adds up all the numbers from 0 - 100
// It then prints the sum to the output

#include <stdio.h>

unsigned int Quotient = -1;
unsigned int Divisor  =  1;
unsigned int TEMP     =  0;
signed   int AC       =  0;

void Division()
{
    TEMP = AC;

    loop:
        ++Quotient;

        TEMP -= Divisor;       // subtract
        AC    = TEMP   ;
        if ( AC < 0) return;
        goto loop;             // repeat
}

int main() {

    // *** 5 / 3 *** //

    Divisor = 3;
    AC      = 50;
    Division();
    printf("%i\n", Quotient);

    Quotient = -1;      // reset quotient


    // *** 90 / 3 *** //

    Divisor = 3;
    AC      = 90;
    Division();
    printf("%i\n", Quotient);

    Quotient = -1;      // reset quotient


    // *** 71 / 5 *** //

    Divisor = 5;
    AC      = 71;
    Division();
    printf("%i\n", Quotient);

    Quotient = -1;      // reset quotient
    return 0;
}