// This program demonstrates branching in the C language.
// First example is your typical if statement
// Second example uses skips

#include <stdio.h>

int main() {

    int AC = 0;
    scanf("%d", &AC);                   // get user input

    if (AC == 0)  goto print_zero;      // normal branching
    if (!(AC < 0)) goto print_pos;      // skipping translates to this
    else            goto print_neg;     // default


    print_zero:
        printf("%i", 0);
        return 0;

    print_pos:
        printf("%i", 1);
        return 0;

    print_neg:
        printf("%i", -1);
        return 0;

    return 0;
}