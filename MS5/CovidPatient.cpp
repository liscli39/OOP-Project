#include "Patient.h"
#include "CovidPatient.h"

namespace sdds {
   int nextCovidTicket = 1;

   CovidPatient::CovidPatient() : Patient(nextCovidTicket) {
      nextCovidTicket++;
   }

   char CovidPatient::type() const {
      return 'C';
   }

   std::istream &CovidPatient::csvRead(std::istream &istr) {
      Patient::csvRead(istr).ignore(1000, '\n');;
      nextCovidTicket = Patient::number() + 1;

      return istr;
   }
   std::ostream &CovidPatient::write(std::ostream &ostr) const {
      if (fileIO()) {
         Patient::csvWrite(ostr);
      } else {
         ostr << "COVID TEST" << std::endl;
         Patient::write(ostr);
         ostr << std::endl;
      }
      return ostr;
   }
   std::istream &CovidPatient::read(std::istream &istr) {
      return fileIO() ? csvRead(istr) : Patient::read(istr);
   }
}