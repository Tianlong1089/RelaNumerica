/*
Ecuacion de onda----> [(fimn+1 - 2 fimn +fimn-1)/(deltaT*deltaT)]-[V*V(fim+1n -2fimn +fim-1n)/(deltaX*deltaX)]
*/
#include<stdio.h>
#include<math.h>
#include <stdlib.h>
#define fi(x) sin(x)
#define dfi(x) cos(x)
//exp(-x*x)
//-2*(x)*exp(-x*x)
int main(){
  double rho,a,b,T,fim0,dfim0,deltaT,deltaX,fim1,fim2,fi21,fi11,fi01;
  int m,n,j,i,ocupadas;

  printf("Dar: intervalo a,b , tiempo  y el valor de courant(rho) \n");
  scanf("%lf %lf %lf %lf",&a, &b,&T,&rho);
  //Datos iniciales
  //k = ((V*V*deltaT*deltaT)/(deltaX*deltaX)); // separo por cuestion estetica en general lleva k pero aqui nos la dan
  deltaT= 0.05; // le asigno desplazamientos de 1s a la malla
  deltaX= deltaT/rho;
  m = fabs(b-a)/deltaX;
  n = fabs(T)/deltaT;
  double malla[m][n],x[m] ;// la malla para  x , t ;
  // trabajamos con un vector para todas las x's
  rho= rho*rho;
//llenado de condicion inicial
  for (int  i =0; i < m; i++) {
    x[i]=i*deltaX;
      malla[i][0]=fi(i*deltaX); // todo el nivel t=0
      malla[i][1]=rho*(malla[i+1][0] + malla[i-1][0])+ 2*(1-rho)*(malla[i][0])+ 2*deltaT*(dfi(i*deltaX)); // todo el nivel t=1
  }
// calculamos t+1
//tenemos 2 niveles ocupados en principio
ocupadas=2;
for (int i = 1; i < T-1; i++) {
  for (int j = ocupadas; j < m-ocupadas; j++) {
    malla[j][i+1]=rho*(malla[j+1][i] + malla[j-1][i]) + 2*(1-rho)*malla[j][i] - malla[j][i-1];
      }
  ocupadas=ocupadas+1;
}
FILE *data_file=fopen("rt2","w");
if(data_file != NULL)
{
ocupadas=0;
for (int  i = 0; i < T-1; i++)
  {
    for (int j = ocupadas; j < m-ocupadas; j++) {
      fprintf(data_file, "%lf \t %lf \n", x[j], malla[j][i]);
    }
  ocupadas=ocupadas+1;
fprintf(data_file, "\n \n" );
  }


  fclose(data_file);
}

}
