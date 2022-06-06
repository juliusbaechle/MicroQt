#include "Synchronizer.h"
#include "EventLoop.h"
using namespace MicroQt;

int Synchronizer::exec() {
  m_exit = false;
  while (!m_exit)
    eventLoop.update();
  return m_exitCode;
}

void Synchronizer::exit(int a_exitCode) {
  eventLoop.enqueueEvent([=]() {
    m_exitCode = a_exitCode;
    m_exit = true;
  });
}