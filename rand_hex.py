import random


if __name__ == "__main__":
    digits = "0123456789ABCDEF"
    print(''.join(random.choices(digits, k=9)))
    print(''.join(random.choices(digits, k=17)))

