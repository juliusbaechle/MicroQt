#pragma once

#include "Vector.h"
#include "Function.h"
#include "Callbacks.h"

template<typename ... Args>
class Signal {
public:
  void operator()(Args ... param);

  void connect(function<void(Args ...)> a_func);
  void disconnect(function<void(Args ...)> a_func);  

  template<typename Class>
  void connect(Class* obj, void(Class::* func)(Args ...));

  template<typename Class>
  void disconnect(Class* obj, void(Class::* func)(Args ...) = nullptr);

private:
  Vector<function<void(Args ...)>> m_callbacks;
  Vector<ObjCallback<Args ...>> m_objCallbacks;
};



template<typename ... Args>
void Signal<Args ...>::operator()(Args ... params) {
  for (int i = 0; i < m_callbacks.size(); i++)
    m_callbacks[i](params ...);
  for (int i = 0; i < m_objCallbacks.size(); i++)
    m_objCallbacks[i](params ...);
}

template<typename ... Args>
void Signal<Args ...>::connect(function<void(Args ...)> a_func) {
  m_callbacks.append(a_func);
}

template<typename ... Args>
void Signal<Args ...>::disconnect(function<void(Args ...)> a_func) {
  m_callbacks.removeAll(a_func);
}

template<typename ... Args> template<typename Class>
void Signal<Args ...>::connect(Class* a_obj, void(Class::* a_func)(Args ...)) {
  ObjCallback<Args ...> objCallback (a_obj, a_func);
  if (!m_objCallbacks.contains(objCallback))
    m_objCallbacks << objCallback;
}

template<typename ... Args> template<typename Class>
void Signal<Args ...>::disconnect(Class* a_obj, void(Class::* a_func)(Args ...)) {
  ObjCallback<Args ...> objCallback(a_obj, a_func);
  m_objCallbacks.removeAll(objCallback);
}
