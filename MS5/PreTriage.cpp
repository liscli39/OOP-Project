#include <string.h>
#include <fstream>

#include "PreTriage.h"
#include "CovidPatient.h"
#include "TriagePatient.h"
#include "Time.h"
#include "Menu.h"
#include "utils.h"

using namespace std;
namespace sdds {
  void PreTriage::reg() {
    if (m_lineupSize >= maxNoOfPatients) {
      cout << "Line up full!" << endl;
    } else {
      int selection;
      m_pMenu >> selection;
      switch (selection) {
      case 1:
        m_lineup[m_lineupSize] = new CovidPatient();
        break;
      case 2:
        m_lineup[m_lineupSize] = new TriagePatient();
        break;
      default:
        break;
      }

      if (selection == 1 || selection == 2) {
        m_lineup[m_lineupSize]->setArrivalTime();
        m_lineup[m_lineupSize]->fileIO(false);
        cout << "Please enter patient information: " << endl;
        cin >> *(m_lineup[m_lineupSize]);
        cout << endl << "******************************************" << endl;
        cout << *(m_lineup[m_lineupSize]);
        cout << "Estimated Wait Time: " << getWaitTime(*(m_lineup[m_lineupSize])) << endl;
        cout << "******************************************\n" << endl;
        m_lineupSize ++;
      }
    }
  }
  void PreTriage::admit() {
    int selection;
    char type;
    m_pMenu >> selection;
    switch (selection) {
    case 1:
      type = 'C';
      break;
    case 2:
      type = 'T';
      break;
    default:
      break;
    }

    if (selection == 1 || selection == 2) {
      int index = indexOfFirstInLine(type);
      if (index != -1) {
        cout << endl << "******************************************" << endl;
        m_lineup[index]->fileIO(false);
        cout << "Calling for ";
        cout << *(m_lineup[index]);
        cout << "******************************************\n" << endl;
        setAverageWaitTime(*(m_lineup[index]));
        removePatientFromLineup(index);
      }
    }

  }
  const Time PreTriage::getWaitTime(const Patient& p)const {
    Time waitTime;
    for (int i = 0; i < m_lineupSize; i++) {
      if (m_lineup[i]->type() == p.type()) {
        waitTime += Time(*m_lineup[i]);
      }
    }

    return waitTime;
  }
  void PreTriage::setAverageWaitTime(const Patient& p) {
    Time current;
    current.setToNow();

    Time awt;
    if (p.type() == 'C') {
      m_averCovidWait = ((current - Time(p)) + (m_averCovidWait * (p.number() - 1))) / p.number();
    } else {
      m_averTriageWait = ((current - Time(p)) + (m_averTriageWait * (p.number() - 1))) / p.number();
    }
  }
  void PreTriage::removePatientFromLineup(int index) {
    removeDynamicElement(m_lineup, index, m_lineupSize);
  }
  int PreTriage::indexOfFirstInLine(char type) const {
    int index = -1, i = 0;
    do {
      if (m_lineup[i]->type() == type) {
        index = i;
      }
    } while (index != i && m_lineupSize > i++);

    return index;
  }
  void PreTriage::load() {
    cout << "Loading data..." << endl;
    ifstream fin(m_dataFilename);

    fin >> m_averCovidWait;
    fin.ignore();
    fin >> m_averTriageWait;
    fin.ignore(1000, '\n');

    while (!fin.eof() && m_lineupSize < maxNoOfPatients) {
      char type = '\0';
      fin >> type;
      fin.ignore();
      
      if (type == 'C') {
        m_lineup[m_lineupSize] = new CovidPatient();
      } else {
        m_lineup[m_lineupSize] = new TriagePatient();
      }
      
      if (type == 'C' || type == 'T') {
        m_lineup[m_lineupSize]->fileIO(true);
        fin >> *(m_lineup[m_lineupSize]);
        m_lineup[m_lineupSize]->fileIO(false);
        m_lineupSize ++;
      }
    }

    if (!fin.eof() && m_lineupSize >= maxNoOfPatients) {
      cout << "Warning: number of records exceeded " << maxNoOfPatients << endl;
      cout << m_lineupSize << " Records imported..." << endl;
    } else if (m_lineupSize == 0) {
      cout << "No data or bad data file!" << endl;
    } else {
      cout << m_lineupSize << " Records imported..." << endl;
    }

    cout << endl;
  }

  // public
  PreTriage::PreTriage(const char* dataFilename) : 
    m_appMenu("General Hospital Pre-Triage Application\n1- Register\n2- Admit", 2),
    m_pMenu("Select Type of Admittance:\n1- Covid Test\n2- Triage", 2),
    m_averCovidWait(15),
    m_averTriageWait(5)
  {
    m_dataFilename = new char[strlen(dataFilename) + 1];
    strcpy(m_dataFilename, dataFilename);

    load();
  }
  PreTriage::~PreTriage() {
    ofstream fout(m_dataFilename);
    fout << m_averCovidWait << "," << m_averTriageWait << endl;
    cout << "Saving Average Wait Times," << endl
         << "   COVID Test: " << m_averCovidWait << endl
         << "   Triage: " << m_averTriageWait << endl;

    cout << "Saving lineup..." << endl;
    for (int i = 0; i < m_lineupSize; i++) {
      m_lineup[i]->fileIO(true);
      fout << *(m_lineup[i]) << endl;
      cout << (i + 1) << "- " << *(m_lineup[i]) << endl;
      delete m_lineup[i];
    }

    fout.close();
    if (m_dataFilename != nullptr) {
      delete [] m_dataFilename;
    }

    cout << "done!" << endl;
  }
  void PreTriage::run(void) {
    int selection;
    while (m_appMenu >> selection) {
      switch (selection) {
      case 1:
        reg();
        break;
      case 2:
        admit();
        break;
      default:
        break;
      }
    }
  }
}