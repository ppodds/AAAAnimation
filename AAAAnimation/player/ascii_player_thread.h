#pragma once
#include <QThread>

class AsciiPlayerThread : public QThread
{
    Q_OBJECT
public:
    AsciiPlayerThread();
    ~AsciiPlayerThread();
    AsciiPlayerThread(std::string file_path);
    void run();
public slots:
    void setPosition(qint64 position);
private:
    std::string file_path;
    qint64 position;
};
