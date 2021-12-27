#pragma once
#include <QThread>

class AsciiPlayerThread : public QThread
{
public:
    AsciiPlayerThread();
    void run();
};
