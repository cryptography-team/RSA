#include "RSA.h"

using std::uniform_int_distribution;

bool RSA::millerRabinIsPrime(uint n) {
  if (n == 2)
    return true;
  if (n < 2 || n % 2 == 0)
    return false;

  uint num = n - 1, k = 0;
  while (num % 2 == 0) {
    k++;
    num /= 2;
  }
  uint q = num;

  uint a = uniform_int_distribution<int>(1, n - 1)(randomGenerator);
  a = fastExponentiation(a, q, n);
  if (a == 1)
    return true;

  for (uint j = 0; j < k; j++, a = (long long)a * a % n) {
    if (a == n - 1)
      return true;
  }
  return false;
}

int RSA::extendedEuclidean(int a, int b, int &x, int &y) const {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }

  int gcd = extendedEuclidean(b, a % b, y, x);

  y -= a / b * x;

  return gcd;
}

uint RSA::getRandomPrimeNumber(const uint &start, const uint &end) {
  uint num = 0;
  while (num == 0) {
    num = uniform_int_distribution<int>(start, end)(randomGenerator);
    for (int i = 0; i < 10; i++)
      if (!millerRabinIsPrime(num)) {
        num = 0;
        break;
      }
  }
  return num;
}

void RSA::calculateInternals() {
  p = getRandomPrimeNumber(100, 10000);
  q = getRandomPrimeNumber((1 << 15) / p, (1 << 16) / p);

  n = p * q;
  phi_n = (p - 1) * (q - 1);
}

string RSA::decrypt(const vector<uint> &cipher) const {
  string plain;
  for (uint c : cipher) {
    c = fastExponentiation(c, d, n);
    plain += char(c / 256);
    plain += char(c % 256);
  }
  return plain;
}
