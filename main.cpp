#include <stdio.h>
#include <string.h>

#include <stdlib.h>
#include <time.h>

int is_num(int c)
{
    if (c >= '0' && c <= '9') {
        return 1;
    }
    return 0;
}

int state = 0;

int main(void)
{
    /* state machine */

    /* -1 error program execution */
    /* 0 normal program execution */

    /* 1 start process input character */
    /* 2 3 4 process input of current integer characters */
    /* 5 end process input of currnet integer characters */

    int input_state = 1; /* default input state */

    int c; /* value to hold current input character */
    int i; /* index of input character position */
    int p; /* padding to fill with 0s */
    int sign; /* integer sign */

    i = 0;
    c = 0;

    while (input_state > 0) {
        switch(input_state) {
            case 1:
                p = 0;
                sign = 0;
                i++; /* advance input by one char */
                c = getchar();
                if (c == '\0') {
                    input_state = 0;
                    break;
                }
                if (c == ' ' || c == '\t' || c == '\r') { /* skip trailing spaces */
                    printf("%c", c); /* print input delimiters */
                    input_state = 1;
                    break;
                }
                if (c == '+' || c == '-') {
                    p = 0;
                    input_state = 2;
                    break;
                }
                p = 0;
                input_state = 3;
                break;
            case 2: /* signed integer */
                if (c == '-') {
                    sign = 1;
                } else {
                    sign = 0;
                }
                i++; /* advance input by one char */
                c = getchar();
                if (c == '\0') {
                    input_state = -1;
                    break;
                }
                if (!is_num(c)) {
                    input_state = -1;  /* stop execution if not number */
                    break;
                }
                input_state = 3;
                break;
            case 3: /*unsigned integer */
                if (c == '0') {
                    printf("%c", c);
                } else {
                    if (sign == 1) {
                        printf("-%c", c);
                    } else {
                        printf("%c", c);
                    }
                }
                input_state = 4;
                break;
            case 4:
                i++; /* advance input by one char */
                c = getchar();
                if (c == '\0') {
                    input_state = 5;
                    break;
                }
                if (c == ' ' || c == '\t' || c == '\r') { /* skip trailing spaces */
                    //printf("%c", c); /* print input delimiters */
                    input_state = 5;
                    break;
                }
                if (is_num(c)) {
                    p++;
                    printf("%c", c);
                    input_state = 4;
                    break;
                }
                input_state = 5;
                break;
            case 5:
                /* start padding of characters */
                if (c != '0' && p > 0) {
                  while (p++ < 9) { /* advance padding by one char */
                    printf("%c", '0');
                  }
                }
                printf("%c", c);
                p = 0; /* reset padding of current integer */
                sign = 0;
                input_state = 1; /* start process next integer */
                break;
        }
    }
    printf("\n");
    /* assertions */
    if (input_state == -1) {
      printf("error at position %d", i);
    }
    return input_state;
}