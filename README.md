# Hardware Preparation
RK3588开发板
4个摄像头模块，每个模块连接到RK3588的MIPI CSI-2接口
一个显示屏模块连接到RK3588的LVDS接口
[参考链接](https://wiki.t-firefly.com/zh_CN/ROC-RK3588-PC/index.html)


# software Preparation
安装Linux操作系统到RK3588开发板
安装OpenCV库和其他必要的开发工具

# visual studio 
我没有硬件平台，所以选择了 visual studio的cmake项目，可跨平台编译。 \
调用了opencv库实现4路摄像头*（基于RK3588软硬解算能力设定合适的清晰度）鸟瞰拼接。 \
常规情况可能会调用Gstreamer库\ffmpeg库
## G++ 如下
g++ -std=c++11 -o panorama panorama.cpp -lcv
如果在linux平台下可直接调用： ./panorama

## TODO
拼接算法、以及摄像头接口新调用（MIPI CSI ）4 lane@30fps ，最多支持7路摄像头 \
链路解析：mipi camera2---> csi2_dphy1 ---> mipi2_csi2 ---> rkcif_mipi_lvds2--->rkcif_mipi_lvds2_sditf --->rkisp0_vir2 \
相对应的节点：mx415 ---> csi2_dphy0 ---> mipi2_csi2 ---> rkcif_mipi_lvds2--->rkcif_mipi_lvds2_sditf --->rkisp0_vir2 \
rk3588支持2个isp硬件，每个isp设备可虚拟出多个虚拟节点，软件上通过回读的方式，依次从ddr读取每一路的图像数据进isp处理。对于多摄方案，建议将数据流平均分配到两个isp上。回读：指数据经过vicap采集到ddr，应用获取到数据后，将buffer地址推送给isp，isp再从ddr获取图像数据。\
两路ISP工作模式：full and split mode \
GST-XXXX-组件支持软硬解码和查看系统摄像头
