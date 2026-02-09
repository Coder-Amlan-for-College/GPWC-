#include <iostream>
using namespace std;

class Matrix{
    int rows=3;
    int cols=3;
    int (*mat)[3]=new int[3][3];
    public:
       void input();
       void display();
       void add(Matrix &m1,Matrix &m2);
       void mul(Matrix &m1,Matrix &m2);
       void transpose();
       void equality(Matrix &m1,Matrix &m2);
       void diagonalMatrix();
       void unitMatrix();
};
void Matrix::input(){
  cout<<"Enter a 3*3 matrix"<<endl;
  for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
        cin>>mat[i][j];
    }
  }
}
void Matrix::display(){
  cout<<"Matrix:"<<endl;
  for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
        cout<<mat[i][j]<<" ";
    }
    cout<<endl;
  }
}
void Matrix::add(Matrix &m1,Matrix &m2){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            mat[i][j]=m1.mat[i][j]+m2.mat[i][j];
        }
    }
}
void Matrix::mul(Matrix &m1, Matrix &m2) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            mat[i][j] = 0; 
            for (int k = 0; k < 3; k++) {
                mat[i][j] += m1.mat[i][k] * m2.mat[k][j];
            }
        }
    }
}
void Matrix::transpose(){
   cout<<"Transpose"<<endl;
   for(int i=0;i<3;i++){
     for(int j=0;j<3;j++){
        cout<<mat[j][i]<<" ";
     }
     cout<<endl;
   }
}
void Matrix::equality(Matrix &m1,Matrix &m2){
    for(int i=0;i<3;i++){
     for(int j=0;j<3;j++){
       if(m1.mat[i][j]!=m2.mat[i][j]){
          cout<<"Unequal Matrices";
          return;
       }
     }
   }
   cout<<"Equal Matrices"<<endl;
}
void Matrix::diagonalMatrix(){
   for(int i=0;i<3;i++){
     for(int j=0;j<3;j++){
          if(i!=j && mat[i][j]!=0){
              cout<<"Not a Diagonal Matrix"<<endl;
              return;
          }
     }
   }
   cout<<"Diagonal Matrix"<<endl;
}
void Matrix::unitMatrix(){
   for(int i=0;i<3;i++){
     for(int j=0;j<3;j++){
          if(i!=j && mat[i][j]!=0){
              cout<<"Not a Unit Matrix"<<endl;
              return;
          }
          else if(i==j && mat[i][j]!=1){
              cout<<"Not a Unit Matrix"<<endl;
              return;
          }
     }
   }
   cout<<"Unit Matrix"<<endl;
}

int main()
{
    
    return 0;
}