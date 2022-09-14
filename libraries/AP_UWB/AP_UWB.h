/*
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <AP_HAL/AP_HAL.h>
#include <AP_AHRS/AP_AHRS.h>
#include <AP_SerialManager/AP_SerialManager.h>

class AP_UWB {
public:
    AP_UWB();

    /* Do not allow copies */
    AP_UWB(const AP_UWB &other) = delete;
    AP_UWB &operator=(const AP_UWB&) = delete;

    //初始化UWB串口
    void init(const AP_SerialManager& serial_manager); 
    //设置接收到基站间距离
    void set_dis_EN() {_dis_EN = true;}
    //获取接收到基站距离状态
    bool get_dis_EN() {return _dis_EN;}
    //获取基站间距离
    uint16_t get_dis_BS1_BS2_cm() {return _dis_BS1_BS2_cm;}
    //更新UWB数据
    bool update(int32_t alt);      
    //获取位置数据NED
    Vector3f get_location(void) {return _loc_NED;} 
    //发送给标签到达指定位置，切换定位基站
    void uwb_send2lable(bool lable);
    //发送基站已获取定位数据
    void uwb_send2baseSta(uint16_t distance_cm);
    //格式化输出
    void printf(const char *format, ...);
    void print(const char* str) {_port->write(str);} 

    // uint32_t last_frame_ms;

    enum sterm {
        Lable2Flight = 0x66,
        Flight2Lable = 0x55,
        BaseStation2Flight = 0x44,
        Flight2BaseStation = 0x33,
        Flight2PC = 0x22,
    };
    

private:
    AP_HAL::UARTDriver *_port;              // UART used to send data to receiver
    Vector3f _loc_NED;
    uint16_t _dis_BS1_BS2_cm;
    bool _dis_EN;

    //位置计算 
    bool location_calculate(uint8_t* data , int32_t alt);
    //距离计算
    bool distance_calculate(uint8_t* data);
};
