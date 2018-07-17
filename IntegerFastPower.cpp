int fast_pow(int a, int b, int p) {
    int r = 1, base = a % p;
    for(;b;b>>1){
        if (b & 1)  r = (r * base) % p;
        base = (base * base) % p;
    }
    return r;
}
