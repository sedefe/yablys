#include <Highs.h>

#include "abstract_wrapper.h"

class HighsWrapper : public AbstractWrapper {
   public:
    HighsWrapper() { highs.setOptionValue("parallel", "off"); }

    void Read(const std::string &model_path) { highs.readModel(model_path); }
    Result Solve() {
        highs.run();

        return Result{int(highs.getModelStatus()), highs.getInfo().objective_function_value};
    }

    ~HighsWrapper() {}

   private:
    Highs highs;
};
