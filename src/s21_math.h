//
// Created by Joselyn Theola on 3/6/23.
//

#ifndef C4_S21_MATH_0_S21_MATH_H
#define C4_S21_MATH_0_S21_MATH_H
#include <math.h>
#include <stdio.h>
#define NaN 0.0 / 0.0
#define PoS_INF 1.0 / 0.0
#define NeG_INF -1.0 / 0.0
#define NULLVAL -0.2
#define EXP 2.71828182845904523536
#define PI 3.14159265358979323846264338327950288

int s21_abs(int x);
long double s21_acos(double x);
long double s21_asin(double x);
long double s21_atan(double x);
long double s21_ceil(double x);
long double s21_cos(double x);
long double s21_exp(double x);
long double s21_fabs(double x);
long double s21_floor(double x);
long double s21_log(double x);
long double s21_sin(double x);
long double s21_sqrt(double x);
long double s21_tan(double x);
long double s21_fmod(double x, double y);
long double s21_pow(double base, double exp);
long int facto(long int x);
long double s21_trunc(double x);
long double validate(double x);
long double pow_int(long double base, int exp);
int positive_check(long double num);

#endif  // C4_S21_MATH_0_S21_MATH_H
