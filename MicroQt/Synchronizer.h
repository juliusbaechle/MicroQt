#pragma once

namespace MicroQt {
  class Synchronizer {
  public:
    int exec();
    void exit(int a_exitCode);
    bool isRunning() { return !m_exit; }

  private:
    bool m_exit = true;
    int m_exitCode = 0;
  };
}