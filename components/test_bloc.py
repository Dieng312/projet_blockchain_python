from sys import setdlopenflags
from ctypes import RTLD_GLOBAL
setdlopenflags (RTLD_GLOBAL | 2)

from bloc_component import Bloc
b=Bloc()
print (b.to_json())
print(" hash de bloc_0 : hash_0 = ", b.getHash())
print(" Test validation du hash de bloc_0 : ", b.validationDifficultyBloc())

b.setHash("1100123456789A123456789A123456789A123456789A123456789A123456789A")

print(" hash de bloc_1 : hash_1 = ", b.getHash())
print(" Test validation du hash de bloc_1 : ", b.validationDifficultyBloc())

b.setHash("1100123456789A123456789A123456789A123456789A123456789A")
print(" hash de bloc_2 : hash_2 = ", b.getHash())
print(" Test validation du hash de bloc_2 : ", b.validationDifficultyBloc())