# distutils: language = c++
from libcpp.string cimport string
from libcpp cimport bool
from cython.operator import dereference,postincrement,postdecrement

cdef extern from "account.h":
    cdef cppclass Account:
        Account(double initial_balance) except +
        void deposit(double amount) except +
        void withdraw(double amount) except +
        double get_balance() except + #const and except + at the same time doesn't work due to the cython's limitations.


cdef class pyAccount:
    cdef Account *c_acc # It has to be done this way as Account class doesn't have a default constructor.
    def __cinit__(self,double init_bal):
        self.c_acc = new Account(init_bal)

    def __dealloc__(self):
        del self.c_acc

    def deposit(self,double amount):
        return self.c_acc.deposit(amount)

    def withdraw(self,double amount):
        return self.c_acc.withdraw(amount)

    def get_balance(self):
        return self.c_acc.get_balance()