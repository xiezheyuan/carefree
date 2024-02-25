# 测试点写入器 / Testcase Writer

### testcase\_io 类 <a href="#testcaseio-lei" id="testcaseio-lei"></a>

#### 构造函数 <a href="#gou-zao-han-shu" id="gou-zao-han-shu"></a>

下面的构造函数中：

* 若 `output_file` 为空，或 `disable_output` 为真，则禁用输出。此时不会生成输出文件，也无法写入。

```cpp
testcase_io(string input_file, string output_file = "")
```

给定输入文件和输出文件。

```cpp
testcase_io(string file_prefix, unsigned data_id, string input_suffix = ".in", string output_suffix = ".out", bool disable_output = false)
```

给定前缀、数据点编号和后缀名。如 `data1.in/data1.out`。

```cpp
testcase_io(string file_prefix, unsigned subtask_id, unsigned task_id, string input_suffix = ".in", string output_suffix = ".out", bool disable_output = false)
```

给定前缀、子任务编号、数据点编号和后缀名。如 `data1-1.in/data1-1.out`。

#### 支持写入的类型 <a href="#zhi-chi-xie-ru-de-lei-xing" id="zhi-chi-xie-ru-de-lei-xing"></a>

* 字符 `char`。
* 各种整数和无符号整数（包含 `__int128` 和 `unsigned __int128`）。
* 字符串 `string` 或 `const char*`。
* 布尔值 `bool`（输出 `true` 或 `false`）。
* 包含上述可输出类型的 `vector` 容器。
* 图 `graph`。
* 边 `edge`。

#### 成员函数 <a href="#cheng-yuan-han-shu" id="cheng-yuan-han-shu"></a>

```cpp
template<class T, typename ...Args>
void input_write(T val, Args ...args)
```

在输入文件中写入若干个变量，各个变量间以空格分隔。

```cpp
template<class T, typename ...Args>
void output_write(T val, Args ...args)
```

在输出文件中写入若干个变量，各个变量间以空格分隔。

```cpp
template<class T, typename ...Args>
void input_writeln(T val, Args ...args)
```

在输入文件中写入若干个变量，各个变量间以空格分隔，最后换行。

```cpp
template<class T, typename ...Args>
void output_writeln(T val, Args ...args)
```

在输出文件中写入若干个变量，各个变量间以空格分隔，最后换行。

```cpp
void input_flush()
```

刷新输入文件缓冲区。

```cpp
void output_flush()
```

刷新输出文件缓冲区。

```cpp
void output_gen(string program)
```

运行给定的程序来自动生成输出文件。注意生成完后对象将处于锁定状态，无法执行上述函数，包含 `output_gen`。注意此函数会调用系统命令行，所以如果在 Linux 下可能要以 `./` 开头。

```cpp
bool is_locked()
```

查询对象是否被锁定。

```cpp
string input_name()
```

获取输入文件名。

```cpp
string output_name()
```

获取输出文件名。
