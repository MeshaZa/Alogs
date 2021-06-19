
// Графы (жестка)

//
Флойд за n^3(Без отрицательных циклов, можно найти на n+1 ой операции)
//

for(k = 0;k<n;k++)
        for(i = 0;i<n;i++)
            for(j = 0;j<n;j++)
                d[i][j] = min(d[i][j], d[k][j]+d[i][k]);

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

//



