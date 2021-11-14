int gcd (int a, int b) {
    return b ? gcd (b, a % b) : a;
}

int lcm (int a, int b) {
    return a / gcd (a, b) * b;
}

int n;
vector<char> prime (n+1, true);
prime[0] = prime[1] = false;
for (int i=2; i<=n; ++i)
    if (prime[i])
        if (i * 1ll * i <= n)
            for (int j=i*i; j<=n; j+=i)
                prime[j] = false;
