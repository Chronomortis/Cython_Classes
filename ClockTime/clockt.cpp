#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

#include "clockt.h"
#include "time.h"

/*********************************************************************/
ClockTime::ClockTime()
{
    static struct tm timeHolder;
    static struct tm *date = &timeHolder;
    time_t tloc;
    
    time(&tloc);

    date = localtime(&tloc);
    
    mySeconds= date->tm_sec;
    myMinutes= date->tm_min;
    myHours=   date->tm_hour;
}


/*********************************************************************/
ClockTime::ClockTime(int secs, int mins, int hours)
  : mySeconds(secs), myMinutes(mins), myHours(hours)
// postcondition: all data fields initialized     
{
    Normalize();
}

//Normally not necessary, added to show some special cases
/*ClockTime::~ClockTime()
{
	mySeconds = myMinutes = myHours = 0;
}*/

//Normally not necessary, added to show some special cases
/*ClockTime::ClockTime (const ClockTime & copy)
	: mySeconds(copy.mySeconds), myMinutes(copy.myMinutes), myHours(copy.myHours)  
{
    Normalize();
}*/

/*********************************************************************/
int ClockTime::Hours() const
// postcondition: return # of hours
{
    return myHours;
}

int ClockTime::Minutes() const
// postcondition: return # of minutes
{
    return myMinutes;
}

int ClockTime::Seconds() const
// postcondition: return # of seconds
{
    return mySeconds;
}

/*********************************************************************/
string ClockTime::tostring() const
{
    ostringstream os;
    os.fill('0');
    os << Hours() << ":" << setw(2) << Minutes() << ":"
       << setw(2) << Seconds();
    
    return os.str();
}

/*********************************************************************/
ostream & operator << (ostream & os, const ClockTime & ct)
// postcondition: inserts ct onto os, returns os
//                format is h:m:s     
{
    ostringstream ostr;
    ostr.fill('0');

	//int h = ct.Hours();
	//int m = ct.Minutes();

    ostr << ct.Hours() << ":" << setw(2) << ct.Minutes() << ":"
       << setw(2) << ct.Seconds();

    //os << ct.tostring();
	os << ostr.str();
    return os;
}

/*********************************************************************/
void ClockTime::Normalize()
{
    myMinutes += mySeconds/60;    // overflow from secs to myMinutes
    mySeconds %= 60;              // now between 0 and 59
    
    myHours += myMinutes/60;      // overflow from myMinutes to myHours
    myMinutes %= 60;              // now between 0 and 59
}

/*********************************************************************/
const ClockTime & ClockTime::operator += (const ClockTime & ct)
// postcondition: add ct, return result (normalized for myMinutes, mySeconds)
{
    mySeconds += ct.mySeconds;           
    myMinutes += ct.myMinutes;
    myHours   += ct.myHours;
    Normalize();
    
    return *this;
}


/*********************************************************************/
//Make the return type   ClockTime &    to experince segmentation fault error
ClockTime operator + (const ClockTime & lhs, const ClockTime & rhs)
// postcondition: return lhs + rhs (normalized for myMinutes, mySeconds)
{
    ClockTime result(lhs);
	result += rhs;
    return result;
}

/*********************************************************************/
bool ClockTime::Equals(const ClockTime& c) const
// postcondition: returns true iff == c
{
    return Hours() == c.Hours() && 
           Minutes() == c.Minutes() &&
           Seconds() == c.Seconds();
}

bool ClockTime::Less(const ClockTime& c) const
// postcondition: returns true iff < c
{
    return ( Hours() < c.Hours() ) ||
           ( ( Hours() == c.Hours() ) && 
               ( ( Minutes() < c.Minutes() ) ||
                 ( ( Minutes() == c.Minutes() ) && ( Seconds() < c.Seconds() ) )
               )
           );
}


bool operator == (const ClockTime& lhs, const ClockTime& rhs)
{
    return lhs.Equals(rhs);
}

bool operator != (const ClockTime& lhs, const ClockTime& rhs)
{
    return ! (lhs == rhs);
}

bool operator <  (const ClockTime& lhs, const ClockTime& rhs)
{
    return lhs.Less(rhs);
}

bool operator >  (const ClockTime& lhs, const ClockTime& rhs)
{
    return rhs < lhs;
}

bool operator <=  (const ClockTime& lhs, const ClockTime& rhs)
{
    return ! (lhs > rhs);
}

bool operator >=  (const ClockTime& lhs, const ClockTime& rhs)
{
    return ! (lhs < rhs);
}

bool operator >= (const int & lhs, const ClockTime & rhs)
{
    ClockTime temp(0, 0, lhs);
    return temp >= rhs;
}



//added by Albert Levi - July 20, 2011
//implementation of friend function operator+
ClockTime operator +  (int lhs, const ClockTime& rhs)
{
	ClockTime temp (rhs.mySeconds, rhs.myMinutes, rhs.myHours + lhs);
	return temp;
}

//added by Albert Levi March 24, 2015
//modified by Albert Levi March 31, 2024
istream &  operator >> (istream & is, ClockTime & ct)
//postcondition: reads private members of ct from is, and normalize ct
//				 returns is
{
    int hr, min, sec;
	is >> hr >> min >> sec;
    ClockTime temp (sec, min, hr);
	temp.Normalize();
    ct=temp;
	return is;
}

//added by Albert Levi to exemplify unary operators - March 31, 2024
//return another ClockTime object by subtracting the operator's seconds and minutes from 60
ClockTime ClockTime::operator~ ()
{
    ClockTime temp(60-mySeconds, 60-myMinutes, myHours);
    return temp;
}
