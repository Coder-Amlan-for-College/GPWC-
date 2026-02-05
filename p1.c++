#include <iostream>
using namespace std;
class Numbers{
    int nums[4];
    public:
       void input();
       void find();
       void swap(int &a,int &b,int &c);

};
void Numbers::swap(int &a,int &b,int &c){
    b=a;
    a=c;
}
void Numbers::input(){
   cout<<"Enter the numbers:"<<endl;
   for(int i=0;i<4;i++){
     cin>>nums[i];
   }
}
void Numbers::find(){
    int largest=nums[0],second_largest=nums[0];
    for(int i=1;i<4;i++){
        if(nums[i]>largest){
             swap(largest,second_largest,nums[i]);
        }
        else if(nums[i]>second_largest && nums[i]!=largest){
            swap(largest,second_largest,nums[i]);
        }
    }
    if(largest!=second_largest){
        cout<<"Largest number: "<<largest<<endl;
        cout<<"Second Largest: "<<second_largest<<endl;
    }
    else{
        cout<<"Largest number: "<<largest<<endl;
        cout<<"No Second Largest"<<endl;
    }

}
int main() {
    Numbers n;
    n.input();
    n.find();
    return 0;
}