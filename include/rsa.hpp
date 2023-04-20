#include <iostream>
#include <algorithm>
#include <time.h>

using __int64 = long long int;

struct key {
    __int64 a;
    __int64 b;
    friend std::ostream& operator<<(std::ostream& out, key& k)
    {
        out << "n: " << k.b << "\n e/d: " << k.a;
        return out;
    }
    key(int a, int b) : a(a), b(b) {}
};

class RSA {
    __int64 p, q, n, z;
    key public_key{0, 0}, private_key{0, 0};

    __int64 pow(int a, int b);
    __int64 gcd(__int64 a, __int64 b);
    int rand_interval(int min, int max);
    bool is_prime(int n);
    int rand_prime(int low, int high);
    __int64 pick_e(int z);
    __int64 pick_d(int z, int e);
    void generate_keys();

public:
    RSA();
    int encrypt(int m);
    int decrypt(int c);
    int encrypt(int m, const key& external_key);
    int decrypt(int c, const key& external_key);
    std::pair<key, key> get_keys() { return std::make_pair(public_key, private_key); }

};

RSA::RSA() {
    srand(time(NULL));
    generate_keys();
}

void RSA::generate_keys() {
    do {
        q = rand_prime(5000, 10000);
        p = rand_prime(5000, 10000);
        n = p * q;
        z = (p - 1) * (q - 1);
    } while (z <= 0);

    __int64 e = pick_e(z);
    __int64 d = pick_d(z, e);
    public_key = key(e, n);
    private_key = key(d, n);
}

//C = M^e mod N
int RSA::encrypt(int m) {
    return pow(m, public_key.a) % public_key.b;
}

//M = C^d mod N
int RSA::encrypt(int m, const key& external_key) {
    return pow(m, external_key.a) % external_key.b;
}

int RSA::decrypt(int c) {
    return pow(c, private_key.a) % private_key.b;
}

int RSA::decrypt(int c, const key& external_key) {
    return pow(c, external_key.a) % external_key.b;
}

bool RSA::is_prime(int n) {
    if (n <= 1)
        return false;
    if (n <= 3)
        return true;
    if (n % 2 == 0 || n % 3 == 0)
        return false;
    for (int i = 5; i * i <= n; i += 6)
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    return true;
}

int RSA::rand_prime(int low = 100, int high = 1000) {
    int n;
    do {
        n = rand_interval(low, high);
    } while (!is_prime(n));
    return n;
}

int RSA::rand_interval(int min, int max) {
    return rand() % (max - min + 1) + min;
}

__int64 RSA::pick_e(int z) {
    __int64 e = rand_prime();
    while (gcd(e, z) != 1)
        e++;
    return e;
}

__int64 RSA::pick_d(int z, int e) {
    __int64 d = 1;
    while ((d * e) % z != 1)
        d++;
    return d;
}

__int64 RSA::pow(int a, int b) {
    __int64 result = 1;
    for (int i = 0; i < b; i++)
        result = (result * a) % public_key.b;
    return result;
}

__int64 RSA::gcd(__int64 a, __int64 b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}
