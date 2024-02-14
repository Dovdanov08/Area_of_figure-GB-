#include <stdio.h>

#include <unistd.h>

#include "RootsArea.h"

void print_x(float x1,float x2,float x3,float x4);															//функция для вывода значения точек пересения на экран
void FindRoots(float *x0,float *x1,float *x2,float *x3,float *x4, float *x5, float eps1, int*);				//фукнция для вычисления точек пересечения фукнций
void FindPrintEachTotalArea(float *x0,float *x1,float *x2,float *x3,float *x4, float *x5, char state);		//фукнция для вычисления площади кривой образованной при пересечении функйия f1, f2, f3

/* 	
	Для решения задачи по поиску точек песечения 3-х функций (f1,f2,f3) мной был выбран метод деления отрезка пополам. 
Все ф-ии для нахождения корней определены в RootsArea.c	
Ф-ия rootFindDiv2 - для нахождения корней уравнения одной функции.
Ф-ия rootFindDiv211 - для нахождения корней уравнения двух  функций
----------------------------------------------------------------------------------------------------------	
	Для решения задачи по вычислению площадей мной был выбран метод трапеций ( ф-ия: calcIntegralTrap).
----------------------------------------------------------------------------------------------------------	
	Границы для поиска корней уравнения мной были найдены графически (график прилагается). Также на прилагаемом графике изображены границы искомой площади (S) 
из чего графически понятно из каких частей (площадей) она состоит.  
*/

/*------------------------Help text---------------------------------*/
char help[MaxText]="The program is designed to find the area of a figure formed by the intersection of the curves of the functions f1,f2,f3.\n\n\
There are several different commands.\n\n\
Commands:\n\
-r - displaying the root of equations;\n\
-e - epsilon value (calculation accuracy) for the roots of the equations (must use with '-r', '-s' and '-S')  ;\n\
-i - additional option displaying of step algorhitm (must use with '-r', '-s' and '-S'); \n\
-s - area of each the figure\n\
-S - total area of the figure \n\
-t - enter yout test data for equations.\n\
Default value esp = 0.001 (accuracy of calculation of equation roots)\n\
For test this programm you can enter test data: lower value= -6.0 upper = -5.5 and then the program will display\n the intersection point of functions f1 and f3.";
/*------------------------------------------------------------------*/

/*-------------------Функции (кривые) f1(x), f2(x), f3(x)--------------------*/                                      
float f1(float x)
{
	return 0.6*x+3;
}
float f2(float x)																				
{
	return ((x-2)*(x-2)*(x-2))-1;
}
float f3(float x)
{
	return 3/x;
}

float f(function f2 , function f3, float x)																		//Функция уравнения f(x)=g(x) => f(x)-g(x)=0
{

	float y=0.0;

	y=f2(x)-f3(x);
	return y;
}
/*-----------------------------------------------------------*/
int main (int argc, char* argv[])
{
	char argum, *eps;
	
	int i=0,  step=0;
	/*------------Корни уравнений----------------*/
	float x0=0.0, x2=0.0, x3=0.0,x5=0.0; 																		// корни уравнений f1=f2;(x0, x3), f2=f3;(x2,x5)
	float x1=0.0, x4=0.0;																						// корни уравнений f1=0;(x1), f3=0;(x4) 

	/*-------------------------------------------*/
	
	/*------------Точность-----------------------*/
	float eps1=0.001;
	/*--------------------------------------------*/
	float xlow=0.0;
	float xup=0.0;
	if(argc <2)
	{
		printf("Please, enter you some command. See help (-h).\nThank you!!");
		return 0;
	}
	while ( (argum = getopt(argc,argv,"he:risSt")) != -1){
		switch (argum){
			case 'h': 
				//printf("This programm on test stady\n\n");														// блок для вывода help информации
				printf("%s",help);
				break;
			case 'e':
				eps1=atof(optarg);				
				break;
			case 'r': 		// корни уравнений	
				FindRoots(&x0,&x1,&x2,&x3,&x4,&x5, eps1, &step);																		
				print_x(x0,x2,x3,x5);
				break;
			case 'i':		
				printf("total step for finding total roots, %d\n", step);	
				break;
			case 's':		// площадь каждой кривой									
				FindRoots(&x0,&x1,&x2,&x3,&x4,&x5, eps1,&step);
				FindPrintEachTotalArea(&x0,&x1,&x2,&x3,&x4,&x5,argum);
				break;
			case 'S': 		// общая площадь
				FindRoots(&x0,&x1,&x2,&x3,&x4,&x5, eps1,&step);
				FindPrintEachTotalArea(&x0,&x1,&x2,&x3,&x4,&x5,argum);	

				break;
			case 't':		//тестовый блок
				printf("Please, enter test data\n");
				printf("lower value iof the root:\n");
				if(scanf("%f", &xlow)<1)
				{
					printf("error,incorrect enter data\n");
					break;
				}
				printf("upper value iof the root:\n");
				if(scanf("%f", &xup)<1)
				{
					printf("error,incorrect enter data\n");
					break;
				}
				x0= rootFindDiv211(xlow,xup, eps1,f,f1,f3,&i);
				printf("x0=%f, i=%d",x0, i);
				break;
		};
	}
	

	return 0;
}
void print_x(float x1,float x2,float x3,float x4)
{
	if ((x1+x2+x3+x4)!=0.0)
	{
		printf("Roots of your equations:\n");
		printf("x1 %.5f\n",x1);
		printf("x2 %.5f\n",x2);
		printf("x3 %.5f\n",x3);
		printf("x4 %.5f\n",x3);
	}
}

void FindRoots(float *x0,float *x1,float *x2,float *x3,float *x4, float *x5, float eps1, int *step)	
{
	int stepcount0=11156, stepcount1=0,stepcount2=0,stepcount3=0,stepcount4=0,stepcount5=0;
	
//--Границы областей в которых находятся корни (точки пересечения фунrций f1,f2,f3)уравнений	//
	float x0Opr1=-6.0, x0Opr2=-5.4;
	float x1Opr1=-5.0, x1Opr2=-4.5;
	float x2Opr1=-0.4, x2Opr2=-0.1;
	float x3Opr1= 0.7, x3Opr2= 1.0;
	float x4Opr1= 2.9, x4Opr2= 3.1;
	float x5Opr1= 3.1, x5Opr2= 3.4;
//-------------------------------------------------------//	

//-----Вычисляем 6 точек пересечения кривых ------------//
	*x1= rootFindDiv2(x1Opr1,x1Opr2, eps1,f1,&stepcount1);		
	*x4= rootFindDiv2(x4Opr1,x4Opr1, eps1,f2, &stepcount4);
	
	*x0= rootFindDiv211(x0Opr1,x0Opr2, eps1,f,f1,f3,&stepcount0);		
	*x2= rootFindDiv211(x2Opr1,x2Opr1, eps1,f,f2,f3,&stepcount2);
	*x3= rootFindDiv211(x3Opr1,x3Opr1, eps1,f,f1,f3,&stepcount3);
	*x5= rootFindDiv211(x5Opr1,x5Opr1, eps1,f,f2,f3,&stepcount5);
//---------------------------------------------------///

	*step=stepcount0+stepcount1+stepcount2+stepcount3+stepcount4+stepcount5;
}
void FindPrintEachTotalArea(float *x0,float *x1,float *x2,float *x3,float *x4, float *x5, char state)		//function for print area of each the figure and total area of the figure
{
	/*-------------------Площади-----------------*/
	float S= 0.0; // Общая площадь
	float s1=0.0, s2=0.0, s3=0.0, s4=0.0;																	// площади образованные кривыыми f1 (s1),f2(s2,s3),f3 (s4)
	float s0=0.0, s5=0.0;																					// ненужные "кусочки" отрезанные функциями f1 и f4
	/*------------------------------------------*/
	
	s1=fabs(calcIntegralTrap(*x1,*x3, 100,f1));
	s2=fabs(calcIntegralTrap(*x0,*x2, 100,f3));
	s3=fabs(calcIntegralTrap(*x3,*x5, 100,f3));
	s4=fabs(calcIntegralTrap(*x2,*x4, 100,f2));
	
	s0=fabs(calcIntegralTrap(*x0,*x1, 100,f1));
	s5=fabs(calcIntegralTrap(*x4,*x5, 100,f2));
	
	S=s1+(s2-s0)+(s3-s5)+s4;																// общая площадь 
	
	if(state=='s')
	{			
		printf("one figure (f1[x1,x2]) area s1=%.3f\n", s1);
		printf("one figure (f2[x0,x2]) area s2=%.3f\n", s2);
		printf("one figure (f2[x3,x5]) area s3=%.3f\n", s3);
		printf("one figure (f3[x2,x4]) area s4=%.3f\n", s4);
	}
	else if(state =='S')							
		printf("Total area (f1,f2,f3[x0,x5]) S=%.3f\n", S);								//выводим общаю площадь согласно графику						
}