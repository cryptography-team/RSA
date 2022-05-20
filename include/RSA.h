#ifndef RSA_HEADER
#define RSA_HEADER

#include <string>
#include <vector>

using std::pair;
using std::string;
using std::vector;

class RSA {
private:
  typedef unsigned int uint;

  uint p, q, n, phi_n, e, d;

  uint fastExponentiation(uint base, uint power) const;
  bool millerRabinIsPrime(uint num) const;
  int extendedEuclidean(int a, int b, int &x, int &y) const;
  void calculateInternals(); // calculates p, q, n, and phi_n
  void calculateExternals(); // calculates e and d

public:
  RSA();
  pair<uint, uint> getPublicKey() const;
  vector<uint> encrypt(const string &plain, const uint &e, const uint &n) const;
  string decrypt(const vector<uint> &cipher) const;
};

#endif
