#include<iostream>

// material properties
float a = 3.0;
float emod = 760e6;
// local stiffness matrix
void elematrix();
// Moment of inertia
double inertia();

int main(){

return 0;
}

void elematrix(float a){
	float  kele[3][3];
	kele[0][0] = kele[2][2] = 3.0;
	kele[0][2] = -kele[0][0];
	kele[0][1] = kele[0][3] = 3.0*a;
	kele[1][1] = kele[3][3] = 4.0*a*a;
	kele[1][2] = kele[2][3] = -kele[0][1];
	kele[1][3] = 2*a*a;

	for(int i = 0; i<3; i++){
		for(int j = i; j<3; j++){
			kele[i][j] = kele[j][i];
		}
	}
}

float inertia(float h, float b, float a, float e){
	float iz = b*h*h*h/12;
	float iner = e*iz/2*a*a*a;
	return iner;
}