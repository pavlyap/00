#include <stdio.h>
#include <math.h>

int main(void) {

    double a,v0,h,g=9.81;

    scanf("%lf%lf",&a,&v0);

    double arad=a*(M_PI / 180.0);
    h=(v0*v0*sin(arad)*sin(arad)/(2*g));
    
    printf("Максимальная высота подъема %lf м\n", h);
    
    return 0;
}