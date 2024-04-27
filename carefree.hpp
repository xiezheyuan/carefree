/*
 * CareFree Library
 * CopyRight (c) xiezheyuan 2024 - now
 * Visit https://github.com/xiezheyuan/carefree for more details.
 */

#pragma once

#if __cplusplus < 201300L
#error "carefree library need C++ 14 or higher version"
#endif
#ifndef __GNUC__
#error "carefree library need GCC compiler or similar"
#endif
#ifndef _WIN32
#ifndef __linux__
#error "carefree library need Linux or Windows system."
#else
#error "carefree library don't support Linux system now.Please wait."
#endif
#else
#include <windows.h>
#ifdef PSAPI_LINKED
#include <psapi.h>
#endif
#endif

#define CAREFREE_VERSION_MAJOR 0
#define CAREFREE_VERSION_MINOR 7
#define CAREFREE_VERSION "0.7"

#include <io.h>
#include <sys/stat.h>
#include <unistd.h>

#include <algorithm>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <fstream>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <typeinfo>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wliteral-suffix"

#if __cplusplus >= 201703L
#define maybe_unused [[maybe_unused]]
#else
#define maybe_unused __attribute__((unused))
#endif

constexpr unsigned long long operator"" B(unsigned long long x) { return x; }

constexpr unsigned long long operator"" KiB(unsigned long long x) { return x * 1024; }

constexpr unsigned long long operator"" MiB(unsigned long long x) { return x * 1024 * 1024; }

constexpr unsigned long long operator"" GiB(unsigned long long x) { return x * 1024 * 1024 * 1024; }

constexpr unsigned long long operator"" TiB(unsigned long long x) { return x * 1024 * 1024 * 1024 * 1024; }

constexpr unsigned long long operator"" NS(unsigned long long x) { return x; }

constexpr unsigned long long operator"" MS(unsigned long long x) { return x * 1000 * 1000; }

constexpr unsigned long long operator"" S(unsigned long long x) { return x * 1000 * 1000 * 1000; }

constexpr unsigned long long operator"" MIN(unsigned long long x) { return x * 1000 * 1000 * 1000 * 60; }

namespace carefree_internal {

    using std::string;

    struct carefree_exception_name {
        virtual string name() { return "carefree_exception"; }
    };

    template <class cpp_err_type, class err_name = carefree_exception_name>
    class carefree_exception {
    private:
        string msg;
        string cls_name;

    public:
        using err_type = cpp_err_type;

        carefree_exception() { cls_name = err_name().name(); }

        carefree_exception(string msg) : msg(msg) { cls_name = err_name().name(); }

        carefree_exception(const char* msg) {
            this->msg = msg;
            cls_name = err_name().name();
        }

        string what() { return cls_name + " : " + get_msg(); }

        cpp_err_type get_err() { return err_type(what()); };

        string get_msg() { return msg; }
    };

    struct carefree_invalid_argument_name : public carefree_exception_name {
        string name() { return "carefree_invalid_argument"; }
    };

    struct carefree_range_exception_name : public carefree_exception_name {
        string name() { return "carefree_range_exception"; }
    };

    struct carefree_unsupported_operation_name : public carefree_exception_name {
        string name() { return "carefree_unsupported_operation"; }
    };

    struct carefree_file_exception_name : public carefree_exception_name {
        string name() { return "carefree_file_exception"; }
    };

    struct carefree_runtime_exception_name : public carefree_exception_name {
        string name() { return "carefree_runtime_exception"; }
    };

    struct carefree_system_exception_name : public carefree_exception_name {
        string name() { return "carefree_system_exception"; }
    };

    struct carefree_validate_failed_name : public carefree_exception_name {
        string name() { return "carefree_validate_failed"; }
    };

    class _base_exception : public std::exception {
    protected:
        string msg;

    public:
        explicit _base_exception(const string& __arg) : msg(__arg) {};
        explicit _base_exception(const char* __arg) : msg(__arg) {};
        virtual ~_base_exception() noexcept = default;
        virtual const char* what() const noexcept { return msg.c_str(); };
    };

    class _unsupported_operation : public _base_exception {
    public:
        explicit _unsupported_operation(const string& __arg) : _base_exception(__arg) {};
        explicit _unsupported_operation(const char* __arg) : _base_exception(__arg) {};
        virtual ~_unsupported_operation() noexcept = default;
    };

    class _file_exception : public _base_exception {
    public:
        explicit _file_exception(const string& __arg) : _base_exception(__arg) {};
        explicit _file_exception(const char* __arg) : _base_exception(__arg) {};
        virtual ~_file_exception() noexcept = default;
    };

    class _system_exception : public _base_exception {
    public:
        explicit _system_exception(const string& __arg) : _base_exception(__arg) {};
        explicit _system_exception(const char* __arg) : _base_exception(__arg) {};
        virtual ~_system_exception() noexcept = default;
    };

    class _validate_failed : public _base_exception {
    public:
        explicit _validate_failed(const string& __arg) : _base_exception(__arg) {};
        explicit _validate_failed(const char* __arg) : _base_exception(__arg) {};
        virtual ~_validate_failed() noexcept = default;
    };

    using _invalid_argument = std::invalid_argument;

    using _range_exception = std::out_of_range;

    using _runtime_exception = std::runtime_error;

    using carefree_invalid_argument = carefree_exception<_invalid_argument, carefree_invalid_argument_name>;

    using carefree_range_exception = carefree_exception<_range_exception, carefree_range_exception_name>;

    using carefree_unsupported_operation = carefree_exception<_unsupported_operation, carefree_unsupported_operation_name>;

    using carefree_file_exception = carefree_exception<_file_exception, carefree_file_exception_name>;

    using carefree_runtime_exception = carefree_exception<_runtime_exception, carefree_runtime_exception_name>;

    using carefree_system_exception = carefree_exception<_system_exception, carefree_system_exception_name>;

    using carefree_validate_failed = carefree_exception<_validate_failed, carefree_validate_failed_name>;

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

    template <class T1, class T2>
    string join_str(T1 a, T2 b) {
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
        return val[randint(0ull, val.size() - 1ull)];
    }

    template <class T>
    void shuffle(T val) {
        std::shuffle(val.begin(), val.end(), public_random_engine);
    }

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

    template <class T, class Compare = std::less<T>>
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

    private:
        struct chain_node {
            int nxt, to;
            _Weight w;
            chain_node() {}
            chain_node(int nxt, int to, _Weight w) : nxt(nxt), to(to), w(w) {}
        };
        std::vector<chain_node> chain;
        std::vector<int> head;
        std::vector<std::map<int, bool>> edge_map;
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
            edge_map = std::vector<std::map<int, bool>>(N + 1);
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
        BalancedTree<std::pair<int, int>> tree;
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

    graph dag(int n, int m, bool repeat_edges = false, _Weight weightL = 0, _Weight weightR = 0) {
        graph tree = random_tree(n, weightL, weightR);
        auto depth = get_depth(tree);
        graph ret = externalize(tree);
        err_geq_checker(m, n - 1, __func__, "m");
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
        err_geq_checker(m, n - 1, __func__, "m");
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
        err_geq_checker(m, n - 1, __func__, "m");
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

    class testcase_writer {
    private:
        class file_writer {
        private:
            std::FILE* fp;
            void _ein() {
                if (fp == nullptr) raise(carefree_file_exception("testcase_writer::file_writer::_ein : file is not opened."));
            }

        public:
            string _filename;
            file_writer() {}
            file_writer(const char* filename) {
                _filename = filename;
                if (std::strlen(filename)) {
                    fp = std::fopen(filename, "w");
                    if (fp == NULL) raise(carefree_file_exception("testcase_writer::file_writer::file_writer : cannot open file " + _filename));
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
            if (locked) raise(carefree_unsupported_operation("testcase_writer::_eil : input/output file has already locked."));
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
            if (returnid != 0) raise(carefree_runtime_exception("testcase_writer::output_gen :  program exited with non-zero return code"));
            dup2(stdin_, fileno(stdin));
            dup2(stdout_, fileno(stdout));
        }

        string input_name() {
            return fin->_filename;
        }

        string output_name() {
            return fout->_filename;
        }

        void close() {
            delete fin;
            delete fout;
            fin = nullptr;
            fout = nullptr;
        }

        ~testcase_writer() {
            if (fin != nullptr) delete fin;
            if (fout != nullptr) delete fout;
        }
    };

    using testcase_io [[deprecated("use testcase_writer instead.")]] = testcase_writer;

    class luogu_testcase_config_writer {
    private:
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

    class process_base {
    public:
        virtual void close() = 0;
        virtual void kill() = 0;
        virtual bool is_running() const = 0;
        virtual int return_code() const = 0;
        virtual int pid() const = 0;
        virtual size_t memory() const = 0;
    };

#ifdef _WIN32
    class process_win : public process_base {
    private:
        string command_, input_file_, output_file_;
        HANDLE process_handle_ = nullptr, hOutputFile = nullptr, hInputFile = nullptr;

    public:
        process_win(const string& cmd, const string& input = "", const string& output = "")
            : command_(cmd), input_file_(input), output_file_(output) {
            _STARTUPINFOA si;
            PROCESS_INFORMATION pi;
            ZeroMemory(&si, sizeof(si));
            si.cb = sizeof(si);
            ZeroMemory(&pi, sizeof(pi));
            if (!input_file_.empty()) {
                SECURITY_ATTRIBUTES saAttr;
                saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
                saAttr.bInheritHandle = TRUE;
                saAttr.lpSecurityDescriptor = NULL;
                hInputFile = CreateFileA(input_file_.c_str(), GENERIC_READ, 0, &saAttr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
                if (hInputFile == INVALID_HANDLE_VALUE) {
                    raise(carefree_file_exception("ProcessWin : failed to open input file " + input_file_));
                }
                si.hStdInput = hInputFile;
            }
            if (!output_file_.empty()) {
                SECURITY_ATTRIBUTES saAttr;
                saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
                saAttr.bInheritHandle = TRUE;
                saAttr.lpSecurityDescriptor = NULL;
                hOutputFile = CreateFileA(output_file_.c_str(), GENERIC_WRITE, 0, &saAttr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
                if (hOutputFile == INVALID_HANDLE_VALUE) {
                    raise(carefree_file_exception("ProcessWin : failed to open output file " + output_file_));
                }
                si.hStdOutput = hOutputFile;
                si.hStdError = NULL;
                si.dwFlags |= STARTF_USESTDHANDLES;
            }
            if (!CreateProcessA(NULL, (char*)(command_.c_str()), NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi)) {
                raise(carefree_system_exception("ProcessWin : failed to create process " + command_));
            }
            CloseHandle(pi.hThread);
            process_handle_ = pi.hProcess;
        }

        void close() {
            if (process_handle_ != nullptr) {
                CloseHandle(process_handle_);
            }
            if (hInputFile != nullptr) CloseHandle(hInputFile);
            if (hOutputFile != nullptr) {
                FlushFileBuffers(hOutputFile);
                CloseHandle(hOutputFile);
            }
        }

        ~process_win() {
            close();
        }

        void kill() {
            if (is_running())
                TerminateProcess(process_handle_, 1);
        }

        bool is_running() const {
            DWORD exit_code;
            if (GetExitCodeProcess(process_handle_, &exit_code) && exit_code == STILL_ACTIVE) {
                return true;
            }
            return false;
        }

        int return_code() const {
            DWORD exit_code;
            if (!GetExitCodeProcess(process_handle_, &exit_code) || exit_code == STILL_ACTIVE) {
                raise(carefree_system_exception("return_code : process has not yet terminated."));
            }
            return static_cast<int>(exit_code);
        }

        int pid() const {
            return (int)GetProcessId(process_handle_);
        }

        size_t memory() const {
#ifdef PSAPI_LINKED
            PROCESS_MEMORY_COUNTERS_EX pmc;
            ZeroMemory(&pmc, sizeof(pmc));
            pmc.cb = sizeof(pmc);
            if (!GetProcessMemoryInfo(process_handle_, (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc))) {
                raise(carefree_system_exception("memory : failed to retrieve process memory information."));
                return 0ull;
            }
            return (size_t)pmc.PrivateUsage;
#else
            return 0ull;
#endif
        }
    };
    using process = process_win;
#endif

    enum judge_result_type {
        Accepted,
        WrongAnswer,
        TimeLimitExceeded,
        MemoryLimitExceeded,
        RuntimeError,
        CompileError,
        PresentationError,
        OutputLimitExceeded,
        UnknownError,
        JudgeFailed,
        PartiallyCorrect,
        Skipped,
    };

    string jrt2s(judge_result_type type) {
        switch (type) {
            case Accepted:
                return "Accepted";
            case WrongAnswer:
                return "Wrong Answer";
            case TimeLimitExceeded:
                return "Time Limit Exceeded";
            case MemoryLimitExceeded:
                return "Memory Limit Exceeded";
            case RuntimeError:
                return "Runtime Error";
            case CompileError:
                return "Compile Error";
            case PresentationError:
                return "Presentation Error";
            case OutputLimitExceeded:
                return "Output Limit Exceeded";
            case UnknownError:
                return "Unknown Error";
            case JudgeFailed:
                return "Judge Failed";
            case PartiallyCorrect:
                return "Partially Correct";
            case Skipped:
                return "Skipped";
            default:
                return "Unknown Error";
        }
        return "Unknown Error";
    }

    string jrt2sf(judge_result_type type) {
        switch (type) {
            case Accepted:
                return "AC";
            case WrongAnswer:
                return "WA";
            case TimeLimitExceeded:
                return "TLE";
            case MemoryLimitExceeded:
                return "MLE";
            case RuntimeError:
                return "RE";
            case CompileError:
                return "CE";
            case PresentationError:
                return "PE";
            case OutputLimitExceeded:
                return "OLE";
            case UnknownError:
                return "UKE";
            case JudgeFailed:
                return "JF";
            case PartiallyCorrect:
                return "PC";
            case Skipped:
                return "SK";
            default:
                return "UKE";
        }
        return "UKE";
    }

    using ull = unsigned long long;

    struct judge_result {
        judge_result_type type;
        string message;
        double ratio;
        ull time;
        ull memory;

        string to_str() const {
            string ret = jrt2s(type) + "\t" + message + "\t";
            ret += std::to_string(time / 1000.0 / 1000.0) + "ms\t";
            ret += std::to_string(memory / 1024.0 / 1024.0) + "MiB\t";
            ret += std::to_string(ratio * 100) + "%";
            return ret;
        }
    };

    std::vector<string> __split(const string& str, string delims) {
        std::vector<string> tokens;
        string tmp;
        for (auto it = str.begin(); it != str.end(); ++it) {
            if (delims.find(*it) != string::npos) {
                tokens.push_back(tmp);
                tmp.clear();
                continue;
            }
            tmp += *it;
        }
        tokens.push_back(tmp);
        return tokens;
    }

    class comparator {
    public:
        class readable {
        public:
            virtual string read() = 0;
        };

        class file : public readable {
        private:
            string filename_;

        public:
            file(const string& filename) : filename_(filename) {}
            string read() {
                std::ifstream file(filename_, std::ios::in);
                if (!file.is_open()) {
                    Sleep(1000);
                    file.open(filename_, std::ios::in);
                    if (!file.is_open()) raise(carefree_file_exception("read : failed to open file " + filename_));
                }
                string content;
                while (file.good()) {
                    string line;
                    std::getline(file, line);
                    content += line + '\n';
                }
                file.close();
                return content;
            }
        };

        class text : public readable {
        private:
            string content_;

        public:
            text(const string& content) : content_(content) {}
            string read() { return content_; }
        };

        virtual judge_result from_text(const string& text1, const string& text2) = 0;

        virtual judge_result from_file(const string& filename1, const string& filename2) {
            return from_text(file(filename1).read(), file(filename2).read());
        }

        template <class T1, class T2>
        judge_result operator()(T1 a, T2 b) {
            return from_text(a.read(), b.read());
        }

        virtual judge_result test(const string& input_path maybe_unused, const string& output_path, const string& answer_path) {
            return from_file(answer_path, output_path);
        }
    };

    using creadable = comparator::readable;
    using ctext = comparator::text;
    using cfile = comparator::file;

    class strict_comparator_naive : public comparator {
    public:
        judge_result from_text(const string& text1, const string& text2) {
            if (text1 == text2) {
                return {Accepted, "correct", 1.0, 0ull, 0ull};
            }
            return {WrongAnswer, "not correct", 0.0, 0ull, 0ull};
        }
    };

    class strict_comparator : public comparator {
    public:
        judge_result from_text(const string& text1, const string& text2) {
            auto lines1 = __split(text1, "\n");
            auto lines2 = __split(text2, "\n");
            if (lines1.size() != lines2.size()) {
                string errmsg = "expected " + std::to_string(lines1.size()) + " line(s), but got " + std::to_string(lines2.size()) + " line(s).";
                return {WrongAnswer, errmsg, 0.0, 0ull, 0ull};
            }
            for (ull i = 0; i < lines1.size(); ++i) {
                if (lines1[i] != lines2[i]) {
                    string errmsg = "at line " + std::to_string(i + 1);
                    errmsg += ", expected \"" + lines1[i] + "\"";
                    errmsg += ", but got \"" + lines2[i] + "\".";
                    return {WrongAnswer, errmsg, 0.0, 0ull, 0ull};
                }
            }
            return {Accepted, "correct", 1.0, 0ull, 0ull};
        }
    };

    class token_comparator : public comparator {
    public:
        judge_result from_text(const string& text1, const string& text2) {
            auto tokens1_ = __split(text1, " \t\r\n");
            auto tokens2_ = __split(text2, " \t\r\n");
            std::vector<string> tokens1, tokens2;
            std::copy_if(tokens1_.begin(), tokens1_.end(), std::back_inserter(tokens1), [](const string& s) { return s != ""; });
            std::copy_if(tokens2_.begin(), tokens2_.end(), std::back_inserter(tokens2), [](const string& s) { return s != ""; });
            if (tokens1.size() != tokens2.size()) {
                string errmsg = "expected " + std::to_string(tokens1.size()) + " token(s), but got " + std::to_string(tokens2.size()) + " token(s).";
                return {WrongAnswer, errmsg, 0.0, 0, 0};
            }
            for (ull i = 0; i < tokens1.size(); ++i) {
                if (tokens1[i] != tokens2[i]) {
                    string errmsg = "at token " + std::to_string(i + 1);
                    errmsg += ", expected \"" + tokens1[i] + "\"";
                    errmsg += ", but got \"" + tokens2[i] + "\".";
                    return {WrongAnswer, errmsg, 0.0, 0ull, 0ull};
                }
            }
            return {Accepted, "correct", 1.0, 0ull, 0ull};
        }
    };

    ull nextid() {
        static ull id;
        return ++id;
    }

    string quote(string s) {
        std::stringstream ss;
        ss << std::quoted(s);
        return ss.str();
    }

    class testlib_comparator : public comparator {
    private:
        string testlib_path;

        string extract_outcome(string xml) {
            size_t start_pos = xml.find("outcome = \"");
            if (start_pos == string::npos) return "";
            start_pos += 11;
            size_t end_pos = xml.find("\"", start_pos);
            if (end_pos == string::npos) return "";
            return xml.substr(start_pos, end_pos - start_pos);
        }

        string extract_points(string xml) {
            size_t start_pos = xml.find("points = \"");
            if (start_pos == string::npos) return "";
            start_pos += 10;
            size_t end_pos = xml.find("\"", start_pos);
            if (end_pos == string::npos) return "";
            return xml.substr(start_pos, end_pos - start_pos);
        }

        string extract_result(string xml) {
            size_t start_pos = xml.find("\">") + 2;
            if (start_pos == string::npos) return "";
            size_t end_pos = xml.rfind("</result>");
            if (end_pos == string::npos) return "";
            return xml.substr(start_pos, end_pos - start_pos);
        }

    public:
        testlib_comparator(const string& testlib_path) {
            this->testlib_path = testlib_path;
        }

        judge_result test(string input_path, string output_path, string answer_path) {
            string cmd = testlib_path + " ";
            cmd += quote(input_path) + " " + quote(output_path) + " " + quote(answer_path);
            cmd += " ";
            string xml_path = "carefree_testlib_report_" + std::to_string(nextid()) + ".xml";
            cmd += quote(xml_path) + " -appes";
            int ret = system(cmd.c_str());
            string content = file(xml_path).read();
            std::remove(xml_path.c_str());
            string outcome = extract_outcome(content);
            string message = extract_result(content);
            if (outcome.empty()) return {UnknownError, "cannot parse report file.", 0.0, 0ull, 0ull};
            if (outcome == "accepted")
                return {Accepted, message, 1.0, 0ull, 0ull};
            else if (outcome == "wrong-answer")
                return {WrongAnswer, message, 0.0, 0ull, 0ull};
            else if (outcome == "presentation-error")
                return {PresentationError, message, 0.0, 0ull, 0ull};
            else if (outcome == "points") {
                string points = extract_points(content);
                if (points.empty()) return {UnknownError, "cannot parse report file.", 0.0, 0ull, 0ull};
                return {PartiallyCorrect, message, std::stod(points), 0ull, 0ull};
            } else
                return {JudgeFailed, message, 0.0, 0ull, 0ull};
        }

        judge_result from_text(const string& text1 maybe_unused, const string& text2 maybe_unused) {
            raise(carefree_unsupported_operation("testlib_comparator::from_text : unsupported from_text method."));
            return {UnknownError, "unsupported from_text method", 0.0, 0ull, 0ull};
        }
    };

    struct limprog {
        string program;
        ull time;
        ull memory;

        limprog(string program, ull time, ull memory) : program(program), time(time), memory(memory) {}
    };

    judge_result limited_run(limprog prog, const string& input_file, const string& output_file) {
        auto start = std::chrono::system_clock::now();
        ull memory = 0, tim = 0;
        process proc(prog.program, input_file, output_file);
        while (proc.is_running()) {
            auto now = std::chrono::system_clock::now();
            tim = std::chrono::duration_cast<std::chrono::nanoseconds>(now - start).count();
            if (tim > prog.time) {
                proc.kill();
                return {TimeLimitExceeded, "time limit exceeded.", 0.0, tim, memory};
            }
            memory = std::max(memory, proc.memory());
            if (memory > prog.memory) {
                proc.kill();
                return {MemoryLimitExceeded, "memory limit exceeded.", 0.0, tim, memory};
            }
        }
        if (proc.return_code() != 0) {
            return {RuntimeError, "program finished with exit non-zero code " + std::to_string(proc.return_code()) + ".", 0.0, tim, memory};
        }
        return {Accepted, "program finished successfully.", 1.0, tim, memory};
    }

    bool is_file_creatable(string filename) {
        if (access(filename.c_str(), F_OK) != -1) return false;
        std::ofstream f(filename, std::ios::out);
        if (f.is_open()) {
            f.close();
            std::remove(filename.c_str());
            return true;
        }
        return false;
    };

    template <class T>
    judge_result judge(limprog prog, const string& input_file, const string& answer_file, T cmp, bool ole_check = true) {
        string output_file;
        do {
            output_file = "carefree_output_" + std::to_string(nextid()) + ".out";
        } while (!is_file_creatable(output_file));
        judge_result ans = limited_run(prog, input_file, output_file);
        if (ans.type != Accepted) {
            std::remove(output_file.c_str());
            return ans;
        }
        if (ole_check) {
            struct stat output_stat {};
            stat(output_file.c_str(), &output_stat);
            struct stat answer_stat {};
            stat(answer_file.c_str(), &answer_stat);
            if (output_stat.st_size > answer_stat.st_size * 10) {
                std::remove(output_file.c_str());
                return {OutputLimitExceeded, "output limit exceeded.", 0.0, ans.time, ans.memory};
            }
        }
        judge_result ans2 = cmp.test(input_file, output_file, answer_file);
        std::remove(output_file.c_str());
        return {ans2.type, ans2.message, ans2.ratio, ans.time, ans.memory};
    }

    template <class T1, class T2>
    bool combat(limprog champion, limprog challenger, T1 input_generator, T2 cmp, int times = -1, bool ole_check = true) {
        for (int i = 0; i != times; i++) {
            fprintf(stderr, "Round #%d : ", i + 1);
            string input_file = "";
            do {
                input_file = "carefree_input_" + std::to_string(nextid()) + ".in";
            } while (!is_file_creatable(input_file));
            testcase_writer writer(input_file, "");
            input_generator(writer);
            string answer_file;
            do {
                answer_file = "carefree_answer_" + std::to_string(nextid()) + ".ans";
            } while (!is_file_creatable(answer_file));
            auto ret = limited_run(champion, input_file, answer_file);
            if (ret.type != Accepted) {
                fprintf(stderr, "champion is lost.\n");
                fprintf(stderr, "%s\n", ret.to_str().c_str());
                fprintf(stderr, "please watch input file \"%s\" to check.", input_file.c_str());
                return false;
            }
            ret = judge(challenger, input_file, answer_file, cmp, ole_check = ole_check);
            if (ret.type != Accepted) {
                fprintf(stderr, "challenger is lost.\n");
                fprintf(stderr, "%s\n", ret.to_str().c_str());
                fprintf(stderr, "please watch input file \"%s\" to check.", input_file.c_str());
                return false;
            }
            std::remove(answer_file.c_str());
            std::remove(input_file.c_str());
            fprintf(stderr, "champion and challenger are still alive.\n");
        }
        return true;
    }

    void listdir(string path, std::vector<string>& files) {
        intptr_t hFile = 0;
        _finddata_t fileinfo;
        if ((hFile = _findfirst(path.append("/*").c_str(), &fileinfo)) != -1) {
            while (_findnext(hFile, &fileinfo) == 0) {
                if (strcmp(fileinfo.name, ".."))
                    files.push_back(fileinfo.name);
            }
            _findclose(hFile);
        }
    }

    string working_directory() {
        return getcwd(NULL, 0);
    }

    int autoclear_tmpfiles() {
        std::vector<string> files;
        listdir(working_directory(), files);
        int cnt = 0;
        for (auto& i : files) {
            if (i.find("carefree_input_") == 0 ||
                i.find("carefree_output_") == 0 ||
                i.find("carefree_answer_") == 0 ||
                i.find("carefree_testlib_report_") == 0) {
                std::remove(i.c_str());
                cnt++;
            }
        }
        return cnt;
    }

    enum optimization_type {
        O0,
        O1,
        O2,
        O3,
        Ofast
    };

    enum cpp_version {
        Cpp98,
        Cpp03,
        Cpp11,
        Cpp14,
        Cpp17,
        Cpp20,
    };

    namespace cpp_warnings {
        const int Wnone = 0;
        const int Wall = 1;
        const int Wextra = 2;
        const int Wpedantic = 4;
        const int Werror = 8;

        using type = int;
    };  // namespace cpp_warnings

    class gcc_compile {
    private:
        string gcc_path = "g++";
        string filename;
        string output_name;
        optimization_type opti = O2;
        cpp_version cpp = Cpp14;
        cpp_warnings::type warning = 0;
        bool link_static = false, debug = false;
        std::vector<string> include_files, include_dirs, link_libs;
        std::map<string, string> defintions;

    public:
        gcc_compile(string filename, string output_name) : filename(filename), output_name(output_name) {};

        gcc_compile& gcc(string gcc_path) {
            this->gcc_path = gcc_path;
            return *this;
        }

        gcc_compile& optimization(optimization_type opti) {
            this->opti = opti;
            return *this;
        }

        gcc_compile& cpp_version(cpp_version cpp) {
            this->cpp = cpp;
            return *this;
        }

        gcc_compile& warning_level(cpp_warnings::type warning) {
            this->warning = warning;
            return *this;
        }

        gcc_compile& add_warning(cpp_warnings::type warning) {
            this->warning |= warning;
            return *this;
        }

        gcc_compile& linking_static(bool link_static = true) {
            this->link_static = link_static;
            return *this;
        }

        gcc_compile& include_file(string filename) {
            this->include_files.push_back(filename);
            return *this;
        }

        gcc_compile& define(string key, string value = "") {
            this->defintions[key] = value;
            return *this;
        }

        gcc_compile& include_dir(string dir) {
            this->include_dirs.push_back(dir);
            return *this;
        }

        gcc_compile& link(string lib) {
            this->link_libs.push_back(lib);
            return *this;
        }

        gcc_compile& debug_mode(bool debug = true) {
            this->debug = debug;
            return *this;
        }

        string command() {
            string cmd = gcc_path + " " + quote(filename);
            if (debug) {
                cmd += " -g";
            }
            switch (opti) {
                case O0:
                    cmd += " -O0";
                case O1:
                    cmd += " -O1";
                    break;
                case O2:
                    cmd += " -O2";
                    break;
                case O3:
                    cmd += " -O3";
                    break;
                case Ofast:
                    cmd += " -Ofast";
                    break;
            }
            switch (cpp) {
                case Cpp98:
                    cmd += " -std=c++98";
                    break;
                case Cpp03:
                    cmd += " -std=c++03";
                    break;
                case Cpp11:
                    cmd += " -std=c++11";
                    break;
                case Cpp14:
                    cmd += " -std=c++14";
                    break;
                case Cpp17:
                    cmd += " -std=c++17";
                    break;
                case Cpp20:
                    cmd += " -std=c++20";
                    break;
            }

            if (warning == cpp_warnings::Wnone) {
                cmd += " -w";
            } else {
                if (warning & cpp_warnings::Wall) {
                    cmd += " -Wall";
                }
                if (warning & cpp_warnings::Wextra) {
                    cmd += " -Wextra";
                }
                if (warning & cpp_warnings::Wpedantic) {
                    cmd += " -pedantic";
                }
                if (warning & cpp_warnings::Werror) {
                    cmd += " -Werror";
                }
            }

            for (auto& i : include_files) {
                cmd += " -include " + i;
            }

            for (auto& i : include_dirs) {
                cmd += " -I" + i;
            }

            for (auto& i : defintions) {
                if (i.second.empty())
                    cmd += " -D" + i.first;
                else
                    cmd += " -D" + i.first + "=" + i.second;
            }

            for (auto& i : link_libs) {
                cmd += " -l" + i;
            }

            if (link_static) {
                cmd += " -static";
            }

            cmd += " -o " + quote(output_name);

            return cmd;
        }

        judge_result_type start() {
            return std::system(this->command().c_str()) == 0 ? judge_result_type::Accepted : judge_result_type::CompileError;
        }
    };

    struct __enum_shortcut {
        exception_policy Throw = exception_policy::Throw;
        exception_policy Ignore = exception_policy::Ignore;
        exception_policy Friendly = exception_policy::Friendly;
        exception_policy Simulate = exception_policy::Simulate;

        judge_result_type Accepted = judge_result_type::Accepted;
        judge_result_type WrongAnswer = judge_result_type::WrongAnswer;
        judge_result_type TimeLimitExceeded = judge_result_type::TimeLimitExceeded;
        judge_result_type MemoryLimitExceeded = judge_result_type::MemoryLimitExceeded;
        judge_result_type RuntimeError = judge_result_type::RuntimeError;
        judge_result_type CompileError = judge_result_type::CompileError;
        judge_result_type PresentationError = judge_result_type::PresentationError;
        judge_result_type OutputLimitExceeded = judge_result_type::OutputLimitExceeded;
        judge_result_type UnknownError = judge_result_type::UnknownError;
        judge_result_type JudgeFailed = judge_result_type::JudgeFailed;
        judge_result_type PartiallyCorrect = judge_result_type::PartiallyCorrect;
        judge_result_type Skipped = judge_result_type::Skipped;

        optimization_type O0 = optimization_type::O0;
        optimization_type O1 = optimization_type::O1;
        optimization_type O2 = optimization_type::O2;
        optimization_type O3 = optimization_type::O3;
        optimization_type Ofast = optimization_type::Ofast;

        cpp_version Cpp98 = cpp_version::Cpp98;
        cpp_version Cpp03 = cpp_version::Cpp03;
        cpp_version Cpp11 = cpp_version::Cpp11;
        cpp_version Cpp14 = cpp_version::Cpp14;
        cpp_version Cpp17 = cpp_version::Cpp17;
        cpp_version Cpp20 = cpp_version::Cpp20;

        cpp_warnings::type Wnone = cpp_warnings::Wnone;
        cpp_warnings::type Wall = cpp_warnings::Wall;
        cpp_warnings::type Wextra = cpp_warnings::Wextra;
        cpp_warnings::type Wpedantic = cpp_warnings::Wpedantic;
        cpp_warnings::type Werror = cpp_warnings::Werror;
    } ES;

    void helloworld() {
        const string version_str = CAREFREE_VERSION;
        const string product_name_art = " .o88b.  .d8b.  d8888b. d88888b d88888b d8888b. d88888b d88888b \nd8P  Y8 d8' `8b 88  `8D 88'     88'     88  `8D 88'     88'     \n8P      88ooo88 88oobY' 88ooooo 88ooo   88oobY' 88ooooo 88ooooo \n8b      88~~~88 88`8b   88~~~~~ 88~~~   88`8b   88~~~~~ 88~~~~~ \nY8b  d8 88   88 88 `88. 88.     88      88 `88. 88.     88.     \n `Y88P' YP   YP 88   YD Y88888P YP      88   YD Y88888P Y88888P \n                                                                \n     \n";
        std::cout << ("Hello World! -- The greeting from Carefree " + version_str + "\n\n");
        std::cout << product_name_art << '\n';
        std::cout << "For more information, please visit : https://github.com/xiezheyuan/carefree/\n";
        std::cout << "Do you want me to help you open this URL? (y | others): ";
        string prompt;
        std::cin >> prompt;
        if (prompt == "y" || prompt == "Y") {
            std::system("start http://github.com/xiezheyuan/carefree/");
        }
    }

    template <class T>
    class condition {
    private:
        std::function<bool(T)> val;

    public:
        condition(std::function<bool(T)> x) : val(x) {}
        bool operator()(T x) const { return val(x); }
    };

    template <class T>
    condition<T> operator||(condition<T> a, condition<T> b) {
        return condition<T>([a, b](T v) { return a(v) || b(v); });
    }

    template <class T>
    condition<T> operator&&(condition<T> a, condition<T> b) {
        return condition<T>([a, b](T v) { return a(v) && b(v); });
    }

    template <class T>
    condition<T> operator!(condition<T> a) {
        return condition<T>([a](T v) { return !a(v); });
    }

    template <class T>
    condition<T> operator|(condition<T> a, condition<T> b) { return a || b; }

    template <class T>
    condition<T> operator&(condition<T> a, condition<T> b) { return a && b; }

    namespace pred {
        namespace num {
            template <class T>
            condition<T> lt(T x) {
                return condition<T>([x](T v) { return v < x; });
            }

            template <class T>
            condition<T> gt(T x) {
                return condition<T>([x](T v) { return v > x; });
            }

            template <class T>
            condition<T> eq(T x) {
                return condition<T>([x](T v) { return v == x; });
            }

            template <class T>
            condition<T> leq(T x) { return lt(x) || eq(x); }

            template <class T>
            condition<T> geq(T x) { return gt(x) || eq(x); }

            template <class T>
            condition<T> neq(T x) { return !eq(x); }

            template <class T>
            condition<T> inrange(T l, T r) { return geq(l) && leq(r); }
        }  // namespace num

        namespace str {
            condition<string> len_lt(size_t x) {
                return condition<string>([x](string v) { return v.length() < x; });
            }

            condition<string> len_gt(size_t x) {
                return condition<string>([x](string v) { return v.length() > x; });
            }

            condition<string> len_eq(size_t x) {
                return condition<string>([x](string v) { return v.length() == x; });
            }

            condition<string> len_leq(size_t x) { return len_lt(x) || len_eq(x); }

            condition<string> len_geq(size_t x) { return len_gt(x) || len_eq(x); }

            condition<string> len_neq(size_t x) { return !len_eq(x); }

            condition<string> len_inrange(size_t l, size_t r) { return len_geq(l) && len_leq(r); }

            condition<string> empty() { return len_eq(0); }

            condition<string> unempty() { return len_gt(0); }

            condition<string> sset(string s) {
                return condition<string>([s](string x) {
                    std::map<char, bool> m;
                    for (size_t i = 0; i < s.length(); i++) {
                        m[s[i]] = true;
                    }
                    for (size_t i = 0; i < x.length(); i++) {
                        if (!m[x[i]]) {
                            return false;
                        }
                    }
                    return true;
                });
            }
        }  // namespace str

        namespace seq {
            template <class T = int>
            condition<std::vector<T>> len_lt(size_t x) {
                return condition<std::vector<T>>([x](string v) { return v.length() < x; });
            }

            template <class T = int>
            condition<std::vector<T>> len_gt(size_t x) {
                return condition<std::vector<T>>([x](string v) { return v.length() > x; });
            }

            template <class T = int>
            condition<std::vector<T>> len_eq(size_t x) {
                return condition<std::vector<T>>([x](string v) { return v.length() == x; });
            }

            template <class T = int>
            condition<std::vector<T>> len_leq(size_t x) { return len_lt(x) || len_eq(x); }

            template <class T = int>
            condition<std::vector<T>> len_geq(size_t x) { return len_gt(x) || len_eq(x); }

            template <class T = int>
            condition<std::vector<T>> len_neq(size_t x) { return !len_eq(x); }

            template <class T = int>
            condition<std::vector<T>> len_inrange(size_t l, size_t r) { return len_geq(l) && len_leq(r); }

            template <class T = int>
            condition<std::vector<T>> empty() { return len_eq(0); }

            template <class T = int>
            condition<std::vector<T>> unempty() { return len_gt(0); }

            template <class T = int>
            condition<std::vector<T>> increase() {
                return condition<std::vector<T>>([](std::vector<T> v) {
                    for (size_t i = 0; i < v.size() - 1; i++) {
                        if (v[i] < v[i + 1]) {
                            return false;
                        }
                    }
                    return true;
                });
            }

            template <class T = int>
            condition<std::vector<T>> decrease() {
                return condition<std::vector<T>>([](std::vector<T> v) {
                    for (size_t i = 0; i < v.size() - 1; i++) {
                        if (v[i] > v[i + 1]) {
                            return false;
                        }
                    }
                    return true;
                });
            }

        }  // namespace seq
    }  // namespace pred

}  // namespace carefree_internal

namespace carefree {
    using carefree_internal::_base_exception;
    using carefree_internal::autoclear_tmpfiles;
    using carefree_internal::binary_tree;
    using carefree_internal::carefree_exception;
    using carefree_internal::carefree_file_exception;
    using carefree_internal::carefree_invalid_argument;
    using carefree_internal::carefree_range_exception;
    using carefree_internal::carefree_runtime_exception;
    using carefree_internal::carefree_system_exception;
    using carefree_internal::carefree_unsupported_operation;
    using carefree_internal::cfile;
    using carefree_internal::chain;
    using carefree_internal::chain_star;
    using carefree_internal::choice;
    using carefree_internal::combat;
    using carefree_internal::comparator;
    using carefree_internal::complete;
    using carefree_internal::complete_binary;
    using carefree_internal::condition;
    using carefree_internal::connected_directed_graph;
    using carefree_internal::connected_undirected_graph;
    using carefree_internal::cpp_version;
    using carefree_internal::creadable;
    using carefree_internal::ctext;
    using carefree_internal::dag;
    using carefree_internal::edge;
    using carefree_internal::ES;
    using carefree_internal::exception_policy;
    using carefree_internal::externalize;
    using carefree_internal::firecrackers;
    using carefree_internal::flower;
    using carefree_internal::fts;
    using carefree_internal::gcc_compile;
    using carefree_internal::gen_data;
    using carefree_internal::get_depth;
    using carefree_internal::get_exception_policy;
    using carefree_internal::graph;
    using carefree_internal::helloworld;
    using carefree_internal::introvert;
    using carefree_internal::is_tree;
    using carefree_internal::jrt2s;
    using carefree_internal::jrt2sf;
    using carefree_internal::judge;
    using carefree_internal::judge_result;
    using carefree_internal::judge_result_type;
    using carefree_internal::limited_run;
    using carefree_internal::limprog;
    using carefree_internal::listdir;
    using carefree_internal::lowhigh;
    using carefree_internal::ltv;
    using carefree_internal::luogu_testcase_config_writer;
    using carefree_internal::max_degree;
    using carefree_internal::naive_tree;
    using carefree_internal::nextid;
    using carefree_internal::optimization_type;
    using carefree_internal::process;
    using carefree_internal::process_base;
    using carefree_internal::prufer_decode;
    using carefree_internal::quote;
    using carefree_internal::raise;
    using carefree_internal::randint;
    using carefree_internal::random;
    using carefree_internal::random_graph;
    using carefree_internal::random_tree;
    using carefree_internal::randstr;
    using carefree_internal::relabel;
    using carefree_internal::sequence;
    using carefree_internal::set_exception_policy;
    using carefree_internal::shuffle;
    using carefree_internal::silkworm;
    using carefree_internal::star;
    using carefree_internal::strict_comparator;
    using carefree_internal::strict_comparator_naive;
    using carefree_internal::tail;
    using carefree_internal::testcase_io;
    using carefree_internal::testcase_writer;
    using carefree_internal::testlib_comparator;
    using carefree_internal::timer;
    using carefree_internal::token_comparator;
    using carefree_internal::uniform;
    using carefree_internal::unweighted_output;
    using carefree_internal::weighted_output;
    using carefree_internal::working_directory;

    namespace strsets = carefree_internal::strsets;
    namespace cpp_warnings = carefree_internal::cpp_warnings;
    namespace pred = carefree_internal::pred;
    namespace pnum = carefree_internal::pred::num;
    namespace pstr = carefree_internal::pred::str;
    namespace pseq = carefree_internal::pred::seq;
}  // namespace carefree

#pragma GCC diagnostic pop
