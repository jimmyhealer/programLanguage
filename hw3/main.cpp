#include <iostream>
using namespace std;

class int_array_cell {
private:
  int *_memory;
  int _counter;

public:
  int_array_cell(int *ptr) : _memory(ptr), _counter(1) { // constructor
    cout << "int_array_cell is allocated\n";
  }
  ~int_array_cell() {
    delete[] _memory; // destructor
  }
  int *get_memory() { return _memory; }
  int get_counter() { return _counter; }
  void inc_counter() {
    ++_counter;
    cout << "int_array_cell counter is increased: counter " << _counter << "\n";
  }
  void dec_counter() {
    --_counter;
    if (_counter == 0) { // if counter is 0, delete the cell
      cout << "int_array_cell counter " << _counter << ": deleted\n";
    } else {
      cout << "int_array_cell counter is decreased: counter " << _counter
           << "\n";
    }
  }
};

class counter_ptr {
private:
  char *_name;
  int_array_cell *_cell_ptr;

public:
  counter_ptr(char *name, int *ptr = 0) : _name(name), _cell_ptr(0) {
    if (ptr) { // if ptr is not null
      _cell_ptr = new int_array_cell(ptr);
      cout << "counter_ptr " << _name
           << " is assigned to an int_array_cell: counter "
           << _cell_ptr->get_counter() << "\n";
    } else { // only name is given
      cout << "counter_ptr " << _name
           << " is not assigned to an int_array_cell\n";
    }
  }
  ~counter_ptr() {
    cout << "counter_ptr " << _name << " is deleted\n";
    if (_cell_ptr) {
      _cell_ptr->dec_counter();
      if (_cell_ptr->get_counter() == 0)
        delete _cell_ptr; // if counter is 0, delete the cell
    }
  }
  int *get_memory() { // get the memory of the cell
    if (_cell_ptr)
      return _cell_ptr->get_memory();
    else
      return 0;
  }
  int &operator[](int index) { // get the value of the memory
    return get_memory()[index];
  }
  void release() {
    if (_cell_ptr) { // if cell_ptr is not null
      _cell_ptr->dec_counter();
      _cell_ptr = 0;
    }
    cout << "counter_ptr " << _name
         << " is not assigned to an int_array_cell\n";
  }
  counter_ptr &operator=(int *ptr) {
    if (_cell_ptr) { // if cell_ptr is not null
      _cell_ptr->dec_counter();
      if (_cell_ptr->get_counter() == 0)
        delete _cell_ptr;
    }
    _cell_ptr = new int_array_cell(ptr); // create a new cell
    cout << "counter_ptr " << _name
         << " is assigned to an int_array_cell: counter "
         << _cell_ptr->get_counter() << "\n";
    return *this;
  }
  counter_ptr &operator=(counter_ptr &ptr) {
    if (_cell_ptr) { // if cell_ptr is not null
      _cell_ptr->dec_counter();
      if (_cell_ptr->get_counter() == 0)
        delete _cell_ptr;
    }
    _cell_ptr = ptr._cell_ptr; // assign the cell of ptr to this
    if (_cell_ptr)
      _cell_ptr->inc_counter(); // if cell_ptr is not null, increase the counter
    cout << "counter_ptr " << _name
         << " is assigned to an int_array_cell: counter "
         << _cell_ptr->get_counter() << "\n";
    return *this;
  }
};

int main() {
  counter_ptr b("b", new int[10]);

  {
    b = new int[100];

    counter_ptr a("a");

    a = b;
  }

  for (int i = 0; i < 10; ++i)
    b[i] = i;

  for (int i = 0; i < 10; ++i)
    cout << b[i] << ' ';
  cout << '\n';

  counter_ptr c("c");

  c = b;
  b.release();
}
