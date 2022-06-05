#pragma once

namespace MicroQt {
  template<typename T>
  class vector {
  public:
    vector(uint8_t space = 0);
    template<size_t N> vector(const T(&a_arr)[N]);
    ~vector();

    bool isEmpty() const { return size() == 0; }
    uint8_t size() const;
    T* begin() const;
    T* end() const;

    void append(T element);
    vector& operator<<(T element);
    void push_back(T element);

    template<size_t N>
    void operator= (const T(&a_arr)[N]);

    void insert(uint8_t index, T element);

    void remove(uint8_t index);
    void removeFirst(T element);
    void removeLast(T element);
    void removeAll(T element);
    void removeFirst() { remove(0); }
    void removeLast() { remove(size() - 1); }

    void clear();

    bool contains(T element) const;
    uint8_t indexOf(T element, uint8_t from = 0) const;
    uint8_t lastIndexOf(T element) const;
    uint8_t lastIndexOf(T element, uint8_t from) const;

    T& at(uint8_t index);
    const T& at(uint8_t index) const;
    T& operator[] (uint8_t index);
    const T& operator[] (uint8_t index) const;
    T& first() { return at(0); }
    T& last() { return at(size() - 1); }

  private:
    T* m_arr = nullptr;
    uint8_t m_space;
    uint8_t m_size;
  };

  #include "Vector.hpp"
}