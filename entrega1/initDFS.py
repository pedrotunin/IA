import os
import sys
import platform

so = platform.system()

problemas = open(sys.argv[1], 'r')

os.system("g++ DFS.cpp -o DFS")

for problema in problemas:
    if so == "Linux" or so == "Darwin":
        comando = "./DFS " + problema
    else:
        comando = "DFS.exe " + problema
    os.system(comando)