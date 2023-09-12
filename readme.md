```bash
$ bazel run //src:main -- --benchmark_repetitions=10 --benchmark_out_format=json --benchmark_out=out.json
INFO: Analyzed target //src:main (0 packages loaded, 0 targets configured).
INFO: Found 1 target...
Target //src:main up-to-date:
  bazel-bin/src/main
INFO: Elapsed time: 0.056s, Critical Path: 0.00s
INFO: 1 process: 1 internal.
INFO: Build completed successfully, 1 total action
INFO: Running command line: bazel-bin/src/main '--benchmark_repetitions=10' '--benchmark_out_format=json' '--benchmark_out=out.json'
2023-09-12T16:23:57-04:00
Running /home/jtervay/.cache/bazel/_bazel_jtervay/b306691e93a3a2b900c867119b9bb87f/execroot/__main__/bazel-out/k8-fastbuild/bin/src/main
Run on (16 X 4700 MHz CPU s)
CPU Caches:
  L1 Data 48 KiB (x8)
  L1 Instruction 32 KiB (x8)
  L2 Unified 1280 KiB (x8)
  L3 Unified 18432 KiB (x1)
Load Average: 0.99, 0.65, 0.69
***WARNING*** CPU scaling is enabled, the benchmark real time measurements may be noisy and will incur extra overhead.
***WARNING*** Library was built as DEBUG. Timings may be affected.
------------------------------------------------------------
Benchmark                  Time             CPU   Iterations
------------------------------------------------------------
BM_flatbuf              2495 ns         2495 ns       289263
BM_flatbuf              2535 ns         2535 ns       289263
BM_flatbuf              2563 ns         2563 ns       289263
BM_flatbuf              2579 ns         2579 ns       289263
BM_flatbuf              2572 ns         2572 ns       289263
BM_flatbuf              2573 ns         2573 ns       289263
BM_flatbuf              2579 ns         2579 ns       289263
BM_flatbuf              2594 ns         2594 ns       289263
BM_flatbuf              2586 ns         2585 ns       289263
BM_flatbuf              2591 ns         2591 ns       289263
BM_flatbuf_mean         2567 ns         2566 ns           10
BM_flatbuf_median       2576 ns         2576 ns           10
BM_flatbuf_stddev       30.3 ns         30.3 ns           10
BM_flatbuf_cv           1.18 %          1.18 %            10
BM_flatbuf_max          2594 ns         2594 ns           10
BM_flatbuf_min          2495 ns         2495 ns           10
BM_proto2               1748 ns         1748 ns       400789
BM_proto2               1755 ns         1755 ns       400789
BM_proto2               1757 ns         1757 ns       400789
BM_proto2               1781 ns         1780 ns       400789
BM_proto2               1775 ns         1772 ns       400789
BM_proto2               1758 ns         1758 ns       400789
BM_proto2               1758 ns         1758 ns       400789
BM_proto2               1766 ns         1766 ns       400789
BM_proto2               1761 ns         1760 ns       400789
BM_proto2               1786 ns         1786 ns       400789
BM_proto2_mean          1765 ns         1764 ns           10
BM_proto2_median        1759 ns         1759 ns           10
BM_proto2_stddev        12.4 ns         12.0 ns           10
BM_proto2_cv            0.70 %          0.68 %            10
BM_proto2_max           1786 ns         1786 ns           10
BM_proto2_min           1748 ns         1748 ns           10
BM_proto3               1538 ns         1538 ns       461493
BM_proto3               1568 ns         1568 ns       461493
BM_proto3               1559 ns         1558 ns       461493
BM_proto3               1533 ns         1533 ns       461493
BM_proto3               1517 ns         1517 ns       461493
BM_proto3               1520 ns         1520 ns       461493
BM_proto3               1521 ns         1520 ns       461493
BM_proto3               1516 ns         1515 ns       461493
BM_proto3               1512 ns         1511 ns       461493
BM_proto3               1510 ns         1509 ns       461493
BM_proto3_mean          1529 ns         1529 ns           10
BM_proto3_median        1521 ns         1520 ns           10
BM_proto3_stddev        20.2 ns         20.1 ns           10
BM_proto3_cv            1.32 %          1.32 %            10
BM_proto3_max           1568 ns         1568 ns           10
BM_proto3_min           1510 ns         1509 ns           10
BM_upb                  1949 ns         1948 ns       357586
BM_upb                  1969 ns         1969 ns       357586
BM_upb                  2012 ns         2011 ns       357586
BM_upb                  2145 ns         2145 ns       357586
BM_upb                  2115 ns         2115 ns       357586
BM_upb                  2032 ns         2032 ns       357586
BM_upb                  2004 ns         2003 ns       357586
BM_upb                  2009 ns         2008 ns       357586
BM_upb                  1997 ns         1997 ns       357586
BM_upb                  2013 ns         2013 ns       357586
BM_upb_mean             2024 ns         2024 ns           10
BM_upb_median           2010 ns         2010 ns           10
BM_upb_stddev           60.9 ns         60.9 ns           10
BM_upb_cv               3.01 %          3.01 %            10
BM_upb_max              2145 ns         2145 ns           10
BM_upb_min              1949 ns         1948 ns           10

$ cat bazel-bin/src/main.runfiles/__main__/out.json
# ...
```


