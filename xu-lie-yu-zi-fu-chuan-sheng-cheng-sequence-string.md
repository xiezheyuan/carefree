# 序列与字符串生成 / Sequence & String

```cpp
template<class T, class Value>
std::vector<Value> sequence(int n, T function)
```

生成一个序列 f(1),f(2),...,f(n)。

```cpp
template<class T>
std::vector<T> sequence(int n, T l, T r)
```

生成一个给定长度的序列，每个序列的元素随机介于 \[l,r] 间。

```cpp
template<class T>
std::vector<T> sequence(int lengthL, int lengthR, T l, T r)
```

生成一个长度介于给定区间的序列，每个序列的元素随机介于 \[l,r] 间。

```cpp
template<class T>
std::vector<T> real_cutting(int length, T total)
```

使用二倍均值法，生成一个长度给定的实数序列，使得总和为一个定值。

```cpp
template<class T>
std::vector<T> int_cutting(int length, T total)
```

使用二倍均值法，生成一个长度给定的整数序列，使得总和为一个定值。

```cpp
string randstr(int length, const string sset = strsets::lower)
```

生成一个给定长度的字符串，每个字符从 `sset` 中等概率选择（按照出现次数加权）。

```cpp
string randstr(int lengthL, int lengthR, const string sset = strsets::lower)
```

生成一个长度位于给定区间的字符串，每个字符从 `sset` 中等概率选择（按照出现次数加权）。

```cpp
namespace strsets{
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
}
```

一些常见字符集。
