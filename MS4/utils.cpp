#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cstring>
#include "utils.h"
#include "Time.h"
using namespace std;
namespace sdds {
  bool debug = false; // made global in utils.h
  int getTime() {
    int mins = -1;
    if (debug) {
      Time t(0);
      cout << "Enter current time: ";
      do {
        cin.clear();
        cin >> t; // needs extraction operator overloaded for Time
        if (!cin) {
          cout << "Invlid time, try agian (HH:MM): ";
          cin.clear();
        } else {
          mins = int(t);
        }

        cin.ignore(1000, '\n');
      } while (mins < 0);
    } else {
      mins = 1063;
    }
    return mins;
  }

  void clearStandardInputBuffer(void) {
    while (getchar() != '\n') {}
  }

  int getInt(const char *prompt) {
    int number = 0;
    char c;
    bool negative = false;

    if (prompt != nullptr) {
      cout << prompt;
    }

    do {
      c = getchar();
      if (number == 0 && c == '-') {
        negative = true;
      } else if (c >= '0' && c <= '9') {
        number = number * 10 + (c - '0');
      } else if (c != '\n') {
        if (number == 0) {
          cout << "Bad integer value, try again: ";
        }
        else {
          cout << "Enter only an integer, try again: ";
        }

        clearStandardInputBuffer();
        number = 0;
      }
    } while (c != '\n');

    number = negative ? - number : number;
    return number;
  }

  int getInt(int min, int max, const char *prompt, const char *errorMessage, bool showRangeAtError) {
    int number;
    cout << prompt;
    do {
      number = getInt();
      if (number < min || number > max) {
        cout << errorMessage;
        if (showRangeAtError) {
          cout << "[" << min << " <= value <= " << max << "]: ";
        }
      }
    } while (number < min || number > max);

    return number;
  }

  char *getcstr(const char *prompt, istream &istr, char delimiter) {
    if (prompt != nullptr) {
      cout << prompt;
    }

    char *str = nullptr;
    char *tmp = nullptr;
    char c;
    int l = 0;

    do {
      istr.get(c);
      if (c != delimiter && c != '\n' && !istr.eof()) {
        if (str != nullptr) {
          delete[] str;
        }
        str = new char[++l + 1];

        if (tmp != nullptr) {
          strcpy(str, tmp);
          delete[] tmp;
        }

        str[l - 1] = c;
        str[l] = '\0';

        tmp = new char[l + 1];
        strcpy(tmp, str);
      }
    } while (c != delimiter && !istr.eof());

    return str;
  }
}
