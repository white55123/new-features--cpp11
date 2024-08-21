# c++11 新特性

## using 的使用

1.定义类型的别名:

在C++中我们可以通过typedef重定义一个类型，语法的格式如下所示:

```c++
typedef 旧的类型名 新的类型名
//使用举例
typedef unsigned int uint_t;
```

被重定义的类型不是一个新的类型，仅仅是给原有的类型取了一个新的名字。



在C++中规定了一种新的方法，使用别名声明(alias declaration)来定义类型的别名，即使用using。

使用的时候，关键字using作为别名声明的开始，其后面紧跟别名和等号，作用是把等号左侧的名字规定成等号右侧类型的别名。**类型别名和类型的名字是等价的，只要是类型名字出现的地方，就能使用类型的别名。使用typedef定义的别名和使用using定义的别名在语义上是等效的。**

格式如下所示：

```c++
using 新的类型=旧的类型
//使用举例
using uint_t = int;

```



```c++
int mytest(int a, string b)
{
    cout << "a: " << a <<", b: " << b << endl;
}
//定义函数指针
typedef int(*func)(int,string);
using func1 = int(*) (int,string);

int main(int argv,char* argv[])
{
    //typedef定义的函数指针
    func f = mytest;
    //using定义的函数指针
    func1 f1 = mytest;
    f(10, "hello");
    f1(10, "hello");
    //解引用的方式
    (*f)(10, "s");
}
```

根据以上内容我们发现，using相比较typedef来说，只是using的可读性更高。

下面我们讲一讲using和typedef的区别:

首先我们通过typedef给一个模板写一个别名

```c++
#include <iostream>
#include <map>
#include <string>
using namespace std;

template <typename T>
class Container
{
public:
    void print(const T& t)const
    {
        auto it = t.begin();
        for (; it != t.end(); ++it)
        {
            cout << it->first << ", " << it->second << endl;
        }
    }
};


//类模板
template <typename T>
struct MyMap
{
    typedef std::map<int, T> mapType;
};

int main(int argc, char* argv[])
{
    MyMap<int>::mapType mm1;
    mm1.insert(std::make_pair(1, 1));
    mm1.insert(std::make_pair(2, 2));
    Container<MyMap<int>::mapType> c;
    c.print(mm1);

    MyMap<double>::mapType mm2;
    mm2.insert(std::make_pair(1, 1.1));
    mm2.insert(std::make_pair(2, 2.2));
    Container<MyMap<double>::mapType> b;
    b.print(mm2);

    MyMap<std::string>::mapType mm3;
    mm3.insert(std::make_pair(1, "hello"));
    mm3.insert(std::make_pair(2, "world"));
    Container<MyMap<std::string>::mapType> a;
    a.print(mm3);

}
```

输出结果：

```bash
1, 1
2, 2
1, 1.1
2, 2.2
1, hello
2, world
```

我们会发现非常麻烦，下面我们使用using:

```c++
#include <iostream>
#include <map>
#include <string>
using namespace std;

template <typename T>
class Container
{
public:
    void print(const T& t)const
    {
        auto it = t.begin();
        for (; it != t.end(); ++it)
        {
            cout << it->first << ", " << it->second << endl;
        }
    }
};


template <typename T>
using MMap = map<int, T>;

int main(int agrc, char* argv[])
{
		MMap<string> mm3;
	    mm3.insert(std::make_pair(1, "hello"));
	    mm3.insert(std::make_pair(2, "world"));
	    Container<MMap<string>> a;
	    a.print(mm3);
}
```

这样子我们会发现，使用using的时候，代码变得更加简洁，可读性也更高了。



**最后强调一下，using的语法和typedef一样，不会创建出新的类型，他们只是给某些类型定义了新的名字。using相比较于typedef的优势在于定义函数指针别名看起来更直观，可读性更高。**