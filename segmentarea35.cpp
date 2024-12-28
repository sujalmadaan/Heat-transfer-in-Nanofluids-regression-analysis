#include<iostream>
#include<cmath>
#include<fstream>
using namespace std;

double f(double t){
    return 0.610719+
0.0248748*t
-0.00436021*t*t
;
    } // this function is Keff as function of particle fraction at 25C

double simpson(double a,double b,int n){
    double h=(b-a)/n;
    double x=f(a)+f(b);
    for(int i=1;i<n;i++)x+=(i%2?4:2)*f(a+i*h);
    return x*h/3;
} // simpson 1/3 method

void c(){
    double a=0.2,b=2.0,h=(b-a)/10;
    fstream outt;
    outt.open("SegmentAreas35.txt",ios::out);
    for(int i=0;i<10;i++){
        double p=a+i*h,q=p+h,r=simpson(p,q,2);
      outt<<p<<" C to "<<q<<" C "<<r/h<<endl;
        // prints the areas under each segment of curve
    }
    outt.close();
}

int main(){
    c();
    return 0;
}
