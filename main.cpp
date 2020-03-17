#include<iostream>

// local stiffness matrix

void elematrix(auto a){
double kele[3][3];
kele[0][0]= 3.0;
kele[0][0]=kele[2][2];
kele[0][2]=-kele[2][2];
kele[0][1]=2*a;
kele[0][3]=kele[0][1];
kele[1][1]=4*a*a;
kele[1][1]=kele[3][3];
kele[2][3]= 2*a*a;
for(int i; i<3;i++){
for(int j; j<3;j++){
kele[j][i]=kele[i][j]; 
}
}

}

int main(){

return 0;
}
