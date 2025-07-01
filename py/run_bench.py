from pathlib import Path
import pandas as pd
import subprocess
import sys

PROJECT_PATH = Path(__file__).parent.parent
BUILD_PATH = PROJECT_PATH / 'build'
RESULTS_PATH = PROJECT_PATH / 'results'

LOG_TOKEN = '[YABLYS]'


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
    if len(argv) != 2:
        print(f'Usage: {argv[0]} PROBLEM_FOLDER')
        return 0

    problem_folder = Path(argv[1])
    RESULTS_PATH.mkdir(parents=True, exist_ok=True)

    res = {}
    for solver_bin in BUILD_PATH.glob('test-*'):
        solver_name = solver_bin.stem.split('-')[1]

        res[f'{solver_name}_c'] = []
        res[f'{solver_name}_y'] = []
        res[f'{solver_name}_t'] = []

        print(f'=== Benchmarking {solver_name} ===')
        log_file = RESULTS_PATH / f'log-{solver_name}.log'
        cmd = f'{BUILD_PATH / solver_bin} {problem_folder} > {log_file}'
        # print(cmd)
        s, e, code = bash_call(cmd)

        with open(log_file, 'r') as f:
            for l in f.readlines():
                if l.startswith(LOG_TOKEN):
                    l = l.split()
                    res[f'{solver_name}_c'].append(int(l[1]))
                    res[f'{solver_name}_y'].append(float(l[2]))
                    res[f'{solver_name}_t'].append(float(l[4]))
    df = pd.DataFrame(res)
    print(df)
    df.to_csv(RESULTS_PATH / f'results.csv', index=False)


if __name__ == "__main__":
    main(sys.argv)
