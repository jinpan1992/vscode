#!/bin/bash

count=0
while true; do
    # 检查网络接口状态
    echo "检查网络接口状态..."
    ip link show

    # 测试有线网络连接
    echo "测试有线网络连接..."
    wired_ping=$(ping -c 1 -I eth0 www.baidu.com | grep "1 received" | wc -l)

    # 测试4G网络连接
    echo "测试4G网络连接..."
    usb0_ping=$(ping -c 1 -I usb0 www.baidu.com | grep "1 received" | wc -l)

    # 根据ping结果设置路由表
    if [ $usb0_ping -eq 1 ] && [ $wired_ping -eq 1 ]; then
        echo "两个网络都可用，设置4G网络优先"
        ip route add default via $(ip route show dev usb0 | grep "default" | awk '{print $3}') dev usb0
        break
    elif [ $usb0_ping -eq 1 ]; then
        echo "只有4G网络可用，设置为默认网络"
        ip route add default via $(ip route show dev usb0 | grep "default" | awk '{print $3}') dev usb0
        break
    elif [ $wired_ping -eq 1 ]; then
        echo "只有有线网络可用，设置为默认网络"
        ip route add default via $(ip route show dev eth0 | grep "default" | awk '{print $3}') dev eth0
        break
    else
        echo "两个网络都不可用"
        count=$((count+1))
        if [ $count -ge 30 ]; then
            echo "连续30次检测都没有网络连接，重启设备"
            reboot
        fi
        sleep 1
    fi
done

