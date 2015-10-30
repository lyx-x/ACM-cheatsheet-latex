struct node_t
{
    node_t *l; // < x
    node_t *r; // >= x
    long long y;
    long long x, value; // the value can be sum or max, etc.
    int size;
    bool reversed;
 
    node_t(long long _x): l(NULL), r(NULL), y(rand() * RAND_MAX + rand()), x(_x),
            value(_x), size(1), reversed(false) {}
 
    void display() {
        push_reverse();
        update();
 
        if (l != NULL)
            l->display();
        cerr << x << " ";
        if (r != NULL)
            r->display();
    }
 
    void update() {
        size = 1;
        value = x;
        if (l != NULL) {
            size += l->size;
            value += l->value; // sum version
        }
        if (r != NULL) {
            size += r->size;
            value += r->value;
        }
    }
 
    void push_reverse() {
        if (reversed) {
            if (r != NULL)
                r->reversed = !r->reversed;
            if (l != NULL)
                l->reversed = !l->reversed;
            swap(r, l);
            reversed = false;
        }
    }
};
 
pair<node_t*, node_t*> split(node_t *t, int s) {
    if (t == NULL)
        return make_pair(nullptr, nullptr);
 
    t->push_reverse();
 
    int left_size = (t->l == NULL) ? 0 : t->l->size;
 
    if (s <= left_size) {
        auto p = split(t->l, s);
        t->l = p.second;
        t->update();
        t->push_reverse();
        return make_pair(p.first, t);
    }
    else {
        auto p = split(t->r, s - left_size - 1);
        t->r = p.first;
        t->update();
        t->push_reverse();
        return make_pair(t, p.second);
    }
}
 
node_t* merge(node_t* a, node_t* b) {
    if (a == NULL)
        return b;
    if (b == NULL)
        return a;
 
    a->push_reverse();
    b->push_reverse();
 
    if (a->y < b->y) {
        a->r = merge(a->r, b);
        a->update();
        return a;
    }
    else {
        b->l = merge(a, b->l);
        b->update();
        return b;
    }
}
 
node_t* insert_pos(node_t* t, int pos, int x) {
    auto p = split(t, pos);
    node_t* tmp = merge(p.first, new node_t(x));
    return merge(tmp, p.second);
}
 
void reverse(node_t* t, int l, int r) {
    auto x = split(t, r);
    auto y = split(x.first, l - 1);
    if (y.second != NULL) {
        y.second->reversed = !y.second->reversed;
        y.second->push_reverse();
    }
    t = merge(merge(y.first, y.second), x.second);
}
 
long long get_sum(node_t* t, int l, int r) {
    auto x = split(t, r);
    auto y = split(x.first, l - 1);
    long long res = 0;
    if (y.second != NULL)
        res = y.second->value;
    t = merge(merge(y.first, y.second), x.second);
    return res;
}