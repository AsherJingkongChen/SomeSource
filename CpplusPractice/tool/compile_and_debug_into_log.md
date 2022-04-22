### One Unix command (gcc, valgrind)

compile (-g debug, -W warnings)

-> debug

-> debug log + runtime log (temp)

-> concate 2 logs

-> remove runtime log (temp)

__And you get `log-test.log`__

```bash
g++ -std=c++17 -g -W test.cpp -o test && \
valgrind \
--leak-check=full \
--track-origins=yes \
./test > log_test.log \
2>&1
```
