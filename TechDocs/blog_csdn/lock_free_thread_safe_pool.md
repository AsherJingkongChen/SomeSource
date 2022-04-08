## Lock-free Thread-safe thread pool (C++ way)

#### 版权声明：本文为CSDN博主「亘井」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
#### 原文链接：https://blog.csdn.net/xhjcehust/article/details/45844901

> LICENSE: CC 4.0 BY-SA
> 
> ORIGIN AUTHOR: [亘井](https://blog.csdn.net/xhjcehust)
> 
> ORIGIN ARTICLE: [高效线程池之无锁化实现(Linux C)](https://blog.csdn.net/xhjcehust/article/details/45844901)

## ZH-tw 摘要

### 1.常見線程池實現原理

多線程 對上 一任務序列

Multi-thread sharing one task queue

!['1-1'](https://img-blog.csdn.net/20150519150636820?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQveGhqY2VodXN0/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/Center)

主線程將任務放進工作隊列，工作者線程從工作隊列中取出任務執行。

共享工作隊列的操作需在 __互斥量的保護 (std::mutex)__ 下安全進行。

#
### 2.無鎖化線程池實現原理

每個線程處理自己的任務序列

Each thread has its own task queue

!['1-2'](https://img-blog.csdn.net/20150519150634289?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQveGhqY2VodXN0/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/Center)

「為解決無鎖化的問題，需要避免共享資源的競爭」

目標是lock-free的設計, __拋棄阻塞設計 (std::mutex)__

主線程放入工作和工作線程取出任務的競爭問題，可以採取 __環形隊列 (ring-buffer)__ 的方式避免。

!['1-3'](https://hackpad-attachments.s3.amazonaws.com/embedded2016.hackpad.com_VJmq0R0ILi6_p.537916_1459270052852_undefined)

「一個消費者對上一個生產者，沒有競爭，[稍微延伸 Google oboe FIFOBuffer](https://github.com/google/oboe/discussions/1402)」

#
### 3.相關資源

[並行程式設計 Lock-Free Programming](https://hackmd.io/@sysprog/concurrency-lockfree)

[亘井 Github Lock-Free Thread Pool](https://github.com/xhjcehust/LFTPool)

[kfifo csdn blog](https://blog.csdn.net/linyt/article/details/53355355)
