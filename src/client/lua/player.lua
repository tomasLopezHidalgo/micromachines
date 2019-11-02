print("Loading Lua Player...")

next_position = {
    [0] = "R",
    [1] = "F",
    [2] = "L"
}

function check_position(position)
    return entities[position]["safe"]
end

function getAction(pos_x, pos_y)
    print(string.format("Repositorio: %s", entities))
    print("Avanzar")
    car_pos = map[pos_x, pos_y]
    -- verificar bordes
    -- si todos son false avanzar aunque choque
    for i in range(3)
        if (check_position(map[i][y + 1]))
            return next_position[i]
        end
    end
    return "F"
end