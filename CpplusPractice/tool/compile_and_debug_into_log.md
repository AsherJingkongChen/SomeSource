### One Unix command (gcc, valgrind)

compile (-g debug, -W warnings)

-> debug (--leak-check=full leaksum, --track-origins=yes tracker)

-> stderr redirect to stdout

__And you get `log-test.log`__

```bash
g++ -std=c++17 -g -W test.cpp -o test && \
valgrind \
--leak-check=full \
--track-origins=yes \
./test > log_test.log \
2>&1 && \
cat test.cpp >> log_test.log
```

__Complete version__

```bash
export CPP_SRC_CODE=test && \
g++ -std=c++17 -g -c -W ${CPP_SRC_CODE}.cpp -o ${CPP_SRC_CODE}.o && \
g++ -std=c++17 -g -W ${CPP_SRC_CODE}.cpp -o ${CPP_SRC_CODE} && \
valgrind \
--leak-check=full \
--track-origins=yes \
./${CPP_SRC_CODE} > log_${CPP_SRC_CODE}.log \
2>&1 && \
cat ${CPP_SRC_CODE}.cpp >> log_${CPP_SRC_CODE}.log && \
objdump -C -D -S -l ${CPP_SRC_CODE}.o > log_asm.log
```
