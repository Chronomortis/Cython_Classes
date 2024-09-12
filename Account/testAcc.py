# Direct implementation of all the C++ Account() class attributes to python pyAccount() class for error throwing and catching. 
import pyAccount as pa

acc = pa.pyAccount(100)

# I experimented with each thrown error on the C++ side, those errors are caught in Python side.

acc2 = pa.pyAccount(-150)
acc.deposit(-50)

acc.withdraw(120)
acc.withdraw(-10)


print(acc.get_balance())

