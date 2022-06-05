#pragma once

template<typename T>
class Vector
{
public:
  Vector(uint8_t space = 0);
  template<size_t N> Vector(const T(&a_arr)[N]);
  ~Vector();

  bool isEmpty() const { return size() == 0; }
  uint8_t size() const;
  T* begin() const;
  T* end() const;

  void append(T element);
  Vector& operator<<(T element);
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






template<typename T>
Vector<T>::Vector(uint8_t space)
{
  m_arr = new T[space];
  m_space = space;
  m_size = 0;
}

template<typename T>
template<size_t N>
Vector<T>::Vector(const T (&a_arr)[N])
: Vector(N) 
{
  for (const T& el : a_arr)
    push_back(el);
}

template<typename T>
Vector<T>::~Vector()
{
  delete[] m_arr;
}

template<typename T>
uint8_t Vector<T>::size() const
{
  return m_size;
}

template<typename T>
T* Vector<T>::begin() const
{
  return m_arr;
}

template<typename T>
T* Vector<T>::end() const
{
  return m_arr + m_size;
}

template<typename T>
template<size_t N>
void Vector<T>::operator= (const T(&a_arr)[N]) {
  clear();
  for (const T& el : a_arr)
    push_back(el);
}

template<typename T>
void Vector<T>::append(T element)
{
  push_back(element);
}

template<typename T>
Vector<T>& Vector<T>::operator<<(T element)
{
  push_back(element);
  return (*this);
};

template<typename T>
void Vector<T>::push_back(T element)
{
  if (m_size >= m_space)
  {
    int newSpace;
    if (m_space > 0) newSpace = m_space * 2;
    else newSpace = 1;

    T* newArr = new T[newSpace];
    for (uint64_t i = 0; i < m_space; i++)
      newArr[i] = m_arr[i];
    delete[] m_arr;
    m_arr = newArr;

    m_space = newSpace;
  }

  m_arr[m_size] = element;
  m_size++;
}

template<typename T>
void Vector<T>::insert(uint8_t index, T element)
{
  T lastElement = m_arr[m_size];
  for (uint8_t i = m_size; i > index; i--)
    m_arr[i] = m_arr[i - 1];
  m_arr[index] = element;
  push_back(element);
}

template<typename T>
void Vector<T>::remove(uint8_t index)
{
  if (index >= m_size) return;

  for (uint8_t i = index; i < m_size - 1; i++)
    m_arr[i] = m_arr[i + 1];
  m_size--;

  if (m_size < m_space / 2)
  {
    T* newArr = new T[m_space / 2];
    for (uint8_t i = 0; i < m_space / 2; i++)
      newArr[i] = m_arr[i];
    delete[] m_arr;
    m_arr = newArr;
    m_space = m_space / 2;
  }
}

template<typename T>
void Vector<T>::removeFirst(T element)
{
  remove(indexOf(element));
}

template<typename T>
void Vector<T>::removeLast(T element)
{
  remove(lastIndexOf(element));
}

template<typename T>
void Vector<T>::removeAll(T element)
{
  uint8_t index = 0;

  while (index < m_size)
  {
    index = indexOf(element, index);
    remove(index);
  }
}

template<typename T>
void Vector<T>::clear()
{
  delete[] m_arr;
  m_size = 0;
  m_space = 2;
  m_arr = new T[m_space];
}

template<typename T>
bool Vector<T>::contains(T element) const {
  for (uint64_t i = 0; i < m_size; i++)
    if (m_arr[i] == element) return true;

  return false;
}

template<typename T>
uint8_t Vector<T>::indexOf(T element, uint8_t from) const
{
  for (uint8_t i = from; i < m_size; i++)
    if (m_arr[i] == element) return i;
  return m_size;
}

template<typename T>
uint8_t Vector<T>::lastIndexOf(T element) const
{
  for (uint8_t i = m_size; i > 0; i--)
    if (m_arr[i] == element) return i;
  return 0;
}

template<typename T>
uint8_t Vector<T>::lastIndexOf(T element, uint8_t from) const
{
  for (uint8_t i = from; i > 0; i--)
    if (m_arr[i] == element) return i;
  return 0;
}

template<typename T>
T& Vector<T>::at(uint8_t index)
{
  if (index > m_size)
    return (*new T());

  return m_arr[index];
}

template<typename T>
const T& Vector<T>::at(uint8_t index) const
{
  if (index > m_size)
    return (*new T());

  return m_arr[index];
}

template<typename T>
T& Vector<T>::operator[] (uint8_t index)
{
  return at(index);
}

template<typename T>
const T& Vector<T>::operator[] (uint8_t index) const
{
  return at(index);
}