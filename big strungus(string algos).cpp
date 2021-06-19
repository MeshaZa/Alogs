
// Строки


//z - функция

vector<ll> z_function (string s) {
    ll n = s.size();
    vector<ll> z (n);
    
    // r = самый правый проверенный элемент
    // l = индекс значение которго приходит в r
    
    for (ll i=1, l=0, r=0; i<n; i++) {
        
        // если i входит в отрезок (l, r) то
        // то значение уже предпосчитано
        // так же для z[i-l] не даем выходить за рамки (мы подсчитаем их потом)
        
        if (i <= r)
            z[i] = min(r-i+1, z[i-l]);
        
        
        // увеличиваем значения вручную
        
        while (i+z[i] < n && s[z[i]] == s[i+z[i]])
            ++z[i];
        
        // если увеличения вручную превысили r то обновляем значения
        
        if (i+z[i]-1 > r)
            l = i,  r = i+z[i]-1;
    }
    
    return z;
}

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


