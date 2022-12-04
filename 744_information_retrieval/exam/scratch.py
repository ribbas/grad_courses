import math


def gap_encode(numbers: list) -> list:
    """Creates a gap list from a list of integers."""
    gaps = [numbers[0]]
    # The first number is the same in the gap list.
    for (number, previous) in zip(numbers[1:], numbers[0:-1]):
        gaps.append(number - previous)
        # Record the difference between a number and the previous number.
    return gaps


def gap_decode(gaps: list) -> list:
    """Decodes a gap list back into the original numbers."""
    numbers = []
    running_total = 0
    for gap in gaps:
        running_total += gap
        numbers.append(running_total)
        # Find each successive number by adding the next gap to the previous
        # number.
    return numbers


def gamma_decode(bits: str) -> list:
    """Decodes a gamma-encoded string of bits
    into a list of decoded base-10 integers."""
    decoded_numbers = []
    # Save the numbers as they are decoded.
    reading_unary = True
    # Keep track of whether we are reading a unary-encoded
    # power of 2 or a binary-encoded remainder.
    power = 0

    for bit in bits:
        if reading_unary:
            power += int(bit)
            # Tally the ones in the unary prefix.
            if bit == "0":
                reading_unary = False
                # The unary prefix ends when a zero is reached.
                decoded_numbers.append(2**power)
                # Save the power of 2 (determined from the prefix) as the next
                # number in the list; we'll add the remainder as we read binary.
        else:
            power -= 1
            # The binary suffix has a number of bits equal to the highest power
            # of 2, so the first bit corresponds to the next smaller power of 2.
            decoded_numbers[-1] += int(bit) * (2**power)
            # Add the remainder to the last number in the list as we read it.
            if power == 0:
                reading_unary = True
                # After reading a number of bits equal to the greatest power of
                # 2 in the number, we start reading the unary prefix of the next
                # number.

    return decoded_numbers


def gamma_encode(number: int, delim=" ") -> str:
    """Performs gamma encoding on an integer or list of integers, returning
    a string of bits."""
    if isinstance(number, list):
        encodings = [gamma_encode(n) for n in number]
        return delim.join(encodings)
        # If the input is a list of numbers, then encode each and concatenate
        # the results. By default, put spaces in between the codes for
        # easier verification of results.

    encoded = ""
    power = 0
    while True:
        if number - 2 ** (power + 1) < 0:
            break
        else:
            power += 1
            encoded += "1"
            # Find the highest power of 2 less than or equal to the number.
    encoded += "0"
    # Terminate the unary power of 2 prefix with a 0.
    remainder = number - 2**power
    while power > 0:
        power -= 1
        if remainder - 2**power >= 0:
            encoded += "1"
            remainder -= 2**power
        else:
            encoded += "0"
        # Keep subtracting the next largest power of 2 from the remainder
        # to find its binary representation.

    return encoded


def simple9_get_word_params(numbers: list) -> str:
    """This function determines the parameters to use when encoding the next
    32-bit word, including the decimal representation of the 4-bit control,
    the number of bits per code, the number of codes in the word, and the
    number of leftover bits."""
    code_lengths = [1, 2, 3, 4, 5, 7, 9, 14, 28]

    for (control, n_bits) in enumerate(code_lengths):
        n_codes = math.floor(28 / n_bits)
        # Determine how many codes can fit in a 28-bit block
        max_code = 2**n_bits
        if all(
            [
                number <= max_code
                for number in numbers[0 : min(n_codes, len(numbers) - 1)]
                # (Ensure we don't read past the end of the list of numbers.)
            ]
        ):
            n_bits_leftover = 28 - (n_bits * n_codes)
            return (control, n_bits, n_codes, n_bits_leftover)
            # If the first n_codes consecutive numbers can all be represented
            # with n_bits, then we're good to go. Otherwise, we need a bigger
            # code length.


def simple9_encode(gaps: list) -> str:
    """Perform Simple9 encoding on a gap list, returning a string of bits."""
    control, n_bits, n_codes, n_bits_leftover = simple9_get_word_params(gaps)
    encoded = f"{control:04b}"
    # Binary-encode the control with 4 bits as the start of the 32-bit block.
    for gap in gaps[0:n_codes]:
        # WARNING: I have no error handling for if a block contains more codes
        # than there are gaps left to encode because I don't actually know how
        # Simple9 deals with this.
        encoded += f"{(gap-1):0{n_bits}b}"
        # Encode the first n_codes numbers in n_bits of binary; since there are
        # no gaps of 0 in a postings list, we encode each number as 1 less.

    encoded += "0" * n_bits_leftover
    # Fill leftover bits with zeroes.

    if len(gaps) > n_codes:
        encoded += simple9_encode(gaps[n_codes:])
        # If there are more numbers to encode, then call this function
        # recursively on the rest of the list.

    return encoded


# =============================================================================
#                      HOMEWORK PROBLEM RESULTS
# =============================================================================

# PROBLEM 2(b)
print("PROBLEM 2(b)")
print("\nBinary:")
print(" ".join([f"{number:012b}" for number in [32, 57, 800]]))
print("\nGamma:")
print(gamma_encode([32, 79]))
print("\n-----------------------------------------------------------------\n")

# PROBLEM 3
print("PROBLEM 3")
lol = "11111010101110001001110010"
# prob3_gaplist = gamma_decode(
#     "1110 0101 1110 1010 1001 1111 1000 0110 1101 1101".replace(" ", "")
# )
prob3_gaplist = gamma_decode(lol)
print("\nGap List:")
print(prob3_gaplist)
print("\nDocids:")
print(gap_decode(prob3_gaplist))

print("\n-----------------------------------------------------------------\n")

# PROBLEM 4
print("PROBLEM 4")
print("\nGap List:")
prob4_gaps = gap_encode([4, 12, 15, 35, 36, 52, 102, 118, 218])
print(prob4_gaps)
print("\nSimple9:")
print(simple9_encode(prob4_gaps))
