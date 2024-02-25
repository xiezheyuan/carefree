# 介绍 / Introduction

## Carefree Library

Carefree 是一个帮助您高效造数据的 C++ 库。它具有如下优点：

* 基于 C++ 实现，相比于 CYaRon 有较高的文件 I/O 和运算效率，且更易上手。
* 自带方便的文件 I/O（参考了 CYaRon 的设计），不必编写复杂的 shell / cmd 脚本（testlib，说的就是你）。
* 自带多种树的构造（参考了 Tree-Generator 的设计），不必费心思就可以造出具有足够强度的数据。
* 可以在造数据中渲染带计时功能的进度条帮您监测造数据进度。
* 支持生成 luogu 题目测试点配置文件，不必手动设置时空限制和子任务。
* 随机使用 `mt19937_64`，在 `main` 函数前自动执行随机数种子设置，保证足够的随机性。

特殊的设计，帮助已经上手了 CYaRon / Tree Generator / Testlib 的您快速上手 carefree，同时新手学习 carefree 难度也不高。

环境要求：C++ 14 或更高版本，GCC/G++ 编译器。也就是说，支持传统的 Dev-C++ 和 NOI Linux 上的编译器。

示例：一个生成 A+B Problem 的生成器，含多档 Subtask：

```cpp
#include "carefree.hpp"
using namespace std;

signed main(){
    gen_data(5, 5, [&](int i, int j){
        testcase_io io("data/", i, j);
        int n = 1e7;
        if(i == 1) n = 10;
        if(i == 2) n = 100;
        if(i == 3) n = 1000;
        if(i == 4) n = 1e5;
        int a = randint(1, n), b = randint(1, n);
        io.input_write(a, b);
        io.output_write(a + b);
    });
}
```

## 近景目标

* 将整个代码用 `namespace` 包裹。
* 添加更多的 OJ 测试点配置写入器支持，如 LibreOJ(syzoj)、hydro、uoj 等。
* 添加让 SPFA 算法（基于队列优化的 Bellman-Ford 算法）运行至复杂度上界的数据。

## Q & A

Q:：这个项目是谁开发的？

A：目前开发者是 xiezheyuan，欢迎大家参与！

Q:：你为什么要起这样一个名字

A：carefree 的意思是无忧无虑地，无所顾忌地。我希望您在使用 CareFree 时可以享受到无忧无虑的轻松体验。

Q：有什么限制吗？

A：没有什么限制。您可以在 MIT License 下自由使用本库，不过如果你将其用在了出题上，请尽量将其推广，以便让更多的人看得到。

Q：如何参与呢？

A：洛谷私信联系 xiezheyuan，或者加 QQ 3523400344。也可以向 Github 发起 PR。
