# 图工具 / Graph Tools

```cpp
bool is_tree(graph g)
```

使用并查集方法，判断 `g` 是否为一棵树。

```cpp
graph relabel(graph g)
```

将给定图的所有点重新标号。

```cpp
graph prufer_decode(int n, std::vector<int> prufer, _Weight weightL = 0, _Weight weightR = 0)
```

给出一个 n 个点的树的 prufer 编码，将其转为树结构，边权在给定范围内随机生成。

```cpp
std::vector<int> get_depth(graph g)
```

获得一棵树各个节点的深度。

```cpp
graph introvert(graph tree)
```

将一棵树转为有向的内向树。

```cpp
graph externalize(graph tree)
```

将一棵树转为有向的外向树。
