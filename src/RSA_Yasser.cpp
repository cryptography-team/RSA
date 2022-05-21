#include "RSA.h"
#include <chrono>

using std::uniform_int_distribution;

uint RSA::fastExponentiation(uint base, uint power, uint mod) const {
  uint res = 1;
  while (power) {
    if (power & 1)
      res = (long long)res * base % mod;
    base = (long long)base * base % mod;
    power >>= 1;
  }
  return res;
}

void RSA::calculateExternals() {
  int E, D, gcd;
  do {
    e = uniform_int_distribution<int>(2, phi_n - 1)(randomGenerator);
    gcd = extendedEuclidean(e, phi_n, E, D);
  } while (gcd != 1);

  if (E < 0)
    E += phi_n;
  d = E;
}

RSA::RSA()
    : randomGenerator(
          std::chrono::steady_clock::now().time_since_epoch().count()) {
  setRandomKey();
}

pair<uint, uint> RSA::getPublicKey() const { return pair<uint, uint>(e, n); }

void RSA::setRandomKey() {
  calculateInternals();
  calculateExternals();
}

vector<uint> RSA::encrypt(const string &plain, const uint &e,
                          const uint &n) const {
  int i = 0, size = plain.size();
  vector<uint> cipher;
  while (i + 1 < size) {
    cipher.push_back(fastExponentiation(plain[i] * 256 + plain[i + 1], e, n));
    i += 2;
  }
  if (i < size)
    cipher.push_back(fastExponentiation(plain[i] * 256, e, n));
  return cipher;
}
