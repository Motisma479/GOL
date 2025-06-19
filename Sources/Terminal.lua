local Terminal = {}

function Terminal.SetCurPos( x, y )
    io.write(string.format("\27[%d;%dH",y,x))
end

return Terminal