# Direct implementation of all the C++ ClockTime() class attributes to python pyClock() class.
import pyClock as clk

#Implementation of each method:

#Initializing objects(<< and >> operators of C++ are implemented as printClock() and writeClock() respectively)
clock1 = clk.pyClock()
clock2 = clk.pyClock(50,30,21)
clock3 = clk.pyClock(50,30,21)

#Printing the result on console:
print("Hours:",clock1.hours(),"  Minutes:",clock1.minutes(),"  Seconds:",clock1.seconds(),sep="")
print(clock1.toString())
clock1.printClock()  #does the same thing as the print(<pyClock Object>.toString()) method.   

print("Hours:",clock2.hours(),"  Minutes:",clock2.minutes(),"  Seconds:",clock2.seconds(),sep="")
print(clock2.toString())

# Testing equal and lesser methods:
if (clock2.equals(clock3)):
    print("The same time can be obtained through both objects.")
else:
    print("These objects hold represent different times.")

if(clock2.lesser(clock1)):
    print("Clock 2 shows an earlier time compared to clock 1.")
else:
    print("Clock 1 shows an earlier time compared to clock 2.")

#Implementation of each operator:
clock4 = ~clock3 # clock3 = 21:30:50
clock3.printClock()
clock4.printClock()

clock5 = clock3 + clock4
clock5.printClock()

if(clock2 == clock3):
    print("Two object holds the same amount of time(==)")

if(clock2 != clock4):
    print("Two object doesn't hold the same amount of time(!=)")

if(clock3 > clock4):
    print("Rightmost object holds less time(>)")

if(clock3 < clock5):
    print("Leftmost object holds less time(<)")


if(clock3 >= clock4 and clock2 >= clock3):
    print("Two object holds the same amount of time or rightmost object holds less time(>=)")

if(clock3 <= clock2 and clock4 <= clock2):
    print("Two objects hold the same amount of time or leftmost object holds less time(<=)")









