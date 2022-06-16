/*
   $ gcc -O6 -o gpio_alert_mod2 gpio_alert_mod2.c -lpigpio -lrt -lpthread
   $
   
   After start of raspivid_ges:
   $ sudo killall pigpiod
   $ sudo ./gpio_alert N
   $
 
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

#include <pigpio.h>

#define gpioStrobe 13
#define gpioHWsync 18
#define gpioStrobe2 19


int wave_id, wave_id2, N=1, Status=0;

gpioPulse_t pulse[5]={
   {0,1<<gpioStrobe,224000},      {1<<gpioStrobe,0,15000},
   {0,1<<gpioStrobe,0}
};

gpioPulse_t pulse2[5]={
   {0,1<<gpioStrobe2,12000},      {1<<gpioStrobe2,0,1000},
   {0,1<<gpioStrobe2,0}
};

void alert(int gpio, int level, uint32_t tick)
{
   if (level!=0)  return;         /* Check if camera signal GPIO is HIGH*/

   if (--N == 0)  gpioSetAlertFunc(gpioHWsync, NULL); /* Check if N is exhausted*/
   
   if (Status <1){

   gpioWaveTxSend(wave_id, PI_WAVE_MODE_ONE_SHOT);
   Status=Status+0;
}
else{
   gpioWaveTxSend(wave_id2, PI_WAVE_MODE_ONE_SHOT);
Status=0;
}
}

int main(int argc, char *argv[])
{
   assert(argc > 1);
   assert(0 < (N = atoi(argv[1])));
       
   assert(gpioInitialise()>=0);




   gpioSetMode(gpioStrobe, PI_OUTPUT);
   gpioWaveAddNew();
   gpioWaveAddGeneric(sizeof(pulse)/sizeof(pulse[0]), pulse);

   wave_id = gpioWaveCreate();

   assert((wave_id >= 0) || !"wave1 create failed\n");


   gpioSetMode(gpioStrobe2, PI_OUTPUT);
   gpioWaveAddNew();
   gpioWaveAddGeneric(sizeof(pulse2)/sizeof(pulse2[0]), pulse2);

   wave_id2 = gpioWaveCreate();

   assert((wave_id2 >= 0) || !"wave2 create failed\n");



   gpioSetAlertFunc(gpioHWsync, alert);

   sleep(N/25);

   gpioTerminate();
}
