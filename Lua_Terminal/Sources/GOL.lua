local terminal = require("Sources.Terminal")

local GOL = {}

-- public
GOL.isFinished = false -- bool

-- private
local colorAlive = "\033[48;2;0;0;0m" -- string
local colorDead = "\033[48;2;255;255;255m" -- string
local firstUpdate = true -- bool
local shouldUpdate -- bool
local size_x
local size_y
local data  = {} -- {bool}
local hasChanged = false -- bool
local waitStart -- time in milliseconds
local restricted = false -- bool

function GOL.Init(_size_x, _size_y, _restricted)
    _restricted = _restricted or false
    
    size_x = _size_x
    size_y = _size_y

    restricted = _restricted

    for x = 1, size_x do
        for y = 1, size_y do
            table.insert(data,false)
        end
    end
end

function GOL.Update(_delay)
    if firstUpdate then
        waitStart = os.clock()
        shouldUpdate = false
        firstUpdate = false
        return true
    end

    if shouldUpdate then
        local tempData = {}
        for k, v in pairs(data) do
            if type(v) == "table" then
                tempData[k] = {}
                for k2, v2 in pairs(v) do
                    tempData[k][k2] = v2
                end
            else
                tempData[k] = v
            end
        end

        for x = 1, size_x do
            for y = 1, size_y do
                tempData[x+y*size_x] = UpdateCell(x, y)
            end
        end
        GOL.isFinished = not hasChanged
        hasChanged = false
        data = tempData
        waitStart = os.clock()
        shouldUpdate = false

        return true
    end

    if waitStart + ( _delay / 1000 ) >= os.clock() then
        return false
    end
    shouldUpdate = true
    return false
end

function GOL.ChangeCell(x, y)
    data[x+y*size_x] = not data[x+y*size_x]
end

function GOL.TerminalPrint()
    terminal.SetCurPos(0,0)
    for y = 1, size_y do
        for x = 1, size_x do
            if data[x+y*size_x] then
                io.write(colorAlive)
            else
                io.write(colorDead)
            end 
            io.write("  ")
        end
        io.write("\n")
    end
    io.write("\27[0m")
end

function GOL.SetColor(_colorAlive, _colorDead)
        colorAlive = "\27[48;2;" .. _colorAlive .. "m"
        colorDead = "\27[48;2;" .. _colorDead .. "m"
end

function UpdateCell(x, y)
    local livingAround = 0

    livingAround = livingAround + GetValue(x-1,y+1);
    livingAround = livingAround + GetValue(x,y+1);
    livingAround = livingAround + GetValue(x+1,y+1);
    livingAround = livingAround + GetValue(x-1,y);

    livingAround = livingAround + GetValue(x+1,y);
    livingAround = livingAround + GetValue(x-1,y-1);
    livingAround = livingAround + GetValue(x,y-1);
    livingAround = livingAround + GetValue(x+1,y-1);

    if data[x+y*size_x] then
        if livingAround < 2 or livingAround > 3 then
            hasChanged = true
            return false
        end
    else
        if livingAround == 3 then
            hasChanged = true
            return true
        end
    end

    return data[x+y*size_x]
end

function GetValue(x, y)
    if not restricted then
        if x < 1 then
            x = x + size_x
        end
        if y < 1 then
            y = y + size_y
        end
        if x > size_x then
            x =  x - size_x
        end
        if y > size_y then
            y = y - size_y
        end
    else
        if x < 1 or y < 1 or x > size_x or y > size_y then
            return 0
        end
    end

    if data[x+y*size_x] then
        return 1
    else
        return 0
    end
end


return GOL