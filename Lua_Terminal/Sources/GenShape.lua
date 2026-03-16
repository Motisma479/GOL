local shapes = {}

-- ░░░░░░░░░░
-- ░░░░██░░░░
-- ░░░░░░██░░
-- ░░██████░░
-- ░░░░░░░░░░
function shapes.GenShape_1(x, y)
    local coordinates = {}
    
    table.insert(coordinates, {x+1, y})
    table.insert(coordinates, {x+2, y+1})
    table.insert(coordinates, {x, y+2})
    table.insert(coordinates, {x+1, y+2})
    table.insert(coordinates, {x+2, y+2})

    return coordinates
end

-- ░░░░░░░░░░
-- ░░░░██░░░░
-- ░░██░░██░░
-- ░░██░░██░░
-- ░░██░░██░░
-- ░░░░██░░░░
-- ░░░░░░░░░░
function shapes.GenShape_2(x, y)
    local coordinates = {}

    table.insert(coordinates, {x+1, y})
    table.insert(coordinates, {x, y+1})
    table.insert(coordinates, {x+2, y+1})
    table.insert(coordinates, {x, y+2})
    table.insert(coordinates, {x+2, y+2})
    table.insert(coordinates, {x, y+3})
    table.insert(coordinates, {x+2, y+3})
    table.insert(coordinates, {x+1, y+4})

    return coordinates
end

-- ░░░░░░░░░░
-- ░░██░░░░░░
-- ░░██████░░
-- ░░░░██░░░░
-- ░░░░░░░░░░
function shapes.GenShape_3(x, y)
    local coordinates = {}

    table.insert(coordinates, {x, y})
    table.insert(coordinates, {x, y+1})
    table.insert(coordinates, {x+1, y+1})
    table.insert(coordinates, {x+2, y+1})
    table.insert(coordinates, {x+1, y+2})

    return coordinates
end

return shapes