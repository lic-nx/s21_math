//
// Created by Joselyn Theola on 3/6/23.
//
#include "s21_math.h"

int s21_abs(int x) {
  if (x < 0) {
    return -x;
  } else {
    return x;
  }
}

long double s21_fabs(double x) {
  if (x < 0) {
    return -x;
  } else {
    return x;
  }
}

long double s21_sqrt(double x) {
  if (x < 0) return NaN;

  long double result = 1;
  long double precision = 1e-18;

  do {
    result = (result + x / result) / 2;
  } while (result - (result + x / result) / 2 > precision);
  return result;
}

long double s21_ceil(double x) {
  long double result = validate(x);
  if (result == 1) {
    if (x > 0) {
      if ((long double)(x == (int)x))
        result = (long long)x;
      else
        result = ((long long)x + 1);
    } else {
      if (x < 0 && -1 < x)
        result = -0.;
      else
        result = ((long long)x);
    }
  }
  return result;
}

long double s21_floor(double x) {
  long double result = 0;
  result = validate(x);
  if (result == 1) {
    if (x >= 0) {
      result = (long)x;
    } else {
      if (x == (double)((long)x)) {
        result = (long)x;
      } else {
        result = (long)x - 1;
      }
    }
  }
  return result;
}

long double s21_exp(double x) {
  if (x == 0) return 1;
  if (x == PoS_INF) return x;
  if (x == NeG_INF) return 0;
  if (x == NaN) return NaN;
  if (x < 0) return 1 / s21_exp(-x);
  long double result = 1;
  long double precision = 1e-18;
  long double temp = 1;
  int n = 1;

  do {
    temp = temp * x / n;
    result += temp;
    n++;
  } while ((temp > precision || temp < -precision) && result < PoS_INF &&
           temp < PoS_INF);

  return result;
}

long int facto(long x) {
  if (x == 1) {
    return 1;
  } else {
    return facto(x - 1) * x;
  }
}

long double pow_int(long double base, int exp) {
  if (exp == 0) return 1;
  if (exp < 0) return NAN;

  long double result = base;

  for (int i = 1; i < exp; i++) {
    result *= base;
  }

  return result;
}

long double s21_log(double x) {
  long double result = NULLVAL;

  long double flag_x = validate(x);
  if (flag_x != 1) {
    if (x == PoS_INF) result = PoS_INF;
    if (x == NeG_INF) result = NaN;
    if (x != x) result = NaN;
    if (x == 0) result = PoS_INF;
  } else {
    if (x == 1) result = 0;
    if (x < 0) result = NaN;
    if (x == EXP) result = 1;

    if (result == NULLVAL) {
      long double x_tmp = x;
      int lowering = 0;

      if (x_tmp > EXP) {
        while (x_tmp > EXP) {
          x_tmp /= EXP;
          lowering += 1;
        }
      }
      if (x_tmp < EXP) {
        while (x_tmp < EXP) {
          x_tmp *= EXP;
          lowering -= 1;
        }
      }

      long double precision = 1e-18;
      long double add = (x_tmp - 1) / (x_tmp + 1);
      long double temp = add;
      result = add;
      int n = 0;

      do {
        temp = temp * add * add * (2 * n + 1) / (2 * n + 3);
        result += temp;
        n++;
      } while ((temp > precision || temp < -precision));

      result = 2 * result + lowering;
    }
  }
  return result;
}

long double s21_sin(double x) {
  long double result = NULLVAL;

  long double flag_x = validate(x);

  if (flag_x != 1) {
    if (x == PoS_INF) result = NaN;
    if (x == NeG_INF) result = NaN;
    if (x != x) result = NaN;
    if (x == 0) result = 0;
  } else {
    while (s21_fabs(x) > 2 * PI) {
      if (x > 2 * PI)
        x -= 2 * PI;
      else
        x += 2 * PI;
    }

    result = x;

    long double precision = 1e-18;
    long double temp = x;
    long int n = 0;

    do {
      temp = -1 * temp * pow_int(x, 2) / ((2 * n + 2) * (2 * n + 3));
      result += temp;
      n++;
    } while (temp > precision || temp < -precision);
  }
  return result;
}

long double s21_cos(double x) {
  long double result = NULLVAL;

  long double flag_x = validate(x);

  if (flag_x != 1) {
    if (x == PoS_INF) result = NaN;
    if (x == NeG_INF) result = NaN;
    if (x != x) result = NaN;
    if (x == 0) result = 1;
  } else {
    while (s21_fabs(x) > 2 * PI) {
      if (x > 2 * PI)
        x -= 2 * PI;
      else
        x += 2 * PI;
    }

    result = 1;

    long double precision = 1e-18;
    long double temp = 1;
    long int n = 1;

    do {
      temp = -1 * temp * pow_int(x, 2) / ((2 * n - 1) * (2 * n));
      result += temp;
      n++;
    } while (temp > precision || temp < -precision);
  }
  return result;
}

long double s21_tan(double x) { return s21_sin(x) / s21_cos(x); }

long double s21_asin(double x) {
  if (fabs(x) > 1.0) return NaN;
  if (x == 1) return PI / 2;
  if (x < 0) return -s21_asin(-x);
  long double result = x;

  long double precision = 1e-18;
  long double temp = x;
  long int n = 1;

  do {
    temp = temp * pow_int(x, 2) * (2 * n - 1) / (2 * n);
    result += temp / (2 * n + 1);
    n++;
  } while (temp / (2 * n + 1) > precision || temp / (2 * n + 1) < -precision);

  return result;
}

long double s21_acos(double x) { return PI / 2 - s21_asin(x); }

long double s21_atan(double x) {
  if (x < 0)
    return -s21_acos(s21_sqrt(1 / (1 + x * x)));
  else
    return s21_acos(s21_sqrt(1 / (1 + x * x)));
}

long double s21_pow(double base, double exp) {
  long double result = 0;
  int sign = 1;

  long double flag_base = validate(base);
  long double flag_exp = validate(exp);

  if (flag_base != 1) {
    if (base == 0 && exp == 0) result = 1;
    if (base != base) result = NaN;
    if (base == PoS_INF) result = PoS_INF;
    if (base == NeG_INF) {
      if ((long int)exp % 2 != 0)
        result = NeG_INF;
      else
        result = PoS_INF;
    }
  }
  if (flag_exp != 1) {
    if (exp != exp) result = NaN;
    if (exp == NeG_INF || exp == PoS_INF) {
      if (base == 0) {
        if (exp == PoS_INF)
          result = 0;
        else
          result = PoS_INF;
      } else {
        if (exp == PoS_INF && base == base) result = PoS_INF;
        if (exp == NeG_INF && base == base) result = 0;
        if (base == NaN) result = NaN;
      }
    }
    if (exp == 0) result = 1;
    if ((base == 1 || base == -1) && exp == exp) result = 1;
  }
  if (flag_base == 1 && flag_exp == 1) {
    if (base < 0 && (double)exp != (long int)exp) {
      result = NaN;
    } else {
      if (base < 0) {
        if ((long int)exp % 2 != 0) sign = -1;
        base = -base;
      }
      result = sign * s21_exp(exp * s21_log(base));
    }
  }
  return result;
}

long double s21_fmod(double x, double y) {
  long double result = NULLVAL;
  long double flag_x = validate(x), flag_y = validate(y);

  if (flag_x != 1 || flag_y != 1) {
    if (x != x || y != y) result = NaN;
    if (y == 0) result = NaN;
    if (x == PoS_INF || x == NeG_INF) result = NaN;
    if (x == 0 && y != 0) result = 0;
    if ((y == PoS_INF || y == NeG_INF) && (x != PoS_INF && x != NeG_INF))
      result = x;
  } else {
    result = x - s21_trunc(x / y) * y;
  }
  return result;
}

long double s21_trunc(double x) {
  if (x < 0)
    return s21_ceil(x);
  else
    return s21_floor(x);
}

long double validate(double x) {
  long double result = 1;
  if (x == PoS_INF) result = PoS_INF;
  if (x == NeG_INF) result = NeG_INF;
  if (x != x) result = NaN;
  if (x == 0) {
    if (positive_check((long double)x))
      result = 0.;
    else
      result = -0.;
  }
  return result;
}

int positive_check(long double num) {
  double b = (double)num;
  int c = (((*((long long*)&b)) & ((long long)1 << 63)) == 0);
  return c;
}
