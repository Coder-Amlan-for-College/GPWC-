#include<iostream>
using namespace std;
class Matrix{
   int mat[10][10],r,c;
   public:
         void set_matrix();
         Matrix operator++();
         Matrix operator--();
         void display();
};
void Matrix::set_matrix(){
    cout<<"Enter the rows"<<endl;
    cin>>r;
    cout<<"Enter the cols"<<endl;
    cin>>c;
    cout<<"Enter the matrix"<<endl;
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            cin>>mat[i][j];
        }
    }
}
Matrix Matrix::operator++(){
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            mat[i][j]=mat[i][j]+1;
        }
    }
    return *this;
}
void Matrix::display(){
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
           cout<<mat[i][j]<<" ";
        }
        cout<<endl;
    }
}

int main(){
   Matrix mat;
   mat.set_matrix();
   ++mat;
   mat.display();
}