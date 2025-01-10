import csv
import os
import sys

mons = {
    "BULBASAUR": 0,
    "IVYSAUR": 1,
    "VENUSAUR": 2,
    "CHARMANDER": 3,
    "CHARMELEON": 4,
    "CHARIZARD": 5,
    "SQUIRTLE": 6,
    "WARTORTLE": 7,
    "BLASTOISE": 8,
    "CATERPIE": 9,
    "METAPOD": 10,
    "BUTTERFREE": 11,
    "WEEDLE": 12,
    "KAKUNA": 13,
    "BEEDRILL": 14,
    "PIDGEY": 15,
    "PIDGEOTTO": 16,
    "PIDGEOT": 17,
    "RATTATA": 18,
    "RATICATE": 19,
    "SPEAROW": 20,
    "FEAROW": 21,
    "EKANS": 22,
    "ARBOK": 23,
    "PIKACHU": 24,
    "RAICHU": 25,
    "SANDSHREW": 26,
    "SANDSLASH": 27,
    "NIDORAN-F": 28,
    "NIDORINA": 29,
    "NIDOQUEEN": 30,
    "NIDORAN-M": 31,
    "NIDORINO": 32,
    "NIDOKING": 33,
    "CLEFAIRY": 34,
    "CLEFABLE": 35,
    "VULPIX": 36,
    "NINETALES": 37,
    "JIGGLYPUFF": 38,
    "WIGGLYTUFF": 39,
    "ZUBAT": 40,
    "GOLBAT": 41,
    "ODDISH": 42,
    "GLOOM": 43,
    "VILEPLUME": 44,
    "PARAS": 45,
    "PARASECT": 46,
    "VENONAT": 47,
    "VENOMOTH": 48,
    "DIGLETT": 49,
    "DUGTRIO": 50,
    "MEOWTH": 51,
    "PERSIAN": 52,
    "PSYDUCK": 53,
    "GOLDUCK": 54,
    "MANKEY": 55,
    "PRIMEAPE": 56,
    "GROWLITHE": 57,
    "ARCANINE": 58,
    "POLIWAG": 59,
    "POLIWHIRL": 60,
    "POLIWRATH": 61,
    "ABRA": 62,
    "KADABRA": 63,
    "ALAKAZAM": 64,
    "MACHOP": 65,
    "MACHOKE": 66,
    "MACHAMP": 67,
    "BELLSPROUT": 68,
    "WEEPINBELL": 69,
    "VICTREEBEL": 70,
    "TENTACOOL": 71,
    "TENTACRUEL": 72,
    "GEODUDE": 73,
    "GRAVELER": 74,
    "GOLEM": 75,
    "PONYTA": 76,
    "RAPIDASH": 77,
    "SLOWPOKE": 78,
    "SLOWBRO": 79,
    "MAGNEMITE": 80,
    "MAGNETON": 81,
    "FARFETCHD": 82,
    "DODUO": 83,
    "DODRIO": 84,
    "SEEL": 85,
    "DEWGONG": 86,
    "GRIMER": 87,
    "MUK": 88,
    "SHELLDER": 89,
    "CLOYSTER": 90,
    "GASTLY": 91,
    "HAUNTER": 92,
    "GENGAR": 93,
    "ONIX": 94,
    "DROWZEE": 95,
    "HYPNO": 96,
    "KRABBY": 97,
    "KINGLER": 98,
    "VOLTORB": 99,
    "ELECTRODE": 100,
    "EXEGGCUTE": 101,
    "EXEGGUTOR": 102,
    "CUBONE": 103,
    "MAROWAK": 104,
    "HITMONLEE": 105,
    "HITMONCHAN": 106,
    "LICKITUNG": 107,
    "KOFFING": 108,
    "WEEZING": 109,
    "RHYHORN": 110,
    "RHYDON": 111,
    "CHANSEY": 112,
    "TANGELA": 113,
    "KANGASKHAN": 114,
    "HORSEA": 115,
    "SEADRA": 116,
    "GOLDEEN": 117,
    "SEAKING": 118,
    "STARYU": 119,
    "STARMIE": 120,
    "MR-MIME": 121,
    "SCYTHER": 122,
    "JYNX": 123,
    "ELECTABUZZ": 124,
    "MAGMAR": 125,
    "PINSIR": 126,
    "TAUROS": 127,
    "MAGIKARP": 128,
    "GYARADOS": 129,
    "LAPRAS": 130,
    "DITTO": 131,
    "EEVEE": 132,
    "VAPOREON": 133,
    "JOLTEON": 134,
    "FLAREON": 135,
    "PORYGON": 136,
    "OMANYTE": 137,
    "OMASTAR": 138,
    "KABUTO": 139,
    "KABUTOPS": 140,
    "AERODACTYL": 141,
    "SNORLAX": 142,
    "ARTICUNO": 143,
    "ZAPDOS": 144,
    "MOLTRES": 145,
    "DRATINI": 146,
    "DRAGONAIR": 147,
    "DRAGONITE": 148,
    "MEWTWO": 149,
    "MEW": 150,
    "CHIKORITA": 151,
    "BAYLEEF": 152,
    "MEGANIUM": 153,
    "CYNDAQUIL": 154,
    "QUILAVA": 155,
    "TYPHLOSION": 156,
    "TOTODILE": 157,
    "CROCONAW": 158,
    "FERALIGATR": 159,
    "SENTRET": 160,
    "FURRET": 161,
    "HOOTHOOT": 162,
    "NOCTOWL": 163,
    "LEDYBA": 164,
    "LEDIAN": 165,
    "SPINARAK": 166,
    "ARIADOS": 167,
    "CROBAT": 168,
    "CHINCHOU": 169,
    "LANTURN": 170,
    "PICHU": 171,
    "CLEFFA": 172,
    "IGGLYBUFF": 173,
    "TOGEPI": 174,
    "TOGETIC": 175,
    "NATU": 176,
    "XATU": 177,
    "MAREEP": 178,
    "FLAAFFY": 179,
    "AMPHAROS": 180,
    "BELLOSSOM": 181,
    "MARILL": 182,
    "AZUMARILL": 183,
    "SUDOWOODO": 184,
    "POLITOED": 185,
    "HOPPIP": 186,
    "SKIPLOOM": 187,
    "JUMPLUFF": 188,
    "AIPOM": 189,
    "SUNKERN": 190,
    "SUNFLORA": 191,
    "YANMA": 192,
    "WOOPER": 193,
    "QUAGSIRE": 194,
    "ESPEON": 195,
    "UMBREON": 196,
    "MURKROW": 197,
    "SLOWKING": 198,
    "MISDREAVUS": 199,
    "UNOWN": 200,
    "WOBBUFFET": 201,
    "GIRAFARIG": 202,
    "PINECO": 203,
    "FORRETRESS": 204,
    "DUNSPARCE": 205,
    "GLIGAR": 206,
    "STEELIX": 207,
    "SNUBBULL": 208,
    "GRANBULL": 209,
    "QWILFISH": 210,
    "SCIZOR": 211,
    "SHUCKLE": 212,
    "HERACROSS": 213,
    "SNEASEL": 214,
    "TEDDIURSA": 215,
    "URSARING": 216,
    "SLUGMA": 217,
    "MAGCARGO": 218,
    "SWINUB": 219,
    "PILOSWINE": 220,
    "CORSOLA": 221,
    "REMORAID": 222,
    "OCTILLERY": 223,
    "DELIBIRD": 224,
    "MANTINE": 225,
    "SKARMORY": 226,
    "HOUNDOUR": 227,
    "HOUNDOOM": 228,
    "KINGDRA": 229,
    "PHANPY": 230,
    "DONPHAN": 231,
    "PORYGON2": 232,
    "STANTLER": 233,
    "SMEARGLE": 234,
    "TYROGUE": 235,
    "HITMONTOP": 236,
    "SMOOCHUM": 237,
    "ELEKID": 238,
    "MAGBY": 239,
    "MILTANK": 240,
    "BLISSEY": 241,
    "RAIKOU": 242,
    "ENTEI": 243,
    "SUICUNE": 244,
    "LARVITAR": 245,
    "PUPITAR": 246,
    "TYRANITAR": 247,
    "LUGIA": 248,
    "HO-OH": 249,
    "CELEBI": 250
}


def print_area_names(file_path):
    with open(file_path, mode='r') as f:
        c = csv.reader(f)
        for r in c:
            output = '"' + r[0] + '"' + ','
            print(output)


# True = FR, False = LG
def read_write_land_slots(file_path, version: bool):
    path = "../LGENCSLOTS/land"
    if version:
        path = "../FRENCSLOTS/land"

    data = []
    with open(file_path, mode='r') as f:
        csf = csv.reader(f)
        next(csf, None)

        for row in csf:
            entry = [0]

            for i in range(1, 25, 2):
                entry.extend([mons[row[i]], int(row[i + 1]), (i // 2) + 1])

            data.append(entry)

    with open(path, 'w', newline='\n', encoding="utf-8") as file:
        writer = csv.writer(file)
        writer.writerows(data)


def read_write_old_rod_slots(file_path, version: bool):
    path = "../LGENCSLOTS/old"
    if version:
        path = "../FRENCSLOTS/old"

    data = []
    with open(file_path, mode='r') as f:
        csf = csv.reader(f)
        next(csf, None)

        for row in csf:
            entry = [0]

            for i in range(1, 5, 2):
                lvl = row[i + 1].split(sep='-')
                entry.extend([int(mons[row[i]]), int(lvl[0]), int(lvl[1]), i])

            data.append(entry)

    with open(path, 'w', newline='\n', encoding="utf-8") as file:
        writer = csv.writer(file)
        writer.writerows(data)


def read_write_good_rod_slots(file_path, version: bool):
    path = "../LGENCSLOTS/good"
    if version:
        path = "../FRENCSLOTS/good"

    data = []
    with open(file_path, mode='r') as f:
        csf = csv.reader(f)
        next(csf, None)

        for row in csf:
            entry = [0]

            for i in range(1, 7, 2):
                lvl = row[i + 1].split(sep='-')
                entry.extend([int(mons[row[i]]), int(lvl[0]), int(lvl[1]), i])

            data.append(entry)

    with open(path, 'w', newline='\n', encoding="utf-8") as file:
        writer = csv.writer(file)
        writer.writerows(data)


def read_write_super_rod_slots(file_path, version: bool):
    path = "../LGENCSLOTS/super"
    if version:
        path = "../FRENCSLOTS/super"

    data = []
    with open(file_path, mode='r') as f:
        csf = csv.reader(f)
        next(csf, None)

        for row in csf:
            entry = [0]

            for i in range(1, 11, 2):
                lvl = row[i + 1].split(sep='-')
                entry.extend([int(mons[row[i]]), int(lvl[0]), int(lvl[1]), i])

            data.append(entry)

    with open(path, 'w', newline='\n', encoding="utf-8") as file:
        writer = csv.writer(file)
        writer.writerows(data)


def read_write_water_slots(file_path, version: bool):
    path = "../LGENCSLOTS/water"
    if version:
        path = "../FRENCSLOTS/water"

    data = []
    with open(file_path, mode='r') as f:
        csf = csv.reader(f)
        next(csf, None)
        for row in csf:
            entry = [0]
            for i in range(1, 10, 2):
                lvl = row[i + 1].split(sep='-')
                entry.extend([int(mons[row[i]]), int(lvl[0]), int(lvl[1]), i])
            data.append(entry)

    with open(path, 'w', newline='\n', encoding="utf-8") as file:
        writer = csv.writer(file)
        writer.writerows(data)


def read_write_rock_slots(file_path, version: bool):
    path = "../LGENCSLOTS/rock"
    if version:
        path = "../FRENCSLOTS/rock"

    data = []
    with open(file_path, mode='r') as f:
        csf = csv.reader(f)
        next(csf, None)
        for row in csf:
            entry = [0]
            for i in range(1, 10, 2):
                lvl = row[i + 1].split(sep='-')
                entry.extend([int(mons[row[i]]), int(lvl[0]), int(lvl[1]), i])
            data.append(entry)

    with open(path, 'w', newline='\n', encoding="utf-8") as file:
        writer = csv.writer(file)
        writer.writerows(data)


def create_all_files():
    script_dir = os.path.dirname(os.path.abspath(__file__))
    data_dir = os.path.join(script_dir, '..', 'raw')
    sys.path.append(data_dir)

    fp_lg_land = os.path.join(data_dir, 'lglandenc.csv')
    fp_fr_land = os.path.join(data_dir, 'frlandenc.csv')

    fp_lg_water = os.path.join(data_dir, 'lgwaterenc.csv')
    fp_fr_water = os.path.join(data_dir, 'frwaterenc.csv')

    fp_lg_smash = os.path.join(data_dir, 'lgrockenc.csv')
    fp_fr_smash = os.path.join(data_dir, 'frrockenc.csv')

    fp_lg_old_rod = os.path.join(data_dir, 'lgoldrod.csv')
    fp_fr_old_rod = os.path.join(data_dir, 'froldrod.csv')

    fp_lg_good_rod = os.path.join(data_dir, 'lggoodrod.csv')
    fp_fr_good_rod = os.path.join(data_dir, 'frgoodrod.csv')

    fp_lg_super_rod = os.path.join(data_dir, 'lgsuperrod.csv')
    fp_fr_super_rod = os.path.join(data_dir, 'frsuperrod.csv')

    # read_write_land_slots(fp_fr_land, True)
    # read_write_land_slots(fp_lg_land, False)
    #
    # read_write_water_slots(fp_fr_water, True)
    # read_write_water_slots(fp_lg_water, False)
    #
    # read_write_rock_slots(fp_fr_smash, True)
    # read_write_rock_slots(fp_lg_smash, False)

    read_write_old_rod_slots(fp_lg_old_rod, False)
    read_write_old_rod_slots(fp_fr_old_rod, True)

    read_write_good_rod_slots(fp_lg_good_rod, False)
    read_write_good_rod_slots(fp_fr_good_rod, True)

    read_write_super_rod_slots(fp_lg_super_rod, False)
    read_write_super_rod_slots(fp_fr_super_rod, True)


def write_land_slot_C(file_path):
    with open(file_path, mode='r') as f:
        csf = csv.reader(f)
        next(csf, None)
        count = 0
        for row in csf:
            output = '{ ' + "GOOD, " + '"' + row[0] + '"' + ', ' + str(count) + ' },'
            count += 1
            print(output)


if __name__ == '__main__':
    create_all_files()

    # script_dir = os.path.dirname(os.path.abspath(__file__))
    # data_dir = os.path.join(script_dir, '..', 'raw')
    # sys.path.append(data_dir)
    #
    # fp_lg_land = os.path.join(data_dir, 'lgsuperrod.csv')
    # write_land_slot_C(fp_lg_land)
