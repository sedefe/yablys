#include <cstdio>
#include <cstring>
#include <ctime>
#include <string>

#include "file_types.h"
#include "return_codes.h"

struct Result {
    Result(int s_, double o_) {
        status = s_;
        objective = o_;
    }

    int status;
    ReturnCode rc;
    double objective;
};

class AbstractWrapper {
   public:
    AbstractWrapper() {}

    virtual std::string GetVersion() const = 0;
    virtual void Read(const std::string&, FileType ft) = 0;
    virtual Result Solve() = 0;

    virtual ReturnCode GetCode(int status) = 0;

    virtual ~AbstractWrapper() {}
};
