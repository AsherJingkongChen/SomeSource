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
--log-file=log_test.log \
--leak-check=full \
--track-origins=yes \
./test > __xLOG_TEMP__ && \
echo '' >> log_test.log && \
cat __xLOG_TEMP__ >> log_test.log && \
rm -f __xLOG_TEMP__
```
