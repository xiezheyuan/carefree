# 计时与批处理 / Batching & Timer

```cpp
template<class T>
double timer(T function)
```

执行给定函数，返回耗时（单位为秒）。

```cpp
template<class T>
void gen_data(int subtask_count, int task_per_subtask, T function)
```

模拟生成含子任务的数据生成，给定子任务数量和每个子任务的测试点数量，调用 f(i,j) 表示第 i 个子任务中的第 j 个测试点。同时绘制进度条。

```cpp
template<class T>
void gen_data(int task_count, T function)
```

模拟普通数据生成，给定测试点数量，调用 f(i) 表示第 i 个测试点，同时绘制进度条。
