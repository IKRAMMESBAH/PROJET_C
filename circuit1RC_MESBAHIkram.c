#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define n 1000
#define PI 3.14


int main()
{
//On initialise les tensions de notre circuit à 0, chaque tension est présentée par un esnsemble des points
    double* Ve=calloc(n,sizeof(double));
    double* VoEuler=calloc(n,sizeof(double)); // la tension de sortie par méthode d'Euler
    double* VoRK1=calloc(n,sizeof(double)); // la tension de sortie par méthode de  Runge-Kutta d’ordre 2
    double* VoRK2=calloc(n,sizeof(double)); // la tension de sortie par méthode de  Runge-Kutta d’ordre 4
    double* VoDiff=calloc(n,sizeof(double)); // la tension de sortie par méthode de differences finies

    int i;

    double R,C;
    double k1,k2,k3,k4;
    printf("Vous avez choisi un circuit RC , donner leurs valeurs respectives\n");

    scanf("%lf",&R);
    scanf("%lf",&C);

//Caractéristiques de circuit

    double Wc=1./(R*C);  //pulsation de copure
    double fc=1./(2*PI*R*C); //fréquence de copure
//PAS
    double h=R*C/10;
    for(i=0; i<n; i++)
    {
        // Ve[i]=1; //echelon
        Ve[i]=sin(2*3.14*fc*i*h);   //descrétisation du temps t=ih

    }

    FILE *fTxt1=fopen("circuit1RC.txt","w");
    if(fTxt1!=NULL)
    {

        for(i=0; i<n; i++)
        {
            //EULER
            VoEuler[i+1]=VoEuler[i]+(h/(R*C))*(Ve[i]-VoEuler[i]);
            //runge Kutta 2
            VoRK1[i+1]=VoRK1[i]+(h/(2.*R*C))*(Ve[i]-VoRK1[i]) +(h/2)*((1/(R*C))*(Ve[i]-VoRK1[i]+h*(1/(R*C))*(Ve[i]-VoRK1[i])));
            //Runge Kutta 4
            k1=(h/(R*C))*(Ve[i]-VoRK2[i]);
            k2=(h/(R*C))*(Ve[i]-(VoRK2[i]+0.5*k1));
            k3=(h/(R*C))*(Ve[i]-(VoRK2[i]+0.5*k2));
            k4=(h/(R*C))*(Ve[i]-(VoRK2[i]+k3));
            VoRK2[i+1]=VoRK2[i]+(double)(1./6.)*(k1+2*k2+2*k3+k4);
            // différence finie
            VoDiff[i+1]=(Ve[i]-VoDiff[i])*h/(R*C)+VoDiff[i];  // DIFFERENCE AVANT
            //Vo4[i+1]=(1/(1+R*C/h))*(Ve[i+1]+Vo4[i]*R*C/h);   DIFFERENCE ARRIERE
            printf("%d\t %lf \t %lf\t %lf \t %lf \t %lf \t %lf \n",i,i*h,Ve[i],VoEuler[i],VoRK1[i],VoRK2[i],VoDiff[i]);
            //  fprintf(fTxt1,"%lf %lf %lf %lf %lf %lf\n",h*i,Ve[i],Vo1[i],Vo2[i],Vo3[i],Vo4[i]);
            fprintf(fTxt1,"%lf\t %lf\t %lf\t \n",h*i,Ve[i],VoEuler[i]);
            // printf("\n");
        }
free(Ve);
Ve=NULL;
free(VoEuler);
free(VoRK1);
free(VoRK2);
free(VoDiff);
VoEuler=NULL;
VoRK1=NULL;
VoRK2=NULL;
VoDiff=NULL;
fclose(fTxt1);
// free(temps);
 //   free(valeur);
 //   temps=NULL;
//    valeur=NULL;
}
    return 0;
}
