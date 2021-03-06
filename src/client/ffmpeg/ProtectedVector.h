#ifndef MICROMACHINES_PROTECTEDVECTOR_H
#define MICROMACHINES_PROTECTEDVECTOR_H

#include "../Window.h"
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>


class ProtectedVector {
private:
    std::vector<char> actualFrame;
    std::mutex m;
    std::condition_variable cv_pop;
    bool _shutdown;

public:
    ProtectedVector();

    void push(std::vector<char>& data);

    bool pop(std::vector<char> &data);

    bool isClose();

    void open();

    void close();

    ~ProtectedVector();
};


#endif
