template<typename T>
Vector<T>::Vector(uint8_t space) {
  m_arr = new T[space];
  m_space = space;
  m_size = 0;
}

template<typename T>
void Vector<T>::append(const T& element) {
  if (m_size >= m_space) {
    m_space = m_space > 0 ? 2 * m_space : 1;
    T* newArr = new T[m_space];
    for (uint64_t i = 0; i < m_size; i++)
      newArr[i] = m_arr[i];
    delete[] m_arr;
    m_arr = newArr;
  }
  m_arr[m_size] = element;
  m_size++;
}

template<typename T>
Vector<T>& Vector<T>::operator<<(const T& element) {
  append(element);
  return (*this);
};

template<typename T>
void Vector<T>::insert(uint8_t index, T element) {
  if (index > m_size) return;

  if (m_size >= m_space) {
    m_space = m_space > 0 ? 2 * m_space : 1;
    T* newArr = new T[m_space];
    for (int16_t i = m_size; i > index; i--)
      newArr[i + 1] = m_arr[i];
    newArr[index] = element;
    for (int16_t i = index - 1; i > 0; i--)
      newArr[i + 1] = m_arr[i];
    delete[] m_arr;
    m_arr = newArr;
    m_size++;
  } else {
    for (uint8_t i = m_size; i > index; i--)
      m_arr[i] = m_arr[i - 1];
    m_arr[index] = element;
    m_size++;
  }
}

template<typename T>
void Vector<T>::removeAt(uint8_t index) {
  if (index >= m_size) return;

  for (uint8_t i = index; i < m_size - 1; i++)
    m_arr[i] = m_arr[i + 1];
  m_size--;

  if (m_size < m_space / 2) {
    T* newArr = new T[m_space / 2];
    for (uint8_t i = 0; i < m_size; i++)
      newArr[i] = m_arr[i];
    delete[] m_arr;
    m_arr = newArr;
    m_space = m_space / 2;
  }
}

template<typename T>
void Vector<T>::removeAll(const T& element) {
  uint8_t index = 0;
  while (index < m_size) {
    index = indexOf(element, index);
    removeAt(index);
  }
}

template<typename T>
T Vector<T>::take(uint8_t index) {
  if (index >= size())
    return T();

  T t;
  t = at(index);
  removeAt(index);
  return t;
}

template<typename T>
void Vector<T>::clear() {
  delete[] m_arr;
  m_size = 0;
  m_space = 2;
  m_arr = new T[m_space];
}

template<typename T>
bool Vector<T>::contains(const T& element) const {
  for (uint64_t i = 0; i < m_size; i++)
    if (m_arr[i] == element) return true;

  return false;
}

template<typename T>
uint8_t Vector<T>::indexOf(const T& element, uint8_t from) const {
  for (uint8_t i = from; i < m_size; i++)
    if (m_arr[i] == element) return i;
  return m_size;
}

template<typename T>
const T& Vector<T>::at(uint8_t index) const {
  static T t;
  if (index > m_size)
    return t;
  return m_arr[index];
}

template<typename T>
T& Vector<T>::operator[] (uint8_t index) {
  static T t;
  if (index > m_size)
    return t;
  return m_arr[index];
}

template<typename T>
bool Vector<T>::operator== (const Vector& vector) {
  if (size() != vector.size())
    return false;
  for (int i = 0; i < vector.size(); i++)
    if (at(i) != vector.at(i))
      return false;
  return true;
}