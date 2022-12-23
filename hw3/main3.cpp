#include <iostream>

using namespace std;

template <class T> class int_array_cell {
private:
  T *_memory;
  int _counter;

public:
  int_array_cell(T *ptr) : _memory(ptr), _counter(1) { // constructor
  }
  ~int_array_cell() {
    delete[] _memory; // destructor
  }
  T *get_memory() { return _memory; }
  int get_counter() { return _counter; }
  void inc_counter() { ++_counter; }
  void dec_counter() {
    --_counter;
    if (_counter == 0) {
      delete this;
    }
  }
};

template <class T> class counter_ptr {
private:
  int_array_cell<T> *_cell_ptr;

public:
  counter_ptr(T *ptr = 0) : _cell_ptr(0) {
    if (ptr) { // if ptr is not null
      _cell_ptr = new int_array_cell<T>(ptr);
    }
  }
  ~counter_ptr() {
    if (_cell_ptr) {
      _cell_ptr->dec_counter();
      if (_cell_ptr->get_counter() == 0)
        delete _cell_ptr; // if counter is 0, delete the cell
    }
  }
  T *get_memory() { // get the memory of the cell
    if (_cell_ptr)
      return _cell_ptr->get_memory();
    else
      return nullptr;
  }
  T &operator[](int index) { // get the value of the memory
    return get_memory()[index];
  }
  void release() {
    if (_cell_ptr) { // if cell_ptr is not null
      _cell_ptr->dec_counter();
      _cell_ptr = nullptr;
    }
  }
  counter_ptr &operator=(T *ptr) {
    if (_cell_ptr) { // if cell_ptr is not null
      _cell_ptr->dec_counter();
      if (_cell_ptr->get_counter() == 0)
        delete _cell_ptr;
    }
    _cell_ptr = new int_array_cell<T>(ptr); // create a new cell
    return *this;
  }
};

class stack {
private:
  int _top;
  counter_ptr<char> _data;

public:
  stack() {
    _top = -1;
    _data = new char[300];
  }
  void push(char *tmp) {
    for (int i = 0; tmp[i] != '\0'; ++i) {
      _data[++_top] = tmp[i];
    }
  }
  void pop() {
    if (_top != -1) {
      char tmp[3] = {_data[_top - 1], _data[_top], '\0'};
      _top -= 2;
      cout << tmp << '\n';
    }
  }
  void print() {
    for (int i = 0; i <= _top; i += 2) {
      char tmp[3] = {_data[i], _data[i + 1], '\0'};
      cout << tmp;
    }
    cout << '\n';
  }
  void printBig5() {
    for (int i = 0; i <= _top; ++i) {
      if (~i & 1)
        cout << "( ";
      cout << (int)_data[i] << ' ';
      if (i & 1)
        cout << ") ";
    }
    cout << '\n';
  }
  void clear() {
    _top = -1;
    _data = new char[300];
  }
  bool find(char *tmp) {
    for (int i = 0; i <= _top; ++i) {
      if (_data[i] == tmp[0] && _data[i + 1] == tmp[1]) {
        return true;
      }
    }
    return false;
  }
};

int main() {
  char in;
  char str[100];
  stack s;
  while (cin >> in) {
    switch (in) {
    case 'I':
      cin >> str;
      s.push(str);
      break;
    case 'P':
      s.print();
      break;
    case 'B':
      s.printBig5();
      break;
    case 'R':
      s.pop();
      break;
    case 'C':
      s.clear();
      break;
    case '?':
      cin >> str;
      cout << (s.find(str) ? "是" : "否") << '\n';
      break;
    }
  }
}