struct Node{ll tree, heap; Node *l, *r;};

Node *merge(Node *L, Node *R){
    
    // Нет ситуации кокгда L == R == NULL
    
    if(L == NULL)
        return R;
    
    if(R == NULL)
        return L;
    
    if(L->heap > R->heap){
        L->r = merge(L->r, R);
        return L;
    }
    
    R->l = merge(L, R->l);
    return R;
}

pair<Node*, Node*> split(Node *x, ll n){
    if(x == NULL)
        return {NULL, NULL};
    
    if(x->tree < n){
        pair<Node*, Node*> Y = split(x->r, n);
        x->r = Y.f;
        return {x, Y.s};
    }
    
    pair<Node*, Node*> Y = split(x->l, n);
    x->l = Y.s;
    return {Y.f, x};
}

Node *Main = NULL;

Node *add(ll n, Node *x = Main){
    pair<Node*, Node*> tree = split(x, n);
    
    
    return merge(tree.f, merge(new Node({n, rand() % INF, NULL, NULL}), tree.s));
}

void draw(Node *x){
    
    queue<Node *> q;
    
    q.push(x);
    
    while(!q.empty()){
        Node* o = q.front();
        q.pop();
        
        if(o == NULL)continue;
        
        q.push(o->l);
        q.push(o->r);
        
        if(o->l != NULL)
            cout << "Val : " << o->tree << " Ran : " << o->heap << " LSon : " << o->l->tree << '\n';
        
        if(o->r != NULL)
            cout << "Val : " << o->tree << " Ran : " << o->heap << " RSon : " << o->r->tree << '\n';
    }
    
}
