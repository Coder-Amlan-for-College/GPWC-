#include<iostream>
using namespace std;
const int SIZE=3;
class vector{
    int v[SIZE];
    public:
       vector();
       vector(int *x);
       friend vector operator*(int a,vector &b);
       friend vector operator*(vector &b,int a);
       friend istream & operator>>(istream &,vector &);
       friend ostream & operator<<(ostream &,vector &);
       
};
vector::vector(){
    for(int i=0;i<SIZE;i++){
      v[i]=0;
    }
}
vector::vector(int *x){
    for(int i=0;i<SIZE;i++){
        v[i]=x[i];
    }
}
vector operator*(int a,vector &b){
   vector c;
   for(int i=0;i<SIZE;i++){
       c.v[i]=a*b.v[i];
   }
   return c;
}
vector operator*(vector &b,int a){
   vector c;
   for(int i=0;i<SIZE;i++){
       c.v[i]=b.v[i]*a;
   }
   return c;
}
istream& operator>>(istream &din,vector &b){
    for(int i=0;i<SIZE;i++){
        din>>b.v[i];
    }
    return din;
}
ostream& operator<<(ostream &dout,vector &b){
    dout<<"("<<b.v[0];
    for(int i=1;i<SIZE;i++){
        dout<<", "<<b.v[i];
    }
    dout<<")";
    return dout;
}
int x[]={2,4,6};
int main(){
  vector a;//default constructor called
  vector b=x;//eq to vector b(x)-->parameterized constructor;
  int i=2;
  vector p;
  p=i*b;//friend 1 called

  vector q;
  q=b*i;//friend 2 called

  cout<<"Input for a 3d vector: ";
  cin>>a;

  cout<<"Vector a:"<<endl;
  cout<<a<<endl;

  cout<<"\nVector p:"<<endl;
  cout<<p<<endl;

  cout<<"\nVector q:"<<endl;
  cout<<q<<endl;

  return 0;
}