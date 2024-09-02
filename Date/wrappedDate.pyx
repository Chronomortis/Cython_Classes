# distutils: language = c++
from libcpp.string cimport string
from libcpp cimport bool
from cython.operator import dereference,postincrement,postdecrement


cdef extern from "<iostream>" namespace "std":
    cdef cppclass ostream:
        # Correct way to define an overloaded operator in Cython
        ostream& operator<<(const char* s)
        ostream& operator<<(int i)
        ostream& operator<<(double d)
        ostream& operator<<(ostream& (*func)(ostream&))
    ostream& endl(ostream& os)
    ostream cout


cdef extern from "date.h":
    cdef cppclass Date:
        
        Date()                       
        Date(long days)          
        Date(int m, int d, int y)      

                

        int Month()          const    
        int Day()            const    
        int Year()           const     
        int DaysIn()         const    
        string DayName()     const    
        string MonthName()   const     
        long Absolute()      const     
        string ToString()    const    

        bool Equal(const Date& rhs) const 
        bool Less(const Date& rhs) const

        

        Date operator ++(int)         
        Date operator --(int)         
        #Date & operator +=(long dx)     These two aren't supported by Cython.
        #Date& operator -=(long dx)      These two aren't supported by Cython.

       
        Date operator + (const Date& d, long dx)   # add dx to date d
        Date operator + (long dx, const Date& d)   # add dx to date d
        Date operator - (const Date& d, long dx)   # subtract dx from date d
        long operator - (const Date& lhs, const Date& rhs)

        ostream& operator << (ostream& os, const Date& d);
        bool operator == (const Date& lhs, const Date& rhs);
        bool operator != (const Date& lhs, const Date& rhs);
        bool operator <  (const Date& lhs, const Date& rhs);
        bool operator >  (const Date& lhs, const Date& rhs);
        bool operator <= (const Date& lhs, const Date& rhs);
        bool operator >= (const Date& lhs, const Date& rhs);
        

cdef class pyDate:
    cdef Date *c_date

    def __cinit__(self,month_or_total=0,int day=0,int year=0):
        if(month_or_total==0 and day==0 and  year==0):
            self.c_date = new Date()
        elif(day==0 and year==0):
            self.c_date = new Date(month_or_total)
        elif(year!=0):
            self.c_date = new Date(month_or_total,day,year)
        
        
    def __dealloc__(self):
        del self.c_date
    
    #Accessor functions are straightforward.
    
    def Month(self):
        return self.c_date.Month()
    
    def Day(self):
        return self.c_date.Day()
    
    def Year(self):
        return self.c_date.Year()
    
    def DaysIn(self):
        return self.c_date.DaysIn()
    
    def DayName(self):
        return self.c_date.DayName().decode('utf-8')
    
    def MonthName(self):
        return self.c_date.MonthName().decode('utf-8')
    
    def Absolute(self):
        return self.c_date.Absolute()

    def ToString(self):
        return self.c_date.ToString().decode('utf-8')

    def Equal(self,pyDate another_date):
        return self.c_date.Equal(dereference(another_date.c_date))
    
    def Less(self,pyDate another_date):
        return self.c_date.Less(dereference(another_date.c_date))
    
    def __pos__(self): # for ++ in date.cpp class, so C++: p++ -> python: +p
        new_date = self
        postincrement(dereference(new_date.c_date))
        return new_date
    
    def __neg__(self): # # for -- in date.cpp class, so C++: p-- -> python: -p
        new_date = self
        postdecrement(dereference(new_date.c_date))
        return new_date

    def __add__(self,long other):
        p_date = pyDate()
        p_date.c_date = new Date(self.c_date.Absolute() + other)
        return p_date
    
    def __radd__(self, other):
        return self.__add__(other)
        
    def __sub__(self,other):
        if isinstance(other,pyDate):
            result = self.Absolute() - other.Absolute()
            return result
        elif isinstance(other,int):
            self.c_date = new Date(self.c_date.Absolute() - other)
            return self
        return NotImplemented
    def __eq__(self, pyDate other):
        cdef bool result = (dereference(self.c_date) == dereference(other.c_date))
        return result
    
    def __ne__(self, pyDate other):
        cdef bool result = (dereference(self.c_date) != dereference(other.c_date))
        return result
    
    def __lt__(self, pyDate other):
        cdef bool result = (dereference(self.c_date) < dereference(other.c_date))
        return result
    
    def __rt__(self, pyDate other):
        cdef bool result = (dereference(self.c_date) > dereference(other.c_date))
        return result
    
    def __le__(self, pyDate other):
        cdef bool result = (dereference(self.c_date) <= dereference(other.c_date))
        return result

    def __ge__(self, pyDate other):
        cdef bool result = (dereference(self.c_date) >= dereference(other.c_date))
        return result

    #A function to directly print dates:
    
cdef void print_to_ostream(ostream& os, pyDate date):
    os << dereference(date.c_date) << endl

def printDate(pyDate p_date):
    print_to_ostream(cout,p_date)

        

   