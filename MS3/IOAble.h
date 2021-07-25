#ifndef SDDS_IOABLE_H
#define SDDS_IOABLE_H
#include <iostream>

namespace sdds {
  class IOAble {
  public:
    virtual std::ostream& csvWrite(std::ostream &ostr) const;
    virtual std::istream& csvRead(std::istream &istr);
    virtual std::ostream& write(std::ostream& ostr) const;
    virtual std::istream& read(std::istream& istr);
    virtual ~IOAble();
  };

  std::ostream& operator<<(std::ostream& ostr, IOAble&);
  std::istream& operator>>(std::istream& istr, IOAble&);
}

#endif // !SDDS_IOABLE_H
