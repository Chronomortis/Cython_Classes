# distutils: language = c++
from libcpp.string cimport string
from libcpp cimport bool
from cython.operator import dereference,postincrement,postdecrement 

# libcpp.iostream doesn't exist for some reason so I directly import the <iostream> library.
cdef extern from "<iostream>" namespace "std":
    cdef cppclass ostream:
        # Correct way to define an overloaded operator in Cython
        ostream& operator<<(const char* s)
        ostream& operator<<(int i)
        ostream& operator<<(double d)
        ostream& operator<<(ostream& (*func)(ostream&))
    
    cdef cppclass istream:
        istream& operator>>(char* s)
        istream& operator>>(int& i)
        istream& operator>>(double& d)

    ostream& endl(ostream& os)
    ostream cout
    istream cin


# Importing a class directly.
cdef extern from "clockt.h":
    cdef cppclass ClockTime:
        ClockTime()  except+
        ClockTime(int secs, int mins, int hours)  except+

        int     Hours()        const        
        int     Minutes()      const       
        int     Seconds()      const           
        string  tostring()     const

        bool    Equals(const ClockTime& ct) const 
        bool    Less  (const ClockTime& ct) const

        
        void Normalize()
        ClockTime operator~ ()
    
    ostream &  operator << (ostream & os, const ClockTime & ct)
    istream &  operator >> (istream & i, ClockTime & ct)
    ClockTime operator + (const ClockTime & lhs, const ClockTime & rhs)

    bool operator ==  (const ClockTime& lhs, const ClockTime& rhs)
    bool operator !=  (const ClockTime& lhs, const ClockTime& rhs)
    bool operator <   (const ClockTime& lhs, const ClockTime& rhs)
    bool operator >   (const ClockTime& lhs, const ClockTime& rhs)
    bool operator <=  (const ClockTime& lhs, const ClockTime& rhs)
    bool operator >=  (const ClockTime& lhs, const ClockTime& rhs)

    bool operator >=  (const int & lhs, const ClockTime & rhs)


cdef void write_to_istream(istream &i, pyClock clock):
    i >> dereference(clock.c_clock)

cdef void print_to_ostream(ostream& os, pyClock clock):
    os << dereference(clock.c_clock) << endl


cdef class pyClock:
    #Using a pointer is necessary when there isn't a nullary constructor but it can be used in all instances.
    cdef ClockTime * c_clock 

    #Constructors and Destructors are defined
    
    def __cinit__(self,int secs=0,int mins=0,int hours=0):
        if(secs == 0  and  mins == 0  and  hours == 0):
            self.c_clock = new ClockTime()
        elif(secs != 0  and  mins != 0  and  hours != 0):
            self.c_clock = new ClockTime(secs,mins,hours)

    def __dealloc__(self):
        del self.c_clock
        self.c_clock = NULL

    #Methods are defined.

    def hours(self):
        return self.c_clock.Hours()

    def minutes(self):
        return self.c_clock.Minutes()

    def seconds(self):
        return self.c_clock.Seconds()

    def toString(self):
        return self.c_clock.tostring().decode('utf-8')

    def equals(self, pyClock other):
        return self.c_clock.Equals(dereference(other.c_clock))
    
    def lesser(self, pyClock other):
        return self.c_clock.Less(dereference(other.c_clock))

    cdef normalize(self):
        return self.c_clock.Normalize()
    
    
    # I had to this manually instead of direct approach.
    def __invert__(self):
        cdef pyClock result = pyClock()
        cdef int sec = 60 - dereference(self.c_clock).Seconds()
        cdef int min = 60 - dereference(self.c_clock).Minutes()
        cdef int hour = dereference(self.c_clock).Hours() 
        result.c_clock = new ClockTime(sec,min,hour)
        return result
        

    def printClock(pyClock p_clock):
        print_to_ostream(cout,p_clock)

    def writeClock(pyClock p_clock):
        write_to_istream(cin,p_clock)

    def __add__(self, pyClock other):
        cdef ClockTime result = dereference(self.c_clock) + dereference(other.c_clock)
        cdef pyClock p_clock = pyClock()
        p_clock.c_clock = new ClockTime(result.Seconds(),result.Minutes(),result.Hours())
        return p_clock

    def __eq__(self, pyClock other):
            cdef bool result = (dereference(self.c_clock) == dereference(other.c_clock))
            return result
        
    def __ne__(self, pyClock other):
        cdef bool result = (dereference(self.c_clock) != dereference(other.c_clock))
        return result
        
    def __lt__(self, pyClock other):
        cdef bool result = (dereference(self.c_clock) < dereference(other.c_clock))
        return result
        
    def __rt__(self, pyClock other):
        cdef bool result = (dereference(self.c_clock) > dereference(other.c_clock))
        return result
        
    def __le__(self, pyClock other):
        cdef bool result = (dereference(self.c_clock) <= dereference(other.c_clock))
        return result

    def __ge__(self, pyClock other):
        cdef bool result = (dereference(self.c_clock) >= dereference(other.c_clock))
        return result
    
    
    


    
