/*
 * To Compile ..
   $ gcc -O6 -o SynchedFlash SynchedFlash.c -lpigpio -lrt -lpthread

   TO excecute ..
   * sudo ./test 25000 20000
   * sudo ./test ProjExpo   LedExpo
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <pigpio.h>

#define gpioStrobe 8
#define gpioHWsync 18
#define gpioStrobe2 25
#define gpioStrt 23

int frame = 0;

int wave_id, wave_id2, N=1, Status=0;


void alert(int gpio, int level, uint32_t tick)
{
	
	if (level!=0)  return;         /* Check if camera signal GPIO is HIGH*/
	
	//if(gpioRead(gpioStrt)!= 1) return;	//Check if recording has started
	//Initialize the log file
	
	//if (Status <1){		//Alternation between white light and SL
		gpioWaveTxSend(wave_id, PI_WAVE_MODE_ONE_SHOT);
		Status=Status+1;
	//}
	//else{
		//gpioWaveTxSend(wave_id2, PI_WAVE_MODE_ONE_SHOT);
		//Status=0;
	//}

	frame += 1;
	printf("---------------------------\n");
	printf("Recording Frame %u\n", frame);
 	
}

int main(int argc, char *argv[])
{	
	assert(argc > 1);
	   
	assert(gpioInitialise()>=0);
	printf("Projector Exposure is %d \n",atoi(argv[1]));
	printf("LED Exposure is %d \n",atoi(argv[2]));
	printf("FPS is %d \n",atoi(argv[3]));

   int Td1=1000000/atoi(argv[3])-60000;
   printf("FPS is %d \n",Td1);
   
   gpioPulse_t pulse[5]={
   {0,1<<gpioStrobe,Td1},      {1<<gpioStrobe,0,atoi(argv[1])},
   {0,1<<gpioStrobe,0}
};

	gpioPulse_t pulse2[5]={
	   {0,1<<gpioStrobe2,3000},      {1<<gpioStrobe2,0,atoi(argv[2])},
	   {0,1<<gpioStrobe2,0}
};

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
	
	
	printf("---------------------------\n");
	printf("\nEnter 0 to exit: \n");
	
	printf("\nWaiting for recording...\n");
	
	gpioSetAlertFunc(gpioHWsync, alert);
	scanf("%d", &N);
	gpioSetAlertFunc(gpioHWsync, NULL);
	sleep(0.5);
	gpioTerminate();

}
