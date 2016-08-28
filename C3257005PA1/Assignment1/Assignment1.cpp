// Assessment 1.cpp : Defines the entry point for the console application.
//
/* Student No: C3257005
*  Name: Matthew Lee
*  Program: LabExt3
*  Date: 27/08/2016
*  Description: This is a program that will allow the single roots of a quartic equation to be estimated by The Bisection Method.
*/
#include "stdafx.h"
#include <math.h>
#include <iostream>
#include <ctime>
#define NMAX 100 /*maximum iterations*/
#define TOL 0.0000001 /*A Tolerance value for finding a root*/
#define T 0.0001 /*A Tolerance value for checking roots*/


double Fx(double x,double a, double b, double c, double d, double e);
void FindRoots(double Up, double Low, double a, double b, double c, double d, double e);
void DisplayResults(double a, double b, double c, double d, double e, double Low, double Up, double Root1, double Root2, double Root3, double Root4);

int main(){
	double Low, /*Lower Limit*/
		Up; /*Upper Limit*/

	double a, b, c, d, e; /*List of coefficients for F(x)*/

	a = 1;


	FILE * file;
	fopen_s(&file, "C:\\Users\\Matthew\\Desktop\\GENG1003-master\\GENG1003-master\\input1.dat", "r");

	//checks if the file is empty by seeking the end of the file and checking whether the pointer position is still at 0
	int filePosTemp = ftell(file);
	fseek(file, 0, SEEK_END);
	if (ftell(file) == 0) {
		printf("The specified file is empty.\n\n");
		printf("This program is designed to find the roots of a quartic function of the form:\n\n\t\t\t\t f(x) = ax^4+bx^3+cx^2+dx+e\n\n");
		printf("Please enter data in the format: a b c d e rangeLower rangeUpper\n");
	}
	//if the file is not empty, continue
	else {
		fseek(file, filePosTemp, SEEK_SET);						//	set the file pointer back to the starting position
		while (!feof(file))
		{
			fscanf_s(file, "%lf", &b);							//	reads 6 values in the file and assign them to the coefficient variables and limits
			fscanf_s(file, "%lf", &c);
			fscanf_s(file, "%lf", &d);
			fscanf_s(file, "%lf", &e);
			fscanf_s(file, "%lf", &Low);
			fscanf_s(file, "%lf", &Up);

			FindRoots(Up, Low, a, b, c, d, e);
		}
	}
		fclose(file);
		return 0;
	}





	/* F(x) =  a.x^4+ b.x^3+ c.x^2+ d.x + e */
	double Fx(double x, double a, double b, double c, double d, double e) {
		double Fx;

		Fx = a*pow(x, 4) + b*pow(x, 3) + c*pow(x, 2) + d*x + e;

		return (Fx);
	}





	void FindRoots(double Up, double Low, double a, double b, double c, double d, double e) {
		double A, /*A temporary value for Low, for a new segment*/
			B, /*A temporary value for Up, for a new segment*/
			Fa, /*F(A) calculating the value of y when x = A*/
			i, /*Counter*/
			L, /*Caculated interval*/
			mid, /*Calculated mid range*/
			Fmid; /*F(mid) Calculating the value of y when x = mid*/


		double 	Root1, Root2, Root3, Root4;

		int N,/*Iteration count*/
			R; /*Count for Roots*/

		i = 0;
		R = 0;
		double Root[4] = { 0.0,0.0,0.0,0.0 };

		/*Determining the overall length between Lower limit and Upper limit*/
		L = fabs(Up) + fabs(Low);
		

		while (i < L && R < 4) { /*This while statment is used to get the 4 roots*/
								 /*------------------ Explanation -----------------*/
			if (i == 0) {			/* This splits the interval into multiple segments */
				A = Low;			/* the segments are then checked to see if a root  */
			}						/* is in it									       */
			if (Low < 0) {
				B = Low + (i + 0.1);
				A = Low + i;
			}
			else {
				B = (i + 0.1);
				A = i;
			}
			/*-------------------------------------------------*/


			N = 1; /*N is defined within side the first loop so it resets once the second loop has finished*/

				   /*Caluclating the roots*/
			while (N != NMAX) {
				mid = (A + B) / 2; /*Calculating the mid point between A and B*/
				Fmid = Fx(mid, a, b, c, d, e); /*Subbing the mid point into F(x)*/
				Fa = Fx(A, a, b, c, d, e); /*Subbing A into F(x)*/


				if (Fmid == 0 || fabs(Fmid) < TOL) { /*If Tolerance is is exceeded or F(mid) = 0, a root is found*/
					Root[R] = mid;
					R = R + 1;
					N = NMAX;
				}
				else {
					N = N + 1; /*Incrimenting N by 1*/
				}

				/*If the sign of Fmid is equal to Fa, then A = mid*/
				if (Fmid*Fa > 0) { /*Logic - A postive*postive = postive, negative*negative = postive, postive*negative = negative*/
					A = mid;
				}
				/*If the sign of Fmid is not equal to Fa, then B = mid*/
				else {
					B = mid;
				}


			}

			i = i + 0.1; /*Incrimenting i by 0.1*/
		}

		for (R = 0; R < 4; R++) {
			if (fabs(Root[R] - Root[R - 1]) < T && R != 0) {
				Root[R] = 0.0;


			}
		}
		Root1 = Root[0];
		Root2 = Root[1];
		Root3 = Root[2];
		Root4 = Root[3];

		DisplayResults(a, b, c, d, e, Low, Up, Root1, Root2, Root3, Root4);
	}

	void DisplayResults(double a, double b, double c, double d, double e, double Low, double Up, double Root1, double Root2, double Root3, double Root4) {
		printf("For quartic polynomial a = %.5lf; b = %.5lf; c = %.5lf; d = %.5lf; e = %.5lf;\n", a, b, c, d, e);
		printf("With range from %.5lf to %.5lf\n", Low, Up);
		printf("Gives F(x) = zero at the following values of x\n");
		if (Root1 == 0 && Root2 == 0 && Root3 == 0 && Root4 == 0) {
			printf("No Roots found\n\n\n");
		}
		else {
			if(Root1 != 0 && Root2 == 0 && Root3 == 0 && Root4 == 0){ 
				printf("x = %5.3f \n", Root1);
				printf("1 distinct roots found\n\n\n");
			}
			else if (Root1 != 0 && Root2 != 0 && Root3 == 0 && Root4 == 0) {
				printf("x = %5.3f, %5.3f\n", Root1, Root2);
				printf("2 distinct roots found\n\n\n");
			}
			else if (Root1 != 0 && Root2 != 0 && Root3 != 0 && Root4 == 0) { 
				printf("x = %5.3f, %5.3f, %5.3f\n", Root1, Root2, Root3);
				printf("3 distinct roots found\n\n\n");
			}
			else {
				printf("x = %5.3f, %5.3f, %5.3f, %5.3f \n", Root1, Root2, Root3, Root4);
				printf("4 distinct roots found\n\n\n");
			}
		}
	}
