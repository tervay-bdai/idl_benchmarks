```bash
$ bazel run //src:main -- --benchmark_repetitions=25 --benchmark_out_format=json --benchmark_out=out.json
# ...

$ cat bazel-bin/src/main.runfiles/__main__/out.json
# ...
```


