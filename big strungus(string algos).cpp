
// Строки


//z - функция


// Префикс функция

vector<ll> pref_func(string s){
    ll n = s.size();
    vector<ll> p(n);
    
    loop(i = 1; i < n;i++){
        ll j = p[i-1];
        
        while(j > 0 and s[j] != s[i])
            j = p[j-1];
    
        j += s[j] == s[i];
        
        p[i] = j;
    }
    
    return p;
}


// Хэши

h[i] = (h[i-1] * P) % R
h[a...b] = (h[b] - h[a-1] * P^(b-a+1)) % R


