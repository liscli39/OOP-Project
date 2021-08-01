#include <string.h>
#include <iomanip>
#include "Patient.h"
#include "utils.h"
using namespace std;

namespace sdds {
  Patient::Patient(int ticket_number, bool fileIO) : m_ticket(ticket_number) {
    m_name = nullptr;
    m_fileIO = fileIO;
    m_OHIP = 0;
  }
  Patient::~Patient() {
    delete [] m_name;
  }
  bool Patient::fileIO() const{
    return m_fileIO;
  }
  void Patient::fileIO(bool fileIO) {
    m_fileIO = fileIO;
  }
  void Patient::setArrivalTime() {
    m_ticket.resetTime();
  }
  int Patient::number() const{
    return m_ticket.number();
  }
  Patient::operator Time() const {
    return Time(m_ticket);
  }

  bool Patient::operator==(const Patient &patient) const{
    return type() == patient.type();
  }
  bool Patient::operator==(const char c) const{
    return type() == c;
  }

  std::ostream& Patient::csvWrite(std::ostream &ostr) const {
    ostr << type() << ','<< m_name  << ',' << m_OHIP << ',';
    return m_ticket.csvWrite(ostr);
  }
  std::istream& Patient::csvRead(std::istream &istr) {
    if (m_name != nullptr) {
      delete [] m_name;
    }

    m_name = getcstr(nullptr, istr, ',');

    istr >> m_OHIP;
    istr.ignore();
    
    m_ticket.csvRead(istr);

    return istr;
  }
  std::ostream& Patient::write(std::ostream& ostr) const {
    m_ticket.write(ostr) << endl;
    if (strlen(m_name) > 25) {
      for (int i = 0; i < 25; i++) ostr << m_name[i];
    } else {
      ostr << m_name;
    }

    ostr << ", OHIP: " << m_OHIP;
    return ostr;
  }
  std::istream& Patient::read(std::istream& istr) {
    if (m_name != nullptr) {
      delete [] m_name;
    }
    m_name = getcstr("Name: ", istr);
    m_OHIP = getInt(100000000, 999999999, "OHIP: ", "Invalid OHIP Number, ", true);
    return istr;
  }
}