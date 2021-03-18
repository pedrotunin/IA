import os
import sys
import platform

so = platform.system()

problemas = open(sys.argv[1], 'r')

os.system("g++ BT.cpp -o BT")

for problema in problemas:
    if so == "Linux" or so == "Darwin":
        comando = "./BT " + problema
    else:
        comando = "BT.exe " + problema
    os.system(comando)

