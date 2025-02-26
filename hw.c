#include <stdio.h>
//#define _USE_MATH_DEFINES
//#define M_PI 3.14159265
//#include <math.h>

int main(void) {

    double m, h;

    scanf("%lf%lf", &m, &h);

    printf("%lf\n", m/(h*h));
    
    return 0;
}