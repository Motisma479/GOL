import sys
import msvcrt
import os

class Terminal:
    def __init__(self):
        pass
    def SetCurPos(self, x : int, y : int):
        print("\033[%d;%dH" % (y, x), end="")
    
    def GetCurPos(self):
        msvcrt.setmode(sys.stdin.fileno(), os.O_BINARY)
        msvcrt.setmode(sys.stdout.fileno(), os.O_BINARY)
        
        x = y = 0
        
        # Get the cursor position
        sys.stdout.write("\x1b[6n")
        sys.stdout.flush()
        
        response = ''
        while True:
            char = msvcrt.getch().decode()
            response += char
            
            if char == 'R':
                break
        
        # Extract x and y position from the response
        position = response[2:-1]
        x, y = position.split(';')
        
        return int(x), int(y)

    def GetTermSize(self):
        try:
            columns, rows = os.get_terminal_size()
            return columns, rows
        except OSError:
            return None


    def NewPage(self):
        a,b = self.GetTermSize();
        x,y = self.GetCurPos();

        for i in range(b):
            print("\n", end="");
