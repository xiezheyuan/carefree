# 随机相关 / Random

```cpp
template<class T>
T randint(T l, T r)
```

随机生成介于 \[l,r] 的整数。

```cpp
template<class T>
T uniform(T l, T r)
```

随机生成介于 \[l,r] 的浮点数。

```cpp
double random();
```

随机生成介于 \[0,1] 的浮点数。

```cpp
template<class T>
typename T::value_type choice(T val)
```

在 `vector` 或其他随机访问容器中随机选择一个元素。

```cpp
template<class T>
void shuffle(T val)
```

随机打乱给定的容器。
