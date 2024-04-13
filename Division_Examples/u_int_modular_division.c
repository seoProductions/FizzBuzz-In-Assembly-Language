// This program implements Modular Division as repeated subrtraction
// It closely resembles assembly language code, with far greater readability
// Modern High level languages are soo powerful we can
// resolve this code down to 1 single line

//     printf("%i\n", 5 % 3);

#include <stdio.h>

unsigned int Remainder = 0;
unsigned int Divisor  =  1;
signed   int AC       =  0;

void Modular_Division()
{   // invisible return adress here

    loop:
        Remainder = AC;

        AC   -= Divisor;       // subtract
        if ( AC < 0 ) return;
        goto loop;             // repeat
}

int main() {
    // * EXAMPLE 1  * //
    // *** 50 % 3 *** //

    Divisor = 3;
    AC      = 50;
    Modular_Division();
    printf("%i\n", Remainder);

    // * EXAMPLE 2  * //
    // *** 90 % 3 *** //

    Divisor = 3;
    AC      = 90;
    Modular_Division();
    printf("%i\n", Remainder);

    // * EXAMPLE 3  * //
    // *** 71 % 5 *** //

    Divisor = 5;
    AC      = 71;
    Modular_Division();
    printf("%i\n", Remainder);

    return 0;
}