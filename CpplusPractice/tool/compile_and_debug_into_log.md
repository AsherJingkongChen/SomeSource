### One Unix command (gcc, valgrind)

__compile__ (-g debug, -W warnings)

__-> debug__

__-> debug log + runtime log (temp)__

__-> concate 2 logs__

__-> remove runtime log (temp)__

#### And You get log-test.log

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
