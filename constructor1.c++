#include<iostream>
using namespace std;

class A{
   int x,y;
   public:
          A();//declaration of default constructor
          A(int m);//declaration of parameterized constructor
          A(A &obj);//declaration of copy constructor
          ~A();//destructor
};
A::A(){
    x=0;
    y=0;
    cout<<"default constructor is called"<<endl;
}
A::A(int m){
    x=m;
    y=m;
    cout<<"Prameterized constructor is invoked"<<endl;
}
A::A(A &obj){
    x=obj.x;
    y=obj.y;
    cout<<"Copy Constructor"<<endl;
}
int main()
{
    A obj1;
    A *obj2=new A(5);
    A obj3(10);
    A obj4(obj1);
    return 0;
}