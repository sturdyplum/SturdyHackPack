unsigned long long HashPair(unsigned long long a, unsigned long long b)
{
    return (a + b) * (a + b + 1) / 2 + a; // where a, b >= 0
}

