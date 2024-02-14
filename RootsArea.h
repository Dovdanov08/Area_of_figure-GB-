#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MaxText 2000


typedef float(*function)(float);																		// pointer for any function of the same type	

typedef float(*function11)(function, function, float);													// a pointer on function takes two pointer on function, because to solve the problem ned to slove the equation: f(x) - g(x)=0

int signF1(float x,function f);																			// функция для изменения знака значения функции			
int signF(float x, function11 f, function f1, function f2);												// функция для изменения знака значения функции	

float rootFindLineSearch1(float xl, float xr, float eps, function f, function f1, int *step);						// метод линейного поиска
float rootFindDiv2(float xl, float xr, float eps, function f, int *step);											// метод деления пополам для одной функции						
float rootFindDiv211(float xl, float xr, float eps, function11 f, function f1, function f2, int *step);				// метод деления отрезка пополас для двух функций
float rootFindChord(float xl, float xr, float eps, function11 f, function f1, function f2, int *step);				// метод хорд
float calcIntegralTrap(float xl, float xr, size_t n, function f);

