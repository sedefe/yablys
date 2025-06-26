#include <cstdio>
#include <cstring>
#include <ctime>
#include <string>

struct Result {
    int status;
    double objective;
};

class AbstractWrapper {
   public:
    AbstractWrapper() {}

    virtual void Read(const std::string&) = 0;
    virtual Result Solve() = 0;

    virtual ~AbstractWrapper() {}
};
