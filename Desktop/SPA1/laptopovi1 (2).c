#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct kupac{
	char ime[21];
	char model[21];
	int novac;
	int vreme;

}Kupac;
typedef struct laptop{
	char model[21];
	int cena;
	int kolicina;
}Laptop;

int Unos1(Kupac **kupac ){
	int i;
	int n;
	FILE *f;
	f=fopen("kupci.txt","r");
	fscanf(f,"%d",&n);
	*kupac=(Kupac*)malloc(n*sizeof(Kupac));
	char ime1[21];
	char model1[21];
	int novac1;
	int vreme1;
	for(i=0;i<n;i++){
		fscanf(f,"%s%s%d%d",ime1,model1,&novac1,&vreme1);
		strcpy((*kupac)[i].ime,ime1);
		strcpy((*kupac)[i].model,model1);
		(*kupac)[i].novac=novac1;
		(*kupac)[i].vreme=vreme1;


	}
	return n;
	fclose(f);
}
int Unos2(Laptop **laptop){
	int i;
	int n;
	FILE *f;
	f=fopen("laptopovi.txt","r");
	fscanf(f,"%d",&n);
	*laptop=(Laptop*)malloc(n*sizeof(Laptop));
	char model1[21];
	int cena1;
	int kolicina1;
	for(i=0;i<n;i++){
		fscanf(f,"%s%d%d",model1,&cena1,&kolicina1);
		strcpy((*laptop)[i].model,model1);
		(*laptop)[i].cena=cena1;
		(*laptop)[i].kolicina=kolicina1;

	}
	return n;
	fclose(f);
}
void Sortiraj(Kupac *kupac,int n)
{
    int i,j,pom;
    char pom1[100];

    for(i=0;i<n-1;i++)
    {
        for(j=i+1;j<n;j++)
        {
            if(kupac[i].vreme>kupac[j].vreme)
            {
            	strcpy(pom1,kupac[i].ime);
            	strcpy(kupac[i].ime,kupac[j].ime);
            	strcpy(kupac[j].ime,pom1);
            	
            	strcpy(pom1,kupac[i].model);
            	strcpy(kupac[i].model,kupac[j].model);
            	strcpy(kupac[j].model,pom1);
            	
            	pom=kupac[i].novac;
            	kupac[i].novac=kupac[j].novac;
            	kupac[j].novac=pom;
            	
            	pom=kupac[i].vreme;
            	kupac[i].vreme=kupac[j].vreme;
            	kupac[j].vreme=pom;
            	
            }

        }
    }
}
void ISPIS(Kupac *kupac,Laptop *laptop,int br_kupac,int br_laptop){
	int i,j;
	Sortiraj(kupac,br_kupac);
	for(i=0;i<br_laptop;i++)
	{
		for(j=0;j<br_kupac;j++)
		{
		if(strcmp(laptop[i].model,kupac[j].model)==0)
            {
                if(laptop[i].kolicina>0 && kupac[j].novac>=laptop[i].cena)
                {


                            laptop[i].kolicina--;
                            kupac[j].novac=kupac[j].novac-laptop[i].cena;

                            printf("%s %s %d \n",kupac[j].ime,kupac[j].model,kupac[j].novac/*-laptop[i].cena*/);
                }

            }
		}
	}
}
int main()
{
Kupac *kupac;
Laptop *laptop;
int i;
int broj_kupac;
int broj_laptopova;
broj_kupac=Unos1(&kupac);
for(i=0;i<broj_kupac;i++){
	printf("%s %s %d %d\n ",kupac[i].ime,kupac[i].model,kupac[i].novac,kupac[i].vreme);
}
printf("\n");
broj_laptopova=Unos2(&laptop);
for(i=0;i<broj_laptopova;i++){
	printf("%s %d %d\n",laptop[i].model,laptop[i].cena,laptop[i].kolicina);
}
printf("\n");

ISPIS(kupac,laptop,broj_kupac,broj_laptopova);



}
