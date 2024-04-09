// This program adds up all the numbers from 0 - 100
// It then prints the sum to the output

#include <stdio.h>

int main() {

    unsigned int SUM = 0;
    unsigned int i   = 10;

    for (; i > 0; i--)
    {
        SUM += i;
    }

    printf("%u", SUM);

    return 0;
}