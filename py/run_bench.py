from collections import defaultdict
from pathlib import Path
import pandas as pd
import subprocess
import sys

PROJECT_PATH = Path(__file__).parent.parent
BUILD_PATH = PROJECT_PATH / 'build'
RESULTS_PATH = PROJECT_PATH / 'results'

LOG_TOKEN_V = '[YABLYS_VERSION]'
LOG_TOKEN_R = '[YABLYS_RESULT]'


def bash_call(cmd, timeout=0):
    stdout = ""
    stderr = ""
    returncode = 0x1488
    try:
        proc = subprocess.run(
            cmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        stdout = proc.stdout.decode().strip()
        stderr = proc.stderr.decode().strip()
        returncode = proc.returncode
    except Exception as e:
        print(e)
    return stdout, stderr, returncode


def main(argv):
    if len(argv) != 3:
        print(f'Usage: {argv[0]} PROBLEM_FOLDER TIMEOUT')
        return 0

    problem_folder = Path(argv[1])
    timeout = float(argv[2])
    RESULTS_PATH.mkdir(parents=True, exist_ok=True)

    res = defaultdict(list)
    for solver_bin in BUILD_PATH.glob('test-*'):
        print(f'=== Benchmarking {solver_bin.name} ===')
        log_file = RESULTS_PATH / f'log-{solver_bin.name}.log'
        cmd = f'{BUILD_PATH / solver_bin} {problem_folder} {timeout} > {log_file}'
        # print(cmd)
        s, e, code = bash_call(cmd)
        if e:
            print(e)

        with open(log_file, 'r') as f:
            for l in f.readlines():
                if l.startswith(LOG_TOKEN_V):
                    l = l.split()
                    solver_name = l[1]
                elif l.startswith(LOG_TOKEN_R):
                    l = l.split()
                    res[f'{solver_name}_m'].append(l[1])
                    res[f'{solver_name}_c'].append(int(l[2]))
                    res[f'{solver_name}_s'].append(int(l[3][1:-1]))
                    res[f'{solver_name}_p'].append(float(l[5]))
                    res[f'{solver_name}_d'].append(float(l[7]))
                    res[f'{solver_name}_t'].append(float(l[9]))
    df = pd.DataFrame(res)
    print(df)
    df.to_csv(RESULTS_PATH / f'results.csv', index=False)


if __name__ == "__main__":
    main(sys.argv)
