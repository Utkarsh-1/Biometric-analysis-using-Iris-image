#include<iostream>
#include<cmath>
#include<fstream>
#define dd double
using namespace std;
float vec[1000][1000];
double eta(dd p, dd q, dd r, dd c, dd xx, dd yy, dd m00){
  dd gamma = 1+(p+q)/2; dd mu_pq=0, mu00=pow(m00, gamma);
  for(int i=0;i<r-2;++i){
    for(int j=0;j<c-2;++j){
      mu_pq = mu_pq + pow(((dd)i-xx), p)*pow(((dd)j-yy),q)*vec[i+1][j+1];
    }
  }
  return(mu_pq/mu00);
}
int main(){
  string name[70];
  for(int i=0; i<70; i++) cin>>name[i];
  for(int i=0; i<70; i++){
    string op = "op"+name[i]+".txt";
    string ip = name[i]+".pgm";
    ifstream in; ofstream out;
    in.open(ip, ios::in); out.open(op, ios::out);
    char s[100];
    in.getline(s, 100); out<<s<<endl;
    in.getline(s, 100); cout<<s<<endl;
    dd r, c, b; in>>r>>c>>b; out<<r<<" "<<c<<" "<<b<<endl;
    for(int i=0;i<r;++i) for(int j=0;j<c;++j) in>>vec[i][j];
    double m00=0, m01=0, m10=0, xx, yy;
    for(int i=0;i<r-2;++i){
      for(int j=0;j<c-2;++j){
        m00=m00+vec[i+1][j+1];
        m10=m10+(dd)i*vec[i+1][j+1];
        m01=m01+(dd)j*vec[i+1][j+1];
      }
    }
    xx=m10/m00;
    yy=m01/m00;
    dd n02, n03, n11, n12, n20, n21, n30;
    n02 = eta(0, 2, r, c, xx, yy, m00);
    n03 = eta(0, 3, r, c, xx, yy, m00);
    n11 = eta(1, 1, r, c, xx, yy, m00);
    n12 = eta(1, 2, r, c, xx, yy, m00);
    n20 = eta(2, 0, r, c, xx, yy, m00);
    n21 = eta(2, 1, r, c, xx, yy, m00);
    n30 = eta(3, 0, r, c, xx, yy, m00);
    dd M[8];
    M[0] = n20 + n02;
    M[1] = pow((n20-n02), 2.0)+4.0*pow(n11, 2);
    M[2] = pow((n30-3.0*n12), 2.0)+pow((3.0*n21-n03), 2.0);
    M[3] = pow((n30+n12), 2.0)+pow((n21+n03), 2.0);
    M[4] = (n30-3.0*n12)*(n30+n12)*(pow((n30+n12), 2.0)-3.0*pow((n21+n03), 2.0))+(3.0*n21-n03)*(n21+n03)*(3.0*pow((n30+n12), 2.0)-pow((n21+n03), 2.0));
    M[5] = (n20-n02)*(pow((n30+n12), 2.0)-pow((n21+n03), 2.0))+4.0*n11*(n30+n12)*(n21+n03);
    M[6] = (3.0*n21-n03)*(n30+n12)*(pow((n30+n12), 2.0)-3.0*pow((n21+n03), 2.0))-(n30-3.0*n12)*(n21+n03)*(3.0*pow((n30+n12), 2.0)-pow((n21+n03), 2.0));
    M[7] = n11*(pow((n30+n12), 2.0)-pow((n03+n21), 2.0))-(n20-n02)*(n30+n12)*(n03+n21);
    for(int i=0; i<8; i++) out<<M[i]<<"\t";
    in.close(); out.close();
  }
  return 0;
}
