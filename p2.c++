#include <iostream>
using namespace std;
class Rectangle{
   double l,b;
   public:
       void input();
       double perimeter();
       double area();
       void output(double &a,double &p);
};
void Rectangle::input(){
    cout<<"Enter the length:"<<endl;
    cin>>l;
    cout<<"Enter the breadth:"<<endl;
    cin>>b;
}
double Rectangle::area(){
    return l*b;
}
double Rectangle::perimeter(){
     return 2*(l+b);
}
void Rectangle::output(double &a,double &b){
   cout<<"Area: "<<b<<endl;
   cout<<"Perimeter: "<<a<<endl;
}
int main() {
    Rectangle r;
    r.input();
    double perm = r.perimeter();
    double area = r.area();
    r.output(perm,area);
    return 0;
}