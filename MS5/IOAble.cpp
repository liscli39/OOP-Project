#include "IOAble.h"
#include "utils.h"
#include <string.h>

using namespace std;
namespace sdds {
    ostream& IOAble::csvWrite(ostream &ostr) const{
      return ostr;
    }
    istream& IOAble::csvRead(istream &istr) {
      return istr;
    }
    ostream& IOAble::write(ostream& ostr) const{
      return ostr;
    }
    istream& IOAble::read(istream& istr) {
      return istr;
    }
    IOAble::~IOAble() { }

    ostream& operator<<(ostream& ostr, IOAble& io) {
      return io.write(ostr);
    }
    
    istream& operator>>(istream& istr, IOAble& io) {
      return io.read(istr);
    }
}