# A Dynamic Programming based Python program for edit
# distance problem


def edit_distance(str1: str, str2: str, m: int, n: int) -> int:
    # Create a table to store results of subproblems
    dp = [[0 for _ in range(n + 1)] for _ in range(m + 1)]

    # Fill d[][] in bottom up manner
    for i in range(m + 1):
        for j in range(n + 1):

            # If first string is empty, only option is to
            # insert all characters of second string
            if i == 0:
                dp[i][j] = j  # Min. operations = j

            # If second string is empty, only option is to
            # remove all characters of second string
            elif j == 0:
                dp[i][j] = i  # Min. operations = i

            # If last characters are same, ignore last char
            # and recur for remaining string
            elif str1[i - 1] == str2[j - 1]:
                dp[i][j] = dp[i - 1][j - 1]

            # If last character are different, consider all
            # possibilities and find minimum
            else:
                dp[i][j] = 1 + min(
                    dp[i][j - 1],  # Insert
                    dp[i - 1][j],  # Remove
                    dp[i - 1][j - 1],  # Replace
                )

    return dp[m][n]


def soundex(name: str) -> str:

    soundexcoding = [" ", " ", " ", " "]
    soundexcodingindex = 1

    #           ABCDEFGHIJKLMNOPQRSTUVWXYZ
    mappings = "01230120022455012623010202"

    soundexcoding[0] = name[0].upper()

    for i in range(1, len(name)):

        c = ord(name[i].upper()) - 65

        if c >= 0 and c <= 25:

            if mappings[c] != "0":

                if mappings[c] != soundexcoding[soundexcodingindex - 1]:

                    soundexcoding[soundexcodingindex] = mappings[c]
                    soundexcodingindex += 1

                if soundexcodingindex > 3:

                    break

    if soundexcodingindex <= 3:
        while soundexcodingindex <= 3:
            soundexcoding[soundexcodingindex] = "0"
            soundexcodingindex += 1

    return "".join(soundexcoding)


def ngram(word: str, n: int):

    return [word[i : i + n] for i in range(len(word) - 1)]


if __name__ == "__main__":
    # Driver code
    str1 = "CHEBYSHEV"
    str2 = "TSCHEBYSCHEF"
    print(edit_distance(str1, str2, len(str1), len(str2)))

    str1 = "LEVINSTINE"
    str2 = "LEVENSHTEIN"
    print(edit_distance(str1, str2, len(str1), len(str2)))

    print("Stanford", soundex("Stanford"))
    print("Georgetown", soundex("Georgetown"))

    s1 = set(ngram("CHEONGSONG", 3))
    s2 = set(ngram("CHEONMACHONG", 3))
    print(s1 & s2)

    s1 = ngram("CHEONGSONG", 4)
    s2 = ngram("CHEONMACHONG", 4)
    print(s1, s2)
    print(set(s1) & set(s2))
