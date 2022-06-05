#pragma once

#include <vector>
#include <initializer_list>

namespace MicroQt {
  template<typename T>
  class Vector {
  public:
    Vector(uint8_t space = 0);
    ~Vector() { delete[] m_arr; }

    uint8_t size() const { return m_size; }
    bool isEmpty() const { return m_size == 0; }

    T* begin() const { return m_arr; }
    T* end() const { return m_arr + sizeof(T) * m_size; }

    bool contains(const T& element) const;
    uint8_t indexOf(const T& element, uint8_t from = 0) const;

    T& operator[] (uint8_t index);
    const T& at(uint8_t index) const;

    bool operator== (const Vector& vector);

    void append(const T& element);
    Vector& operator<<(const T& element);
    Vector& operator+=(const T& element) { return operator<<(element); }
    void push_back(const T& element) { append(element); }
    void insert(uint8_t index, T element);

    void removeAll(const T& element);
    void removeAt(uint8_t index);
    T take(uint8_t index);
    void clear();

  private:
    T* m_arr = nullptr;
    uint8_t m_space;
    uint8_t m_size;
  };

  #include "Vector.hpp"
}