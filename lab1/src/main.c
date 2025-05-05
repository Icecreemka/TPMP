#include <stdio.h>
#include <stdlib.h>

int main() {
  double a, b, c;
  double res1, res2, res3;
  double sa, sb, sc;

  printf("Enter sides a, b, c:\n");

  int read = scanf("%lf %lf %lf", &a, &b, &c);
  if (read != 3) {
    printf("Invalid input. Please enter three numbers.\n");
    return 1; 
  }

  if (!(a + b > c && a + c > b && b + c > a)) {
    printf("Triangle with sides: %.0lf, %.0lf, %.0lf doesn't exist", a, b, c);
    return 0;
  }

  sa = a * a;
  sb = b * b;
  sc = c * c;

  res1 = (sa - sb - sc) / (-2 * b * c);
  res2 = (sb - sa - sc) / (-2 * a * c);
  res3 = (sc - sa - sb) / (-2 * a * b);
  if (res1 <= 0 || res2 <= 0 || res3 <= 0) {
    printf("Triangle with sides: %.0lf, %.0lf, %.0lf isn't acute-angled", a, b, c);
  } else {
    printf("Triangle with sides: %.0lf, %.0lf, %.0lf is acute-angled", a, b, c);
  }
	return 0;
}