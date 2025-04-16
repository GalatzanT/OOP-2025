#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
/// <summary>
/// functie care calculeaza x la puterea n prin inmultiri succesive
//
/// </summary>
/// <param name="x">de tip float, valoarea pe care o ridicam la putere</param>
/// <param name="n">de tip int, reprezinta puterea</param>
/// <returns>returneaza x^n</returns>
float power(float x, int n) {
	if (n < 0) {
		x = 1 / x;
		n = -n;
	}
	if (n == 0)
		return 1;
	float p = 1;
	while (n > 0) {
		p *= x;
		n--;
	}
	return p;
}
/// <summary>
///  functie care citeste un numar int de la user si valideaza sa fie int
/// </summary>
/// <param name="x">va avea o valaore de tip int</param>
void citireInt(int* x) {
	int ok = 1;
	while (ok) {
		printf("=");
		if (scanf("%d", x) != 1 || x < 0) {
			printf("trebuie sa fie de tip int\n");
			while (getchar() != '\n');
		}
		else {
			ok = 0;
		}
	}
}

/// <summary>
///  functie care citeste un numar int de la user si valideaza sa fie int
/// </summary>
/// <param name="x">va avea o valaore de tip int</param>
void citireInt2(int* x) {
	int ok = 1;
	while (ok) {
		printf("=");
		if (scanf("%d", x) != 1) {
			printf("trebuie sa fie de tip int\n");
			while (getchar() != '\n');
		}
		else {
			ok = 0;
		}
	}
}

/// <summary>
/// citeste un numar de tip float de la user si valideaza sa fie float
/// </summary>
/// <param name="x">va fi float</param>
void citireFloat(float* x) {
	int ok = 1;
	while (ok) {
		printf("=");
		if (scanf("%f", x) != 1) {
			printf("trebuie sa fie de tip float\n");
			while (getchar() != '\n');
		}
		else {
			ok = 0;
		}
	}
}
/// <summary>
/// functie care verifica daca un numar este prim
/// </summary>
/// <param name="x">numarul cautat de tip int</param>
/// <returns>0 - daca x e neprim, 1 - daca x e prim</returns>
int numarPrim(int x) {
	if (x < 2) {
		return 0;
	}
	for (int i = 2; i <= x / 2; i++) {
		if (x % i == 0) {
			return 0;
		}
	}
	return 1;
}
/// <summary>
///  afiseaza primele n numere prime
/// </summary>
/// <param name="n"> reprezinta numarul de prime care vor fi afisate</param>
void primeleNnrPrime(int n) {
	int i = 2;
	int nr = 0;
	while (nr < n) {
		if (numarPrim(i) == 1) {
			printf("%d ", i);
			nr++;
		}
		i++;
	}
	printf("\n");
}

int main() {


	int ok = 1;
	int opt;
	while (ok) {
		printf("2. Primele n numere prime\n");
		printf("12. x^n\n");
		printf("Scrie numarul problemei dorite (ex: 2, 12):\n>>> ");

		if (scanf("%d", &opt) != 1) {
			printf("Trebuie sa introduceti un numar int valid!\n");
			while (getchar() != '\n');
			continue;
		}

		switch (opt) {
		case 2: {
			int n;
			printf("n");
			citireInt(&n);
			primeleNnrPrime(n);
			break;
		}
		case 12: {
			float x;
			int n;

			printf("x");
			citireFloat(&x);
			printf("n");
			citireInt2(&n);

			float pow = power(x, n);
			printf("%.3f^%d = %.3f\n", x, n, pow);
			break;
		}
		default:
			printf("nu exista alta problema\n");
			break;
		}
	}
	return 0;
}