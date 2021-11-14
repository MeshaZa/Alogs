// convex-hull trick

typedef long double ld;
typedef __int128 fbl;

struct line{
    ll a, b;
    line(ll _a, ll _b){a = _a;b = _b;}
    ll get(ll x){return a*x+b;}
};

struct dot{
    // int128 для нормального сравнивания дробей
    fbl x, y;
    dot(ll _x, ll _y){x=fbl(_x);y=fbl(_y);}
};

dot cross(line a, line b){
    dot ans(b.b-a.b, a.a-b.a);
    return ans;
}

bool comp(dot a, dot b){
    return a.x*b.y < b.x*a.y;
}

vector<dot> dots;
vector<line> lines;

void add(line next){

    if(lines.empty()){lines.pb(next);return;}

    while(dots.size() and comp(cross(lines.back(), next), dots.back())){
        lines.ppb();
        dots.ppb();
    }
    
    dots.pb(cross(lines.back(), next));
    lines.pb(next);
}

ll get(ll x){
    dot now(x, 1);
    ll ind = lower_bound(dots.begin(), dots.end(), now, comp)-dots.begin();
    return lines[ind].get(x);
}




// Li Chao Tree

typedef complex<long long> line;
#define xs real
#define ys imag

line tree[8*SIZE];


ll func(line a, ll x){
    line now(x, 1);
    return (conj(a) * now).xs();
}


void add(line next, ll l, ll r, ll k){
    ll mid = (l+r)/2; 
    bool left = func(next, l) < func(tree[k], l);
    bool middle = func(next, mid) < func(tree[k], mid);
    if(middle)swap(tree[k], next);
    if(r-l == 1)return;
    if(left != middle)
        add(next, l, mid, k*2);
    else
        add(next, mid, r, k*2+1);
}

ll get(ll x, ll l, ll r, ll k){
    ll mid = (l+r)/2;
    if(r-l==1)
        return func(tree[k], x);
    else if(x < m)
        return min(func(tree[k], x), get(x, l, mid, k*2));
    else
        return min(func(tree[k], x), get(x, mid, r, k*2+1));
}

void add(ll a, ll k){
    line newline(a, k);
    add(newline, 0, n, 1);
}

ll get(ll x){
    return get(x, 0, n, 1);
}


// разделяйка








