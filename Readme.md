# Yet Another Benchmarking LibrarY for Solvers
## Build
`./build.sh OPTIONS`

Options:
```
    -C : use CBC
    -S : use SCIP
    -H : use HiGHS
    -O : use COPT
```
## Run
`python py/run_bench.py <PATH_TO_MODEL_DIR>`
## Performance profiling
`python py/make_report.py <PATH_TO_RESULTING_CSV>`
