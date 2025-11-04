from decimal import ROUND_HALF_UP, Decimal, getcontext


def format_with_fixed_exp(x, fixed_exp, sig_digits=4):
    # small extra precision to avoid rounding surprises
    getcontext().prec = sig_digits + 6
    d = Decimal(str(x)) / (Decimal(10) ** fixed_exp)
    if d == 0:
        digits_before = 1
    else:
        digits_before = d.adjusted() + 1
    dec_places = max(sig_digits - digits_before, 0)
    q = Decimal(1).scaleb(-dec_places)  # 10**(-dec_places)
    rounded = d.quantize(q, rounding=ROUND_HALF_UP)
    # format exponent as e+03 style
    return f"{rounded}e{fixed_exp:+03d}"


while True:
    [left, right] = map(lambda x: int(x), input().split(" "))
    if left == 0 and right == 0:
        break

    res = Decimal(0)
    for i in range(left, right + 1):
        i = Decimal(i)
        res += (i + Decimal(1e-15)) ** Decimal(1 / 3) - i ** Decimal(1 / 3)
