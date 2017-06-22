//
//  main.c
//  test
//
//  Created by 帅气的杨同学 on 2017/6/22.
//  Copyright © 2017年 帅气的杨同学. All rights reserved.
//

#include <stdio.h>
#include <string.h>

void load()
{
    char str1[100];//$GPRMC第一行
    char str2[100];//$GPGGA第二行
    int time[10];
    char lat[10];//纬度；
    char latitude;//纬度方向；
    char lon[10];//经度；
    char longitude;//经度方向；
    FILE *fp;
    int i;
    fp = fopen("//Users//y20161104577//Desktop//test//GPS.log","r");
    fscanf(fp,"%s %s",&str1,&str2);
    for(i=0; i<8; i++) {
        lat[i] = str1[i+16];
        lon[i] = lat[i];
        if(i<6)
        time[i] = (int)str1[i+8];
    }
    printf("%s\n%s\n%d\n",str1,str2);
    for(i=0; i<6; i++) {
        printf("%d",time[i]);
    }
        
    fclose(fp);
}
int main() {
    load();
    return 0;
}
