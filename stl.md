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

