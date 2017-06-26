//
//  main.c
//  test
//
//  Created by 帅气的杨同学 on 2017/6/22.
//  Copyright © 2017年 帅气的杨同学. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void load()
{
    char str1[100];//$GPRMC第一行
    char str2[100];//$GPGGA第二行
    int time[10];//UTC时间；
    int date[10];//UTC年月日
    int year;//
    int month;//
    int day;//
    int hour;//小时
    int minute;//
    int seconds;//
    int have = 0;//计数；
    char lat[15];//纬度
    int newlat[15];//纬度整型
    int lat1;//纬度中的度
    double lat2;//纬度的分
    char latitude;//纬度方向；
    char lon[15];//经度；
    int newlon[15];//
    int lon1;//经度的度
    double lon2;//经度的分
    char longitude;//经度方向；
    int  elevation = 0;//海拔高度；
    FILE *fp;
    int i;
    fp = fopen("//Users//y20161104577//Desktop//test//GPS.log","r");
    fscanf(fp,"%s %s",&str1,&str2);
    for(i=0; i<9; i++) {
        if(i<8)
            lat[i] = str2[i+14];
        lon[i] = str2[i+25];
        if(i<6){
            date[i] = str1[i+51] - 48;
            time[i] = str2[i+7] - 48;
        }
    }
    for(i=0; i<8; i++) {
        if(lat[i]='.') {
            newlat[i] = 0;
        }
        else {
            newlat[i] = lat[i] - 48;
        }
    }
    for(i=0; i<8; i++) {
        if(lon[i]='.') {
            newlon[i] = 0;
        }
        else {
            newlon[i] = lon[i] - 48;
        }
    }
    lat1 = newlat[0]*10 + newlat[1];
    
    printf("lat = %s\nlon = %s\n",lat,lon);
/*********************************************************************************************/
    //对UTC时间提取，分析                                                                         时间
    hour = time[0]*10 + time[1];
    minute = time[2]*10 + time[3];
    seconds = time[4]*10 + time[5];
    //将UTC时间变成北京时间
    if(hour<16)
        hour = 8 + hour;
    else {
        have++;
        hour = hour - 16;
    }
    printf("时间为：%d：%d：%d\n",hour,minute,seconds);
/********************************************************************************************/
    //对UTC日期读取，分析                                                                         日期
    day = date[0]*10 + date[1];
    month = date[2]*10 + date[3];
    year = date[4]*10 + date[5];
    if(have != 0) {
        day++;
    }
    printf("日期为：20%d，%d，%d\n",year,month,day);
/********************************************************************************************/
    latitude = str2[23];                                                                     //经度纬度
    longitude = str2[35];
    printf("纬度方向 = %c\n",latitude);
    printf("经度方向 = %c\n",longitude);
    //显示完毕；
/********************************************************************************************/
    for(i=43; i<47; i++) {
        elevation = elevation*10 + (str2[i]-48);
    }
    printf("elevation(海拔高度) = %dm\n",elevation);                                            //海拔高度
    printf("GPRMC读取数据为： %s\n",str1);
    printf("GPGGA读取数据为： %s\n",str2);
    fclose(fp);
}
int main() {
    load();
    return 0;
}
