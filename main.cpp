#include "common.h"
#include "get_wrapper.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s PATH\n", argv[0]);
        return 0;
    }
    std::string models_path = argv[1];

    SOLVER_CLASS solver;
    printf("[YABLYS_VERSION] %s\n", solver.GetVersion().c_str());

    for (const auto& entry : std::filesystem::directory_iterator(models_path)) {
        auto extension = entry.path().extension();
        auto ft = extension2FileType(extension);
        if (ft != FileType::kUnknown) {
            solver.Read(entry.path(), ft);
            auto t = clock();
            auto res = solver.Solve();
            t = clock() - t;

            printf("[YABLYS_RESULT] %d %10.2f | %7.3f ms\n", res.status, res.objective,
                   1e3 * t / CLOCKS_PER_SEC);
        }
    }

    return 0;
}
