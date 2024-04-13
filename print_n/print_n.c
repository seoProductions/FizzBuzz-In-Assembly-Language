// Print each digit of the value of N ( as a char & using ASCII table )
// Combination of both modular and regular division
// Very tedious

#include <stdio.h>

unsigned int N;                 // for counting
unsigned int Quotient = -1;     // store quotient
unsigned int Remainder = 0;     // store remainder
unsigned int Divisor  =  1;     // store divisor
signed   int AC       =  0;     // Accumulator
signed   int Temp_N   =  0;     // Temporary N value
signed   int TEMP     =  0;     // Temporary N value



void Modular_Division()
{   // invisible return address here

    loop:
        Remainder = AC;

        AC   -= Divisor;       // subtract
        if ( AC < 0 ) return;
        goto loop;             // repeat
}

void Division()
{   // invisible return address here

    TEMP = AC;

    loop:
        ++Quotient;

        TEMP -= Divisor;       // subtract
        AC    = TEMP   ;
        if ( AC < 0 ) return;
        goto loop;             // repeat
}

void print_N() {
    Temp_N = N;     // dont want to override our current N

    loop:
        /* if N is one digit long, print and return */
        AC     = Temp_N;
        AC    -= 10;

        if ( AC < 0 )
        {
            putchar(Temp_N + 48);  // 48 is UNICODE offset
            return;
        }

        /* if N is two digits long, print 2nd digit and remove it */
        AC     = Temp_N;
        AC    -= 100;

        if ( AC < 0 )
        {
            // isolate 2nd digit using division & print it

            Divisor = 10;
            AC      = Temp_N;
            Division();
            putchar(Quotient + 48);
            Quotient = -1;

            // eliminate 2nd digit using modular division

            Divisor = 10;
            AC      = Temp_N;
            Modular_Division();
            Temp_N = Remainder;     // now 1 digit long

            goto loop;
        }

        /* if N is three digits long, print 3rd digit and remove it */
        AC     = Temp_N;
        AC    -= 1000;

        if ( AC < 0 )
        {

            // isolate 3rd digit using division & print it

            Divisor = 100;
            AC      = Temp_N;
            Division();
            putchar(Quotient + 48);

            Quotient = -1;

            // eliminate 3rd digit using modular division

            Divisor = 100;
            AC      = Temp_N;
            Modular_Division();
            Temp_N = Remainder;     // now 2 digits long

            goto loop;
        }

        /* if N is four digits long, print 4th digit and remove it */
        AC     = Temp_N;
        AC    -= 10000;

        if ( AC < 0 )
        {
            // isolate 4th digit using division & print it

            Divisor = 1000;
            AC      = Temp_N;
            Division();
            putchar(Quotient + 48);

            Quotient = -1;

            // eliminate 4th digit using modular division

            Divisor = 1000;
            AC      = Temp_N;
            Modular_Division();
            Temp_N = Remainder;     // now 3 digits long

            goto loop;
        }
        else
        {
            /* On computers with binary signed 2's compliment */
            /* max integer cant exeed 32,767 (5 digits) */

            // ****** DEFAULT CASE ******
            // isolate 5th digit using division & print it

            Divisor = 10000;
            AC      = Temp_N;
            Division();
            putchar(Quotient + 48);

            Quotient = -1;

            // eliminate 5th digit using modular division

            Divisor = 10000;
            AC      = Temp_N;
            Modular_Division();
            Temp_N = Remainder;     // now 4 digits long

            goto loop;
        }
}
//#define DEBUG

int main() {

    // print from 0 -> 99
    for (N = 0; N < 99; N++)
        print_N();


    return 0;
}