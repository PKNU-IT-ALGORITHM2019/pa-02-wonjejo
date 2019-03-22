#include<stdio.h>
#include<math.h>

#define MIN 1000
#define MAX 300

#pragma warning(disable:4996)

typedef struct dot {
	int index;
	int x;
	int y;
} Dot;

int N;
int tour[MAX];
double min_Tour(Dot lct[], int k, double min);
double measure_Sum(Dot data[], int n);
double measure(Dot a, Dot b);
void swap(Dot lct[], int a, int b);

int main(void) {
	Dot lct[MAX];
	char input[20];
	double min = MIN;

	printf("filename input >>> "); scanf("%s", input);
	printf("\n");

	FILE *fp = fopen(input, "r");

	if (fp == NULL) {
		printf("No exist!!!\n");
	}

	fscanf(fp, "%d", &N);

	for (int i = 0; i < N; i++) {
		lct[i].index = i;
		fscanf(fp, "%d %d", &lct[i].x, &lct[i].y);
	}
	fclose(fp);

	printf("<< Distance >>\n%lf\n\n", min_Tour(lct, 0, min));
	printf("<< Route >>\n");

	for (int i = 0; i < N - 1; i++) {
		printf("%d >> ", tour[i]);
	}

	printf("%d\n", tour[N - 1]);


	getchar();

	return 0;
}

double min_Tour(Dot lct[], int k, double min) {
	if (k == N) {
		return measure_Sum(lct, N);
	}
	else {
		for (int i = k; i < N; i++) {
			swap(lct, k, i);
			double tmp_val = min_Tour(lct, k + 1, min);
			if (min > tmp_val) {
				min = tmp_val;
				if (k == N - 1) {
					for (int i = 0; i < N; i++) {
						tour[i] = lct[i].index;
					}
				}
			}
			swap(lct, k, i);
		}
		return min;
	}
}

double measure_Sum(Dot data[], int n) {
	double sum = 0;
	for (int i = 0; i < n; i++) {
		if (i == n - 1) {
			sum = sum + measure(data[i], data[0]);
		}
		else {
			sum = sum + measure(data[i], data[i + 1]);
		}
	}
	return sum;
}

double measure(Dot a, Dot b) {
	double ver = a.x - b.x;
	double hor = a.y - b.y;
	return sqrt((ver*ver) + (hor*hor));
}

void swap(Dot lct[], int a, int b) {
	Dot tmp = lct[a];
	lct[a] = lct[b];
	lct[b] = tmp;
}