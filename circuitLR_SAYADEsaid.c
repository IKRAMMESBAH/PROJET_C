#include <stdio.h>
#include <stdlib.h>
#include<math.h>

int main()

{   int i,n=1000;
    double h=0.001;
    double R,L;
    double k1,k2,k3,k4;
    //déclaration des vecteurs
    double* U=calloc(n,sizeof(double));
    double* dU=calloc(n,sizeof(double));
    double* Vr=calloc(n,sizeof(double));
    double* Vr1=calloc(n,sizeof(double));
    double* Vr2=calloc(n,sizeof(double));
    double* Vr3=calloc(n,sizeof(double));

    printf("entrez les valeurs de R et L \n");
    R=scanf("%f",&R);
    L=scanf("%f",&L);
    double f=R/(2*3.14*L);
    for(i=0;i<n;i++)
{
    U[i]=sin(2*3.14*f*i*h);

}

    for(i=0; i<n; i++)
        {
            // méthode d'Euler
            Vr[i+1]=Vr[i]+h*(R/L)*(U[i]-Vr[i]);

            //runge kutta
            Vr1[i+1]=Vr1[i]+(h*R)/(2.*L)*(U[i]-Vr1[i])+((h*R)/(2.*L))*(U[i]-(Vr1[i]+h*(R/L)*(U[i]-Vr1[i])));

            //Runge Kutta ordre 4
            k1=(h*R/L)*(U[i]-Vr2[i]);
            k2=(h*R/L)*(U[i]-(Vr2[i]+0.5*k1));
            k3=(h*R/L)*(U[i]-(Vr2[i]+0.5*k2));
            k4=(h*R/L)*(U[i]-(Vr2[i]+k3));
            Vr2[i+1]=Vr2[i]+(double)(1./6.)*(k1+2.*k2+2.*k3+k4);

            // Difference finie
            Vr3[i+1]=(U[i]-Vr3[i])*h*R/L+Vr3[i];

            printf("%d\t %lf\t %lf \t %lf \t %lf \t %lf \n",i,U[i],Vr[i],Vr1[i],Vr2[i],Vr3[i]);}



    return 0;
}
