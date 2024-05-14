def egcd(a, b):
    if a == 0:
        return (b, 0, 1)
    else:
        g, y, x = egcd(b % a, a)
        return (g, x - (b // a) * y, y)

def modinv(a, m):
    g, x, y = egcd(a, m)
    if g != 1:
        raise Exception('Modular inverse does not exist')
    else:
        return x % m

def hex_modinv(a_hex, m_hex):
    a = int(a_hex, 16)
    m = int(m_hex, 16)
    inv = modinv(a, m)
    return hex(inv)[2:]  # Remove '0x' prefix from hex representation

if __name__ == "__main__":
    with open("data/inputs_bigint-inverse-12.txt", "r") as f:
        lines = f.readlines()
        a_s = ""
        m_s = ""
        invs = ""
        for line in lines:
            a_hex, m_hex = line.split()
            result = hex_modinv(a_hex, m_hex)
            a_s += ('"' + a_hex + '"' + ", ")
            m_s += ('"' + m_hex + '"'  + ", ")
            invs += ('"' + result + '"'  + ", ")
        print(f"a_s: {a_s}")
        print(f"m_s: {m_s}")
        print(f"invs: {invs}")
