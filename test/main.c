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
void load();
int main() {
    load();
    return 0;
}
void load()
{
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
    int  elevation;//海拔高度；
    int i;
    FILE *fp;
    char str1[100];//$GPRMC第一行
    char str2[100];//$GPGGA第二行
    double speed;//地面速率
    char speedch[6];//读取str中的速率
    double speedint[6];//转化地面速率为int
    int moon;//卫星颗数
    char chmoon[4];//提取卫星颗数
    char charcourse[6];//提取航向
    double intcourse[6];//转换为double型数组
    double course;//整理为数字；
    //将数据写入excel
    FILE *fl;
    fl = fopen("//Users//y20161104577//Desktop//test//information.csv","w");
    fprintf(fl,"日期,时间,纬度方向,纬度,经度方向,经度,地面速度,海拔高度,卫星颗数,航向\n");
    fp = fopen("//Users//y20161104577//Desktop//test//GPS.log","r");
    if(fp == NULL) {
        printf("文件打开失败！\n");
    }
    else {
        while(fscanf(fp,"%s %s",str1,str2)!=EOF) {
            elevation = 0;
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
                if(lat[i]=='.') {
                    newlat[i] = 0;
                }
                else {
                    newlat[i] = lat[i] - 48;
                }
            }
            for(i=0; i<9; i++) {
                if(lon[i]=='.') {
                    newlon[i] = 0;
                }
                else {
                    newlon[i] = lon[i] - 48;
                }
            }
            lat1 = newlat[0]*10 + newlat[1];
            lat2 = newlat[2]*10000 + newlat[3]*1000 + newlat[5]*100 + newlat[6]*10 + newlat[7];
            lat2 /= 1000;
            printf("纬度为：%d'%.3f\n",lat1,lat2);
            lon1 = newlon[0]*100 + newlon[1]*10 + newlon[2];
            lon2 = newlon[3]*10000 + newlon[4]*1000 + newlon[6]*100 + newlon[7]*10 + newlon[8];
            lon2 /= 1000;
            printf("经度为：%d'%.3lf\n",lon1,lon2);

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
                                                                                                        //卫星颗数
            chmoon[0] = str2[39];
            chmoon[1] = str2[40];
            moon = (chmoon[0] - 48)*10 +(chmoon[1] - 48);
            printf("卫星颗数为：%d\n",moon);
            /********************************************************************************************/
                                                                                                        //航向
            for(i=0; i<5; i++) {
                charcourse[i] = str1[i+45];
                if(charcourse[i] == '.') {
                    intcourse[i] = 0;
                }
                else
                    intcourse[i] = charcourse[i] - 48;
            }
            course = intcourse[0]*100 +intcourse[1]*10 +intcourse[2] +intcourse[4]/10;
            printf("航向：%.1lf\n",course);
            /********************************************************************************************/
                                                                                                        //地面速率
            for(i=0; i<5; i++) {
                speedch[i] = str1[i+39];
                if(speedch[i] == '.') {
                    speedint[i] = 0;
                }
                else
                    speedint[i] = speedch[i] - 48;
            }
            speed = speedint[0]*100 + speedint[1]*10 +speedint[2] +speedint[4]/10;
            speed *=1.852;
            printf("地面速度：%.1lf\n",speed);
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
            fprintf(fl,"20%d年%d月%d日,%d:%d:%d,%c,%d'%.3lf,%c,%d'%.3lf,%.1lf,%dm,%d,%.1lf\n",year,month,day,hour,minute,seconds,latitude,lat1,lat2,longitude,lon1,lon2,speed,elevation,moon,course);

        }
        fclose(fl);
        fclose(fp);
    }

    /********************************************************************************************/
}

