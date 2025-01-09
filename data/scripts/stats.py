import json

results = "results.txt"
gr = {
    "100% male": "MaleOnly",
    "0% male": "FemaleOnly",
    "87.5% male": "F1M7",
    "75% male": "F1M3",
    "50% male": "F1M1",
    "25% male": "F3M1",
    -1: "Unknown"
}

with open("pokemon-stats-gen1-abilites.json") as d:
    data = json.load(d)

with open(results, "w") as f:
    for i in range(251, 386):
        index = data[str(i + 1)]
        name = index["name"]
        stats = '{' + (f"{int(index["HP"])}, "
                       f"{index["Attack"]}, "
                       f"{index["Defense"]}, "
                       f"{index["Sp. Atk"]}, "
                       f"{index["Sp. Def"]}, "
                       f"{index["Speed"]}") + '}'
        gender = gr[index["Male Gender Ratio"]]
        ability1 = index["Ability 1"]
        ability2 = index["Ability 2"]
        output = '{ ' + str(i + 1) + ', "' + name + '", ' + stats + ', ' + gender + ', "' + ability1 + '", ' + '"' + ability2 + '"' + ' },'
        f.write(output + '\n')

for i in range(251, 386):
    index = data[str(i + 1)]
    name = index["name"]
    output = '"' + name.upper() + '"' + ':' + str(i) + ','
    print(output)
