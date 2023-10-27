# ░░░░░░░░░░
# ░░░░██░░░░
# ░░░░░░██░░
# ░░██████░░
# ░░░░░░░░░░
def genShape_1(x : int, y : int):
    coordinates = []

    coordinates.append([x+1, y])
    coordinates.append([x+2, y+1])
    coordinates.append([x, y+2])
    coordinates.append([x+1, y+2])
    coordinates.append([x+2, y+2])

    return coordinates

# ░░░░░░░░░░
# ░░░░██░░░░
# ░░██░░██░░
# ░░██░░██░░
# ░░██░░██░░
# ░░░░██░░░░
# ░░░░░░░░░░
def genShape_2(x : int, y : int):
    coordinates = []

    coordinates.append([x+1, y])
    coordinates.append([x, y+1])
    coordinates.append([x+2, y+1])
    coordinates.append([x, y+2])
    coordinates.append([x+2, y+2])
    coordinates.append([x, y+3])
    coordinates.append([x+2, y+3])
    coordinates.append([x+1, y+4])

    return coordinates

# ░░░░░░░░░░
# ░░██░░░░░░
# ░░██████░░
# ░░░░██░░░░
# ░░░░░░░░░░
def genShape_3(x : int, y : int):
    coordinates = []

    coordinates.append([x, y])
    coordinates.append([x, y+1])
    coordinates.append([x+1, y+1])
    coordinates.append([x+2, y+1])
    coordinates.append([x+1, y+2])

    return coordinates