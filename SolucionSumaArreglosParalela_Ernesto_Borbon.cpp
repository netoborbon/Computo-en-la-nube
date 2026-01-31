// Tarea1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//#include "pch.h"
#include <iostream>
#include <omp.h>

#define N 1000
#define chunk 100
#define mostrar 10

using namespace std;

void imprimeArreglo(float* d);
void imprimeArreglo2(float* a, float* b, float* c, float* h);
int tid;

int main()
{
	srand(time(NULL));
	cout << "Sumando Arreglos en Paralelo!\n";

	float a[N], b[N], c[N], h[N];
	int i;

	for (i = 0; i < N; i++)
	{
		a[i] = rand();
		b[i] = rand();
	}
	
	int pedazos = chunk;

	#pragma omp parallel for \
	shared(a,b,c,pedazos) private(i)\
	schedule(static,pedazos)

	for (i = 0; i < N;i++)
	{
		c[i] = a[i] + b[i];
		////Verificar que este funcionado el trabajo paralelo
		tid = omp_get_thread_num();
		h[i] = tid;
		//cout << "Thread: " << tid << ":" << a[i] << "+" << b[i] << "=" << c[i] <<"\n" << endl;
	}

	//cout << "\n" << endl;
	cout << "Imprimiendo " << mostrar << " valores del arreglo a: " << endl;
	imprimeArreglo(a);
	cout << "Imprimiendo " << mostrar << " valores del arreglo b: " << endl;
	imprimeArreglo(b);
	cout << "Imprimiendo " << mostrar << " valores del arreglo c: " << endl;
	imprimeArreglo(c);
	cout << "Imprimiendo " << mostrar << " hilos que se usaron: " << endl;
	imprimeArreglo(h);

	cout << "\nOperaciones:\n" << endl;
	cout << "Thread:# -> a + b = c\n" << endl;
	imprimeArreglo2(a,b,c,h);
}

void imprimeArreglo(float* d)
{

	for (int x = 0; x < mostrar; x++)
		cout << d[x] << " - ";
	cout << endl;
}

void imprimeArreglo2(float* a, float* b, float* c, float* h)
{
	// Crear arreglo de índices
	int* idx = new int[N];
	for (int i = 0; i < N; i++)
		idx[i] = i;

	// Barajar índices (Fisher-Yates)
	for (int i = N - 1; i > 0; i--)
	{
		int j = rand() % (i + 1);
		int temp = idx[i];
		idx[i] = idx[j];
		idx[j] = temp;
	}

	// Imprimir 10 valores
	for (int i = 0; i < mostrar; i++)
	{
		int k = idx[i];
		cout << " Thread:" << h[k]<< "->" << a[k] << " + " << b[k] << " = " << c[k]<< endl;
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
