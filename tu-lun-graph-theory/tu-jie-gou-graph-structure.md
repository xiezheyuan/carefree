# 图结构 / Graph Structure

### graph 类 <a href="#graph-lei" id="graph-lei"></a>

#### 构造函数 <a href="#gou-zao-han-shu" id="gou-zao-han-shu"></a>

```cpp
graph(int N, bool directed = false, bool enable_edge_map = true)
```

* N 表示点数。
* `directed` 表示是否有向。
* `enable_edge_map` 表示是否建立边映射，如果不建立无法使用 `has_edge` 功能，如果建立则加入新边需要 O(log n) 的时间复杂度。

#### 成员函数 <a href="#cheng-yuan-han-shu" id="cheng-yuan-han-shu"></a>

```cpp
void add(edge edg, bool __add_vector = true)
void add(int from, int to, _Weight weight = 0)
```

表示添加一条边，`__add_vector` 请勿填写。

```cpp
bool has_edge(edge edg)
bool has_edge(int from, int to)
```

查询是否存在一条边。不考虑边权。

```cpp
std::vector<edge> get_edges()
```

获取所有边。

```cpp
std::vector<edge> get_edges(int from)
```

获取一个点的所有出边。

```cpp
template<class T = weighted_output>
string to_string(bool shuffle = false)
```

将图转为字符串。`shuffle` 表示是否需要打乱边的顺序，`T` 为边输出方法，后文将会介绍。

### edge 结构体 <a href="#edge-jie-gou-ti" id="edge-jie-gou-ti"></a>

#### 构造函数 <a href="#gou-zao-han-shu-1" id="gou-zao-han-shu-1"></a>

```cpp
edge(int from, int to, _Weight weight = 0)
```

表示一条边的各个信息。

#### 成员变量 <a href="#cheng-yuan-bian-liang" id="cheng-yuan-bian-liang"></a>

```cpp
int from, to;
_Weight weight;
```

表示一条边的各个信息。

### 边输出方法 <a href="#bian-shu-chu-fang-fa" id="bian-shu-chu-fang-fa"></a>

#### weighted\_output 结构体 <a href="#weightedoutput-jie-gou-ti" id="weightedoutput-jie-gou-ti"></a>

表示为带权图，即每条边输出三个数，为起点、终点、边权。

#### unweighted\_output 结构体 <a href="#unweightedoutput-jie-gou-ti" id="unweightedoutput-jie-gou-ti"></a>

表示为无权图，即每条边输出两个数，为起点、终点。

#### 自定义边输出方法 <a href="#zi-ding-yi-bian-shu-chu-fang-fa" id="zi-ding-yi-bian-shu-chu-fang-fa"></a>

定义一个结构体，定义下面的方法即可，表示将一条边转为字符串：

```cpp
string operator()(edge edg)
```
