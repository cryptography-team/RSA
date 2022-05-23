#ifndef RSA_HEADER
#define RSA_HEADER

#include <random>
#include <string>
#include <vector>

using std::mt19937;
using std::pair;
using std::string;
using std::vector;

class RSA {
private:
  typedef unsigned int uint;

  uint p, q, n, phi_n, e, d;
  mt19937 randomGenerator;

  uint fastExponentiation(uint base, uint power, uint mod) const;
  bool millerRabinIsPrime(uint n);
  int extendedEuclidean(int a, int b, int &x, int &y) const;
  uint getRandomPrimeNumber(const uint &start, const uint &end);
  void calculateInternals(); // calculates p, q, n, and phi_n
  void calculateExternals(); // calculates e and d

public:
  RSA();
  pair<uint, uint> getPublicKey() const;
  void setRandomKey();
  vector<uint> encrypt(const string &plain, const uint &e, const uint &n) const;
  string decrypt(const vector<uint> &cipher) const;
};

#endif
