/*
 * CareFree Library
 * CopyRight (c) xiezheyuan 2024 - now
 * Visit https://github.com/xiezheyuan/carefree/ for more information.
 */

#pragma once

#if __cplusplus < 201402L
#error "carefree library need C++ 14 or higher version"
#endif
#ifndef __GNUC__
#error "carefree library need GCC compiler or similar"
#endif

#define CAREFREE_VERSION_MAJOR 0
#define CAREFREE_VERSION_MINOR 3
#define CAREFREE_VERSION "0.3"

#include <unistd.h>

#include <algorithm>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <initializer_list>
#include <iostream>
#include <queue>
#include <random>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <typeinfo>
#include <vector>

namespace carefree_internal {

    using std::string;

    struct carefree_exception_name {
        string cls_name;
        carefree_exception_name() { cls_name = "carefree_exception"; }
    };

    template <class cpp_err_type, class err_name = carefree_exception_name>
    class carefree_exception {
    protected:
        string msg;
        string cls_name;

    public:
        using err_type = cpp_err_type;
        carefree_exception() { cls_name = err_name().cls_name; }
        carefree_exception(string msg) : msg(msg) { cls_name = err_name().cls_name; }
        carefree_exception(const char* msg) {
            this->msg = msg;
            cls_name = err_name().cls_name;
        }
        string what() { return cls_name + " : " + get_msg(); }
        cpp_err_type get_err() { return err_type(what()); };
        string get_msg() { return msg; }
    };

    struct carefree_invalid_argument_name {
        string cls_name;
        carefree_invalid_argument_name() { cls_name = "carefree_invalid_argument"; }
    };

    struct carefree_range_exception_name {
        string cls_name;
        carefree_range_exception_name() { cls_name = "carefree_range_exception"; }
    };

    struct carefree_unsupported_operation_name {
        string cls_name;
        carefree_unsupported_operation_name() { cls_name = "carefree_unsupported_operation"; }
    };

    struct carefree_file_exception_name {
        string cls_name;
        carefree_file_exception_name() { cls_name = "carefree_file_exception"; }
    };

    struct carefree_runtime_exception_name {
        string cls_name;
        carefree_runtime_exception_name() { cls_name = "carefree_runtime_exception"; }
    };

    using carefree_invalid_argument = carefree_exception<std::invalid_argument, carefree_invalid_argument_name>;
    using carefree_range_exception = carefree_exception<std::out_of_range, carefree_range_exception_name>;
    using carefree_unsupported_operation = carefree_exception<std::logic_error, carefree_unsupported_operation_name>;
    using carefree_file_exception = carefree_exception<std::runtime_error, carefree_file_exception_name>;
    using carefree_runtime_exception = carefree_exception<std::runtime_error, carefree_runtime_exception_name>;

    enum exception_policy {
        Throw,
        Ignore,
        Friendly,
        Simulate,
    };

    exception_policy exception_policy_val = exception_policy::Throw;

    exception_policy get_exception_policy() noexcept {
        return exception_policy_val;
    }

    template <class T1, class T2>
    void raise(carefree_exception<T1, T2> err) {
        switch (get_exception_policy()) {
            case Throw:
                throw err.get_err();
                break;
            case Ignore:
                std::fprintf(stderr, "CareFree Library : An Error Occured.\n%s\n", err.what().c_str());
                break;
            case Friendly:
                std::fprintf(stderr, "CareFree Library : An Error Occured.\n%s\n", err.what().c_str());
                exit(0);
                break;
            case Simulate:
                std::fprintf(stderr, "CareFree Library : An Error Occured.\n%s\n", err.what().c_str());
                std::terminate();
                break;
            default:
                __builtin_unreachable();
                std::abort();
                break;
        }
    }

    template <class T>
    void err_range_checker(T l, T r, string func_name) {
        string errmsg = func_name + " : " + "l(" + std::to_string(l) + ") > r(" + std::to_string(r) + ").";
        if (l > r) raise(carefree_range_exception(errmsg));
    }

    template <class T>
    void err_unempty_checker(T x, string func_name, string var_name) {
        string errmsg = func_name + " : " + var_name + " is empty.";
        if (x.empty()) raise(carefree_invalid_argument(errmsg));
    }

    template <class T>
    void err_positive_checker(T x, string func_name, string var_name) {
        string errmsg = func_name + " : " + var_name + "(" + std::to_string(x) + ") is not positive.";
        if (x <= 0) raise(carefree_invalid_argument(errmsg));
    }

    template <class T>
    void err_natural_checker(T x, string func_name, string var_name) {
        string errmsg = func_name + " : " + var_name + "(" + std::to_string(x) + ") is not natural.";
        if (x < 0) raise(carefree_invalid_argument(errmsg));
    }

    template <class T>
    void err_inrange_checker(T x, T l, T r, string func_name, string var_name) {
        string errmsg = func_name + " : " + var_name + "(" + std::to_string(x) + ") is not in range [" + std::to_string(l) + ", " + std::to_string(r) + "].";
        if (x < l || x > r) raise(carefree_range_exception(errmsg));
    }

    template <class T>
    void err_less_checker(T x, T l, string func_name, string var_name) {
        string errmsg = func_name + " : " + var_name + "(" + std::to_string(x) + ") is not less than " + std::to_string(l) + ".";
        if (x >= l) raise(carefree_range_exception(errmsg));
    }

    template <class T>
    void err_greater_checker(T x, T l, string func_name, string var_name) {
        string errmsg = func_name + " : " + var_name + "(" + std::to_string(x) + ") is not greater than " + std::to_string(l) + ".";
        if (x <= l) raise(carefree_range_exception(errmsg));
    }

    template <class T>
    void err_leq_checker(T x, T l, string func_name, string var_name) {
        string errmsg = func_name + " : " + var_name + "(" + std::to_string(x) + ") is not less than or equal to " + std::to_string(l) + ".";
        if (x > l) raise(carefree_range_exception(errmsg));
    }

    template <class T>
    void err_geq_checker(T x, T l, string func_name, string var_name) {
        string errmsg = func_name + " : " + var_name + "(" + std::to_string(x) + ") is not greater than or equal to " + std::to_string(l) + ".";
        if (x < l) raise(carefree_range_exception(errmsg));
    }

    template <class T>
    void err_equal_checker(T x, T l, string func_name, string var_name) {
        string errmsg = func_name + " :" + var_name + "(" + std::to_string(x) + ") is not equal to " + std::to_string(l) + ".";
        if (x != l) raise(carefree_range_exception(errmsg));
    }

    template <class T>
    void err_unequal_checker(T x, T l, string func_name, string var_name) {
        string errmsg = func_name + " : " + var_name + "(" + std::to_string(x) + ") is not unequal to " + std::to_string(l) + ".";
        if (x == l) raise(carefree_range_exception(errmsg));
    }

    void set_exception_policy(exception_policy policy) {
        if (policy != Throw && policy != Ignore && policy != Friendly && policy != Simulate) {
            raise(carefree_invalid_argument("set_exception_policy : unsupport policy."));
        }
        exception_policy_val = policy;
    }

    // type convert

    template <class T1, class T2>
    std::string join_str(T1 a, T2 b) {
        return string(a) + string(b);
    }

    template <class T>
    string __fts(T val, unsigned precision = 10) {
        static char buffer[255], buffer2[2047];
        if (std::is_same<T, float>::value)
            sprintf(buffer, "%%.%df", precision);
        else if (std::is_same<T, double>::value)
            sprintf(buffer, "%%.%dlf", precision);
        else if (std::is_same<T, long double>::value)
            sprintf(buffer, "%%.%dlf", precision);
        else {
            const std::type_info& x = typeid(T);
            raise(carefree_invalid_argument(join_str("__fts : unsupport type ", x.name()).c_str()));
        }
        sprintf(buffer2, buffer, val);
        string str(buffer2);
        return str;
    }

    string fts(float val, unsigned precision = 10) {
        return __fts(val, precision);
    }

    string fts(double val, unsigned precision = 10) {
        return __fts(val, precision);
    }

    string fts(long double val, unsigned precision = 10) {
        return __fts(val, precision);
    }

    template <class T>
    std::vector<string> fts(std::vector<T> val, unsigned precision = 10) {
        std::vector<string> ans;
        for (auto it = val.begin(); it != val.end(); ++it) {
            ans.push_back(fts(*it, precision));
        }
        return ans;
    }

    template <class T>
    std::vector<T> ltv(std::initializer_list<T> val) {
        return std::vector<T>(val);
    }

    // random tricks

    std::mt19937_64 public_random_engine;

    template <class T>
    T randint(T l, T r) {
        err_range_checker(l, r, __func__);
        return std::uniform_int_distribution<T>(l, r)(public_random_engine);
    }

    template <class T>
    T uniform(T l, T r) {
        err_range_checker(l, r, __func__);
        return std::uniform_real_distribution<T>(l, r)(public_random_engine);
    }

    double random() {
        return uniform(0.0, 1.0);
    }

    template <class T>
    typename T::value_type choice(T val) {
        err_unempty_checker(val, __func__, "val");
        return val[randint(0ull, val.size() - 1)];
    }

    template <class T>
    void shuffle(T val) {
        std::shuffle(val.begin(), val.end(), public_random_engine);
    }

    // sequence & string generator

    template <class T, class Value>
    std::vector<Value> sequence(int n, T function) {
        std::vector<Value> data;
        err_positive_checker(n, __func__, "n");
        for (int i = 1; i <= n; i++) {
            data.push_back(function(i));
        }
        return data;
    }

    template <class T>
    std::vector<T> sequence(int n, T l, T r) {
        static_assert(std::is_integral<T>::value || std::is_floating_point<T>::value, "T must be integral or floating point");
        return sequence(n, [&](int i) {
            if (std::is_integral<T>::value)
                return (T)randint(l, r);
            else
                return (T)uniform(l, r);
        });
    }

    template <class T>
    std::vector<T> sequence(int lengthL, int lengthR, T l, T r) {
        static_assert(std::is_integral<T>::value || std::is_floating_point<T>::value, "T must be integral or floating point");
        return sequence(randint(lengthL, lengthR), [&](int i) {
            if (std::is_integral<T>::value)
                return (T)randint(l, r);
            else
                return (T)uniform(l, r);
        });
    }

    template <class T>
    std::vector<T> real_cutting(int length, T total) {
        err_positive_checker(length, __func__, "length");
        std::vector<T> data;
        for (int i = length; i >= 2; i--) {
            int tmp = uniform(0.0, total / i * 2);
            data.push_back(tmp);
            total = total - tmp;
        }
        data.push_back(total);
        shuffle(data);
        return data;
    }

    template <class T>
    std::vector<T> int_cutting(int length, T total) {
        err_positive_checker(length, __func__, "length");
        std::vector<double> data = real_cutting(length, (double)total);
        std::vector<T> data2;
        for (int i = 0; i < data.size(); i++) data2.push_back((T)data[i]);
        T delta = total - std::accumulate(data2.begin(), data2.end(), T(0.0));
        for (T i = 1; i <= delta; i = i + 1) data2[randint(0, length - 1)] += 1;
        shuffle(data2);
        return data2;
    }

    namespace strsets {
        const string lower = "abcdefghijklmnopqrstuvwxyz";
        const string upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        const string digit = "0123456789";
        const string alphanum = lower + upper + digit;
        const string alphabet = lower + upper;
        const string slug = lower + digit + "-";
        const string var_name = lower + upper + digit + "_";
        const string bracket_general = "()[]{}<>";
        const string bracket = "()[]{}";
        const string quotes = "\"'";
        const string math_symbols_naive = "+-*";
        const string math_symbols_simple = "+-*/%";
        const string math_symbols = math_symbols_simple + "^";
        const string bool_symbols = "|&!";
        const string bitwise_symbols = bool_symbols + "~^";
    }  // namespace strsets

    string randstr(int length, const string sset = strsets::lower) {
        err_natural_checker(length, __func__, "length");
        err_unempty_checker(sset, __func__, "sset");
        string str;
        for (int i = 0; i < length; i++) str += choice(sset);
        return str;
    }

    string randstr(int lengthL, int lengthR, const string sset = strsets::lower) {
        return randstr(randint(lengthL, lengthR), sset);
    }

    // batching and timer

    template <class T>
    double timer(T function) {
        auto start = std::chrono::system_clock::now();
        function();
        auto end = std::chrono::system_clock::now();
        return (double)std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
    }

    template <class T>
    void gen_data(int subtask_count, int task_per_subtask, T function) {
        err_positive_checker(subtask_count, __func__, "subtask_count");
        err_positive_checker(task_per_subtask, __func__, "task_per_subtask");
        int total_tasks = subtask_count * task_per_subtask;
        int current_task = 0;
        double average = 0;
        int barWidth = 100;
        std::cout << "[";
        for (int k = 0; k < barWidth; ++k) {
            std::cout << " ";
        }
        std::cout << "] " << 0 << "% ";
        std::cout << "#-# N/A it / s\r";
        for (int i = 1; i <= subtask_count; i++) {
            for (int j = 1; j <= task_per_subtask; j++) {
                double time_ = timer([&]() {
                    function(i, j);
                });
                average += time_;
                current_task++;
                float progress = static_cast<float>(current_task) / total_tasks;
                int pos = static_cast<int>(barWidth * progress);
                std::cout << "[";
                for (int k = 0; k < barWidth; ++k) {
                    if (k < pos)
                        std::cout << "=";
                    else if (k == pos)
                        std::cout << ">";
                    else
                        std::cout << " ";
                }
                std::cout << "] " << int(progress * 100.0) << "% ";
                std::cout << i << "-" << j << " ";
                std::cout << fts(average / current_task, 2) << " it / s";
                std::cout << "\r";
                std::cout.flush();
            }
        }
        std::cout << std::endl;
    }

    template <class T>
    void gen_data(int task_count, T function) {
        err_positive_checker(task_count, __func__, "task_count");
        int total_tasks = task_count;
        int current_task = 0;
        double average = 0;
        int barWidth = 100;
        std::cout << "[";
        for (int k = 0; k < barWidth; ++k) {
            std::cout << " ";
        }
        std::cout << "] " << 0 << "% ";
        std::cout << "# N/A it / s\r";
        for (int i = 1; i <= task_count; i++) {
            double time_ = timer([&]() {
                function(i);
            });
            average += time_;
            current_task++;
            float progress = static_cast<float>(current_task) / total_tasks;
            int pos = static_cast<int>(barWidth * progress);
            std::cout << "[";
            for (int k = 0; k < barWidth; ++k) {
                if (k < pos)
                    std::cout << "=";
                else if (k == pos)
                    std::cout << ">";
                else
                    std::cout << " ";
            }
            std::cout << "] " << int(progress * 100.0) << "% ";
            std::cout << i << " ";
            std::cout << fts(average / current_task, 2) << " it / s";
            std::cout << "\r";
            std::cout.flush();
        }
        std::cout << std::endl;
    }

    __attribute__((constructor)) static void init_rnd_seed() {
        public_random_engine.seed(std::time(NULL));
    }

    // useful data structures

    template <class T, class Compare = std::less<T> >
    class BalancedTree {
    private:
        __gnu_pbds::tree<T, __gnu_pbds::null_type, Compare, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update> tree;

    public:
        void insert(T x) { tree.insert(x); }
        bool erase(T x) { return tree.erase(x); }
        int rnk(T x) { return tree.order_of_key(x) + 1; }
        T kth(int x) { return *tree.find_by_order(x - 1); }
        int size() { return tree.size(); }
        bool empty() { return tree.empty(); }
    };

    // graph structure

    using _Weight = long long;

    class graph {
    public:
        struct edge {
            int from, to;
            _Weight weight;
            edge(int from, int to, _Weight weight = 0) : from(from), to(to), weight(weight) {}
        };

        struct weighted_output {
            string operator()(edge edg) {
                return std::to_string(edg.from) + " " + std::to_string(edg.to) + " " + std::to_string(edg.weight);
            }
        };

        struct unweighted_output {
            string operator()(edge edg) {
                return std::to_string(edg.from) + " " + std::to_string(edg.to);
            }
        };

    protected:
        struct chain_node {
            int nxt, to;
            _Weight w;
            chain_node() {}
            chain_node(int nxt, int to, _Weight w) : nxt(nxt), to(to), w(w) {}
        };
        std::vector<chain_node> chain;
        std::vector<int> head;
        std::vector<std::map<int, bool> > edge_map;
        std::vector<edge> edge_vct;

    public:
        int N;
        bool directed;
        bool enable_edge_map;

        graph(int N, bool directed = false, bool enable_edge_map = true) {
            err_positive_checker(N, __func__, "N");
            this->N = N;
            this->directed = directed;
            this->enable_edge_map = enable_edge_map;
            head = std::vector<int>(N + 1, -1);
            edge_map = std::vector<std::map<int, bool> >(N + 1);
        }

        void add(edge edg, bool __add_vector = true) {
            err_inrange_checker(edg.from, 0, N, __func__, "edg.from");
            err_inrange_checker(edg.to, 0, N, __func__, "edg.to");
            chain.push_back(chain_node(head[edg.from], edg.to, edg.weight));
            head[edg.from] = chain.size() - 1;
            if (!directed && __add_vector) add(edge(edg.to, edg.from, edg.weight), false);
            if (__add_vector) edge_vct.push_back(edg);
            if (enable_edge_map) edge_map[edg.from][edg.to] = true;
        }

        void add(int from, int to, _Weight weight = 0) {
            add(edge(from, to, weight));
        }

        bool has_edge(edge edg) {
            if (!enable_edge_map) raise(carefree_unsupported_operation("has_edge : edge map is not enabled"));
            return edge_map[edg.from][edg.to];
        }

        bool has_edge(int from, int to) {
            return has_edge(edge(from, to));
        }

        std::vector<edge> get_edges() {
            return edge_vct;
        }

        std::vector<edge> get_edges(int from) {
            err_inrange_checker(from, 0, N, __func__, "from");
            std::vector<edge> edges;
            for (int i = head[from]; ~i; i = chain[i].nxt) edges.push_back(edge(from, chain[i].to, chain[i].w));
            return edges;
        }

        template <class T = weighted_output>
        string to_string(bool shuffle = false) {
            std::vector<edge> edges = get_edges();
            if (shuffle) std::shuffle(edges.begin(), edges.end(), public_random_engine);
            string str;
            for (auto it = edges.begin(); it != edges.end(); ++it) {
                str += T()(*it);
                if ((it + 1) != edges.end()) str += '\n';
            }
            return str;
        }
    };

    using edge = graph::edge;
    using weighted_output = graph::weighted_output;
    using unweighted_output = graph::unweighted_output;

    // graph tools

    bool is_tree(graph g) {
        std::vector<int> fa(g.N + 1);
        for (int i = 1; i <= g.N; i++) fa[i] = i;
        auto edges = g.get_edges();
        if (edges.size() != (unsigned)(g.N - 1)) return false;
        std::function<int(int)> find = [&](int x) {
            return fa[x] == x ? x : fa[x] = find(fa[x]);
        };
        for (auto i : edges) {
            int u = i.from, v = i.to;
            if (find(u) == find(v)) return false;
            fa[find(u)] = find(v);
        }
        return true;
    }

    graph relabel(graph g) {
        std::vector<int> perm;
        for (int i = 1; i <= g.N; i++) perm.push_back(i);
        std::shuffle(perm.begin(), perm.end(), public_random_engine);
        graph new_(g.N, g.directed, g.enable_edge_map);
        for (auto i : g.get_edges()) {
            new_.add(perm[i.from - 1], perm[i.to - 1], i.weight);
        }
        return new_;
    }

    graph prufer_decode(int n, std::vector<int> prufer, _Weight weightL = 0, _Weight weightR = 0) {
        std::vector<int> deg(n + 1, 1);
        prufer.insert(prufer.begin(), 0);
        graph g(n, false);
        if (prufer.size() != (unsigned)(n - 1)) raise(carefree_invalid_argument("prufer_decode : prufer size must be n-1"));
        for (int i = 1; i <= (n - 2); i++) {
            err_inrange_checker(prufer[i], 1, n, __func__, "prufer[" + std::to_string(i) + "]");
        }
        for (int i = 1; i <= (n - 2); i++) deg[prufer[i]]++;
        int ptr = 1, leaf = 0;
        while (deg[ptr] != 1) ptr++;
        leaf = ptr;
        for (int i = 1; i <= (n - 2); i++) {
            int v = prufer[i];
            g.add(v, leaf, randint(weightL, weightR));
            if (--deg[v] == 1 && v < ptr)
                leaf = v;
            else {
                ptr++;
                while (deg[ptr] != 1) ptr++;
                leaf = ptr;
            }
        }
        g.add(n, leaf, randint(weightL, weightR));
        return g;
    }

    std::vector<int> get_depth(graph g) {
        std::queue<int> q;
        std::vector<int> depth(g.N + 1);
        q.push(1);
        depth[1] = 1;
        while (!q.empty()) {
            auto u = q.front();
            q.pop();
            for (auto i : g.get_edges(u)) {
                if (!depth[i.to]) {
                    depth[i.to] = depth[u] + 1;
                    q.push(i.to);
                }
            }
        }
        return depth;
    }

    graph introvert(graph tree) {
        auto depth = get_depth(tree);
        graph g(tree.N, true);
        for (auto i : tree.get_edges()) {
            int u = i.from, v = i.to;
            auto w = i.weight;
            if (depth[u] < depth[v]) std::swap(u, v);
            g.add(u, v, w);
        }
        return g;
    }

    graph externalize(graph tree) {
        auto depth = get_depth(tree);
        graph g(tree.N, true);
        for (auto i : tree.get_edges()) {
            int u = i.from, v = i.to;
            auto w = i.weight;
            if (depth[u] > depth[v]) std::swap(u, v);
            g.add(u, v, w);
        }
        return g;
    }

    // tree generator and constructor

    graph lowhigh(int n, double low, double high, _Weight weightL = 0, _Weight weightR = 0) {
        graph g(n, false);
        for (int i = 2; i <= n; i++) {
            int fa = randint(std::max((int)((i - 1) * low), 1), std::min((int)((i - 1) * high), i - 1));
            g.add(fa, i, randint(weightL, weightR));
        }
        return g;
    }

    graph naive_tree(int n, _Weight weightL = 0, _Weight weightR = 0) {
        return lowhigh(n, 0, 1, weightL, weightR);
    }

    graph tail(int n, int k, _Weight weightL = 0, _Weight weightR = 0) {
        graph g(n, false);
        for (int i = 2; i <= n; i++) {
            int fa = randint(std::max(i - k, 1), i - 1);
            g.add(fa, i, randint(weightL, weightR));
        }
        return g;
    }

    graph chain(int n, _Weight weightL = 0, _Weight weightR = 0) {
        return tail(n, 1, weightL, weightR);
    }

    graph star(int n, _Weight weightL = 0, _Weight weightR = 0) {
        graph g(n, false);
        for (int i = 2; i <= n; i++) {
            g.add(1, i, randint(weightL, weightR));
        }
        return g;
    }

    graph flower(int n, _Weight weightL = 0, _Weight weightR = 0) {
        return star(n, weightL, weightR);
    }

    graph max_degree(int n, int k, _Weight weightL = 0, _Weight weightR = 0) {
        graph g(n, false);
        BalancedTree<std::pair<int, int> > tree;
        tree.insert({1, 0});
        for (int i = 2; i <= n; i++) {
            auto fa = tree.kth(randint(1, tree.size()));
            tree.erase(fa);
            if (fa.second < k) tree.insert({fa.first, fa.second + 1});
            g.add(fa.first, i, randint(weightL, weightR));
            tree.insert({i, 0});
        }
        return g;
    }

    graph binary_tree(int n, _Weight weightL = 0, _Weight weightR = 0) {
        return max_degree(n, 3, weightL, weightR);
    }

    graph chain_star(int n, int k, _Weight weightL = 0, _Weight weightR = 0) {
        graph g(n, false);
        for (int i = 2; i <= k; i++) g.add(i - 1, i, randint(weightL, weightR));
        for (int i = k + 1; i <= n; i++) g.add(randint(1, k), i, randint(weightL, weightR));
        return g;
    }

    graph silkworm(int n, _Weight weightL = 0, _Weight weightR = 0) {
        graph g(n, false);
        for (int i = 2; i <= (n >> 1); i++) g.add(i - 1, i, randint(weightL, weightR));
        for (int i = (n >> 1) + 1; i <= (n >> 1) << 1; i++) g.add(i - (n >> 1), i, randint(weightL, weightR));
        if (((n >> 1) << 1) != n) g.add(randint(1, n - 1), n, randint(weightL, weightR));
        return g;
    }

    graph firecrackers(int n, _Weight weightL = 0, _Weight weightR = 0) {
        graph g(n, false);
        int tmp = n / 3;
        for (int i = 2; i <= tmp; i++) g.add(i - 1, i, randint(weightL, weightR));
        for (int i = tmp + 1; i <= tmp * 2; i++) g.add(i - tmp, i, randint(weightL, weightR));
        for (int i = (tmp << 1) + 1; i <= tmp * 3; i++) g.add(i - (tmp << 1), i, randint(weightL, weightR));
        for (int i = (tmp * 3 + 1); i <= n; i++) g.add(randint(1, i - 1), i, randint(weightL, weightR));
        return g;
    }

    graph complete(int n, int k, _Weight weightL = 0, _Weight weightR = 0) {
        graph g(n, false);
        std::queue<int> q;
        q.push(1);
        int tot = 1;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            int bound = std::min(tot + k - 1, n);
            for (int i = tot + 1; i <= bound; i++) {
                g.add(u, (++tot), randint(weightL, weightR));
                q.push(i);
            }
        }
        return g;
    }

    graph complete_binary(int n, _Weight weightL = 0, _Weight weightR = 0) {
        return complete(n, 3, weightL, weightR);
    }

    graph random_tree(int n, _Weight weightL = 0, _Weight weightR = 0) {
        graph g(n, false);
        std::vector<int> prufer;
        for (int i = 1; i <= n - 2; i++) prufer.push_back(randint(1, n));
        return prufer_decode(n, prufer, weightL, weightR);
    }

    // graph generator & constructor

    graph dag(int n, int m, bool repeat_edges = false, _Weight weightL = 0, _Weight weightR = 0) {
        graph tree = random_tree(n, weightL, weightR);
        auto depth = get_depth(tree);
        graph ret = externalize(tree);
        err_geq_checker(m, n, __func__, "m");
        for (int i = n; i <= m; i++) {
            while (true) {
                int u = randint(1, n);
                int v = randint(1, n);
                if (u == v) continue;
                if (depth[u] > depth[v]) std::swap(u, v);
                if (!repeat_edges && ret.has_edge(u, v)) continue;
                ret.add(u, v, randint(weightL, weightR));
                break;
            }
        }
        return ret;
    }

    graph connected_undirected_graph(int n, int m, bool repeat_edges = false, bool self_loop = false, _Weight weightL = 0, _Weight weightR = 0) {
        graph tree = random_tree(n, weightL, weightR);
        graph ret = tree;
        err_geq_checker(m, n, __func__, "m");
        for (int i = n; i <= m; i++) {
            while (true) {
                int u = randint(1, n);
                int v = randint(1, n);
                if (!self_loop && u == v) continue;
                if (!repeat_edges && ret.has_edge(u, v)) continue;
                ret.add(u, v, randint(weightL, weightR));
                break;
            }
        }
        return ret;
    }

    graph connected_directed_graph(int n, int m, bool repeat_edges = false, bool self_loop = false, _Weight weightL = 0, _Weight weightR = 0) {
        graph tree = random_tree(n, weightL, weightR);
        graph ret = externalize(tree);
        err_geq_checker(m, n, __func__, "m");
        for (int i = n; i <= m; i++) {
            while (true) {
                int u = randint(1, n);
                int v = randint(1, n);
                if (!self_loop && u == v) continue;
                if (!repeat_edges && ret.has_edge(u, v)) continue;
                ret.add(u, v, randint(weightL, weightR));
                break;
            }
        }
        return ret;
    }

    graph random_graph(int n, int m, bool directed = true, bool repeat_edges = false, bool self_loop = false, _Weight weightL = 0, _Weight weightR = 0) {
        graph ret(n, directed);
        for (int i = 1; i <= m; i++) {
            while (true) {
                int u = randint(1, n);
                int v = randint(1, n);
                if (!self_loop && u == v) continue;
                if (!repeat_edges && ret.has_edge(u, v)) continue;
                ret.add(u, v, randint(weightL, weightR));
                break;
            }
        }
        return ret;
    }

    // Input & Output

    class testcase_writer {
    protected:
        class file_writer {
        protected:
            std::FILE* fp;
            void _ein() {
                if (fp == nullptr) raise(carefree_file_exception("testcase_io::file_writer::_ein : file is not opened."));
            }

        public:
            string _filename;
            file_writer() {}
            file_writer(const char* filename) {
                _filename = filename;
                if (std::strlen(filename)) {
                    fp = std::fopen(filename, "w");
                    if (fp == NULL) raise(carefree_file_exception("testcase_io::file_writer::file_writer : cannot open file " + _filename));
                } else
                    fp = nullptr;
            }
            void close() {
                if (fp != nullptr) std::fclose(fp);
            }
            ~file_writer() { close(); }
            void writeChar(char val) {
                _ein();
                std::fputc(val, fp);
            }
            template <class T>
            void writeInteger(T val) {
                _ein();
                if (val < 0) {
                    val = -val;
                    writeChar('-');
                }
                if (val == 0) {
                    writeChar('0');
                    return;
                }
                if (val >= 10) writeInteger(val / 10);
                writeChar('0' + val % 10);
            }
            void writeString(const char* val) {
                _ein();
                const char* ptr = val;
                while (*ptr != '\0') writeChar(*(ptr++));
            }
            void writeString(string val) {
                _ein();
                writeString(val.c_str());
            }
            void flush() {
                _ein();
                std::fflush(fp);
            }
        };

        file_writer* fin;
        file_writer* fout;
        bool locked;

        void _eil() {
            if (locked) raise(carefree_unsupported_operation("testcase_io::_eil : input/output file has already locked."));
        }
        void lock() { locked = true; }

    public:
        testcase_writer(string input_file, string output_file = "") {
            fin = new file_writer(input_file.c_str());
            fout = new file_writer(output_file.c_str());
            locked = false;
        }

        testcase_writer(string file_prefix, unsigned data_id, string input_suffix = ".in", string output_suffix = ".out", bool disable_output = false) {
            fin = new file_writer((file_prefix + std::to_string(data_id) + input_suffix).c_str());
            if (!disable_output)
                fout = new file_writer((file_prefix + std::to_string(data_id) + output_suffix).c_str());
            else
                fout = new file_writer("");
            locked = false;
        }

        testcase_writer(string file_prefix, unsigned subtask_id, unsigned task_id, string input_suffix = ".in", string output_suffix = ".out", bool disable_output = false) {
            fin = new file_writer((file_prefix + std::to_string(subtask_id) + "-" + std::to_string(task_id) + input_suffix).c_str());
            if (!disable_output)
                fout = new file_writer((file_prefix + std::to_string(subtask_id) + "-" + std::to_string(task_id) + output_suffix).c_str());
            else
                fout = new file_writer("");
            locked = false;
        }

        void input_write(char val) {
            _eil();
            fin->writeChar(val);
        }
        void output_write(char val) {
            _eil();
            fout->writeChar(val);
        }

        void input_write(int val) {
            _eil();
            fin->writeInteger(val);
        }
        void output_write(int val) {
            _eil();
            fout->writeInteger(val);
        }

        void output_write(long long val) {
            _eil();
            fout->writeInteger(val);
        }
        void input_write(long long val) {
            _eil();
            fin->writeInteger(val);
        }

        void input_write(unsigned int val) {
            _eil();
            fin->writeInteger(val);
        }
        void output_write(unsigned int val) {
            _eil();
            fout->writeInteger(val);
        }

        void input_write(unsigned long long val) {
            _eil();
            fin->writeInteger(val);
        }
        void output_write(unsigned long long val) {
            _eil();
            fout->writeInteger(val);
        }

        void input_write(unsigned short val) {
            _eil();
            fin->writeInteger(val);
        }
        void output_write(unsigned short val) {
            _eil();
            fout->writeInteger(val);
        }

        void input_write(short val) {
            _eil();
            fin->writeInteger(val);
        }
        void output_write(short val) {
            _eil();
            fout->writeInteger(val);
        }

#ifdef CAREFREE_INT128_SUPPORT
        void input_write(__int128 val) {
            _eil();
            fin->writeInteger(val);
        }
        void output_write(__int128 val) {
            _eil();
            fout->writeInteger(val);
        }

        void input_write(unsigned __int128 val) {
            _eil();
            fin->writeInteger(val);
        }
        void output_write(unsigned __int128 val) {
            _eil();
            fout->writeInteger(val);
        }
#endif
        void input_write(string val) {
            _eil();
            fin->writeString(val);
        }
        void output_write(string val) {
            _eil();
            fout->writeString(val);
        }

        void input_write(const char* val) {
            _eil();
            fin->writeString(val);
        }
        void output_write(const char* val) {
            _eil();
            fout->writeString(val);
        }

        void input_write(bool val) {
            _eil();
            fin->writeString(val ? "true" : "false");
        }
        void output_write(bool val) {
            _eil();
            fout->writeString(val ? "true" : "false");
        }

        template <class T>
        void input_write(std::vector<T> val) {
            _eil();
            for (auto it = val.begin(); it != val.end(); ++it) {
                input_write(*it);
                if ((it + 1) != val.end()) input_write(' ');
            }
        }
        template <class T>
        void output_write(std::vector<T> val) {
            _eil();
            for (auto it = val.begin(); it != val.end(); ++it) {
                output_write(*it);
                if ((it + 1) != val.end()) output_write(' ');
            }
        }

        void input_write(graph val) {
            _eil();
            input_write(val.to_string());
        }
        void output_write(graph val) {
            _eil();
            output_write(val.to_string());
        }

        void input_write(edge val) {
            _eil();
            input_write(weighted_output()(val));
        }
        void output_write(edge val) {
            _eil();
            output_write(weighted_output()(val));
        }

        template <class T, typename... Args>
        void input_write(T val, Args... args) {
            _eil();
            input_write(val);
            input_write(' ');
            input_write(args...);
        }

        template <class T, typename... Args>
        void output_write(T val, Args... args) {
            _eil();
            output_write(val);
            output_write(' ');
            output_write(args...);
        }

        void input_writeln() { input_write('\n'); }
        void output_writeln() { output_write('\n'); }

        template <class T>
        void input_writeln(T val) {
            _eil();
            input_write(val);
            input_write('\n');
        }

        template <class T>
        void output_writeln(T val) {
            _eil();
            output_write(val);
            output_write('\n');
        }

        template <class T, typename... Args>
        void input_writeln(T val, Args... args) {
            _eil();
            input_write(val);
            input_write(' ');
            input_writeln(args...);
        }

        template <class T, typename... Args>
        void output_writeln(T val, Args... args) {
            _eil();
            output_write(val);
            output_write(' ');
            output_writeln(args...);
        }

        bool is_locked() { return locked; }

        void input_flush() { fin->flush(); }
        void output_flush() { fout->flush(); }

        void output_gen(string program) {
            _eil();
            fin->close();
            fout->close();
            lock();
            int stdin_ = dup(fileno(stdin));
            freopen(fin->_filename.c_str(), "r", stdin);
            int stdout_ = dup(fileno(stdout));
            freopen(fout->_filename.c_str(), "w", stdout);
            int returnid = std::system(program.c_str());
            if (returnid != 0) raise(carefree_runtime_exception("testcase_io::output_gen :  program exited with non-zero return code"));
            dup2(stdin_, fileno(stdin));
            dup2(stdout_, fileno(stdout));
        }

        string input_name() {
            return fin->_filename;
        }

        string output_name() {
            return fout->_filename;
        }

        ~testcase_writer() {
            delete fin;
            delete fout;
        }
    };

    class luogu_testcase_config_writer {
    protected:
        string content;

    public:
        luogu_testcase_config_writer() {
            content = "";
        }

        void add(string input_name, int time_limit, int memory_limit, int score = -1, int subtask_id = -1) {
            const string space = "    ";
            string current = "";
            current += (input_name + ":\n");
            current += (space + "timeLimit: " + std::to_string(time_limit) + "\n");
            current += (space + "memoryLimit: " + std::to_string(memory_limit) + "\n");
            if (score != -1) current += (space + "score: " + std::to_string(score) + "\n");
            if (subtask_id != -1) current += (space + "subtaskId: " + std::to_string(subtask_id) + "\n");
            current += "\n";
            content += current;
        }

        void save(string filename = "config.yml") {
            FILE* fobj = fopen(filename.c_str(), "w");
            if (fobj == NULL) raise(carefree_file_exception("luogu_testcase_config_writer::save : failed to open file " + filename));
            fputs(content.c_str(), fobj);
            if (fclose(fobj) != 0) raise(carefree_file_exception("luogu_testcase_config_writer::save : failed to close file " + filename));
        }

        string to_string() {
            return content;
        }
    };
}  // namespace carefree_internal

namespace carefree {
    using carefree_internal::carefree_exception;
    using carefree_internal::carefree_file_exception;
    using carefree_internal::carefree_invalid_argument;
    using carefree_internal::carefree_range_exception;
    using carefree_internal::carefree_runtime_exception;
    using carefree_internal::carefree_unsupported_operation;
    using carefree_internal::choice;
    using carefree_internal::exception_policy;
    using carefree_internal::fts;
    using carefree_internal::get_exception_policy;
    using carefree_internal::int_cutting;
    using carefree_internal::ltv;
    using carefree_internal::raise;
    using carefree_internal::randint;
    using carefree_internal::random;
    using carefree_internal::real_cutting;
    using carefree_internal::sequence;
    using carefree_internal::set_exception_policy;
    using carefree_internal::shuffle;
    using carefree_internal::uniform;
    namespace strsets = carefree_internal::strsets;
    using carefree_internal::binary_tree;
    using carefree_internal::chain;
    using carefree_internal::chain_star;
    using carefree_internal::complete;
    using carefree_internal::complete_binary;
    using carefree_internal::connected_directed_graph;
    using carefree_internal::connected_undirected_graph;
    using carefree_internal::dag;
    using carefree_internal::edge;
    using carefree_internal::externalize;
    using carefree_internal::firecrackers;
    using carefree_internal::flower;
    using carefree_internal::gen_data;
    using carefree_internal::get_depth;
    using carefree_internal::graph;
    using carefree_internal::introvert;
    using carefree_internal::is_tree;
    using carefree_internal::lowhigh;
    using carefree_internal::luogu_testcase_config_writer;
    using carefree_internal::max_degree;
    using carefree_internal::naive_tree;
    using carefree_internal::prufer_decode;
    using carefree_internal::random_graph;
    using carefree_internal::random_tree;
    using carefree_internal::randstr;
    using carefree_internal::relabel;
    using carefree_internal::silkworm;
    using carefree_internal::star;
    using carefree_internal::tail;
    using carefree_internal::testcase_writer;
    using testcase_io = carefree_internal::testcase_writer;
    using carefree_internal::timer;
    using carefree_internal::unweighted_output;
    using carefree_internal::weighted_output;
}  // namespace carefree

// notes: if you want to update this code, don't forget to format in the configure under this sentence:
// {BasedOnStyle: Google,IndentWidth: 4,TabWidth: 4,UseTab: Never,BreakBeforeBraces: Attach,ColumnLimit: 0,NamespaceIndentation: All,AccessModifierOffset : -4}
