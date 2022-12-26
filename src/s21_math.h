#ifndef SRC_S21_MATH_H_
#define SRC_S21_MATH_H_

#include <stdio.h>
#include <stdlib.h>

#define s21_PI 3.14159265358979323846264338327950288
#define s21_NPI -3.14159265358979323846264338327950288
#define s21_NAN 0.0 / 0.0
#define s21_INF 1.0 / 0.0
#define s21_NEG_INF -1.0 / 0.0
#define s21_EPSILON 1e-17
#define s21_LN10 2.30258509299404590109
#define s21_EXP 2.7182818284590452353602874713526624
#define s21_max 9007199254740990
#define s21_ISNAN(x) (!(x >= 0) && !(x < 0))
#define s21_ISINF(x) ((x == s21_INF) || (x == -s21_INF))
#define s21_TOLERANCE 1e-14
#define s21_LN2 0.6931471805599453
#define s21_EPS 1e-9
#define SIX 1000000

static const double POW_EPS = 1e-100l;

int s21_abs(int x);
long double s21_asin(double x);
long double s21_acos(double x);
long double checker(double x);
long double s21_atan(double x);
long double s21_ceil(double x);
long double s21_fabs(double x);
long double s21_floor(double x);
long double s21_fmod(double x, double y);
long double s21_sin(double x);
long double s21_cos(double x);
long double s21_tan(double x);
long double s21_sqrt(double x);
long double s21_function(long double x0, double x);
long double s21_derivative(long double x0);
long double s21_exp(double x);
long double s21_log(double x);
long double s21_pow(double base, double exp);
int is_nan(double x);
int is_inf(double x);

#endif  // SRC_S21_MATH_H_
