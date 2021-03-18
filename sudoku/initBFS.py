import os
import sys
import platform

so = platform.system()

problemas = open(sys.argv[1], 'r')

os.system("g++ BFS.cpp -o BFS")

for problema in problemas:
    if so == "Linux" or so == "Darwin":
        comando = "./BFS " + problema
    else:
        comando = "BFS.exe " + problema
    os.system(comando)
