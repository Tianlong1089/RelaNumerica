//Carlos Rub?n Carrera Padilla
//Codigo que evoluciona una funci?n con la apraximaci?n explicita para
//phi(n+1,m)=2*phi(n,m)-phi(n-1,m)+(v * dt/dx)^2 (phi(n,m+1)-2*phi(n,m)+phi(n,m-1))
//Observamos que  (v * dt/dx) = rho  ie Factor de Courant
#include<stdio.h>
#include<math.h>
#include <stdlib.h>
#define fi(x) sin(x)
#define dfi(x) cos(x)

//exp(-x*x)
//-2*(x)*exp(-x*x)
int main(){
	
  double a,b,Tiempo;               //variables intervalo 
  double rho,Fcou;                 //variables de velocidad
  double Dt,Dx;                    // variables  de  Paso
  
  int h,s,cont1,cont2;            //Contadores   
  int var1; 
   
  printf("Dar: intervalo a,b \n");
  scanf("%lf %lf",&a, &b);
  printf("Dar: tiempo  \n");
  scanf("%lf ",&Tiempo);
  printf("Dar: Factor de Courant  \n");
  scanf("%lf",&rho);

  Dt= 0.05;        // Desplazamiento para  nuestra particula computacional en tiempo
  Dx= Dt/rho;      // Desplazamiento para  nuestra particula computacional en espacio 
  
  h = fabs(b-a)/Dx;         //Numero de paso dentro de nuestro intervalo espacial
  s = fabs(Tiempo)/Dt;      //Numero de paso en el tiempo    
  
  double punto[h][s] ;           //  Observamos los puntos de la paricula computacional
  double x[h];                   //  posiciones en x
  
  Fcou= rho*rho;

//Condicion inicial

  for (int  cont1 =0; cont1 < h; cont1++) {
  	
    x[cont1]=cont1*Dx;
    
      punto[cont1][0]=fi(cont1*Dx);                                                                                           //  el nivel inicial
      punto[cont1][1]=Fcou*(punto[cont1+1][0] + punto[cont1-1][0])+ 2*(1-Fcou)*(punto[cont1][0])+ 2*Dt*(dfi(cont1*Dx));       // nivel siguiente 
  
  }
  
var1=2; // Se tienen  los 2 primeros  niveles

for (int cont1 = 1; cont1 < Tiempo-1; cont1++) {
	
   for (int cont2 = var1; cont2 < h-var1; cont2++) {
   	
    punto[cont2][cont2+1]=Fcou*(punto[cont2+1][cont1] + punto[cont2-1][cont1]) + 2*(1-Fcou)*punto[cont2][cont1] - punto[cont2][cont1-1];          //paso timepo siguiente
    
	  }
  
  var1=var1+1;              // Se hacen tantos puntos  como  el intervalo se quiera
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
// SECCION DE DATOS A IMPRIMIR 

FILE *arch=fopen("Ejercio4","w");                     
if(arch != NULL) {
	
var1=0;

for (int  cont1 = 0; cont1 < Tiempo-1; cont1++)  {
    
	for (int cont2 = var1; cont2 < h-var1; cont2++) {
		
      fprintf(arch, "%lf \t %lf \n", x[cont2], punto[cont2][cont1]);
    
	}

  var1=var1+1;

fprintf(arch, "\n \n" );
  }
  fclose(arch);

}

}
