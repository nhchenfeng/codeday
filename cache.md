## CPU体系结构-Cache

### cache的相关术语  

1. cacheline  
    cacheline是cache的最小操作力度，当前的cpu体系中，多为64bytes的data，但  
    cacheline本身还包括了valid，dirty，NS等bit位.  

2. set  
    set中包括多个cacheline，N-Way的cache，则包含了N个cacheline  

3. way  
    如上，一个set中cacheline的个数

4. block  
    block这个概念现在不常提了，一般可以默认block和cacheline是一件事情，如果  
    非要说不同，可以认为block是cacheline中除了valid，dirty, ns位意外的字节，具体  
    的data数据。

###  cache的映射与寻址  
1. 映射方式  
  &emsp;&emsp;cache的组成方式，有直接映射，组相连映射，全相连映射。 分别表示一个  
  地址(物理地址)。对应cache中存放位置的映射方式。  

&emsp;&emsp;一张图看懂cache映射方式  
![](https://ws2.sinaimg.cn/large/006tKfTcgy1fqmywaqo6yj30es0fnacs.jpg)  

2. cache寻址  

![](https://ws2.sinaimg.cn/large/006tKfTcgy1fqmzb73tuoj30j30ct76c.jpg)
![](https://ws2.sinaimg.cn/large/006tKfTcgy1fqmzbfe4t6j30ix07vgm4.jpg)  

###  cache的策略与地址属性     
1. Write allocation (WA)  
  &emsp;&emsp;如果这个写操作，发生了了cachemiss，那表示这写之前，会有一个cacheline的fill过程，即使写一个byte，也会把这一个byte所在的64bytes（cacheline-size）全部load到cacheline中。  
2. Read allocation (RA)   
  &emsp;&emsp; 同WA，当发生了cachemiss时，同理。  
3. Write-back (WB)
  &emsp;&emsp; 写操作只操作cache，并把对应的cacheline标记为dirty，当发生了cache替换策略时，或者强制执行了cacheline的操作。才会update到memory（DDR）中。
4. Write-through (WT)
  &emsp;&emsp; 同时写到了cache和memory中，但不会标记cacline为dirty，因为本来也不是dirty，cache和memory中的数据是一样的。


###  cache指令与PoU PoC  
1. PoU（Point of unification)   
  &emsp;&emsp; cache的统一性，一般是从cpu的维度，即cpu间看到的cache一致性。  

2. PoC (Point of coherency)  
  &emsp;&emsp; cache的一致性，这个是大一统，即从SoC的较多，多个master之间看到的一致性，一般就是到memory层了，比如cpu和dma看到的一致性。  

3. cache指令  

| DC   | CISW    | Clean and invalidate by Set/Way                              |
| ---- | ------- | ------------------------------------------------------------ |
|      | CIVAC   | Clean and Invalidate by Virtual Address to Point of Coherency |
|      | CSW     | Clean by Set/Way                                             |
|      | CVAC    | Clean by Virtual Address to Point of Coherency               |
|      | CVAU    | Clean by Virtual Address to Point of Unification             |
|      | ISW     | Invalidate by Set/Way                                        |
|      | IVAC    | Invalidate by Virtual Address, to Point of Coherency         |
|      | ZVA     | Cache zero by Virtual Address                                |
| IC   | IALLUIS | Invalidate all, to Point of Unification, Inner Sharable      |
|      | IALLU   | Invalidate all, to Point of Unification, Inner Shareable     |
|      | IVAU    | Invalidate by Virtual Address to Point of Unification        |

&emsp;&emsp; 由上可见，只有dache有PoC/PoU的概念，ICACHE不涉及，不需要与其他master保持指令一致性。  

&emsp;&emsp; D-cache的invalid和clean一般有DC IVAC IVAU从PoC和PoU两个角度。  
当然还包括了ISW/CISW通过set way的方式。  
&emsp;&emsp; 但是需要注意的是这样的set/way的操作方式，没有从PoC的角度，所以一般涉及到同master的一致性时，需要每个cpu都调用。  

### 内存属性与指令序列

1. Normal Memory 

​       Normal-memory的性能最高，这没用明确的数据依赖的前提下，可以乱序，重组。

​       可以产生分支预测，cache-line-fill等操作。

2. Device Memory

   Device属性，一般用于产生side-effect效应的地址。比如读取timer（寄存器），写contoller触发一个中断等场景

   1. Device-nGnRnE与ARMV7的strong-order类似

   2. Device-nGnRE

   3. Device-nGRE

   4. Device-GRE

      ​

3. Gathering or non Gathering (G or nG)

   是否可以合并，用于告诉处理器是否可以将多个access合并成一个bus-transaction. 如果是nG的话，每次core交给总线的数据长度根code中的一致，如果是G（Gathering）的话，例如可以将多个byte单字节的操作合并成一个word操作。另外一个是repeat，当某条load/store指令在pipeline的access memory阶段，发生cache miss(对于non-cacheable的memory就直接跳过，不过对于device memory一般都是non-cacheable的)后，需要将access memory请求发到总线上(例如AXI总线)，通过AXI总线访问device memory，这个通过总线访问memory的过程被称为一次transaction. 为了优化性能考虑，在core内，会引入一个Buffer, 当发生一个access memory请求后，会将这个请求信息丢到Buffer中，若某条指令和上一条指令共享同一个cache line或者是访问同一个地址,那么，该条指令便不会再向总线发送transaction了，它share上一条指令 读到buffer中的结果。这个share的过程称为gathering. 读到buffer中的数据，如果是cacheable的，会在某个时间内腾到cache中。

4. Re-ordering (R or nR)

   eordering也是针对device memory的transaction, that is, 某个device memory的连续access的transaction或者device memory之间的连续access的transaction. 对某个device memory的一次transaction 必须等到上一次device memory的transaction结束后（上一次load或者 write的ack发生后）才可以进行，这叫non-reordering. 若这些transaction可以乱序,不需要等待上一次access的ack就可以进行transaction，这种方式叫reordering

5. Early Write Acknowledgement (E or nE)

   当对某个Device memory进行write时，需要ACK,下一个对device memory进行access的transaction才能进行。为了性能优化的考虑，device会提供一个类似与寄存器的程序员不可见的buffer,这样当CPU通过总线向device memory写数据的时候，直接写到buffer里就可以了。这样buffer就可以向cpu返回一个ACK,表示写successfully.至于何时buffer将数据真正腾到device memory就看device内部的协议了，一般是DMC（DDR CONTROLLER）这边的操作。

6. Barriers 屏障

   ARM体系结构提供了屏障的指令，主要用来保证执行的顺序和完成的顺序。

   1. ISB (Instruction Synchronization Barrier)

      指令同步屏障，一般保证指令的fetch顺序（官方说的是fetch，我理解就是执行顺序），如检查MMU的配置，写系统寄存器。

   2. DMB(Data Memory Barrier)

      阻止数据的re-order，但是指令的prefetch不阻止

      ```
      LDR x0, [x1] // Must be seen by the memory system before the STR below. 
      DMB ISHLD
      ADD x2, #1 // May be executed before or after the memory system sees 
      LDR.
      STR x3, [x4] // Must be seen by the memory system after the LDR above.

      上面 LOAD X1地址内容到X0
      下面 STORE X3到X4的地址
      保证了数据的存储顺序
      ```

      ```
      DC CSW, x5 // Data clean by Set/way
      LDR x0,
      [x1] // Effect of data cache clean might not be seen by this instruction
      DMB ISH
      LDR x2, [x3] // Effect of data cache clean will be seen by this instruction

      刷cache
      DMB 保证LDR X2,[X3]会这刷cache完成

      ```

      ​

   3. DSB(Data Synchronization Barrier)

      DSB可以理解为更严格的DMB，除了存储屏障意外，还阻止了指令的prefetch

      尤其这core同步的时候比较有用，比如SMP里边，通知core启动之前，需要刷新cache，刷新tlb等操作

      然后SEV(send event)，顺便说下,WFE和WFI均进入低功耗模式，均可以被irq唤醒，WFE还可以被任何core的SEV唤醒，类似spinlock的实现。Core1访问资源，acquire lock，获得资源，Core2访问资源，此时资源不空闲，执行WFE指令，让core进入low-power state，Core1释放资源，release lock，释放资源，同时执行SEV指令，唤醒Core2。这里SEV可以同时唤醒多个core，即所有core有相同的几率得到spinlock。Core2得到获得资源。以前没有获得资源会loop busy，现在有了WFE可以low-power standby节省功耗。

      ```
      DC ISW, x5 // operation must have completed before DSB can complete STR x0, [x1] // Access must have completed before DSB can complete DSB ISH
      ADD x2, x2, #3 // Cannot be executed until DSB completes
      ```

   4. Volatile

      volatile是防止编译器优化指令，与地址本身的cache和device属性无关

      如下面代码

      ```
      void non_vo_test(void)
      {
              int *test = 3;
              int data;
              data = *test;
      }

      void vo_test(void)
      {
              volatile int *test = 3;
              int data;
              data = *test;
      }
      ```

      ​

      ```
      0000000000000184 <non_vo_test>:
       184:   d65f03c0        ret

      0000000000000188 <vo_test>:
       188:   d2800060        mov     x0, #0x3                        // #3
       18c:   b9400000        ldr     w0, [x0]
       190:   d65f03c0        ret
      ```

      告诉编译器永远发出对应地址的指令操作，不是优化掉。

