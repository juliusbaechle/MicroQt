template<typename T>
vector<T>::vector(uint8_t space) {
  m_arr = new T[space];
  m_space = space;
  m_size = 0;
}

template<typename T>
template<size_t N>
vector<T>::vector(const T(&a_arr)[N])
  : vector(N) {
  for (const T& el : a_arr)
    push_back(el);
}

template<typename T>
vector<T>::~vector() {
  delete[] m_arr;
}

template<typename T>
uint8_t vector<T>::size() const {
  return m_size;
}

template<typename T>
T* vector<T>::begin() const {
  return m_arr;
}

template<typename T>
T* vector<T>::end() const {
  return m_arr + m_size;
}

template<typename T>
template<size_t N>
void vector<T>::operator= (const T(&a_arr)[N]) {
  clear();
  for (const T& el : a_arr)
    push_back(el);
}

template<typename T>
void vector<T>::append(T element) {
  push_back(element);
}

template<typename T>
vector<T>& vector<T>::operator<<(T element) {
  push_back(element);
  return (*this);
};

template<typename T>
void vector<T>::push_back(T element) {
  if (m_size >= m_space) {
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
void vector<T>::insert(uint8_t index, T element) {
  T lastElement = m_arr[m_size];
  for (uint8_t i = m_size; i > index; i--)
    m_arr[i] = m_arr[i - 1];
  m_arr[index] = element;
  push_back(element);
}

template<typename T>
void vector<T>::remove(uint8_t index) {
  if (index >= m_size) return;

  for (uint8_t i = index; i < m_size - 1; i++)
    m_arr[i] = m_arr[i + 1];
  m_size--;

  if (m_size < m_space / 2) {
    T* newArr = new T[m_space / 2];
    for (uint8_t i = 0; i < m_space / 2; i++)
      newArr[i] = m_arr[i];
    delete[] m_arr;
    m_arr = newArr;
    m_space = m_space / 2;
  }
}

template<typename T>
void vector<T>::removeFirst(T element) {
  remove(indexOf(element));
}

template<typename T>
void vector<T>::removeLast(T element) {
  remove(lastIndexOf(element));
}

template<typename T>
void vector<T>::removeAll(T element) {
  uint8_t index = 0;

  while (index < m_size) {
    index = indexOf(element, index);
    remove(index);
  }
}

template<typename T>
void vector<T>::clear() {
  delete[] m_arr;
  m_size = 0;
  m_space = 2;
  m_arr = new T[m_space];
}

template<typename T>
bool vector<T>::contains(T element) const {
  for (uint64_t i = 0; i < m_size; i++)
    if (m_arr[i] == element) return true;

  return false;
}

template<typename T>
uint8_t vector<T>::indexOf(T element, uint8_t from) const {
  for (uint8_t i = from; i < m_size; i++)
    if (m_arr[i] == element) return i;
  return m_size;
}

template<typename T>
uint8_t vector<T>::lastIndexOf(T element) const {
  for (uint8_t i = m_size; i > 0; i--)
    if (m_arr[i] == element) return i;
  return 0;
}

template<typename T>
uint8_t vector<T>::lastIndexOf(T element, uint8_t from) const {
  for (uint8_t i = from; i > 0; i--)
    if (m_arr[i] == element) return i;
  return 0;
}

template<typename T>
T& vector<T>::at(uint8_t index) {
  if (index > m_size)
    return (*new T());

  return m_arr[index];
}

template<typename T>
const T& vector<T>::at(uint8_t index) const {
  if (index > m_size)
    return (*new T());

  return m_arr[index];
}

template<typename T>
T& vector<T>::operator[] (uint8_t index) {
  return at(index);
}

template<typename T>
const T& vector<T>::operator[] (uint8_t index) const {
  return at(index);
}