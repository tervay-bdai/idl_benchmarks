```bash
$ bazel run //src:main -- --benchmark_repetitions=10 --benchmark_display_aggregates_only=true --benchmark_out_format=json --benchmark_out=out.json
$ cat bazel-bin/src/main.runfiles/__main__/out.json
# ...
```
