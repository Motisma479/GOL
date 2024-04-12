from Sources.GOL import *
from Sources.Gen_Shape import *

def main():
    gol = GOL(32,16)
    gol.SetColor("159;223;76", "37;27;44")
#-----------------------------------------------------------
    for i in genShape_1(0,0):
        gol.ChangeCell(i[0],i[1])

    for i in genShape_2(8,6):
        gol.ChangeCell(i[0],i[1])

    for i in genShape_2(16,6):
        gol.ChangeCell(i[0],i[1])
#-----------------------------------------------------------
    while gol.isFinished == False:
        if gol.Update(100):
            gol.TerminalPrint()

main()