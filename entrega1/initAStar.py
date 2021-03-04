import os
import sys
import platform

so = platform.system()

problemas = open(sys.argv[1], 'r')

os.system("g++ AStar.cpp -o AStar")

for problema in problemas:
    if so == "Linux" or so == "Darwin":
        comando = "./AStar " + problema
    else:
        comando = "AStar.exe " + problema
    os.system(comando)