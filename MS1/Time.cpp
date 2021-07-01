#include "Time.h"
#include "utils.h"
using namespace std;
namespace sdds
{
  Time &Time::setToNow()
  {
    m_min = getTime();
  }
  Time::Time(unsigned int min)
  {
    m_min = min;
  }
  ostream &Time::write(ostream &ostr) const
  {
    int minute = m_min % 60;
    int hour = (m_min - minute) / 60;

    if (hour < 10) {
      ostr << "0" << hour;
    } else {
      ostr << hour;
    }
    ostr << ":";
    if (minute < 10) {
      ostr << "0" << minute;
    } else {
      ostr << minute;
    }

    return ostr;
  }
  istream &Time::read(istream &istr)
  {
    char c = '\n';
    int l = 0;
    int hour = 0;
    int minute = 0;
    bool change = false;

    do
    {
      istr.get(c);
      if (c != '\n' && ((c >= '0' && c <= '9') || c == ':'))
      {
        if (c == ':')
        {
          change = true;
        }
        else if (change)
        {
          minute = minute * 10 + (c - '0');
        }
        else
        {
          hour = hour * 10 + (c - '0');
        }
      }
      else if (c != '\n')
      {
        istr.setstate(ios::failbit);
      }
    } while (c != '\n' && ((c >= '0' && c <= '9') || c == ':'));

    if (!istr.fail()) {
      m_min = hour * 60 + minute;
    }

    return istr;
  }
  Time &Time::operator-=(const Time &D)
  {
    while (m_min < D.m_min)
    {
      m_min += 24 * 60;
    }

    m_min -= D.m_min;
    return *this;
  }
  Time Time::operator-(const Time &D) const
  {
    Time t(m_min);

    while (t.m_min < D.m_min)
    {
      t.m_min += 24 * 60;
    }

    t.m_min -= D.m_min;

    return t;
  }
  Time &Time::operator+=(const Time &D)
  {
    m_min += D.m_min;
    return *this;
  }
  Time Time::operator+(const Time &D) const
  {
    Time t(m_min + D.m_min);
    return t;
  }
  Time &Time::operator=(unsigned int val)
  {
    m_min = val;
    return *this;
  }
  Time &Time::operator*=(unsigned int val)
  {
    m_min *= val;
    return *this;
  }
  Time &Time::operator/=(unsigned int val)
  {
    m_min /= val;
    return *this;
  }
  Time Time::operator*(unsigned int val) const
  {
    Time t(m_min * val);
    return t;
  }
  Time Time::operator/(unsigned int val) const
  {
    Time t(m_min / val);
    return t;
  }
  Time::operator unsigned int() const
  {
    return m_min;
  }
  Time::operator int() const
  {
    return m_min;
  }
  ostream &operator<<(ostream &ostr, const Time &D)
  {
    D.write(ostr);
    return ostr;
  }
  istream &operator>>(istream &istr, Time &D)
  {
    D.read(istr);
    return istr;
  }
}