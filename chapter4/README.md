## Interactive GDB session

```shell 
(gdb) # commands used
(gdb) break exit
Download failed: Invalid argument.  Continuing without source file ./stdlib/./stdlib/exit.c.
Note: breakpoint 2 also set at pc 0x7ffff78486a0.
Breakpoint 3 at 0x7ffff78486a0: file ./stdlib/exit.c, line 147.
(gdb) run
The program being debugged has been started already.
Start it from the beginning? (y or n) y
Starting program: /home/caiosa/cplusplus/chapter4/cmake-build-debug/mem_pool_example
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/usr/lib/x86_64-linux-gnu/libthread_db.so.1".
Download failed: Invalid argument.  Continuing without source file ./stdlib/./stdlib/exit.c.
prim elem:0 allocated at:0x555555573020
struct elem:0,1,2 allocated at:0x555555573690
deallocating prim elem:0 from:0x555555573020
deallocating struct elem:0,1,2 from:0x555555573690
prim elem:1 allocated at:0x555555573030
struct elem:1,2,3 allocated at:0x5555555736a0
prim elem:2 allocated at:0x555555573040
struct elem:2,3,4 allocated at:0x5555555736b0
prim elem:3 allocated at:0x555555573050
struct elem:3,4,5 allocated at:0x5555555736c0
prim elem:4 allocated at:0x555555573060
struct elem:4,5,6 allocated at:0x5555555736d0
prim elem:5 allocated at:0x555555573070
struct elem:5,6,7 allocated at:0x5555555736e0
deallocating prim elem:5 from:0x555555573070
deallocating struct elem:5,6,7 from:0x5555555736e0
prim elem:6 allocated at:0x555555573080
struct elem:6,7,8 allocated at:0x5555555736f0
prim elem:7 allocated at:0x555555573090
struct elem:7,8,9 allocated at:0x555555573700
prim elem:8 allocated at:0x5555555730a0
struct elem:8,9,10 allocated at:0x555555573710
prim elem:9 allocated at:0x5555555730b0
struct elem:9,10,11 allocated at:0x555555573720
prim elem:10 allocated at:0x5555555730c0
struct elem:10,11,12 allocated at:0x555555573730
deallocating prim elem:10 from:0x5555555730c0
deallocating struct elem:10,11,12 from:0x555555573730
prim elem:11 allocated at:0x5555555730d0
struct elem:11,12,13 allocated at:0x555555573740
prim elem:12 allocated at:0x5555555730e0
struct elem:12,13,14 allocated at:0x555555573750
prim elem:13 allocated at:0x5555555730f0
struct elem:13,14,15 allocated at:0x555555573760
prim elem:14 allocated at:0x555555573100
struct elem:14,15,16 allocated at:0x555555573770
prim elem:15 allocated at:0x555555573110
struct elem:15,16,17 allocated at:0x555555573780
deallocating prim elem:15 from:0x555555573110
deallocating struct elem:15,16,17 from:0x555555573780
prim elem:16 allocated at:0x555555573120
struct elem:16,17,18 allocated at:0x555555573790
prim elem:17 allocated at:0x555555573130
struct elem:17,18,19 allocated at:0x5555555737a0
prim elem:18 allocated at:0x555555573140
struct elem:18,19,20 allocated at:0x5555555737b0
prim elem:19 allocated at:0x555555573150
struct elem:19,20,21 allocated at:0x5555555737c0
prim elem:20 allocated at:0x555555573160
struct elem:20,21,22 allocated at:0x5555555737d0
deallocating prim elem:20 from:0x555555573160
deallocating struct elem:20,21,22 from:0x5555555737d0
prim elem:21 allocated at:0x555555573170
struct elem:21,22,23 allocated at:0x5555555737e0
prim elem:22 allocated at:0x555555573180
struct elem:22,23,24 allocated at:0x5555555737f0
prim elem:23 allocated at:0x555555573190
struct elem:23,24,25 allocated at:0x555555573800
prim elem:24 allocated at:0x5555555731a0
struct elem:24,25,26 allocated at:0x555555573810
prim elem:25 allocated at:0x5555555731b0
struct elem:25,26,27 allocated at:0x555555573820
deallocating prim elem:25 from:0x5555555731b0
deallocating struct elem:25,26,27 from:0x555555573820
prim elem:26 allocated at:0x5555555731c0
struct elem:26,27,28 allocated at:0x555555573830
prim elem:27 allocated at:0x5555555731d0
struct elem:27,28,29 allocated at:0x555555573840
prim elem:28 allocated at:0x5555555731e0
struct elem:28,29,30 allocated at:0x555555573850
prim elem:29 allocated at:0x5555555731f0
struct elem:29,30,31 allocated at:0x555555573860
prim elem:30 allocated at:0x555555573200
struct elem:30,31,32 allocated at:0x555555573870
deallocating prim elem:30 from:0x555555573200
deallocating struct elem:30,31,32 from:0x555555573870
prim elem:31 allocated at:0x555555573210
struct elem:31,32,33 allocated at:0x555555573880
prim elem:32 allocated at:0x555555573220
struct elem:32,33,34 allocated at:0x555555573890
prim elem:33 allocated at:0x555555573230
struct elem:33,34,35 allocated at:0x5555555738a0
prim elem:34 allocated at:0x555555573240
struct elem:34,35,36 allocated at:0x5555555738b0
prim elem:35 allocated at:0x555555573250
struct elem:35,36,37 allocated at:0x5555555738c0
deallocating prim elem:35 from:0x555555573250
deallocating struct elem:35,36,37 from:0x5555555738c0
prim elem:36 allocated at:0x555555573260
struct elem:36,37,38 allocated at:0x5555555738d0
prim elem:37 allocated at:0x555555573270
struct elem:37,38,39 allocated at:0x5555555738e0
prim elem:38 allocated at:0x555555573280
struct elem:38,39,40 allocated at:0x5555555738f0
prim elem:39 allocated at:0x555555573290
struct elem:39,40,41 allocated at:0x555555573900
prim elem:40 allocated at:0x5555555732a0
struct elem:40,41,42 allocated at:0x555555573910
deallocating prim elem:40 from:0x5555555732a0
deallocating struct elem:40,41,42 from:0x555555573910
prim elem:41 allocated at:0x5555555732b0
struct elem:41,42,43 allocated at:0x555555573920
prim elem:42 allocated at:0x5555555732c0
struct elem:42,43,44 allocated at:0x555555573930
prim elem:43 allocated at:0x5555555732d0
struct elem:43,44,45 allocated at:0x555555573940
prim elem:44 allocated at:0x5555555732e0
struct elem:44,45,46 allocated at:0x555555573950
prim elem:45 allocated at:0x5555555732f0
struct elem:45,46,47 allocated at:0x555555573960
deallocating prim elem:45 from:0x5555555732f0
deallocating struct elem:45,46,47 from:0x555555573960
prim elem:46 allocated at:0x555555573300
struct elem:46,47,48 allocated at:0x555555573970
prim elem:47 allocated at:0x555555573310
struct elem:47,48,49 allocated at:0x555555573980
prim elem:48 allocated at:0x555555573320
struct elem:48,49,50 allocated at:0x555555573990
prim elem:49 allocated at:0x555555573330
struct elem:49,50,51 allocated at:0x5555555739a0
MEMORY LAYOUT
0x555555573330
0x555555573320
0x555555573310
0x555555573300
0x5555555732f0
0x5555555732e0
0x5555555732d0
0x5555555732c0
0x5555555732b0
0x5555555732a0
0x555555573290
0x555555573280
0x555555573270
0x555555573260
0x555555573250
0x555555573240
0x555555573230
0x555555573220
0x555555573210
0x555555573200
0x5555555731f0
0x5555555731e0
0x5555555731d0
0x5555555731c0
0x5555555731b0
0x5555555731a0
0x555555573190
0x555555573180
0x555555573170
0x555555573160
0x555555573150
0x555555573140
0x555555573130
0x555555573120
0x555555573110
0x555555573100
0x5555555730f0
0x5555555730e0
0x5555555730d0
0x5555555730c0
0x5555555730b0
0x5555555730a0
0x555555573090
0x555555573080
0x555555573070
0x555555573060
0x555555573050
0x555555573040
0x555555573030
0x555555573020
ASSERT : Element being deallocated does not belong to this Memory pool.
Download failed: Invalid argument.  Continuing without source file ./stdlib/./stdlib/exit.c.

Breakpoint 2, __GI_exit (status=1) at ./stdlib/exit.c:147
⚠️ warning: 147 ./stdlib/exit.c: No such file or directory
(gdb) backtrace
#0  __GI_exit (status=1) at ./stdlib/exit.c:147
#1  0x0000555555556f51 in ASSERT (cond=false, msg="Element being deallocated does not belong to this Memory pool.")
    at /home/caiosa/cplusplus/chapter4/macros.h:14
#2  0x000055555555704f in Common::MemPool<double>::deallocate (this=0x7fffffffdd90, elem=0x5555555739c0)
    at /home/caiosa/cplusplus/chapter4/mem_pool.h:45
#3  0x00005555555568aa in main () at /home/caiosa/cplusplus/chapter4/mem_pool_example.cpp:54
(gdb) frame 2
#2  0x000055555555704f in Common::MemPool<double>::deallocate (this=0x7fffffffdd90, elem=0x5555555739c0)
    at /home/caiosa/cplusplus/chapter4/mem_pool.h:45
45                              ASSERT(elem_index >= 0 && static_cast<size_t>(elem_index) < store_.size(), "Element being deallocated does not belong to this Memory pool.");
(gdb) print elem
$4 = (const double *) 0x5555555739c0
(gdb) print elem_index
$5 = 154
(gdb) print &store_[0]
$6 = (Common::MemPool<double>::ObjectBlock *) 0x555555573020
```

List of commands used:
```shell
break exit # tells the debugger to stop whenever an exit is triggered
run # run the program
backtrace # open what happened
frame 2 # select the part I am interested
print elem # find its exact value
print &stack_[0] # exact value
print elem_index # shows me why it violated the logic
```


