from sys import setdlopenflags
from ctypes import RTLD_GLOBAL
setdlopenflags (RTLD_GLOBAL | 2)

from bloc_component import Bloc
b=Bloc()


print ("bloc_0 : ",b.to_json())
print(" Test validation du hash de bloc_0 : ")
print(b.validationDifficultyBloc())

b.setHash("1100123456789A123456789A123456789A123456789A123456789A123456789A")

print ("bloc_1 : ",b.to_json())
print(" Test validation du hash de bloc_1 : ")
print(b.validationDifficultyBloc())

b.setHash("1100123456789A123456789A123456789A123456789A123456789A")

print("bloc_2 : ", b.to_json())
print(" Test validation du hash de bloc_2 : ") 
print(b.validationDifficultyBloc())