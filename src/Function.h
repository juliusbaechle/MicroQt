#pragma once

template<typename Result, typename ...Args>
struct abstract_function {
  virtual Result operator()(Args... args) = 0;
  virtual abstract_function *clone() const = 0;
  virtual ~abstract_function() = default;
};

template<typename Func, typename Result, typename ...Args>
class concrete_function : public abstract_function<Result, Args...> {
  Func m_func;

public:
  concrete_function(const Func &x)
    : m_func(x) {}

  Result operator()(Args... args) override {
    return m_func(args...);
  }

  concrete_function *clone() const override {
    return new concrete_function{ m_func };
  }
};


// Takes function declarations and converts them to function pointers
template<typename Func> struct func_filter { typedef Func type; };
template<typename Result, typename ...Args> struct func_filter<Result(Args...)> { typedef Result(*type)(Args...); };


template<typename signature>
class function;

template<typename Result, typename ...Args>
class function<Result(Args...)> {
public:
  function()
    : m_func(nullptr) {}

  template<typename Func> function(const Func &x)
    : m_func(new concrete_function<typename func_filter<Func>::type, Result, Args...>(x)) {}

  function(const function &rhs)
    : m_func(rhs.m_func ? rhs.m_func->clone() : nullptr) {}

  ~function() {
    delete m_func;
  }

  function &operator=(const function &rhs) {
    if ((&rhs != this) && (rhs.m_func)) {
      auto *temp = rhs.m_func->clone();
      delete m_func;
      m_func = temp;
    }
    return *this;
  }

  template<typename Func> function &operator=(const Func &x) {
    auto *temp = new concrete_function<typename func_filter<Func>::type, Result, Args...>(x);
    delete m_func;
    m_func = temp;
    return *this;
  }

  Result operator()(Args... args) {
    if (m_func)
      return (*m_func)(args...);
    else
      return Result();
  }

private:
  abstract_function<Result, Args...> *m_func;
};