#include "RootsArea.h"

int signF1(float x,function f)
{
	if (f(x)<0)
		return -1;
	return 1;
}

int signF(float x, function11 f, function f1, function f2)
{
	if (f(f1,f2,x)<0)
		return -1;
	return 1;
}
/* 	Различные фукнции, выражающие численные методы нахождения корней (точек пересечения) уравнения (fucntion f) 
	
	Линейный оиск точек пересечения					float rootFindLineSearch1(float xl, float xr, float eps, function f, function f1,int *step) 
	Метод деления отрезка пополам 					float rootFindDiv2(float xl, float xr, float eps, function f, int *step) 			
	Метод хорд (секущих)							float rootFindChord(float xl, float xr, float eps, function11 f, function f1, function f2, int *step) 						

*/
float rootFindDiv2(float xl, float xr, float eps, function f, int *step) 
{
	int count=0; //число шагов
	float xm;
	while(fabs(xr-xl)>eps) { //вещественный модуль разницы
		count++;
		xm=(xl+xr)/2; // середина отрезка
		if(f(xr)==0) { // нашли решение на правой границе
			//printf("Find root for %d steps\n",stepcount);
		return xr;
		}
		if(f(xl)==0) { // нашли решение на левой границе
			//printf("Find root for %d steps\n",stepcount);
			return xl;
		}
		if(signF1(xl,f) != signF1(xm,f)) //если знак отличается
			xr=xm;
		else
			xl=xm;
	}
	*step=count;
	return (xl+xr)/2;
}

float rootFindLineSearch1(float xl, float xr, float eps, function f, function f1,int *step) 						//функция линейного поиска точки пересечения
{
	float x, minx = xl, nextstep;
	nextstep = fabs(xr-xl)/(1/eps); //разбиваем на отрезки интервал
	int stepcount=0;
	for(x=xl; x<xr; x += nextstep, stepcount++) 
	{
		if( fabs(f1(x)) < fabs(f(minx)) )
			minx = x;
	}
	*step=stepcount;
	return minx;
}
/* 	измененый метод деления отрезка пополам (Решение уравнения f1(x)=f2(x)) 
	ДЛя решения уравнения f1(x)=f2(x), передаём в данную указатель на функцию f(x) 
	Тип фукнции function11.
*/
float rootFindDiv211(float xl, float xr, float eps, function11 f, function f1, function f2, int *step)  		
{
	int stepcount=0; //число шагов
	float xm;
	while(fabs(xr-xl)>eps) 
	{ //вещественный модуль разницы
		stepcount++;
		xm=(xl+xr)/2; // середина отрезка
		if(f(f1,f2,xr)==0) 
		{ // нашли решение на правой границе
			//printf("Find root for %d steps\n",stepcount);
			return xr;
		}
		if(f(f1,f2,xr)==0) 
		{ // нашли решение на левой границе
			//printf("Find root for %d steps\n",stepcount);
			return xl;
		}
		if(signF(xl,f,f1, f2) != signF(xm, f,f1,f2)) 	//если знак отличается
			xr=xm;
		else
			xl=xm;
	}
	*step=stepcount;									//статистика
	return (xl+xr)/2;
}
float rootFindChord(float xl, float xr, float eps, function11 f, function f1, function f2, int *step) 			// метод хорд
{
	int stepcount=0;
		printf("\nFind root for steps\n");
	while(fabs(xr - xl) > eps)
	{
		xl = xr - (xr - xl) * f(f1,f2,xr) / (f(f1,f2,xr) - f(f1,f2,xl));
		xr = xl - (xl - xr) * f(f1,f2,xl) / (f(f1,f2,xl) - f(f1,f2,xr));
		stepcount++;
	}
	//printf("\nFind root for %d steps\n");
	*step=stepcount;
	//printf("stepcount=%d\n", stepcount);
	return xr;
}


float calcIntegralTrap(float xl, float xr, size_t n, function f) 						// фукцния вычисления интеграла по методу трапеций											
{
	float sum = 0;
	float h = (xr-xl)/n;
	int stepcount=0;
	
	for(float x=xl+h; x<xr-h; x+=h) 
	{
		sum += 0.5*h*(f(x)+f(x+h));
		++stepcount;
	}

	return sum;
}

