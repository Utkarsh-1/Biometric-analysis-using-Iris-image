#include<iostream>
#include<cmath>
#include<fstream>
#define dd double
using namespace std;
int vec[1000][1000];
double mean(int row, int col){
  dd m; int sum=0;
  for(int i=row; i<row+4; i++){
    for(int j=col; j<col+40; j++){
      sum+=vec[i][j];
    }
  }
  m = (dd)sum/160;
  return m;
}
double sd(int row, int col, dd xx){
  dd sum=0, sd;
  for(int i=row; i<row+4; i++){
    for(int j=col; j<col+40; j++){
      sum = sum + (dd)pow((vec[i][j]-xx), 2);
    }
  }
  sum/=160.0;
  sd = sqrt(sum);
  return sd;
}
// int rep(int a, int b){
//   int c[2]={0};
//   for(int i=0; i<2; i++){
//     c[(vec[a+i][b])]++;
//     c[(vec[a][b+i])]++;
//   }
//   if(c[0]>c[1]){
//     if(c[0]>c[2]) return 0;
//     else return -1;
//   }
//   else{
//     if(c[1]>c[2]) return 1;
//     else return -1;
//   }
// }
int main(){
  string name[70];
  for(int i=0; i<70; i++) cin>>name[i];
  for(int i=0; i<70; i++){
    ifstream in; ofstream out;
    string ip = name[i]+".pgm";
    string op = "op"+name[i]+".txt";
    in.open(ip, ios::in); out.open(op, ios::app);
    char s[100];
    in.getline(s, 100); //out<<s<<endl;
    in.getline(s, 100); //out<<s<<endl;
    dd r, c, b; in>>c>>r>>b; //out<<r<<" "<<c<<" "<<b<<endl;
    for(int i=0;i<r;++i) for(int j=0;j<c;++j) in>>vec[i][j];
    int col = c/40, row = r/4;
    dd M[row][col], SD[row][col];
    //localised mean and standard deviation
    for(int i=0; i<row; i++){
      for(int j=0; j<col; j++){
        M[i][j] = mean(i*4, j*40);
        SD[i][j] = sd(i*4, j*40, M[i][j]);
      }
    }
  // generalised range of all sub-matrices
    dd lower[row][col][8];
    for(int i=0; i<row; i++){
      for(int j=0; j<col; j++){
        for(int k=0; k<4; k++)
          lower[i][j][k] = M[i][j]-(SD[i][j]*(4.0-(dd)k))/4.0;
        for(int k=4; k<8; k++)
          lower[i][j][k] = M[i][j]+(SD[i][j]*((dd)k-3.0))/4.0;
      }
    }
  //resetting the vector in binary -1 to 7 and output the said binary matrix
    for(int i=0; i<r; i++){
      int l = i/4;
      for(int j=0; j<c; j++){
        int k = j/40;
        if(vec[i][j]>lower[k][l][0] && vec[i][j]<lower[k][l][1]) vec[i][j]=0;
        else if(vec[i][j]>lower[k][l][1] && vec[i][j]<lower[k][l][2]) vec[i][j]=1;
        else if(vec[i][j]>lower[k][l][2] && vec[i][j]<lower[k][l][3]) vec[i][j]=2;
        else if(vec[i][j]>lower[k][l][3] && vec[i][j]<M[k][l]) vec[i][j]=3;
        else if(vec[i][j]>M[k][l] && vec[i][j]<lower[k][l][4]) vec[i][j]=4;
        else if(vec[i][j]>lower[k][l][4] && vec[i][j]<lower[k][l][5]) vec[i][j]=5;
        else if(vec[i][j]>lower[k][l][5] && vec[i][j]<lower[k][l][6]) vec[i][j]=6;
        else if(vec[i][j]>lower[k][l][6] && vec[i][j]<lower[k][l][7]) vec[i][j]=7;
        else vec[i][j]=-1;
        //cout<<vec[i][j]<<" ";
      }
      //cout<<endl;
    }
    // int vec[10][120];
    // for(int i=0; i<10; i++){
    //   for(int j=0; j<120; j++){
    //     vec[i][j]=rep(i*2, j*2);
    //   }
    // }
    int cm225_1[8][8]={0}, cm225_2[8][8]={0}, cm225_3[8][8]={0}, cm225_4[8][8]={0};
    int cm270_1[8][8]={0}, cm270_2[8][8]={0}, cm270_3[8][8]={0}, cm270_4[8][8]={0};
    int cm315_1[8][8]={0}, cm315_2[8][8]={0}, cm315_3[8][8]={0}, cm315_4[8][8]={0};
    int cm360_1[8][8]={0}, cm360_2[8][8]={0}, cm360_3[8][8]={0}, cm360_4[8][8]={0};
    for(int i=0; i<r-1; i++){
      for(int j=1; j<c; j++){
        if(vec[i][j]!=-1 && vec[i+1][j-1]!=-1)
          cm225_1[(vec[i][j])][(vec[i+1][j-1])]++;
      }
      for(int j=2; j<c && i<r-2; j++){
        if(vec[i][j]!=-1 && vec[i+2][j-2]!=-1)
          cm225_2[(vec[i][j])][(vec[i+2][j-2])]++;
      }
      for(int j=3; j<c && i<r-3; j++){
        if(vec[i][j]!=-1 && vec[i+3][j-3]!=-1)
          cm225_3[(vec[i][j])][(vec[i+3][j-3])]++;
      }
      for(int j=4; j<c && i<r-4; j++){
        if(vec[i][j]!=-1 && vec[i+4][j-4]!=-1)
          cm225_4[(vec[i][j])][(vec[i+4][j-4])]++;
      }
    }
    for(int j=0; j<c; j++){
      for(int i=0; i<r-1; i++){
        if(vec[i][j]!=-1 && vec[i+1][j]!=-1)
          cm270_1[(vec[i][j])][(vec[i+1][j])]++;
      }
      for(int i=0; i<r-2; i++){
        if(vec[i][j]!=-1 && vec[i+2][j]!=-1)
          cm270_2[(vec[i][j])][(vec[i+1][j])]++;
      }
      for(int i=0; i<r-3; i++){
        if(vec[i][j]!=-1 && vec[i+3][j]!=-1)
          cm270_3[(vec[i][j])][(vec[i+1][j])]++;
      }
      for(int i=0; i<r-4; i++){
        if(vec[i][j]!=-1 && vec[i+4][j]!=-1)
          cm270_4[(vec[i][j])][(vec[i+1][j])]++;
      }
    }
    for(int i=0; i<r-1; i++){
      for(int j=0; j<c-1; j++){
        if(vec[i][j]!=-1 && vec[i+1][j+1]!=-1)
          cm315_1[(vec[i][j])][(vec[i+1][j+1])]++;
      }
      for(int j=0; j<c-2 && i<r-2; j++){
        if(vec[i][j]!=-1 && vec[i+2][j+2]!=-1)
          cm315_2[(vec[i][j])][(vec[i+2][j+2])]++;
      }
      for(int j=0; j<c-3 && i<r-3; j++){
        if(vec[i][j]!=-1 && vec[i+3][j+3]!=-1)
          cm315_3[(vec[i][j])][(vec[i+3][j+3])]++;
      }
      for(int j=0; j<c-4 && i<r-4; j++){
        if(vec[i][j]!=-1 && vec[i+4][j+4]!=-1)
          cm315_4[(vec[i][j])][(vec[i+4][j+4])]++;
      }
    }
    for(int i=0; i<r; i++){
      for(int j=0; j<c-1; j++){
        if(vec[i][j]!=-1 && vec[i][j+1]!=-1)
          cm360_1[(vec[i][j])][(vec[i][j+1])]++;
      }
      for(int j=0; j<c-2; j++){
        if(vec[i][j]!=-1 && vec[i][j+2]!=-1)
          cm360_2[(vec[i][j])][(vec[i][j+2])]++;
      }
      for(int j=0; j<c-3; j++){
        if(vec[i][j]!=-1 && vec[i][j+3]!=-1)
          cm360_3[(vec[i][j])][(vec[i][j+3])]++;
      }
      for(int j=0; j<c-4; j++){
        if(vec[i][j]!=-1 && vec[i][j+4]!=-1)
          cm360_4[(vec[i][j])][(vec[i][j+4])]++;
      }
    }
    //cout<<endl;
    for(int i=0; i<8; i++){
      for(int j=0; j<8; j++){
        out<<cm225_1[i][j]<<" ";
      }
      out<<endl;
    }
    out<<"\n";
    for(int i=0; i<8; i++){
      for(int j=0; j<8; j++){
        out<<cm225_2[i][j]<<" ";
      }
      out<<endl;
    }
    out<<"\n";
    for(int i=0; i<8; i++){
      for(int j=0; j<8; j++){
        out<<cm225_3[i][j]<<" ";
      }
      out<<endl;
    }
    out<<"\n";
    for(int i=0; i<8; i++){
      for(int j=0; j<8; j++){
        out<<cm225_4[i][j]<<" ";
      }
      out<<endl;
    }
    out<<"\n";
    for(int i=0; i<8; i++){
      for(int j=0; j<8; j++){
        out<<cm270_1[i][j]<<" ";
      }
      out<<endl;
    }
    out<<"\n";
    for(int i=0; i<8; i++){
      for(int j=0; j<8; j++){
        out<<cm270_2[i][j]<<" ";
      }
      out<<endl;
    }
    out<<"\n";
    for(int i=0; i<8; i++){
      for(int j=0; j<8; j++){
        out<<cm270_3[i][j]<<" ";
      }
      out<<endl;
    }
    out<<"\n";
    for(int i=0; i<8; i++){
      for(int j=0; j<8; j++){
        out<<cm270_4[i][j]<<" ";
      }
      out<<endl;
    }
    out<<"\n";for(int i=0; i<8; i++){
      for(int j=0; j<8; j++){
        out<<cm315_1[i][j]<<" ";
      }
      out<<endl;
    }
    out<<"\n";
    for(int i=0; i<8; i++){
      for(int j=0; j<8; j++){
        out<<cm315_2[i][j]<<" ";
      }
      out<<endl;
    }
    out<<"\n";
    for(int i=0; i<8; i++){
      for(int j=0; j<8; j++){
        out<<cm315_3[i][j]<<" ";
      }
      out<<endl;
    }
    out<<"\n";
    for(int i=0; i<8; i++){
      for(int j=0; j<8; j++){
        out<<cm315_4[i][j]<<" ";
      }
      out<<endl;
    }
    out<<"\n";for(int i=0; i<8; i++){
      for(int j=0; j<8; j++){
        out<<cm360_1[i][j]<<" ";
      }
      out<<endl;
    }
    out<<"\n";
    for(int i=0; i<8; i++){
      for(int j=0; j<8; j++){
        out<<cm360_2[i][j]<<" ";
      }
      out<<endl;
    }
    out<<"\n";
    for(int i=0; i<8; i++){
      for(int j=0; j<8; j++){
        out<<cm360_3[i][j]<<" ";
      }
      out<<endl;
    }
    out<<"\n";
    for(int i=0; i<8; i++){
      for(int j=0; j<8; j++){
        out<<cm360_4[i][j]<<" ";
      }
      out<<endl;
    }
    out<<"\n";
    in.close(); out.close();
  }
  return 0;
}
