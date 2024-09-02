#ifndef _CLOCKTIME_H
#define _CLOCKTIME_H

#include <iostream>
#include <string>
using namespace std;

// class for manipulating "clock time", time given in hours, minutes, seconds
// class supports only construction, addition, Print() and output <<
//
// Owen Astrachan: written May 25, 1994
//                 modified Aug 4, 1994, July 5, 1996, April 29, 1999
//
// ClockTime(int secs, int mins, int hours)
//      -- normalized to <= 60 secs, <= 60 mins
//
//      access functions
//
//      Hours()    -- returns # of hours in ClockTime object
//      Minutes()  -- returns # of minutes in ClockTime object
//      Seconds()  -- returns # of seconds in ClockTime object
//      tostring() -- time in format h:m:s
//                    (with :, no space, zero padding)    
//
//      operators (for addition and output)
//
//      ClockTime & operator +=(const ClockTime & ct)
//      ClockTime operator +(const ClockTime & a, const ClockTime & b)
//
//      ostream & operator <<(ostream & os, const ClockTime & ct)
//           inserts ct into os, returns os, uses Print()

class ClockTime
{
  public:
    ClockTime();
    ClockTime(int secs, int mins, int hours);

	//Destructor and Copy Constructor are normally not necessary, added to show some special cases
	//~ClockTime();
	//ClockTime::ClockTime (const ClockTime & copy);

    int     Hours()        const;        // returns # hours
    int     Minutes()      const;        // returns # minutes
    int     Seconds()      const;        // returns # seconds   
    string  tostring()     const;        // converts to string
    
    bool    Equals(const ClockTime& ct) const; // true if == ct
    bool    Less  (const ClockTime& ct) const; // true if < ct
	
    const ClockTime & operator +=(const ClockTime & ct);
    void Normalize();        // < 60 secs, < 60 min

    //added by Albert Levi to exemplify unary operators - March 31, 2024
    ClockTime operator~ ();

  private:

    int mySeconds;           // constrained: 0-59    
    int myMinutes;           // constrained: 0-59
    int myHours;


  //added by Albert Levi - July 20, 2011
  //free friend function that adds lhs hours to rhs and returns 
  //the resulting clock value
  friend ClockTime operator +  (int lhs, const ClockTime& rhs);
  //friend int main();  //NEVER DO THIS
};


// free functions, not member functions
ostream &  operator << (ostream & os, const ClockTime & ct);

//added by Albert Levi March 24, 2015 - March 31, 2024
istream &  operator >> (istream & is, ClockTime & ct);

ClockTime operator + (const ClockTime & lhs, const ClockTime & rhs);
                //Make the return type   ClockTime &    to experince segmentation fault error

bool operator ==  (const ClockTime& lhs, const ClockTime& rhs);
bool operator !=  (const ClockTime& lhs, const ClockTime& rhs);
bool operator <   (const ClockTime& lhs, const ClockTime& rhs);
bool operator >   (const ClockTime& lhs, const ClockTime& rhs);
bool operator <=  (const ClockTime& lhs, const ClockTime& rhs);
bool operator >=  (const ClockTime& lhs, const ClockTime& rhs);

bool operator >=  (const int & lhs, const ClockTime & rhs);


#endif
