// Дерево отрезков

// позволяет найти опреацию * на подотрезке


// Должно быть ассоциотивно : a * (b * c) = (a * b) * c
// Должен быть нейтрайльный элемент Nan : a * Nan = Nan * a = a (Для заполнения пустоты)
// свойство (a * b) = (b * a) не обязательно
// можно заменять элементы в массиве на моноиды


// Дерево отрезков снизу(обновление измененных значений)

ll sum(ll a, ll b){
    // отсчет с 1
    a += n;
    b += n;
    ll ans = 0;
    while(a <= b){
        if(a%2 == 1) ans += tree[a++];
        if(b%2 == 0) ans += tree[b--];
        a/=2;
        b/=2;
    }
    return ans;
}
    
ll add(ll ind, ll x){
    ind += n;
    tree[ind] += x;
    for(ind/=2;ind>=1;ind/=2){
        tree[ind] = tree[2*ind] + tree[2*ind+1];
    }
}


// --------------------------------------------- //
// Разностный массив где Ras[i] = a[i] - a[i-1];
// чтобы прибавить число на отрезке {a, b}
// мы увеличиваем Ras[a] и уменьшаем Ras[b+1] на x
// чтобы узнать число в i мы смотрим сумму в Ras[1 ... i];
// --------------------------------------------- //


// Дерево отрезков для модификаций

// отсчет с 0

ll sum (ll a, ll b, ll k = 1, ll l = 0, ll r = n-1){
    if(b < l or r < a)return 0;
    if(l <= a and b <= r)return tree[k];
    ll mid = (l+r)/2;
    return sum(a, b, k*2, l, mid) + sum(a, b, k*2+1, mid+1, r);
}

void add(ll ind, ll x, ll k, ll l, ll r){
    if(ind < l or r < ind)return;
    if(l == r){tree[k] += x;return;}

    ll mid = (l+r)/2;

    if(k <= mid)
        add(ind, x, k*2, l, mid);
    else
        add(ind, x, k*2+1, mid+1, r);
    
    // Обновление дерева //
    tree[k] = tree[2*k] + tree[2*k+1];
}

// Ленивое дерево отрезков

void update(ll x, ll l, ll r){
    if(!updt[x])
        return;
    
    lazy[2*x] = lazy[x];
    lazy[2*x+1] = lazy[x];
    
    ll mid = (l+r)/2;
    
    // обновление на отрезке
    tree[2*x] = lazy[x] * (mid - l + 1);
    tree[2*x+1] = lazy[x] * (r - (mid+1) + 1);
    //
    
    updt[2*x] = 1;
    updt[2*x+1] = 1;
    
    updt[x] = 0;
    lazy[x] = 0;
    
}


ll sum(ll a, ll b, ll k, ll l, ll r){
    if(b < l or r < a)return 0;
    if(a <= l and r <= b)return tree[k];
    
    // проталкивание перед рекурсивным вызовом
    update(k, l, r);
    //
    
    ll mid = (l+r) / 2;
    
    // операция пересчета вершины
    return sum(a, b, k*2, l, mid) + sum(a, b, k*2 + 1, mid+1, r);
}

void change(ll a, ll b, ll x, ll k, ll l, ll r){
    if(b < l or r < a)return;
    if(a <= l and r <= b){
        tree[k] = x * (r - l + 1);
        updt[k] = 1;
        lazy[k] = x; return;}
    
    // проталкивание перед рекурсивным вызовом
    update(k, l, r);
    //
    
    ll mid = (l+r)/2;
    
    change(a, b, x, 2 * k, l, mid);
    change(a, b, x, 2 * k + 1, mid+1, r);
    
    // операция пересчета вершины
    tree[k] = tree[2*k] + tree[2*k+1];
    //
}


ll sum(ll l, ll r){
    return sum(l, r, 1, 0, n-1);
}

void change(ll a, ll b, ll x){
    change(a, b, x, 1, 0, n-1);
}

//

// Дерево отрезков с динамическим вызовом и ленивым проталкиванием

// вместо индекса k в массиве мы будем передавать ссылку на обьем памяти с нужной вершиной

struct Node{
    bool updt;
    ll tree, lazy;
    Node *l, *r;
};

// функция для добавления вершин к веришне(чё?) которую мы ёще не трогали

void build(Node *x){
    if(x->l != NULL)return;
    
    x->l = (new Node());
    x->r = (new Node());
}


void update(Node *x, ll l, ll r){
    if(!(x->updt))
        return;
    
    
    x->l->lazy = x->lazy;
    x->r->lazy = x->lazy;
    
    
    ll mid = (l+r)/2;
    
    // обновление на отрезке
    x->l->tree = x->lazy * (mid - l + 1);
    x->r->tree = x->lazy * (r - (mid+1) + 1);
    //
    
    x->l->updt = 1;
    x->r->updt = 1;

    x->updt = 0;
    x->lazy = 0;
}


ll sum(ll a, ll b, Node *k, ll l, ll r){
    if(b < l or r < a)return 0;
    if(a <= l and r <= b)return k->tree;
    
    
    
    // проталкивание перед рекурсивным вызовом
    build(k);
    update(k, l, r);
    //
    
    ll mid = (l+r) / 2;
    
    // операция пересчета вершины
    return sum(a, b, k->l, l, mid) + sum(a, b, k->r, mid+1, r);
}

void change(ll a, ll b, ll x, Node *k, ll l, ll r){
    if(b < l or r < a)return;
    if(a <= l and r <= b){
        k->tree = x * (r - l + 1);
        k->updt = 1;
        k->lazy = x; return;}
    
    
    
    // проталкивание перед рекурсивным вызовом
    build(k);
    update(k, l, r);
    //
    
    ll mid = (l+r)/2;
    
    change(a, b, x, k->l, l, mid);
    change(a, b, x, k->r, mid+1, r);
    
    // операция пересчета вершины
    k->tree = k->l->tree + k->r->tree;
    //
}

Node Main;

ll sum(ll l, ll r){
    return sum(l, r, &Main, 0, n-1);
}

void change(ll a, ll b, ll x){
    change(a, b, x, &Main, 0, n-1);
}





