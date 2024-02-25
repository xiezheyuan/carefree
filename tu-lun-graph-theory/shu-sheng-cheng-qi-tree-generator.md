# 树生成器 / Tree Generator

```cpp
graph lowhigh(int n, double low, double high, _Weight weightL = 0, _Weight weightR = 0)
```

随机生成一个 n 个点的树，从第二节点开始，每个节点的父亲从 \[(i-1)\*low,(i-1)\*high] 中选择，边权从给定区间中随机选择。若 low,high 设置得当，可以生成强度足够的树。

```cpp
graph naive_tree(int n, _Weight weightL = 0, _Weight weightR = 0)
```

使用经典的随机选择父亲法生成树，边权从给定区间中随机选择。

```cpp
graph tail(int n, int k, _Weight weightL = 0, _Weight weightR = 0)
```

随机生成一个 n 个点的树，每个点仅选择最后 k 个节点作为父亲，边权从给定区间中随机选择。可以生成较高的树。

```cpp
graph chain(int n, _Weight weightL = 0, _Weight weightR = 0)
```

生成一条长度为 n 的链，边权从给定区间中随机选择。

```cpp
graph star(int n, _Weight weightL = 0, _Weight weightR = 0)
graph flower(int n, _Weight weightL = 0, _Weight weightR = 0)
```

生成一个 n 个点的菊花图，边权从给定区间中随机选择。

```cpp
graph max_degree(int n, int k, _Weight weightL = 0, _Weight weightR = 0)
```

随机生成一个 n 个点的树，不过每个点度数不超过 k，边权从给定区间中随机选择。

```cpp
graph binary_tree(int n, _Weight weightL = 0, _Weight weightR = 0)
```

随机生成一个 n 个点的二叉树，边权从给定区间中随机选择。

```cpp
graph chain_star(int n, int k, _Weight weightL = 0, _Weight weightR = 0)
```

生成一个链套菊花的结构，先生成一个长度为 k 的链，然后随机挂上 n-k 个点，边权从给定区间中随机选择。

```cpp
graph silkworm(int n, _Weight weightL = 0, _Weight weightR = 0)
```

生成一个毛毛虫，就是先生成一个长度为 n/2 的链，然后在每个链上的点上挂一个点，边权从给定区间中随机选择。

```cpp
graph firecrackers(int n, _Weight weightL = 0, _Weight weightR = 0)
```

生成一个爆竹树，就是先生成一个长度为 n/3 的链，然后在每个链上的点上挂两个点，边权从给定区间中随机选择。

```cpp
graph complete(int n, int k, _Weight weightL = 0, _Weight weightR = 0)
```

生成一个 n 个点的完全 k 叉树，边权从给定区间中随机选择。

```cpp
graph complete_binary(int n, _Weight weightL = 0, _Weight weightR = 0)
```

生成一个 n 个点的完全二叉树，边权从给定区间中随机选择。

```cpp
graph random_tree(int n, _Weight weightL = 0, _Weight weightR = 0)
```

使用 Prufer 序列生成一个真正随机的树，边权从给定区间中随机选择。
