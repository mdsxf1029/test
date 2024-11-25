**来自Claude**
以下是 Google C++ 代码风格指南的主要要点总结：

1. 文件相关
- 文件名全小写，用下划线连接：my_file_name.cc
- C++ 文件以 .cpp 结尾，头文件以 .h 结尾
- 每个头文件都应该使用 #pragma once 或头文件保护宏
```cpp
#ifndef FOO_BAR_BAZ_H_
#define FOO_BAR_BAZ_H_
...
#endif // FOO_BAR_BAZ_H_
```

2. 命名约定
- 类名：大驼峰命名法 MyClass
- 变量名：小驼峰命名法 myVariable
- 常量名：k开头的大驼峰 kMaxCount
- 函数名：大驼峰命名法 MyFunction()
- 命名空间：全小写，下划线连接 my_namespace
- 枚举名：大驼峰命名法
- 宏定义：全大写，下划线连接 MY_MACRO

3. 格式化
- 缩进使用2个空格，不用 tab
- 行长度最多80字符
- 函数参数如果太长需要换行，参数要对齐
```cpp
ReturnType LongFunctionName(Type par1, Type par2,
                           Type par3) {
  DoSomething();
}
```

4. 类的声明
- public、protected、private 按顺序排列
- 成员函数和数据成员分别归类
```cpp
class MyClass {
 public:
  MyClass();
  ~MyClass();
 
 protected:
  void DoSomething();
 
 private:
  int private_var_;
};
```

5. 注释规范
- 文件开头注释描述文件内容
- 类的注释说明用途
- 函数注释说明功能、参数、返回值
```cpp
// 单行注释

/*
 * 多行注释
 */

/// 文档注释 (用于生成文档)
```

6. 其他规范
- 使用 nullptr 而不是 NULL
- 优先使用 auto 进行类型推导
- 优先使用 STL 容器
- 在构造函数中使用初始化列表
- 明确类成员的初始化顺序

7. 代码组织
- 相关的声明放在同一个命名空间中
- 避免使用全局变量
- .h文件中只放声明，实现放在.cc文件中
- 内联函数定义可以放在头文件中

8. 最佳实践
- 禁用异常
- 避免使用多重继承
- 构造函数中只做初始化工作
- 使用前置声明减少依赖
- 注意变量的作用域最小化
- 智能指针优于原始指针

9. 头文件包含顺序
```cpp
1. 相关头文件
2. C 系统文件
3. C++ 系统文件
4. 其他库的 .h 文件
5. 本项目内 .h 文件
```

10. 特性使用
- 谨慎使用 C++11 新特性
- 使用 override 标记重写函数
- 使用 const 修饰不变内容
- 合理使用引用和指针

遵循以上规范可以：
- 提高代码可读性
- 保持代码风格统一
- 避免常见错误
- 方便团队协作
- 提高代码维护性

注意：具体项目中可能会有自己的编码规范，应该以项目实际规范为准。