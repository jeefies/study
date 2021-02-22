nums = "0123456789"
lower = "abcdefghijklmnopqrstuvwxyz"
upper = lower.upper()
other = (".-:+=^!/"
        "*?&<>()[]{"
        "}@%$#")
encoder = nums + lower + upper + other

def p85en(b, chars)
