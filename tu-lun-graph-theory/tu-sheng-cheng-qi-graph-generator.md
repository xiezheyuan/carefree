# 图生成器 / Graph Generator

```cpp
graph dag(int n, int m, bool repeat_edges = false, _Weight weightL = 0, _Weight weightR = 0)
```

随机生成一个 n 个点 m 条边的 DAG（保证连通），可以指定是否允许有重边。边权在给定区间中随机选择。

```cpp
graph connected_undirected_graph(int n, int m, bool repeat_edges = false, bool self_loop = false, _Weight weightL = 0, _Weight weightR = 0)
```

随机生成一个 n 个点 m 条边的无向连通图，可以指定是否允许有重边或自环。边权在给定区间中随机选择。

```cpp
graph connected_directed_graph(int n, int m, bool repeat_edges = false, bool self_loop = false, _Weight weightL = 0, _Weight weightR = 0)
```

随机生成一个 n 个点 m 条边的有向连通图，可以指定是否允许有重边或自环。边权在给定区间中随机选择。

```cpp
graph random_graph(int n, int m, bool directed = true, bool repeat_edges = false, bool self_loop = false, _Weight weightL = 0, _Weight weightR = 0)
```

随机生成一个 n 个点 m 条边的图，可以指定是否有向、是否允许有重边或自环。边权在给定区间中随机选择。
