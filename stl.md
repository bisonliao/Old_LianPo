### C++ STL 容器关键成员函数和常见使用方法要点

#### 0. vector/list/deque/set/map共有的几个含成员函数：

- `m.size();`：返回当前元素个数。
- `m.empty();`：检查是否为空。
- `m.begin(), m.end();`：返回迭代器。 
- `m.clear();`：清空所有元素。

stack特殊一点，没有后面三个，只有size()和empty()



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
  - `m.find(key);`：查找键，返回迭代器。
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



#### 7.  string

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
  访问指定位置的字符（可读写）。

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
  获取子字符串。pos：子字符串的起始位置（从0开始计数）；npos: 要提取的子字符串的长度。如果省略此参数，默认提取从起始位置到字符串末尾的所有字符。

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
  替换子字符串。

##### 9. 比较
- **比较两个字符串是否相等**
  ```cpp
  bool operator==(const std::string& str) const;
  ```
  比较两个字符串是否相等。

- **比较两个字符串**
  ```cpp
  int compare(const std::string& str) const;
  int compare(size_t pos, size_t n, const std::string& str) const;
  int compare(size_t pos, size_t n, const std::string& str, size_t pos2, size_t n2) const;
  ```
  比较两个字符串。

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
  ```
  返回迭代器。

#### 8、排序函数std::sort

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

