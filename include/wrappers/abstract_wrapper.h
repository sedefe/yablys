#include <cstdio>
#include <cstring>
#include <ctime>
#include <string>

#include "file_types.h"
#include "return_codes.h"

struct Result {
    Result(int s_, double p_, double d_) {
        status = s_;
        primal_bound = p_;
        dual_bound = d_;
    }

    int status;
    ReturnCode rc;
    double primal_bound;
    double dual_bound;
};

class AbstractWrapper {
   public:
    AbstractWrapper() {}

    virtual std::string GetVersion() const = 0;
    virtual void Read(const std::string&, FileType ft) = 0;
    virtual Result Solve(double timeout) = 0;

    virtual ReturnCode GetCode(int status) = 0;

    virtual ~AbstractWrapper() {}
};
