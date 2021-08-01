#include "Patient.h"
#include "TriagePatient.h"
#include "utils.h"

namespace sdds {
   int nextTriageTicket = 1;

   TriagePatient::TriagePatient() : Patient(nextTriageTicket) {
      nextTriageTicket ++;
      C = nullptr;
   }
   TriagePatient::~TriagePatient() {
      delete [] C;
   }
   char TriagePatient::type() const {
      return 'T';
   }

   std::ostream &TriagePatient::csvWrite(std::ostream &ostr) const {
      return Patient::csvWrite(ostr) << ',' << C;
   }
   std::istream &TriagePatient::csvRead(std::istream &istr) {
      if (C != nullptr) {
         delete [] C;
      }

      Patient::csvRead(istr).ignore();
      C = getcstr(nullptr, istr, '\n');
      nextTriageTicket = Patient::number() + 1;

      return istr;
   }
   std::ostream &TriagePatient::write(std::ostream &ostr) const {
      if (fileIO()) {
         csvWrite(ostr);
      } else {
         ostr << "TRIAGE" << std::endl;
         Patient::write(ostr) << std::endl;
         ostr << "Symptoms: " << C << std::endl;
      }

      return ostr;
   }
   std::istream &TriagePatient::read(std::istream &istr) {
      if (fileIO()) {
         csvRead(istr);
      } else {
         if (C != nullptr) {
            delete [] C;
         }

         Patient::read(istr);
         std::cout << "Symptoms: ";
         C = getcstr(nullptr, istr, '\n');
      }
      
      return istr;
   }
}