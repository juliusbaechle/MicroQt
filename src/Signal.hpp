template<typename ... Args>
void Signal<Args ...>::operator()(Args ... a_params) {
  for (int i = 0; i < m_callbacks.size(); i++)
    m_callbacks[i](a_params ...);
}

template<typename ... Args>
uint32_t Signal<Args ...>::connect(function<void(Args ...)> a_func) {
  if (m_connectionIds.size() == UINT8_MAX) {
    Serial.println("maximum connections reached");
    return 0;
  }

  uint32_t connectionId = m_lastConnectionId++;
  while (m_connectionIds.contains(connectionId)) connectionId++;

  m_callbacks.append(a_func);
  m_connectionIds.append(connectionId);
  return connectionId;
}

template<typename ... Args>
void Signal<Args ...>::disconnect(uint32_t a_connectionId) {
  uint8_t index = m_connectionIds.indexOf(a_connectionId);
  m_connectionIds.removeAt(index);
  m_callbacks.removeAt(index);
}