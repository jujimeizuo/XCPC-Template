struct Tree {
    Tree *l;
    Tree *r;
    int x;
    int siz;
    Tree(Tree *v) { *this = *v; }
    Tree(int x = 0) : l(nullptr), r(nullptr), x(x), siz(1) {}
    void pull() {
        siz = 1;
        if (l != nullptr) {
            siz += l->siz;
        }
        if (r != nullptr) {
            siz += r->siz;
        }
    }
};
 
int cnt = 0;
constexpr int N = 1e7;
Tree pool[N];
 
std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
 
template<class... T>
Tree *newTree(T... x) {
    Tree *t = &pool[cnt++];
    *t = Tree(x...);
    return t;
}
 
Tree *merge(Tree *a, Tree *b) {
    if (a == nullptr) {
        return b;
    }
    if (b == nullptr) {
        return a;
    }
    Tree *t;
    if (int(rnd() % (a->siz + b->siz)) < a->siz) {
        t = newTree(a);
        t->r = merge(t->r, b);
    } else {
        t = newTree(b);
        t->l = merge(a, t->l);
    }
    t->pull();
    return t;
}
 
std::pair<Tree *, Tree *> split(Tree *t, int k) {
    if (t == nullptr || k == 0) {
        return {nullptr, t};
    }
    if (t->siz == k) {
        return {t, nullptr};
    }
    int szl = t->l == nullptr ? 0 : t->l->siz;
    Tree *u = newTree(t);
    if (k <= szl) {
        auto [a, b] = split(t->l, k);
        u->l = b;
        u->pull();
        return {a, u};
    } else {
        auto [a, b] = split(t->r, k - 1 - szl);
        u->r = a;
        u->pull();
        return {u, b};
    }
}