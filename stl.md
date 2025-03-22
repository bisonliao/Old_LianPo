### C++ STL 容器关键成员函数和常见使用方法要点

#### 0. vector/list/deque/set/map共有的几个含成员函数：

- `m.size();`：返回当前元素个数。
- `m.empty();`：检查是否为空。
- `m.begin(), m.end();`：返回迭代器。 
- `m.rbegin(), m.rend();`: 返回逆向迭代器，迭代器类型为`reverse_iterator`或者`const_reverse_iterator`，也是采用**自增方式移动**
- `m.clear();`：清空所有元素。

stack特殊一点，没有后面五个，只有size()和empty()



#### 1. `std::vector`
- **简介**：动态数组，支持快速随机访问。尾部压入和尾部弹出。
- **常用成员函数**：
  - `vector<int> v;`：创建一个空的`vector`。
  - `v.push_back(x);`：在末尾添加元素`x`。
  - `v.pop_back();`：移除末尾元素。
  - `v.front(); v.back()`: 访问首部/尾部元素。
  - `v[i];`：访问第`i`个元素（支持随机访问）。
- **常见使用方法**：
  ```cpp
  vector<int> v = {1, 2, 3};
  v.push_back(4);
  cout << v[0] << endl; // 输出 1
  v.pop_back();
  cout << v.size() << endl; // 输出 3
  ```

#### 2. `std::list`
- **简介**：双向链表，支持快速插入和删除。首尾都可以压入和弹出。
- **常用成员函数**：
  - `list<int> l;`：创建一个空的`list`。
  - `l.push_back(x);`：在末尾添加元素`x`。
  - `l.push_front(x);`：在开头添加元素`x`。
  - `l.pop_back();`：移除末尾元素。
  - `l.pop_front();`：移除开头元素。
  - `l.back(); l.front()`：访问尾部或首部元素。
- **常见使用方法**：
  ```cpp
  list<int> l = {1, 2, 3};
  l.push_back(4);
  l.push_front(0);
  cout << l.size() << endl; // 输出 5
  l.pop_front();
  ```

#### 3. `std::stack`
- **简介**：后进先出（LIFO）的栈。只能在顶部压入和弹出。
- **常用成员函数**：
  - `stack<int> s;`：创建一个空的`stack`。
  - `s.push(x);`：压入元素`x`。
  - `s.pop();`：弹出栈顶元素。
  - `s.top();`：访问栈顶元素。
  - `s.size();`：返回当前元素个数。
  - `s.empty();`：检查是否为空。
- **常见使用方法**：
  ```cpp
  stack<int> s;
  s.push(1);
  s.push(2);
  cout << s.top() << endl; // 输出 2
  s.pop();
  cout << s.size() << endl; // 输出 1
  ```

#### 4. `std::deque`
- **简介**：双端队列，支持在两端快速插入和删除。随机访问、首尾压入和弹出。
- **常用成员函数**：
  - `deque<int> dq;`：创建一个空的`deque`。
  - `dq.push_back(x);`：在末尾添加元素`x`。
  - `dq.push_front(x);`：在开头添加元素`x`。
  - `dq.pop_back();`：移除末尾元素。
  - `dq.pop_front();`：移除开头元素。
  - `dq.front(); dq.back()`：访问首部或尾部元素。
  - `dq[i];`：访问第`i`个元素（支持随机访问）。
- **常见使用方法**：
  ```cpp
  deque<int> dq = {1, 2, 3};
  dq.push_back(4);
  dq.push_front(0);
  cout << dq[0] << endl; // 输出 0
  dq.pop_front();
  ```

#### 5. `std::set`
- **简介**：有序集合，自动排序且不允许重复元素。元素类型要支持operator<，因为内部用了红黑树。
- **常用成员函数**：
  - `set<int> s;`：创建一个空的`set`。
  - `s.insert(x);`：插入元素`x`。
  - `s.erase(x);`：移除元素`x`。
  - `s.find(x);`：查找元素`x`，返回迭代器。
- **常见使用方法**：
  ```cpp
  set<int> s = {1, 2, 3};
  s.insert(4);
  s.erase(2);
  cout << s.size() << endl; // 输出 3
  auto it = s.find(3);
  if (it != s.end()) {
      cout << *it << endl; // 输出 3
  }
  ```

#### 6. `std::map`
- **简介**：键值对的有序映射，自动排序且不允许重复键。键的类型要支持operator<，因为内部用了红黑树。
- **常用成员函数**：
  - `map<int, string> m;`：创建一个空的`map`。
  - `m[key] = value;`：插入或更新键值对。
  - `m.erase(key);`：移除键值对。
  - `m.find(key);`：查找键，返回**迭代器**。**迭代器变量名假设叫it，it->first是key，it->second是value。**
- **常见使用方法**：
  ```cpp
  map<int, string> m = {{1, "one"}, {2, "two"}};
  m[3] = "three";
  m.erase(2);
  cout << m.size() << endl; // 输出 2
  auto it = m.find(1);
  if (it != m.end()) {
      cout << it->second << endl; // 输出 "one"
  }
  ```

#### 7. operator<

set和map需要为key类型定义operator<函数，可以是全局函数，也可以是类成员函数，特别注意这个函数的原型：

```c++
bool operator<(const node_t &a ,const node_t &b) //全局函数
{
    if (a.m_x == b.m_x)
    {
        return a.m_y < b.m_y;
    }
    else
    {
        return a.m_x < b.m_x;
    }
};
class PathListID
{
public:
    int from_x;
    int from_y;
    int to_x;
    int to_y;
    PathListID()
    {
        this->from_x = this->from_y = this->to_x = this->to_y = 0;
    };
    PathListID(int fx, int fy, int tx, int ty)
    {
        this->from_x = fx;
        this->from_y = fy;
        this->to_x = tx;
        this->to_y = ty;
    };
    bool operator<(const PathListID&a) const
    {
        if (this->from_x != a.from_x) return this->from_x < a.from_x;
        if (this->from_y != a.from_y) return this->from_y < a.from_y;
        if (this->to_x != a.to_x) return this->to_x < a.to_x;
        return this->to_y < a.to_y;
    };

};
```

#### 8. operator[]

用户程序通过std::map/ vector / deque的operator[]来访问容器中的元素，如果指定的key不存在：

- **`std::map`**：如果指定的键不存在，`operator[]` 会自动插入一个默认构造的值，并返回这个新插入的值的引用。
- **`std::vector`**：如果指定的索引超出范围，`operator[]` 会导致未定义行为，通常会导致程序崩溃。
- **`std::deque`**：如果指定的索引超出范围，`operator[]` 会导致未定义行为，通常会导致程序崩溃。

为了避免未定义行为，建议在访问 `std::vector` 和 `std::deque` 的元素时，先检查索引是否在合法范围内。对于 `std::map`，如果不想自动插入新键值对，可以使用 `find` 方法来检查键是否存在。

vector/deque我们有时候索引超出范围也没有崩溃，是因为底层分配的空间会比较富余。如果索引太大，还是会导致程序崩溃的。

#### 9. pair

这个模板类有时候挺有用的，用于快速把一对相关联的数据组合在一起。另外std::map在调用insert()的时候，可以传入一个pair，里面是一对key value。

std::pair的使用，要包含头文件 

```c++
#include <utility>
```



#### 10.  string

 `std::string` 的一些常用成员函数及其参数原型和简要说明：

##### 1. 构造函数
- **默认构造函数**
  ```cpp
  std::string();
  ```
  创建一个空字符串。

- **从 C 风格字符串初始化**
  ```cpp
  std::string(const char* s);
  ```
  从 C 风格字符串初始化。

- **拷贝构造函数**
  ```cpp
  std::string(const std::string& str);
  ```
  从另一个字符串对象拷贝初始化。

- **从子字符串初始化**
  ```cpp
  std::string(const char* s, size_t n);
  ```
  从 C 风格字符串的前 `n` 个字符初始化。

- **从子字符串初始化**
  ```cpp
  std::string(const std::string& str, size_t pos, size_t n = npos);
  ```
  从另一个字符串的子字符串初始化。

- **重复字符初始化**
  ```cpp
  std::string(size_t n, char c);
  ```
  创建一个包含 `n` 个字符 `c` 的字符串。

##### 2. 赋值操作
- **赋值操作符**
  ```cpp
  std::string& operator=(const std::string& str);
  ```
  将另一个字符串对象赋值给当前对象。

- **通用赋值函数**
  ```cpp
  std::string& assign(const char* s);
  std::string& assign(const char* s, size_t n);
  std::string& assign(const std::string& str);
  std::string& assign(const std::string& str, size_t pos, size_t n);
  std::string& assign(size_t n, char c);
  ```
  更通用的赋值函数，可以指定赋值的内容和范围。

##### 3. 字符访问
- **下标操作符**
  ```cpp
  char& operator[](size_t pos);
  const char& operator[](size_t pos) const;
  ```
  访问指定位置的字符，**可读写，即可以 a[0] = '1'; 修改字符串指定位置的字符。**

- **范围检查访问**
  
  ```cpp
  char& at(size_t pos);
  const char& at(size_t pos) const;
  ```
  访问指定位置的字符，范围检查（抛出 `std::out_of_range` 异常）。

##### 4. 字符串大小和容量
- **获取字符串长度**
  
  ```cpp
  size_t size() const;
  size_t length() const;
  ```
返回字符串的长度。
  
- **获取当前分配的容量**
  ```cpp
  size_t capacity() const;
  ```
  返回当前分配的容量。

- **检查字符串是否为空**
  ```cpp
  bool empty() const;
  ```
  检查字符串是否为空。

##### 5. 字符串修改
- **清空字符串内容**
  ```cpp
  void clear();
  ```
  清空字符串内容。

- **调整字符串大小**
  ```cpp
  void resize(size_t n, char c = char());
  ```
  调整字符串大小，不足部分用 `c` 填充。

- **在字符串末尾添加一个字符**
  ```cpp
  void push_back(char c);
  ```
  在字符串末尾添加一个字符。

- **移除字符串末尾的一个字符**

  ```cpp
  void pop_back();
  ```
  移除字符串末尾的一个字符。

  **在字符串前端插入字符**

  ```cpp
  std::string s = "World";
  s.insert(0, "Hello ");
  std::cout << s << std::endl; // 输出 "Hello World"
  ```

##### 6. 字符串拼接
- **拼接字符串**
  ```cpp
  std::string& operator+=(const std::string& str);
  std::string& operator+=(const char* s);
  std::string& operator+=(char c);
  #全局拼接函数，返回拷贝，效率应该比成员函数更低
  std::string operator+(const std::string& lhs, const std::string& rhs);
  std::string operator+(const std::string& lhs, const char* rhs);
  std::string operator+(const std::string& lhs, char rhs);
  std::string operator+(char lhs, const std::string& rhs);
  ```
  拼接字符串。
  
- **通用拼接函数**
  ```cpp
  std::string& append(const char* s);
  std::string& append(const char* s, size_t n);
  std::string& append(const std::string& str);
  std::string& append(const std::string& str, size_t pos, size_t n);
  std::string& append(size_t n, char c);
  ```
  更通用的拼接函数。


##### 7. 子字符串操作
- **获取子字符串**
  ```cpp
  std::string substr(size_t pos = 0, size_t n = npos) const;
  ```
  获取子字符串。pos：子字符串的起始位置（从0开始计数）；n: 要提取的子字符串的长度。如果省略此参数，默认npos表示提取从起始位置到字符串末尾的所有字符。

##### 8. 查找和替换
- **查找子字符串的位置**
  
  ```cpp
  size_t find(const std::string& str, size_t pos = 0) const;
  size_t find(const char* s, size_t pos = 0) const;
  size_t find(char c, size_t pos = 0) const;
  ```
查找子字符串的位置。pos：子字符串查找的起始位置（从0开始计数）
  
- **从后向前查找子字符串的位置**
  
  ```cpp
  size_t rfind(const std::string& str, size_t pos = npos) const;
  size_t rfind(const char* s, size_t pos = npos) const;
  size_t rfind(char c, size_t pos = npos) const;
  ```
从后向前查找子字符串的位置。
  
- **替换子字符串**
  ```cpp
  std::string& replace(size_t pos, size_t n, const std::string& str);
  std::string& replace(size_t pos, size_t n, const char* s);
  std::string& replace(size_t pos, size_t n, size_t m, char c);
  ```
  替换子字符串。把字符串中从pos位置开始长度位n的这一段替换位str/s/m个c。

##### 9. 比较
- **比较两个字符串是否相等**
  ```cpp
  bool operator==(const std::string& str) const;
  ```
  比较两个字符串是否相等。

- **比较两个字符串**
  ```cpp
  int compare(const std::string& str) const;
  ```
  比较两个字符串。返回值：  <0表示比参数字符串小， ==0表示等于参数字符串， >0表示比参数字符串大

##### 10. 转换
- **返回 C 风格字符串**
  ```cpp
  const char* c_str() const;
  ```
  返回 C 风格字符串。

- **返回字符串的内部数据**
  ```cpp
  const char* data() const;
  ```
  返回字符串的内部数据。

##### 11. 迭代器
- **返回迭代器**
  ```cpp
  iterator begin();
  const_iterator begin() const;
  iterator end();
  const_iterator end() const;
  
  reverse_iterator rbegin();
  reverse_iterator rend();
  ```
  返回迭代器。

#### 8、排序函数std::sort()

std::sort()要求排序的容器提供随机访问迭代器，也就是支持 operator[]，例如std::vector  std::deque 原生数组。

std::sort()不能对std::list使用，因为list不提供随机访问能力。std::list本身有个成员函数叫sort，原型：

```c++
void std::list.sort();
#为list内元素提供这个函数即可：
bool operator<(const T & a, const T &b);
```

std::sort()的使用示例：

```
#include <iostream>
#include <vector>
#include <algorithm>  /////////////这个头文件要记住
#include <string>

// 自定义结构体
struct Person {
    std::string name;
    int age;

    // 构造函数
    Person(const std::string& n, int a) : name(n), age(a) {}

};

// 比较函数，记住它的原型，bool 函数名(const 类名 & a, const 类名&b)
bool compareByAge(const Person& a, const Person& b) {
    return a.age < b.age; // 升序排序
}

int main() {
    // 创建一个 Person 对象的 vector
    std::vector<Person> people = {
        {"Alice", 30},
        {"Bob", 25},
        {"Charlie", 35}
    };

    // 使用 std::sort 和自定义比较函数
    std::sort(people.begin(), people.end(), compareByAge);


    return 0;
}
```

### C语言二维数组类型的函数参数

在C语言中，将二维数组作为函数参数时，有几种不同的方式可以声明函数和在函数体中使用该参数。以下是几种常见的方法：

#### 1. 指定数组的行和列
在函数声明中，可以指定二维数组的行和列的大小。这种方式在编译时需要知道数组的具体大小。

```c
#include <stdio.h>

void printArray(int arr[3][4], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("arr[%d][%d] = %d\n", i, j, arr[i][j]);
        }
    }
}

int main() {
    int arr[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };

    printArray(arr, 3, 4);

    return 0;
}
```

#### 2. 指定数组的列，省略行
在函数声明中，可以省略行的大小，但必须指定列的大小。这种方式在编译时只需要知道数组的列大小。

```c
#include <stdio.h>

void printArray(int arr[][4], int rows) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < 4; j++) {
            printf("arr[%d][%d] = %d\n", i, j, arr[i][j]);
        }
    }
}

int main() {
    int arr[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };

    printArray(arr, 3);

    return 0;
}
```

#### 3. 使用指针表示二维数组
可以使用指针来表示二维数组。这种方式更加灵活，可以在函数中动态处理不同大小的数组。

```c
#include <stdio.h>

void printArray(int *arr, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("arr[%d][%d] = %d\n", i, j, *(arr + i * cols + j));
        }
    }
}

int main() {
    int arr[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };

    printArray(&arr[0][0], 3, 4);

    return 0;
}
```

#### 4. 使用指针的指针表示二维数组
如果二维数组的行数和列数都不固定，可以使用指针的指针来表示二维数组。这种方式需要在调用函数时传递一个指针数组，每个指针指向一行。

```c
#include <stdio.h>

void printArray(int **arr, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("arr[%d][%d] = %d\n", i, j, arr[i][j]);
        }
    }
}

int main() {
    int arr[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };

    int *ptr[3];
    for (int i = 0; i < 3; i++) {
        ptr[i] = arr[i];
    }

    printArray(ptr, 3, 4);

    return 0;
}
```

#### 5. 总结
- **指定数组的行和列**：适用于数组大小固定的情况。
- **指定数组的列，省略行**：适用于数组行数可变但列数固定的情况。
- **使用指针表示二维数组**：适用于数组大小完全动态的情况，但需要手动计算偏移。
- **使用指针的指针表示二维数组**：适用于行数和列数都不固定的情况，但需要额外的指针数组来管理行。

选择哪种方式取决于你的具体需求和数组的大小是否固定。

### C语言中的随机数

在C语言中，随机数生成主要通过标准库 `<stdlib.h>` 和 `<time.h>` 来实现。以下是一些关键的常用函数，以及它们的使用方法。这些函数对于生成随机数非常重要，建议你记住它们的用法。

#### 1. `srand()`
**用途**：设置随机数生成器的种子。
**原型**：
```c
void srand(unsigned int seed);
```
**参数**：
- `seed`：一个无符号整数，作为随机数生成器的种子。

**说明**：

- 每次调用 `srand()` 时，都会重新初始化随机数生成器。
- 如果不调用 `srand()`，随机数生成器会使用默认种子（通常是1），导致每次运行程序时生成的随机数序列相同。
- 通常使用当前时间作为种子，以确保每次运行程序时生成的随机数序列不同。

**示例**：
```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL)); // 使用当前时间作为种子
    return 0;
}
```

#### 2. `rand()`
**用途**：生成一个伪随机数。
**原型**：
```c
int rand(void);
```
**返回值**：
- 返回一个介于 0 和 `RAND_MAX` 之间的伪随机整数。`RAND_MAX` 是一个常量，通常为 32767。

**说明**：
- 在调用 `rand()` 之前，通常需要先调用 `srand()` 设置种子。
- 如果不设置种子，`rand()` 会使用默认种子，导致每次运行程序时生成的随机数序列相同。

**示例**：
```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL)); // 使用当前时间作为种子
    int random_number = rand(); // 生成一个随机数
    printf("Random number: %d\n", random_number);
    return 0;
}
```

#### 3. 生成指定范围的随机数
**用途**：生成一个指定范围内的随机数。
**方法**：
```c
int random_number = rand() % (upper - lower + 1) + lower;
```
**说明**：
- `rand() % (upper - lower + 1)` 生成一个介于 0 和 `upper - lower` 之间的随机数。
- 加上 `lower`，将范围调整到 `[lower, upper]`。

**示例**：
```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL)); // 使用当前时间作为种子
    int lower = 10, upper = 20;
    int random_number = rand() % (upper - lower + 1) + lower;
    printf("Random number between %d and %d: %d\n", lower, upper, random_number);
    return 0;
}
```

#### 4. 生成浮点数随机数
**用途**：生成一个介于 0 和 1 之间的随机浮点数。
**方法**：
```c
double random_double = (double)rand() / RAND_MAX;
```
**说明**：
- `(double)rand()` 将 `rand()` 的返回值转换为双精度浮点数。
- 除以 `RAND_MAX`，将范围缩放到 `[0, 1)`。

**示例**：
```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL)); // 使用当前时间作为种子
    double random_double = (double)rand() / RAND_MAX;
    printf("Random double between 0 and 1: %f\n", random_double);
    return 0;
}
```

#### 5. 生成指定范围的浮点数随机数
**用途**：生成一个指定范围内的随机浮点数。
**方法**：
```c
double random_double = (double)rand() / RAND_MAX * (upper - lower) + lower;
```
**说明**：
- `(double)rand() / RAND_MAX` 生成一个介于 0 和 1 之间的随机浮点数。
- 乘以 `(upper - lower)`，将范围缩放到 `[0, upper - lower)`。
- 加上 `lower`，将范围调整到 `[lower, upper)`。

**示例**：
```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL)); // 使用当前时间作为种子
    double lower = 10.0, upper = 20.0;
    double random_double = (double)rand() / RAND_MAX * (upper - lower) + lower;
    printf("Random double between %.2f and %.2f: %.2f\n", lower, upper, random_double);
    return 0;
}
```

#### 6. 总结
- **`srand(unsigned int seed)`**：设置随机数生成器的种子。
- **`rand()`**：生成一个介于 0 和 `RAND_MAX` 之间的伪随机整数。
- **生成指定范围的随机整数**：`rand() % (upper - lower + 1) + lower`。
- **生成介于 0 和 1 之间的随机浮点数**：`(double)rand() / RAND_MAX`。
- **生成指定范围的随机浮点数**：`(double)rand() / RAND_MAX * (upper - lower) + lower`。

这些函数和方法是C语言中生成随机数的基础，建议你记住它们的用法，以便在考试中能够熟练使用。