#include<iostream>
using namespace std;
int main(){
  char s1[100];
  cin>>s1;//it will work for a single word
  cin.getline(s1,100);//any string including space

  char *s = new char[100];
  cin>>s;
  cin.getline(s,100);
}