# Direct implementation of all the C++ Date() class attributes to python pyDate() class.
import pyDate

#Implementation of each method:
dat = pyDate.pyDate(5,12,2003)   # American-style dates
print(dat.Day(),dat.Month(),dat.Year(),end="\n")
print(dat.DayName(),dat.MonthName(),end="\n")
print(dat.Absolute())
print(dat.ToString())

#Implementation of each operation(except -= and += as they aren't supported by cython):
dat2 =  dat + 3
+dat2   # equivalent of dat2++
print(dat2.ToString())
-dat2   # equivalent of dat2--
print(dat2.ToString())
dat2 = dat2 + 2
print(dat2.ToString())

dat3 = dat2 - dat # Subtraction between two dates, returning a long value
print(dat3)

dat4 = dat2 - 1 # Subtraction of a date from a number, resulting in another date value.
print(dat4.Day(),dat4.Month(),dat4.Year())

date1 = pyDate.pyDate(4,3,2009)
date2 = pyDate.pyDate(4,3,2009)
if(date1 == date2):
    print("These two dates are the same(==)")

date2 = date2 + 5

if(date1 != date2):
    print("These two dates are not the same(!=)")


if(date1 < date2):
    print("Date 2 is at a later point in time compared to date 1.(<)")

date1 = date1 + 10

if(date1 > date2):
    print("Date 1 is at a later point in time compared to date 2.(>)")

date2 = date2 + 5

# These operations are tested when date1 == date2
if(date1 >= date2):
    print("Date 1 is either at a later point in time compared to date 2 or these are the same dates.(>=)")

if(date1 <= date2):
    print("Date 2 is either at a later point in time compared to date 1 or these are the same dates.(<=)")

#Tested in date1 > date2 case
date1 = date1 + 1
if(date1 >= date2):
    print("Date 1 is either at a later point in time compared to date 2 or these are the same dates.(>=)")

#Tested in date1 < date2 case
date2 = date2 + 3
if(date1 <= date2):
    print("Date 2 is either at a later point in time compared to date 1 or these are the same dates.(<=)")


#A function that directly prints dates from pyDate class, just like overloaded "<<" operation in Date class.
pyDate.printDate(date1)
pyDate.printDate(date2)
pyDate.printDate(dat)




