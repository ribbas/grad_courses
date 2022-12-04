def front_code(dictionary, reverse=False, sort=True):

    if reverse:
        dictionary = [i[::-1] for i in dictionary]

    if sort:
        dictionary.sort()

    uncompressed_len = sum(len(i) for i in dictionary)

    last_prefix = dictionary.pop(0)
    compressed_dict = f"0{last_prefix}"

    for word in dictionary:

        for offset, chr in enumerate(zip(last_prefix, word)):
            if chr[0] != chr[1]:
                compressed_dict += f"{offset}{word[offset:]}"
                break
        else:
            compressed_dict += f"{offset+1}{word[offset+1:]}"

        last_prefix = word

    return uncompressed_len, len(compressed_dict)


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


print(front_code(example, True, True))
print(front_code(oxides, True, True))
