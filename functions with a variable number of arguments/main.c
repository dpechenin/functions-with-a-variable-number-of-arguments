#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#define UNSIGNED_OVERFLOW -4

unsigned summ(unsigned char num, unsigned first, ...) {
    unsigned sum = 0;
    unsigned testsum = 0;
    unsigned *p = &first;
    while (num--) {
        testsum += *p;
        if (testsum >= sum) {
            sum = testsum;
        }
        else {
            exit(UNSIGNED_OVERFLOW);
        }
        p++;
    }
    return sum;
}

unsigned summ2(unsigned char num, ...) {
    unsigned sum = 0;
    unsigned testsum = 0;
    //Для увеличения скорости работы адреса кратны 4 байтам,
    //даже если реальный размер переменной меньше
    unsigned *p = (unsigned*)(&num+4);
    while (num--) {
        testsum += *p;
        if (testsum >= sum) {
            sum = testsum;
        }
        else {
            exit(UNSIGNED_OVERFLOW);
        }
        p++;
    }
    return sum;
}

unsigned summ3(unsigned first, ...) {
    unsigned sum = 0;
    unsigned testsum = 0;
    unsigned *p = &first;
    while (*p) {
        testsum += *p;
        if (testsum >= sum) {
            sum = testsum;
        }
        else {
            exit(UNSIGNED_OVERFLOW);
        }
        p++;
    }
    return sum;
}

int summ4(unsigned num, ...) {
    va_list args;
    int sum = 0;
    va_start(args, num);
    while (num--) {
        sum += va_arg(args, int);
    }
    va_end(args);
    return sum;
}

int summ5(int n, ...) {
    int *p = &n;
    int s = 0;
    while (n--) {
        s += *(++p);
    }
    return s;
}

int main(int argc, const char * argv[]) {
    int sum = summ(5, 1u, 2u, 3u, 4u, 5u);
    printf("summ = %d\n", sum);
    
    sum = summ2(5, 1u, 2u, 3u, 4u, 5u);
    printf("summ = %u\n", sum);
    
    sum = summ3(1u, 2u, 3u, 4u, 5u, 0);
    printf("summ = %u\n", sum);
    
    int sum2 = summ4(5, 1, 2, 3, 4, 5);
    printf("summ = %d\n", sum2);
    
    sum2 = summ5(5, 1, 2, 3, 4, 5);
    printf("summ = %d\n", sum);
    return 0;
}
