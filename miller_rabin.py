if __name__ == "__main__":
    n = 5915587276
    s = 0
    while n % 2 == 0:
        n = n // 2
        s += 1
    print(f"s: {s}")

    moduli = 6000000001
    rinv_mod_m = 2278679299
    y = n
    for i in range(10):
        y = (y * y * rinv_mod_m) % moduli
        print(f"y**2 mod m: {hex(y)}")
