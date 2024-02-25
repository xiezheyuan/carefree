# 类型转换 / Type Converter

```cpp
string fts(float val, unsigned precision = 10)
string fts(double val, unsigned precision = 10)
string fts(long double val, unsigned precision = 10)
```

将浮点数类型转为字符串，保留给定的小数位数，默认为 10 位。

主要用在 `testcase_io` 上，因为 `testcase_io` 不支持浮点数输出。

```cpp
template<class T>
std::vector<string> fts(std::vector<T> val, unsigned precision = 10)
```

将一个 `vector` 内的所有浮点数转为字符串，保留给定的小数位数，默认为 10 位。

```cpp
template<class T>
std::vector<T> ltv(std::initializer_list<T> val)
```

将 `initializer_list`转为 `vector`。例子：

```cpp
vector<int> lst = ltv({114, 514, 1919, 810});
```
