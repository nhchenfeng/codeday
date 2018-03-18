### fs-verity

#### 简介
　　fs-verity是以单文件为单位的完整性检查，类似fs/crypto在文件系统层的实现。  
与dm-verity有相似之处。但dm-vertiy基于full partition，fs-vertiy基于per-file。  
　　文件的可信树在文件内容的末尾，当文件管理器设置上verity bit时，去更新文件的i_size，  
因此对user-land说，这些设计是透明的。  
　　当前内核里边已经有了IMA/EVM的设计，也是用于文件的integrity检查。  fs-verity与IMA  
实现的主要区别是：  
　　1. 文件的检查在pages被load的时候，以page为单位如此可减少文件打开时的latency。 尤其是  
　　　　大文件。  
　　2. 另外一个是设计层面，fs-verity不是一个LSM，基于文件系统层，可以支持多文件系统，包括   
　　　none-fs的文件。

####  主要设计  

