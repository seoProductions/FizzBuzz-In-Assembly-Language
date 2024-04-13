        //    Yup! Fizzbuzz in Assembly!    //
        //         Translated into C!       //
        // COSC-2425 Computer Architecture  //
        //          Eliseo Duque            //
        //         April 13, 2024           //
#include <stdio.h>

    // ********************* //
    // * Global Variables  * //
    // ********************* //

unsigned int N          = 1 ;     // for counting
unsigned int N_MAX      = 99;

unsigned int Remainder  =  0;     // store remainder
unsigned int Divisor    =  1;     // store divisor
signed   int Quotient   = -1;     // store quotient

signed   int AC       =  0;     // Accumulator
signed   int Temp_N   =  0;     // Temporary N value (for Division())
signed   int TEMP     =  0;     // Temporary N value (for print_N() )

unsigned int divisible_flag = 0;

    // ************************ //
    // * Function Prototypes  * //
    // ************************ //

void Modular_Division();
void Division();
void print_N();
void print_Fizz();
void print_Buzz();

        // ********* //
        // * Main  * //
        // ********* //

int main() {
    main_loop:
        Divisor = 3;            // N mod 3
        AC      = N;
        Modular_Division();

        // check if divisible
        if (Remainder == 0)
            print_Fizz();

        Divisor = 5;            // N mod 5
        AC      = N;
        Modular_Division();

        // check if divisible
        if (Remainder == 0)
            print_Fizz();

        // If neither print_fizz nor print_buzz invoked, then we print_N
        if (!divisible_flag)
            print_N();

        putchar('\n');      // new line

        //check if we need to repeat main() loop
        if (N > N_MAX) return 0;

        ++N;                    // increment
        divisible_flag = 0;     // clear flag
        goto main_loop;         // and repeat
}

    // ***************************** //
    // * Function Implementations  * //
    // ***************************** //

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

void print_N()
{
    Temp_N = N;     // dont want to override our current N

    loop:
    /* if N is one digit long, print and return */
    AC     = Temp_N;
    AC    -= 10;

    if ( AC < 0 )
    {
        putchar(Temp_N + 48);   // 48 is UNICODE offset
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
        putchar(Quotient + 48); // 48 is UNICODE offset

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
        /* max integer cant exceed 32,767 (5 digits) */

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

/* No support for C-strings yet */

void print_Fizz()
{
    putchar('F');
    putchar('I');
    putchar('Z');
    putchar('Z');

    divisible_flag = 1;  // set to not print N
}

void print_Buzz()
{
    putchar('B');
    putchar('U');
    putchar('Z');
    putchar('Z');

    divisible_flag = 1;  // set to not print N
}