local gol = require("Sources.GOL")
local genShape = require("Sources.GenShape")


function main()
    gol.Init(32, 16)
    gol.SetColor("159;223;76", "37;27;44")

----------------------------------------    
    for i, v in  pairs(genShape.GenShape_1(1,1)) do
        gol.ChangeCell(v[1], v[2])
    end

    for i, v in  pairs(genShape.GenShape_2(9,7)) do
        gol.ChangeCell(v[1], v[2])
    end

    for i, v in  pairs(genShape.GenShape_2(17,7)) do
        gol.ChangeCell(v[1], v[2])
    end

----------------------------------------

    while not gol.isFinished do
        if gol.Update(100) then
            gol.TerminalPrint()
        end
    end


end

main()