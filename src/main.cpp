#include "RSA.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

template <typename T> unsigned int getline(istream &in, vector<T> &vec);
template <typename T> ostream &operator<<(ostream &out, const vector<T> &vec);

template <typename T> void getText(const string &type, T &text);
template <typename T> void printText(const string &type, const T &text);

int main() {

  RSA tool;
  string plain;
  vector<unsigned int> cipher;

  cout
      << "  ================================================================\n";
  cout << "\tRSA tool was initiated with a random key.\n";
  while (true) {
    cout
        << "  "
           "================================================================\n";
    cout << "\tChoose one of the following options:\n";
    cout << "\t1- Encrypt a plain text\n";
    cout << "\t2- Decrypt a cipher text\n";
    cout << "\t3- Set another random key\n";
    cout << "\t4- Get the current public key\n";
    cout << "\t*- Exit the program\n";
    cout << "\n\tYour choice is: " << flush;
    int choice;
    cin >> choice;
    cin.ignore();
    if (choice == 1) {
      getText("plain", plain);
      cout << "Set the public key:\n\te = " << flush;
      int e;
      cin >> e;
      cout << "\tn = " << flush;
      int n;
      cin >> n;
      cipher = tool.encrypt(plain, e, n);
      printText("cipher", cipher);
    } else if (choice == 2) {
      getText("cipher", cipher);
      plain = tool.decrypt(cipher);
      printText("plain", plain);
    } else if (choice == 3) {
      tool.setRandomKey();
      cout << "The key has been updated" << endl;
    } else if (choice == 4) {
      pair<unsigned int, unsigned int> pu = tool.getPublicKey();
      cout << '{' << pu.first << ", " << pu.second << '}' << endl;
    } else {
      break;
    }
    cout << endl;
#ifdef __unix__
    system("read -p \"Press return key to continue...\"");
    system("clear");
#else
    system("pause");
    system("cls");
#endif
  }
  cout
      << "  ================================================================\n";
  cout << "\tSad to see you go :(\n";

  return 0;
}

template <typename T> unsigned int getline(istream &in, vector<T> &vec) {
  string s;
  getline(in, s);
  stringstream ss;
  ss << s;
  T num;
  while (ss >> num)
    vec.push_back(num);
  return vec.size();
}

template <typename T> ostream &operator<<(ostream &out, const vector<T> &vec) {
  bool first = true;
  for (auto &it : vec) {
    if (first)
      first = false;
    else
      out << ' ';
    out << it;
  }
  return out;
}

template <typename T> void getText(const string &type, T &text) {
  cout << "\tSet your " << type << " text from a file? (y/N): " << flush;
  char ch;
  cin >> ch;
  cin.ignore();
  if (ch == 'y') {
    cout << "\tEnter file name: " << flush;
    string tmp;
    cin >> tmp;
    cin.ignore();
    ifstream in(tmp);
    text.clear();
    T getter;
    while (getline(in, getter))
      text.insert(text.end(), getter.begin(), getter.end());
  } else {
    cout << "\tSet your " << type << " text (in one line):\n\t" << flush;
    // The input cursor is at the last place where input was taken using cin,
    // so when we use cin.ignore(), it moves down to the current location. Not
    // using this function yields in invalid input (the line read using
    // getline will be an empty line for example).

    // getline -by default- takes input from the user until he presses the
    // return key
    getline(cin, text);
  }
}

template <typename T> void printText(const string &type, const T &text) {
  cout << "\tPrint to a file? (y/N): " << flush;
  char ch;
  cin >> ch;
  cin.ignore();
  if (ch == 'y') {
    cout << "\tEnter file name: " << flush;
    string tmp;
    cin >> tmp;
    cin.ignore();
    ofstream out(tmp);
    out << text << endl;
  } else
    cout << "\tThis is the corresponding " << type << " text:\n\t" << text
         << endl;
}
