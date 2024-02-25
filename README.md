[文档](https://xie-zheyuan.gitbook.io/carefree-cn/)

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



