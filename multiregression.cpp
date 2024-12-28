#include<iostream>
#include <fstream>
#include <vector>
#include <math.h>
using namespace std;
 /*This Program takes a text file as input which conatins Number of Datapoints ,
  Variables, Values Of varaiables, values of function at variables*/
 
vector<vector<double>> matrixmultiply(vector<vector<double>> a,vector<vector<double>> b){
    
    int n=a.size();
    int m=b.size();
    int p=b[0].size();
    vector<vector<double>>prod(n,vector<double> (p));
    for(int i=0;i<n;i++){
    for(int j=0;j<p;j++){
        for(int k=0;k<m;k++){
            
        prod[i][j]+=a[i][k]*b[k][j];
    
    }
    }
    }
    return prod;
}
vector<double> matrixvecmultiply(vector<vector<double>> &A,  vector<double> &v) {
    int rows = A.size();
    int cols = A[0].size();
    vector<double> result(rows, 0);
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            result[i] += A[i][j] * v[j];
    return result;

}
vector<vector<double>> transposematrix(vector<vector<double>> X){
   
    int n=X.size();
    int m=X[0].size();
     vector<vector<double>> t(m,vector<double>(n));
    for(int i=0;i<n;i++){
    for(int j=0;j<m;j++){
    t[j][i]=X[i][j];
    }
    }
    return t;
}

vector<double> gausselimination(const vector<vector<double>>& J, const vector<double>& F) {
    int n = F.size();
    vector<vector<double>> A = J;
    vector<double> B = F;

    for (int i=0;i<n;++i) {

        for (int j=i+1;j<n;++j) {
            if(fabs(A[j][i]) >fabs(A[i][i])) {
                swap(A[i], A[j]);
                swap(B[i], B[j]);
            }
        }


        for (int j=i+1;j<n;++j) {
            double factor=A[j][i]/A[i][i];
            for(int k = i;k<n;++k) {
                A[j][k]-=factor*A[i][k];
            }
            B[j]-=factor*B[i];
        }
    }


    vector<double> X(n);
    for(int i= n-1; i>= 0;--i) {
        X[i] = B[i];
        for (int j=i+1; j<n;++j) {
            X[i]-= A[i][j]*X[j];
        }
        X[i]/=A[i][i];
    }

    return X;
}
 int main(){
    fstream in;
in.open("multiregressioninput.txt",ios::in);
int datapoints;
in>>datapoints;
int variables;
in>>variables;
vector<vector<double>> x(datapoints,vector<double>(variables+1));
for(int i=0;i<datapoints;i++){
    x[i][0]=1;
}
vector<double> y(variables);


for(int j=1;j<=variables;j++){
for(int i=0;i<datapoints;i++){
   in>>x[i][j];
    
}
}
for(int i=0;i<datapoints;i++){
    in>>y[i];
}
in.close();
fstream outt;
outt.open("multiregressionoutput.txt",ios::out);



vector<vector<double>> xt(variables+1,vector<double>(datapoints));
xt=transposematrix(x);

vector<vector<double>> xtx(variables+1, vector<double>(variables+1));

xtx=matrixmultiply(xt,x);

vector<double>ans(variables+1);
vector<double> xty=matrixvecmultiply(xt,y);
ans=gausselimination(xtx,xty);

for(auto it:ans){
    outt<<it<<endl;
} // coefficients of function obtained
outt.close();
    return 0;
 }