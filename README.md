# TC275Lite_CpuSleep

## ⛓ 依赖

1. 开发板套件：[Infineon KIT_AURIX_TC275_LITE](https://www.infineon.com/cms/cn/product/microcontroller/32-bit-tricore-microcontroller/32-bit-tricore-aurix-tc2xx/)；
2. 本工程基于AURIX Development Studio开发。

## 🛠 工程

该项目实现简单的三核轮休：Cpu0检测按键按下，之后唤醒Cpu1并翻转LED1，1秒后唤醒Cpu2并翻转LED2，之后进入系统休眠状态。

工程代码讲解及效果参见：

1. [CSDN工程详解](https://blog.csdn.net/weixin_46422143/article/details/126303016)
2. [B站：工程演示](https://www.bilibili.com/video/BV1ed4y1o7bK)
