#include <stdio.h>
#include <stdlib.h>

#define INF (1)
#define NILL (-1)
#define TRUE 1
#define FALSE 0

int jeManji(int i, int j) {
	if (i==INF)
		return FALSE;
	if (j==INF)
		return TRUE;
	return i<j;
}

int nadjiMinimum(int *obidjen, int *d, int n) {
	int i;
	int min = INF, minCvor=NILL;
	for (i=1; i<=n; i++) // ne gleda za pomocni cvor 0
    {
		if (obidjen[i]==FALSE && jeManji(d[i], min)) {
			min = d[i];
			minCvor = i;
		}
	}

	
    return minCvor;
}

void relax(int **graf, int *d, int *pret, int u, int v) 
{
	if (jeManji(d[u]+graf[u][v], d[v])) {
		d[v] = d[u]+graf[u][v];
		pret[v] = u;
	}
}

void relax_2(int **graf, int *d, int *pret, int u, int v) 
{
	if (jeManji(d[u]+graf[0][v], d[v])) {
		d[v] = d[u]+graf[0][v];
		pret[v] = u;
	}
}

void dijkstra(int **graf, int *obidjen, int *d, int *pret, int n)
{
	int u, i, v, v_pom;
	for (i=1; i<=n; i++) {
		u = nadjiMinimum(obidjen, d, n);
		obidjen[u] = TRUE;
		for (v=0; v<=n; v++) 
        {
			if (graf[u][v]!=INF && obidjen[v]==FALSE)
                if(v != 0)
				    relax(graf, d, pret, u, v);
                else
                {
                    for(v_pom = 1; v_pom<=n; v_pom++)
                        if(graf[0][v_pom]!=INF && obidjen[v_pom]==FALSE)
                        {
                            relax_2(graf, d, pret, u, v_pom);
                            break;
                        }
                }
		}
	}
}


void rekonstrukcija(int i, int polaziste, int *pret) 
{
	if (i==polaziste) {
		printf("%d ", i);
	} else if (pret[i] == NILL)
    {
        printf("Ne postoji putanja do %d\n", i);
    }
	else  {
		rekonstrukcija(pret[i], polaziste, pret);
		printf("%d ", i);
	}
}

int main() {
	int **graf;
	int *d, *pret, *obidjen;
	int n, m;
    double l, ku;
    int i, j, u, v;
	scanf("%d%d", &n, &m);

	graf = (int **)malloc((n+1)*sizeof(int *));
	d = (int *)malloc((n + 1) *sizeof(int));
	pret = (int *)malloc((n + 1) *sizeof(int));
	obidjen = (int *)malloc((n + 1)*sizeof(int));

	for (i=0; i<=n; i++) {
		graf[i] = (int *)malloc((n+1)*sizeof(int));
		d[i] = INF;
		pret[i] = NILL;
		obidjen[i] = FALSE;
	}

	for (i=0; i<=n; i++)
		for (j=0; j<=n; j++)
			graf[i][j] = INF;

	for (i=0; i<m; i++) {
		scanf("%d%d%lf%lf", &u, &v, &l, &ku);
		if(graf[u][v] == INF)
            graf[u][v] = - l * ku;
        else{
            // ako su dve grane za isti par cvorova
            // onda je veza od u do v zapisana preko pomocnog gvora 0
            // tj u->v je u->0 sa tezinom 0 i 0->v sa originalnom tezinom
            graf[u][0] = 0;
            graf[0][v] = - l * ku;
        } 
	}


    int k, kafic, v_pom;
    scanf("%d", &k);
    for(i=0; i<k; i++)
    {
        scanf("%d", &kafic);
        for (v=0; v<=n; v++) 
        {
			if (graf[kafic][v]!=INF )
                if(v != 0)
				    graf[kafic][v] = graf[kafic][v] * 1.15;
                else
                {
                    for(v_pom = 1; v_pom<=n; v_pom++)
                        if(graf[0][v_pom]!=INF)
                        {
                            graf[0][v_pom] = graf[0][v_pom] * 1.15;
                            break;
                        }
                }
		}
        
    }


    int V,P;
    scanf("%d%d", &V, &P);
    int *podnozja = (int *)malloc(P * sizeof(int));
    for(i=0; i<P; i++)
    {
        scanf("%d", &podnozja[i]);
    }

    d[V] = 0;
	dijkstra(graf, obidjen, d, pret, n);

	double min = d[podnozja[0]];
    int min_index = 0;
    for(i=1; i<P; i++)
    {
        if(jeManji(d[podnozja[i]], min ))
        {
            min = d[podnozja[i]];
            min_index = i;
        }
    }

    printf("%.2lf\n", min * (-1));
    rekonstrukcija(podnozja[min_index], V, pret);
    printf("\n");
	return 0;

}
