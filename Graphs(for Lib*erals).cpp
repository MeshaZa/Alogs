// Графы (жестка)

//
Флойд за n^3(Без отрицательных циклов, можно найти на n+1 ой операции)
//

for(k = 0;k<n;k++)
        for(i = 0;i<n;i++)
            for(j = 0;j<n;j++)
                if(d[i][k] < INF and d[k][j] < INF)
                    d[i][j] = min(d[i][j], d[i][k]+d[k][j]);

//
Форд-беллман за n*m(Без отрицательных циклов, можно найти на nой операции)
//

struct edge {
    int a, b, cost;
};
 
int n, m, v;
vector<edge> e;
const int INF = 1000000000;
 
void solve() {
    vector<int> d (n, INF);
    d[v] = 0;
    for (int i=0; i<n-1; ++i)
        for (int j=0; j<m; ++j)
            if (d[e[j].a] < INF)
                d[e[j].b] = min (d[e[j].b], d[e[j].a] + e[j].cost);
}

//
Дейкстра за m log n (Отрицательные вершины - ужас)
//

// Ищем минимальную не использованную вершину и
// обновляем через ее ребра другие вершины

#define INF = 1000000000;
 
int main() {
    int n;
    ... чтение n ...
    vector<vector<pair<int,int>>> g(n);
    ... чтение графа ...
    int s = ...; // стартовая вершина
 
    vector<int> d(n, INF),  p(n);
    d[s] = 0;
    set<pair<int,int>> q;
    q.insert({d[s], s});
    
    while (!q.empty()) {
        int v = q.begin()->second;
        q.erase (q.begin());
 
        for (size_t j=0; j<g[v].size(); ++j) {
            int to = g[v][j].first,
                len = g[v][j].second;
            if (d[v] + len < d[to]) {
                q.erase ({d[to], to});
                d[to] = d[v] + len;
                p[to] = v;
                q.insert ({d[to], to});
            }
        }
    }
}

//
сиска за n * k(n)
//

(Брать минимальное ребро до образования циклов)

link[i] = i
size[i] = 1;

ll find(ll x){
    if(x == link[x])return x;
    return link[x] = find(link[x]);
}

void add(ll a, ll b){
    a = find(a);
    b = find(b);
    if(size[a] < size[b])swap(a,b);
    link[b] = a;
    size[a] += size[b];
}

//
Алгоритм Крускала за(n*n)
//

// храним минимальное ребро от уаждой не приклееной вершины,
// на каждой операции приклеиваем вершину с мин ребром и обновляем
// через него другие не выбранные вершины

// входные данные
int n;
vector < vector<int> > g;
const int INF = 1000000000; // значение "бесконечность"
 
// алгоритм
vector<bool> used (n);
vector<int> min_e (n, INF), sel_e (n, -1);
min_e[0] = 0;
for (int i=0; i<n; ++i) {
    int v = -1;
    for (int j=0; j<n; ++j)
        if (!used[j] && (v == -1 || min_e[j] < min_e[v]))
            v = j;
    if (min_e[v] == INF) {
        cout << "No MST!";
        exit(0);
    }
 
    used[v] = true;
    if (sel_e[v] != -1)
        cout << v << " " << sel_e[v] << endl;
 
    for (int to=0; to<n; ++to)
        if (g[v][to] < min_e[to]) {
            min_e[to] = g[v][to];
            sel_e[to] = v;
        }
}

//
эйлеров цикл за (m)
//

vector<ll> ans;
vector<ll> edge[SIZE];

ll dfs(ll x){
    for(ll i = 0; i < edge[x].size();i++)
        if(edge[x][i] != -1){
            ll layer = edge[x][i];
            edge[x][i] = -1;
            dfs(layer);
    }
    ans.push_back(x);
}

//
топологическая сортировка
//

ll used[SIZE];
vector<ll> ans;
vector<ll> edge[SIZE];

ll dfs(ll x){
    was[x] = 1;
    for(auto u : edge[x])
        if(!was[u])
            dfs(u);
    
    ans.push_back(x);
}

reverse(ans);


// Поиск компонент сильной связности, построение конденсации графа

vector < vector<int> > g, gr;
vector<char> used;
vector<int> order, component;
 
void dfs1 (int v) {
    used[v] = true;
    for (size_t i=0; i<g[v].size(); ++i)
        if (!used[ g[v][i] ])
            dfs1 (g[v][i]);
    order.push_back (v);
}
 
void dfs2 (int v) {
    used[v] = true;
    component.push_back (v);
    for (size_t i=0; i<gr[v].size(); ++i)
        if (!used[ gr[v][i] ])
            dfs2 (gr[v][i]);
}
 
int main() {
    int n;
    ... чтение n ...
    for (;;) {
        int a, b;
        ... чтение очередного ребра (a,b) ...
        g[a].push_back (b);
        gr[b].push_back (a);
    }
 
    used.assign (n, false);
    for (int i=0; i<n; ++i)
        if (!used[i])
            dfs1 (i);
    used.assign (n, false);
    for (int i=0; i<n; ++i) {
        int v = order[n-1-i];
        if (!used[v]) {
            dfs2 (v);
            ... вывод очередной component ...
            component.clear();
        }
    }
}


// мосты

const int MAXN = ...;
vector<int> g[MAXN];
bool used[MAXN];
int timer, tin[MAXN], fup[MAXN];
 
void dfs (int v, int p = -1) {
    used[v] = true;
    tin[v] = fup[v] = timer++;
    for (size_t i=0; i<g[v].size(); ++i) {
        int to = g[v][i];
        if (to == p)  continue;
        if (used[to])
            fup[v] = min (fup[v], tin[to]);
        else {
            dfs (to, v);
            fup[v] = min (fup[v], fup[to]);
            if (fup[to] > tin[v])
                IS_BRIDGE(v,to);
        }
    }
}
 
void find_bridges() {
    timer = 0;
    for (int i=0; i<n; ++i)
        used[i] = false;
    for (int i=0; i<n; ++i)
        if (!used[i])
            dfs (i);
}


// шарниры

vector<int> g[MAXN];
bool used[MAXN];
int timer, tin[MAXN], fup[MAXN];
 
void dfs (int v, int p = -1) {
    used[v] = true;
    tin[v] = fup[v] = timer++;
    int children = 0;
    for (size_t i=0; i<g[v].size(); ++i) {
        int to = g[v][i];
        if (to == p)  continue;
        if (used[to])
            fup[v] = min (fup[v], tin[to]);
        else {
            dfs (to, v);
            fup[v] = min (fup[v], fup[to]);
            if (fup[to] >= tin[v] && p != -1)
                IS_CUTPOINT(v);
            ++children;
        }
    }
    if (p == -1 && children > 1)
        IS_CUTPOINT(v);
}
 
int main() {
    int n;
    ... чтение n и g ...
 
    timer = 0;
    for (int i=0; i<n; ++i)
        used[i] = false;
    dfs (0);
}


// двоичные подъемы

ll up[SIZE][22];
vector<ll> edges[SIZE];

void hang(ll v = 1, ll p=0){
    up[v][0] = p;
    ll deg = 1;
    
    while(up[v][deg-1])
        up[v][deg] = up[up[v][deg-1]][deg-1], deg++;
    
    for(auto u : edges[v])
        if(u != p)
            hang(u, v);
}

ll find(ll v, ll x){
    ll deg = 0;
    while(x){
        if(x%2)
            v = up[v][deg];
        deg++;
        x/=2;
    }
    return v;
}

