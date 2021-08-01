#ifndef SDDS_PATIENT_H_
#define SDDS_PATIENT_H_
#include "IOAble.h"
#include "Ticket.h"
#include "Time.h"

namespace sdds {
  class Patient : public IOAble {
    char *m_name;
    int m_OHIP;
    Ticket m_ticket;
    bool m_fileIO;

  public:
    Patient(int ticket_number = 0, bool fileIO = false);
    ~Patient();
    virtual char type() const = 0;
    bool fileIO() const;
    void fileIO(bool fileIO);
    void setArrivalTime();
    int number() const;
    operator Time() const;
    bool operator==(const Patient &patient) const;
    bool operator==(const char c) const;

    std::ostream& csvWrite(std::ostream &ostr) const;
    std::istream& csvRead(std::istream &istr);
    std::ostream& write(std::ostream& ostr) const;
    std::istream& read(std::istream& istr);
  };
}
#endif // !SDDS_PATIENT_H_
