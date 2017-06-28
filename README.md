# mips_sim
2017 SJTU PPCA project

## 2017-6-26

- 阅读了http://www.cnblogs.com/thoupin/p/4018455.html 受益匪浅
- 阅读了助教给的pdf
- 简单画了一下项目需要的类，初步认识了五级流水以及hazard
- 写了line类用于区分每行
- 写了main函数部分，确定了整个框架
- 写了部分Parser
- 测试了函数指针

## 2017-6-27

- 完成了parser
- 在spill2上测试了parser得到了对应结构文件
- 思考了带分支预测的五级流水结构
- 完成了结构的流程图（手画+电子版）

## 2017-6-29

- 进行了程序label的预处理（替换为行号）
- cpu进行内存的预分配
- 架好了5级流水的程序框架
- 更新了代表内存的Brick类（lohi要8位）
- 修正了'('')''$'的读入错误
- 写了IF(未进行分支预测)
- 更新了许多常数表
- 改变了原来distribute的位置
- 学习了c++11风格的多线程写法#include<thread>