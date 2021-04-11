#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "sys/types.h"
#include <stdlib.h>

int main()
{
        int isCharging = 0;
        long long energyFull, energyNow;
        char status[32],line[128];
        FILE *file;
        long long totalPhysMem, physMemFree;
        double batteryPercent;
        double physMemPercent;
        int firstFlag=0;
        int i,j;
        while(1)
        {
		file = fopen("/proc/meminfo","r");
                fscanf(file," %[^\n]s",line);
                for(i=0;line[i]<'0'||line[i]>'9';i++);
                for(j=i;line[j]!=' ';j++)
		{
                        line[j-i] = line[j];
                }
                line[j-i]='\0';
                totalPhysMem = atoi(line);
                fscanf(file," %[^\n]s",line);
                fscanf(file," %[^\n]s",line);
                for(i=0;line[i]<'0'||line[i]>'9';i++);
                for(j=i;line[j]!=' ';j++)
                {
                        line[j-i] = line[j];
                }
                line[j-i]='\0';
                physMemFree = atoi(line);
                fclose(file);
                file = fopen("/sys/class/power_supply/BAT1/status","r");
                fscanf(file," %s",status);
                fclose(file);
                file = fopen("/sys/class/power_supply/BAT1/energy_full","r");
                fscanf(file," %lli",&energyFull);
                fclose(file);
                file = fopen("/sys/class/power_supply/BAT1/energy_now","r");
                fscanf(file," %lli",&energyNow);
                fclose(file);
                double newBatteryPercent = (energyNow*1.0)/(energyFull*1.0);
                newBatteryPercent *= 100;
                double newPhysMemPercent = (physMemFree*1.0)/(totalPhysMem*1.0);
                newPhysMemPercent *= 100;
                if(firstFlag==0)
                {
                        printf("%s\nBattery remaining: %lf %% \nPhysical memory remaining: %lf %% \n",status,newBatteryPercent,newPhysMemPercent);
                        isCharging = strcmp(status,"Charging")==0? 1: 0;
                        firstFlag=1;
                }
		else
                {
                        if(isCharging==0 && strcmp(status,"Charging")==0)
                        {
                                printf("Plugged in, Charging!!!\n");
                        }
                        if(isCharging==1 && strcmp(status,"Discharging")==0)
                        {
                                if(batteryPercent<20)
                                {
                                        printf("Low battery!!! remaining: %lf %%\n",batteryPercent);
                                }
                                else
                                {
                                        printf("Plugged out, Battery remaining: %lf %%\n",newBatteryPercent);
                                }
                        }
                        isCharging = strcmp(status,"Charging")==0? 1: 0;
                        if(newBatteryPercent<20 && batteryPercent>=20)
                        {
                                printf("Low battery!!! less than 20 %% remaining...\n");
                        }
                        if(newPhysMemPercent<20 && physMemPercent>=20)
                        {
                                printf("Physical memory availablity LESS than 20 %%!!!\n");
                        }
                        if(newPhysMemPercent>=20 && physMemPercent<20)
                        {
                                printf("Physical memory availablity MORE than 20 %%!!!\n");
                        }
                }
                batteryPercent = newBatteryPercent;
                physMemPercent = newPhysMemPercent;
                sleep(1);
        }
}