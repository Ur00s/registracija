#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0


#define AUTOPUT 1
#define REGIONALNI_PUT 0




int *pripadnost, N, L, brUvrstenih, *uvrsteneVeze;

typedef struct {
	int u;
	int v;
	double w;
    double w_original;
} Veza;

Veza *veze;

void promeniPripadnost(int u, int v) {
	int i;
	int pom = pripadnost[v];
	for (i=1; i<=N; i++) {
		if (pripadnost[i]==pom) {
			pripadnost[i] = pripadnost[u];
		}
	}
}

int main() {
	int i, j, oznakaPuta, brojAutoPuteva = 0;
    double cenaIzgradnje, novacOdRusenja, saldo;
	scanf("%d%d", &N, &L);
	pripadnost = (int *)malloc((N+1)*sizeof(int));
	uvrsteneVeze = (int *)malloc((L+1)*sizeof(int));
	veze = (Veza *)malloc((L+1)*sizeof(Veza));
	
	for (i=1; i<=N; i++) {
		pripadnost[i] = i;
	}
	
	for (i=1; i<=L; i++) {
		scanf("%d%d%lf", &veze[i].u, &veze[i].v, &veze[i].w_original);
        scanf("%d", &oznakaPuta);
        
        if (oznakaPuta == AUTOPUT) {
            veze[i].w = 0;
            brojAutoPuteva++;
        }
        else{
            veze[i].w = veze[i].w_original;
        }

		uvrsteneVeze[i] = FALSE;
	}
	
    scanf("%lf%lf", &cenaIzgradnje, &novacOdRusenja);
	scanf("%lf", &saldo);
	
	
	int trenutna = 1;
	brUvrstenih = 0;
	
	//sortiranje veza
	for (i=1; i<=L-1; i++)
		for (j=i+1; j<=L; j++) 
			if (veze[i].w > veze[j].w) {
				Veza pom=veze[i];
				veze[i] = veze[j];
				veze[j] = pom;
			}
    
    // sortiranje po originalnim tezinama - samo autoputevi
    for (i=1; i<=brojAutoPuteva-1; i++)
		for (j=i+1; j<=L; j++) 
			if (veze[i].w_original > veze[j].w_original) {
				Veza pom=veze[i];
				veze[i] = veze[j];
				veze[j] = pom;
			}
    
	double trosak = 0;
	while (brUvrstenih<N-1) {
		if (pripadnost[veze[trenutna].u] != pripadnost[veze[trenutna].v]) {
			promeniPripadnost(veze[trenutna].u, veze[trenutna].v);
			trosak += veze[trenutna].w;
			brUvrstenih++;
			uvrsteneVeze[trenutna] = TRUE;
		}
		trenutna++;
	}

    trosak = trosak * cenaIzgradnje * 1000;
    saldo = saldo - trosak;
    
    if (saldo < 0) {
        printf("%d\n", -1);
        return 0;
    }
    
    double zarada = 0;
    for( i = 1; i <= brojAutoPuteva; i++)
    {    
        if (uvrsteneVeze[i] == FALSE) {
            zarada += veze[i].w_original;
        }   
    }
    
    zarada = zarada * novacOdRusenja * 1000;
    saldo = saldo + zarada;

    printf("%lf\n", saldo);
    return 0;
}










