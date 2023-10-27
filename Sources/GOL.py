from Sources.terminal import *
from datetime import datetime, timedelta

class GOL:
    #PUBLIC
    def __init__(self, size_x : int, size_y : int, restricted : bool = False):
        self.colorAlive : str = "\033[48;2;0;0;0m"
        self.colorDead : str = "\033[48;2;255;255;255m"
        self.size_x : int = size_x
        self.size_y : int = size_y

        self.isFinished : bool = False

        self.terminal : Terminal = Terminal()
        self.terminal.NewPage()

        self.data : list[bool] = []
        for x in range(size_x):
            for y in range(size_y):
                self.data.append(False)

        self.shouldUpdate : bool = True
        self.firstUpdate : bool = True
        self.waitStart : datetime = datetime.now()
        self.restricted : bool = restricted
        self.hasChanged : bool = False

    def Update(self, delay : int) -> bool:
        if self.firstUpdate:
            self.waitStart = datetime.now()
            self.shouldUpdate = False
            self.firstUpdate = False
            return True
        if self.shouldUpdate:
            tempData : list[bool] = self.data.copy()
            for x in range(self.size_x):
                for y in range(self.size_y):
                    tempData[x+y*self.size_x] = self.__UpdateCell(x,y)
            self.isFinished = not self.hasChanged
            self.hasChanged = False
            self.data = tempData
            self.waitStart = datetime.now()
            self.shouldUpdate = False
            return True
        if self.waitStart + timedelta(milliseconds=delay) >= datetime.now():
            return False
        self.shouldUpdate = True
        return False
    
    def TerminalPrint(self):
        self.terminal.SetCurPos(0,0)
        for y in range(self.size_y):
            for x in range(self.size_x):
                if self.data[x+y*self.size_x]:
                    print(self.colorAlive+"  ", end="") # color: 0, 0, 0 by default
                else:
                    print(self.colorDead+"  ", end="") # color: 255, 255, 255 by default
            print("\n", end="");
        print("\033[0m", end="")
    

    def ChangeCell(self, x : int, y : int):
        self.data[x+y*self.size_x] = not self.data[x+y*self.size_x]
    
    def SetColor(self, colorAlive : str, colorDead : str):
        self.colorAlive = "\033[48;2;" + colorAlive + "m"
        self.colorDead = "\033[48;2;" + colorDead + "m"
    #PRVATE
    def __GetValue(self, x : int, y : int) -> bool:
        if not self.restricted:
            if x < 0:
                x += self.size_x

            if y < 0:
                y += self.size_y

            if x > self.size_x-1:
                x -= self.size_x

            if y > self.size_y-1:
                y -= self.size_y
        else:
            if x < 0 or y < 0 or x > self.size_x-1 or y > self.size_y-1:
                return False

        return self.data[x+y*self.size_x]
    
    def __UpdateCell(self, x : int, y : int) -> bool:
        livingAround : int = 0

        livingAround += self.__GetValue(x-1,y+1);
        livingAround += self.__GetValue(x,y+1);
        livingAround += self.__GetValue(x+1,y+1);
        livingAround += self.__GetValue(x-1,y);

        livingAround += self.__GetValue(x+1,y);
        livingAround += self.__GetValue(x-1,y-1);
        livingAround += self.__GetValue(x,y-1);
        livingAround += self.__GetValue(x+1,y-1);

        if self.data[x+y*self.size_x]:
            if livingAround < 2 or livingAround > 3:
                self.hasChanged = True
                return False
        else:
            if livingAround == 3:
                self.hasChanged = True
                return True
        return self.data[x+y*self.size_x]