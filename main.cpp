#include <dirent.h>

#include "get_wrapper.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s PATH\n", argv[0]);
        return 0;
    }
    std::string models_path = argv[1];

    SOLVER_CLASS solver;

    DIR *pDir;
    struct dirent *ptrFile;
    if (!(pDir = opendir(models_path.c_str()))) {
        fprintf(stderr, "Err model folder %s\n", models_path.c_str());
        exit(1);
    }
    while ((ptrFile = readdir(pDir)) != nullptr) {
        if (strcmp(ptrFile->d_name, ".") != 0 && strcmp(ptrFile->d_name, "..") != 0) {
            auto model_path = models_path + "/" + ptrFile->d_name;
            auto str = model_path.c_str();
            if (strlen(str) > 3 && !strcmp(str + strlen(str) - 3, ".lp")) {
                printf("%s\n", model_path.c_str());
            } else {
                continue;
            }

            solver.Read(model_path);
            auto t = clock();
            auto res = solver.Solve();
            t = clock() - t;

            printf("FF %d %10.2f | %7.3f ms\n", res.status, res.objective,
                   1e3 * t / CLOCKS_PER_SEC);
        }
    }

    return 0;
}
