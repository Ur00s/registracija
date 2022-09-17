#include <stdio.h>
#include <stdlib.h>

#define nepovezano 0
#define povezano 1
#define vuk 2
#define nedefinisano -1

typedef struct _cvor{
	int broj;
	struct _cvor *sledeci;
}cvor;

void dodaj(cvor **p,cvor **k,int broj){
	cvor *novi;
	novi=(cvor*)malloc(sizeof(cvor));
	novi->broj=broj;
	novi->sledeci=NULL;
	if(*p==NULL){
		*p=*k=novi;
	}
	else{
		(*k)->sledeci=novi;
		*k=novi;
	}
}

int skini(cvor **p,cvor **k){
	int n;
	cvor *c;
	if(*p==NULL){
		return nedefinisano;
	}
	else{
		c=*p;
		*p=c->sledeci;
		if(*p==NULL){
			*p=*k=NULL;
		}
		n=c->broj;
		free(c);
		return n;
	}
}

void stampanje(int *pret,int u,int v){
	if(u==v)
		printf("%d ",u);
	else if(pret[v]==nedefinisano)
		printf("Nema puta.\n");
	else{
		stampanje(pret,u,pret[v]);
		printf("%d ",v);
	}
}

void main(){
	int **graf,*pret,*koraci;
	int n,l,m;
	int i,j;
	int u,v;
	int ind;
	int zec,mladunce,*vukovi;
	
	cvor *p,*k;
	
	scanf("%d%d%d",&n,&l,&m);
	
	graf=(int**)malloc(n*sizeof(int*));
	for(i=0;i<n;i++)
		graf[i]=(int*)malloc(n*sizeof(int));
	pret=(int*)malloc(n*sizeof(int));
	koraci=(int*)malloc(n*sizeof(int));
	vukovi=(int*)malloc(m*sizeof(int));
	
	for(i=0;i<n;i++){
		for(j=0;j<n;j++)
			graf[i][j]=nepovezano;
		pret[i]=nedefinisano;
		koraci[i]=nedefinisano;
	}
	
	for(i=0;i<l;i++){
		scanf("%d%d",&u,&v);
		graf[v][u]=graf[u][v]=povezano;
	}
	
	for(i=0;i<m;i++){
		scanf("%d",&vukovi[i]);
		for(j=0;j<n;j++){
			graf[vukovi[i]][j]*=vuk;
			graf[j][vukovi[i]]*=vuk;
		}
	}

	
	scanf("%d%d",&zec,&mladunce);

	p=NULL;
	k=NULL;
	koraci[zec]=0;
	dodaj(&p,&k,zec);
	ind=1;
	while((u=skini(&p,&k))!=nedefinisano){
		if(koraci[u]!=1 && koraci[u]%3==1 && ind){
			for(i=0;i<m;i++){//svaki vuk
				for(j=0;j<n;j++){//vise nije opasno na ovim mestima
					graf[vukovi[i]][j]/=vuk;
					graf[j][vukovi[i]]/=vuk;
				}
				for(j=0;j<n;j++){//bira se sledece mesto vuka
					if(graf[vukovi[i]][j]!=nepovezano){
						//printf("vuk je %d\n",j);
						vukovi[i]=j;
						break;
					}
				}
				for(j=0;j<n;j++){//namestaju se opasna mesta
					graf[vukovi[i]][j]*=vuk;
					graf[j][vukovi[i]]*=vuk;
				}
			}
			ind=0;
		}
		if(koraci[u]%3!=1) ind=1;
		for(v=0;v<n;v++){
			if(graf[u][v]==povezano && koraci[v]==nedefinisano){
				dodaj(&p,&k,v);
				koraci[v]=koraci[u]+1;
				pret[v]=u;
			}
		}
	}

	if(koraci[mladunce]!=nedefinisano){
		printf("Zec je stigao do mladunceta u %d koraka.\n",koraci[mladunce]);
		stampanje(pret,zec,mladunce);
		printf("\n");
	}
	else printf("Zec ne moze da stigne do mladunceta.\n");	
}
