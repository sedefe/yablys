from pathlib import Path
import sys
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
from enum import Enum

PROJECT_PATH = Path(__file__).parent.parent
BUILD_PATH = PROJECT_PATH / 'build'
RESULTS_PATH = PROJECT_PATH / 'results'


class MilpStatus(Enum):
    OPT = 0
    INF = 1
    UNB = 2
    INF_UNB = 3
    TO = 4
    HZ = -1


def plot(df: pd.DataFrame):
    def is_time(x): return x.endswith('_t')
    def get_name(x): return x[:-2]
    solvers = sorted(set(map(get_name, filter(is_time, df.columns))))

    sdf = df[filter(is_time, df.columns)]
    t_min = sdf.to_numpy().min()
    t_max = sdf.to_numpy().max()

    xs = np.logspace(np.log10(t_min), np.log10(t_max), num=101)
    plt.figure(figsize=(8, 4))
    m = 10
    for solver in solvers:
        ts = sdf[f'{solver}_t'].to_numpy()
        ys = np.zeros_like(xs)
        for i, x in enumerate(xs):
            ys[i] = np.mean(ts < x) * 100
        plt.plot(xs, ys, label=solver)

    plt.xscale('log')
    plt.xlabel('Time, ms')
    plt.ylabel('% problems solved')
    plt.legend(loc='lower right')
    plt.tight_layout()
    plt.savefig(RESULTS_PATH / f'perf-profile.svg')
    plt.show()


def main(argv):
    if len(argv) != 2:
        print(f'Usage: {argv[0]} CSV_FILE')
        return 0
    file = Path(argv[1])
    RESULTS_PATH.mkdir(parents=True, exist_ok=True)

    df = pd.read_csv(file, index_col=False)
    print(df)
    plot(df)


if __name__ == "__main__":
    main(sys.argv)
