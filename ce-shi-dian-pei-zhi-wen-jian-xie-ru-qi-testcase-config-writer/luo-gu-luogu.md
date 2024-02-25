# 洛谷 / Luogu

### luogu\_testcase\_config\_writer 类 <a href="#luogutestcaseconfigwriter-lei" id="luogutestcaseconfigwriter-lei"></a>

#### 构造函数 <a href="#gou-zao-han-shu" id="gou-zao-han-shu"></a>

```cpp
luogu_testcase_config_writer()
```

#### 成员函数 <a href="#cheng-yuan-han-shu" id="cheng-yuan-han-shu"></a>

```cpp
void add(string input_name, int time_limit, int memory_limit, int score = -1, int subtask_id = -1)
```

添加一个测试点，给定输入文件，时间限制，空间限制，子任务编号（可留空），分值（可留空）。

```cpp
void save(string filename = "config.yml")
```

保存配置文件。

```cpp
string to_string()
```

获取配置文件的字符串内容。
