
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main()
{
    double f,R,L,h,k1,k2,k3,k4;


    int i, n=10000;
    double* Ve=calloc(n,sizeof(double));
    double* dVe=calloc(n,sizeof(double));
    double* Voeul=calloc(n,sizeof(double));
    double* Vork2=calloc(n,sizeof(double));
    double* Vork4=calloc(n,sizeof(double));
    double* Vodf=calloc(n,sizeof(double));

    printf("vous avez choisis un circuit RL, donnez leurs valeurs respectives \n");
    scanf("%lf",&R);
    scanf("%lf",&L);
    f=R/(2*3.14*L);
    h=0.001;
    for(i=0; i<n; i++)
    {
         //Ve[i]=1;
        Ve[i]=sin(2*3.14*f*i*h);
    }
    for(i=0; i<n-1; i++)
    {
        dVe[i]=(Ve[i+1]-Ve[i])/h;
    }
    dVe[n-1]=(Ve[n-1]-Ve[n-2])/h;

    FILE *fTxtRL=fopen("circuit3RL.txt","w");
    if(fTxtRL!=NULL)
    {
        for(i=0; i<n; i++)
        {
            // METHODE d'EULER
            Voeul[i+1]=Voeul[i]+h*(dVe[i]-(R/L)*Voeul[i]);

            // Runge-Kutta ordre 2
            Vork2[i+1]= Vork2[i]+(h/2)*(dVe[i]-(R/L)*Vork2[i])+(h/2)*(dVe[i]-(R/L)*(Vork2[i]+h*(dVe[i]-(R/L)*(Vork2[i]))));
            //Runge-Kutta ordre 4
            k1=h*(dVe[i]-(R/L)*Vork4[i]);
            k2=h*(dVe[i]-(R/L)*(Vork4[i]+0.5*k1));
            k3=h*(dVe[i]-(R/L)*(Vork4[i]+0.5*k2));
            k4=h*(dVe[i]-(R/L)*(Vork4[i]+k3));


            Vork4[i+1]=Vork4[i]+(1./6.)*(k1+2*k2+2*k3+k4);

            // Différences finies
            Vodf[i+1]=h*(dVe[i]-(R/L)*Vodf[i])+Vodf[i];

            printf("%d\t %lf \t %lf\t %lf \t %lf \t %lf \t %lf \n",i,i*h,Ve[i],Voeul[i],Vork2[i],Vork4[i],Vodf[i]);
            fprintf(fTxtRL,"%lf %lf %lf\n",h*i,Ve[i],Voeul[i]);


        }

        free(Ve);
        free(dVe);
        Ve=NULL;
        dVe=NULL;
        free(Voeul);
        free(Vork2);
        free(Vork4);
        free(Vodf);
        Voeul=NULL;
        Vork2=NULL;
        Vork4=NULL;
        Vodf=NULL;
        fclose(fTxtRL);
    }
    return 0;
}
