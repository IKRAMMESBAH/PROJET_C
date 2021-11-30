#include <stdio.h>
#include <stdlib.h>

int main()
{
    double h=0.001; // le pas (plus petit possible)
    int n=1000;
    int i;
    double R, C;
    double* Ve=calloc(n,sizeof(double)); // initialisation du tableau des valeur du signal d'entrée
    double* dVe=calloc(n,sizeof(double));
    double* Voext=calloc(n,sizeof(double));//  initialisation du tableau des valeur du signal de sortie
    double* Voeul=calloc(n,sizeof(double));
    double* Vork2=calloc(n,sizeof(double));
    double* Vork4=calloc(n,sizeof(double));
    double* Vodf=calloc(n,sizeof(double));
    double k1,k2,k3,k4;


// demande à l'utilisateur de rentrer les valeurs du circuit
    printf("vous avez choisi un circuit CR , donnez leurs valeurs respectives\n");
    scanf("%lf",&C);
    scanf("%lf",&R);
  double f=1/(2*3.14*R*C); // calcul de la fréquence de coupure

    for(i=0; i<n; i++)
    {
         //Ve[i]=1;
        Ve[i]=sin(2*3.14*f*i*h);
    }
// la solution exact de l'équation différentielle dépend de l'entrée du système.
    for(i=0; i<n-1; i++)
    {
        dVe[i]=(Ve[i+1]-Ve[i])/h;
    }
    dVe[n-1]=(Ve[n-1]-Ve[n-2])/h;

    //Ouverture en écriture d'un fichier texte pour récupérer les valeurs de sortie

    FILE *fTxt2;
    fTxt2=fopen("circuitCR.txt","w");
    if(fTxt2!=NULL)
    {

        // Application des méthodes
        for(i=0; i<n; i++)
        {
            // Méthode 1 : euler 2
            Voeul[i+1]=Voeul[i] + h*((dVe[i] - Voeul[i])/(R*C));
            // Méthode 2 : différences finies
            Vodf[i+1]= (dVe[i]-Vodf[i]/(R*C))*h+Vodf[i];
            // Méthode 3 : Runge Kutta 2
            Vork2[i+1]=Vork2[i]+(h/2)*(dVe[i]-Vork2[i]/(R*C))+(h/2)*(dVe[i]-Vork2[i]/(R*C)+(h/2)*(dVe[i]-Vork2[i]/(R*C)));
            // Méthode 4 : Runge Kutta 4
            k1=h*(dVe[i]-(Vork4[i]/(R*C)));
            k2=h*(dVe[i]-(Vork4[i]/(R*C)+0.5*k1));
            k3=h*(dVe[i]-(Vork4[i]/(R*C)+0.5*k2));
            k4=h*(dVe[i]-(Vork4[i]/(R*C)+k3));

            Vork4[i+1]=Vork4[i]+(double)(1./6.)*(k1+2*k2+2*k3+k4);

            printf("%lf\t %lf \t %lf \t %lf \t %lf \n",Ve[i],Voeul[i],Vodf[i],Vork2[i],Vork4[i]);
            fprintf(fTxt2," %lf %lf %lf %lf %lf\n",Ve[i],Voeul[i],Vodf[i],Vork2[i],Vork4[i]);
            // printf("\n");
        }
        free(Ve);
        Ve=NULL;
        free(Voeul);
        free(Vodf);
        free(Vork2);
        free(Vork4);
        free(dVe);
        Voeul=NULL;
        Vodf=NULL;
        Vork2=NULL;
        Vork4=NULL;
        dVe=NULL;
        fclose(fTxt2);
    }
    else  printf("erreur");

    return 0;
}
