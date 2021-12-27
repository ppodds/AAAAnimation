#pragma once
#include <QThread>

class AsciiPlayerThread : public QThread
{
public:
    AsciiPlayerThread();
    AsciiPlayerThread(std::string file_path);
    void run();
private:
    std::string file_path;
};
