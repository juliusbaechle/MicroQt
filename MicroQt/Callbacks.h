#pragma once

template<typename ... Args>
class Callback {
public:
  virtual void operator() (Args ... params) const = 0;
};

template<typename ... Args>
class ObjCallback : public Callback<Args ...> {
private:
  class Callable {};

public:
  ObjCallback() {}

  template<typename Class>
  ObjCallback(Class* a_obj, void(Class::*a_func)(Args ...)) {
    m_obj = (Callable*)a_obj;
    m_func = (void(Callable::*)(Args ...)) a_func;
  }

  bool operator==(const ObjCallback& a_callback) const {
    if (m_obj != a_callback.m_obj) return false;
    if (m_func != a_callback.m_func && a_callback.m_func != nullptr) return false;
    return true;
  }

  void operator()(Args ... params) const override {
    if (m_obj && m_func)
      (m_obj->*m_func)(params ...);
  }

private:
  Callable* m_obj;
  void(Callable::*m_func)(Args ...);
};
