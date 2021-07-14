def round_to_double(x: int) -> int:
    # Truncate interger to make it fit in IEEE-754 double.
    if x == 0:
        return 0

    # Remove trailing zeros because it's represented in the exponent part.
    # Assumes x can be expressed by the exponent part without loss.
    num_trailing_zero = 0
    while x & 1 == 0:
        num_trailing_zero += 1
        x //= 2

    binary = bin(x).lstrip('0b')
    significand_candidate = int(binary[:53], 2)
    rounded_out = binary[53:]

    if rounded_out:
        # round-to-even
        half = '1' + '0' * (len(rounded_out) - 1)
        # print(f'{rounded_out} {half}')
        if rounded_out < half:
            significand = significand_candidate
        if rounded_out > half:
            significand = significand_candidate + 1
        elif rounded_out == half:
            significand = significand_candidate + (significand_candidate & 1)

    result = significand * 2 ** (num_trailing_zero + len(rounded_out))
    return result


def bytes_to_bits(data: bytes, byteorder: str = 'little') -> str:
    # https://stackoverflow.com/a/43787135
    # Leading zeros will be stripped away when converted to int.
    stripped_binary = bin(int.from_bytes(data, byteorder=byteorder)).lstrip('0b')
    return'0' * (len(data) * 8 - len(stripped_binary)) + stripped_binary


def interpret_IEEE754_double(raw_data: bytes, byteorder: str = 'little') -> int:
    """ Only handles normalized positive integers. """
    binary = bytes_to_bits(raw_data, byteorder)
    exponent = int(binary[1: 1 + 11], 2) - (2 ** 10 - 1)
    value = int('1' + binary[1 + 11: 1 + 11 + min(exponent, 52)] + '0' * max(exponent - 52, 0), 2)
    print(binary, exponent, value)


# Paste the output of 2.89.c here.
x, y, z = 1208192249, 1962479619, 2081355124
dxdy = 2371052664496272896
exp1 = 4935002612523170298928824320
dydz = 4084617010751217664
exp2 = 4935002612523170848684638208

dxdy_expected = round_to_double(x * y)
exp1_expected = round_to_double(round_to_double(x * y) * z)
dydz_expected = round_to_double(y * z)
exp2_expected = round_to_double(x * round_to_double(y * z))

print(dxdy_expected, dxdy_expected == dxdy)
print(exp1_expected, exp1_expected == exp1)
print(dydz_expected, dydz_expected == dydz)
print(exp2_expected, exp2_expected == exp2)
