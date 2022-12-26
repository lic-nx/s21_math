#include "s21_math.h"

int s21_abs(int x) { return (x > 0 ? x : -x); }

long double s21_asin(double x) {
  long double rez = x, y = x;
  long double i = 1;
  while (s21_fabs(rez) > s21_EPSILON) {
    if (x < -1 || x > 1) {
      y = s21_NAN;
      break;
    }
    if (x == 1 || x == -1) {
      y = s21_PI / 2 * x;
      break;
    }
    rez *= x * x * (2 * i - 1) * (2 * i - 1) / ((2 * i + 1) * 2 * i);
    i += 1;
    y += rez;
  }
  return y;
}

long double s21_acos(double x) {
  if (x <= 1 && x >= -1) {
    x = s21_PI / 2. - s21_asin(x);
  } else {
    x = s21_NAN;
  }
  return x;
}

long double checker(double x) {
  long double rez = x, y = x, i = 1;
  while (s21_fabs(rez) > s21_EPS) {
    rez = -1 * rez * x * x * (2 * i - 1) / (2 * i + 1);
    i += 1;
    y += rez;
  }
  return y;
}

long double s21_atan(double x) {
  long double y = 0;
  y = (x < 1 && x > -1) ? checker(x) : y;
  y = x == 1 ? s21_PI / 4 : x == -1 ? s21_NPI / 4 : x == 0 ? 0 : y;
  y = x > 1    ? s21_PI / 2 - checker(1 / x)
      : x < -1 ? s21_NPI / 2 - checker(1 / x)
               : y;
  return y;
}

long double s21_ceil(double x) {
  long double res = 0;
  if (s21_ISNAN(x) || s21_ISINF(x)) {
    res = x;
  } else {
    if (x >= 0) {
      long double condition = x - (long long int)x;
      if (condition <= 0.00000001) {
        res = x;
      } else {
        res = (long long int)x + 1;
      }
    } else {
      res = (long long int)x;
    }
  }
  return res;
}

long double s21_fabs(double x) {
  if (x < 0) {
    x *= -1;
  }
  return x;
}

long double s21_floor(double x) { return (x < 0 ? (int)--x : (int)x); }

long double s21_fmod(double x, double y) {
  double result, all_res;
  result = (x < 0 || y < 0 ? s21_abs(x / y) * (-1) : s21_abs(x / y));
  all_res = x - result * y;
  all_res = (y == 0 ? s21_NAN : all_res);
  return all_res;
}

long double s21_sin(double x) {
  long double result;
  if (x == s21_INF || x == -s21_INF || x != x) {
    result = s21_NAN;
  } else {
    while (x > s21_PI) {
      x = x - 2 * s21_PI;
    }
    while (x < -s21_PI) {
      x = x + 2 * s21_PI;
    }
    result = x;
    long double temp = x;
    for (int i = 1; s21_fabs(temp) > s21_EPSILON; i++) {
      temp = temp * (-1) * s21_pow(x, 2) / (2 * i * (2 * i + 1));
      result = result + temp;
    }
  }
  return result;
}

long double s21_cos(double x) {
  long double result;
  if (x == s21_INF || x == -s21_INF || x != x) {
    result = s21_NAN;
  } else {
    while (x > s21_PI) {
      x = x - 2 * s21_PI;
    }
    while (x < -s21_PI) {
      x = x + 2 * s21_PI;
    }
    result = 1;
    if (x == s21_PI / 2 || x == -s21_PI / 2) {
      result = 0;
    } else {
      long double temp = 1;
      for (int i = 1; s21_fabs(temp) > s21_EPSILON; i++) {
        temp = temp * (-1) * s21_pow(x, 2) / ((2 * i - 1) * 2 * i);
        result = result + temp;
      }
    }
  }
  return result;
}

long double s21_tan(double x) { return s21_sin(x) / s21_cos(x); }

long double s21_sqrt(double x) {
  long double x1 = (x == 0) ? 0 : s21_NAN;

  if (x == s21_INF) {
    x1 = s21_INF;
  } else if (x > 0) {
    long double x0 = 1.0;

    for (int i = 0; i < 90; i++) {
      x1 = x0 - (s21_function(x0, x) / s21_derivative(x0));
      if (s21_fabs((double)(x1 - x0)) <= s21_TOLERANCE) {
        break;
      }

      x0 = x1;
    }
  }

  return x1;
}

long double s21_function(long double x0, double x) { return x0 * x0 - x; }

long double s21_derivative(long double x0) { return 2 * x0; }

long double s21_exp(double x) {
  long double result = 1.0;
  if (x == 0.0) {
    result = 1.0;
  } else {
    long double add_value = 1;
    long double i = 1;
    int breck = 1;
    while (s21_fabs(add_value) > s21_EPSILON && breck != 0) {
      add_value *= x / i;
      i += 1;
      result += add_value;
      if (result > s21_max) {
        result = s21_INF;
        breck = 0;
      }
    }
  }
  return result;
}

long double s21_log(double x) {
  int ex_pow = 0;
  double result = 0;
  double compare = 0;
  if (x == s21_INF) {
    result = s21_INF;
  } else if (x == 0) {
    result = -s21_INF;
  } else if (x < 0) {
    result = s21_NAN;
  } else if (x == 1) {
    result = 0;
  } else {
    for (; x >= s21_EXP; x /= s21_EXP, ex_pow++) continue;
    int i;
    for (i = 0; i < 100; i++) {
      compare = result;
      result = compare + 2 * (x - s21_exp(compare)) / (x + s21_exp(compare));
    }
  }
  return (result + ex_pow);
}

long double s21_pow(double base, double exp) {
  long double res = 1;
  if (s21_fabs(exp) <= POW_EPS) {
    res = 1.0l;
  } else if (s21_fabs(base) <= POW_EPS && exp > 0) {
    res = 0.0l;
  } else if (s21_fabs(base - 1.0) <= POW_EPS) {
    res = 1.0l;
  } else if (is_nan(base) || is_nan(exp)) {
    res = s21_NAN;
  } else if (base < 0 && s21_fabs(s21_fmod(exp, 1.0)) > POW_EPS) {
    res = -s21_NAN;
  } else if (is_inf(base) && base < 0 &&
             s21_fabs(s21_fmod(exp, 2.0)) > POW_EPS) {
    res = -s21_INF;
  } else if (is_inf(base) && base < 0 && s21_fmod(exp, 2.0) <= POW_EPS &&
             exp > 0) {
    res = s21_INF;
  } else if (is_inf(base) && base < 0 && exp < 0) {
    res = 0.0l;
  } else if (is_inf(base) && base < 0 && exp > 0) {
    res = s21_INF;
  } else if (is_inf(base) && base > 0 && exp < 0) {
    res = 0.0l;
  } else if (is_inf(base) && base > 0 && exp > 0) {
    res = s21_INF;
  } else if (s21_fabs(base) <= POW_EPS && base >= 0 && exp < 0) {
    res = s21_INF;
  } else if (s21_fabs(base) <= POW_EPS && base >= 0) {
    res = 0.0l;
  } else if (base < 0 && s21_fabs(base) - 1 <= POW_EPS && is_inf(exp)) {
    res = 1.0l;
  } else if ((s21_fabs(base) - 1 < POW_EPS && is_inf(exp) && exp < 0) ||
             (s21_fabs(base) - 1 > POW_EPS && is_inf(exp) && exp > 0)) {
    res = s21_INF;
  } else if ((s21_fabs(base) - 1 > POW_EPS && is_inf(exp) && exp < 0) ||
             (s21_fabs(base) - 1 < POW_EPS && is_inf(exp) && exp > 0)) {
    res = 0.0l;

  } else {
    int neg_base = base < 0;
    int neg_pow = exp < 0;
    if (neg_base) base = -base;
    if (neg_pow) exp = -exp;
    res = s21_exp(exp * s21_log(base));
    if (neg_base && s21_fabs(s21_fmod(exp, 2.0)) > POW_EPS) res = -res;
    if (neg_pow) res = 1. / res;
  }
  return res;
}

int is_nan(double x) { return x != x; }
int is_inf(double x) { return x == s21_INF; }
