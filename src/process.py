import json
import os
import sys
from pprint import pprint
from typing import TypedDict, List
from collections import defaultdict
import csv


class CSVRow(TypedDict):
    protocol: str
    num_cycles: int
    min: float
    max: float
    q1: float
    q3: float
    mean: float
    median: float
    stddev: float
    cv: float


def main():
    relative_path = (
        "bazel-bin/src/main.runfiles/__main__/out.json"
        if len(sys.argv) == 0
        else sys.argv[1]
    )

    # this is ugly because i want to use an output file from another binary without
    # having to tell bazel about it, and i don't know how right now and am impatient
    json_path = os.path.join(
        os.environ["BUILD_WORKSPACE_DIRECTORY"],  # set by Bazel
        relative_path,
    )

    with open(json_path, "r") as f:
        data = json.load(f)

    stats_builder = defaultdict(CSVRow)

    for benchmark in data["benchmarks"]:
        if benchmark["run_type"] != "aggregate":
            continue

        split_name = benchmark["name"].split("_")
        stat = split_name[-1]
        test_name = "_".join(split_name[1:-1])
        protocol, num_cycles = test_name.split("/")

        stats_builder[(protocol, int(num_cycles))]["protocol"] = protocol
        stats_builder[(protocol, int(num_cycles))]["num_cycles"] = int(num_cycles)
        stats_builder[(protocol, int(num_cycles))][stat] = benchmark["real_time"]

    with open("out.csv", "w+", newline="") as f:
        writer = csv.DictWriter(f, fieldnames=list((stats_builder.values()))[0].keys())

        # Write the header row
        writer.writeheader()

        # Write the data rows
        for row in sorted(stats_builder.values(), key=lambda d: d["num_cycles"]):
            writer.writerow(row)


if __name__ == "__main__":
    main()
