#include <Highs.h>

#include "abstract_wrapper.h"

class HighsWrapper : public AbstractWrapper {
   public:
    HighsWrapper() { highs.setOptionValue("parallel", "off"); }

    std::string GetVersion() const { return std::string("HiGHS-") + highsVersion(); }

    void Read(const std::string &model_path, FileType ft) { highs.readModel(model_path); }
    Result Solve() {
        highs.run();

        return Result{int(highs.getModelStatus()), highs.getInfo().objective_function_value};
    }

    ~HighsWrapper() {}

   private:
    Highs highs;
};
