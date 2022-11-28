def front_code(dictionary):

    dictionary = [i[::-1] for i in dictionary]
    dictionary.sort()

    compressed_dict = []
    last_prefix = ""
    offset = -1

    for idx, word in enumerate(dictionary):

        if not idx:
            compressed_dict.append(f"0{word}")

        else:
            for offset, chr in enumerate(zip(last_prefix, word)):
                if chr[0] != chr[1]:
                    compressed_dict.append(f"{offset}{word[offset:]}")
                    break
            else:
                compressed_dict.append(f"{offset+1}{word[offset + 1 :]}")

        last_prefix = word

    return sum(len(i) for i in dictionary), sum(len(i) for i in compressed_dict)


example = [
    "trovato",
    "trovavano",
    "trovava",
    "trovati",
    "trova",
    "trovo",
    "trovata",
    "trovare",
    "trovarsi",
    "trovano",
]

oxides = [
    "Aluminium oxide",
    "Antimony trioxide",
    "Antimony tetroxide",
    "Antimony pentoxide",
    "Arsenic trioxide",
    "Arsenic pentoxide",
    "Barium oxide",
    "Bismuth(III) oxide",
    "Bismuth(V) oxide",
    "Calcium oxide",
]


print(front_code(example))
print(front_code(oxides))
