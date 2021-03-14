
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

GPIO_InitTypeDef LED;
TIM_TimeBaseInitTypeDef TIMBaseStruct;
TIM_OCInitTypeDef TIM_PWM;

uint16_t delay_cnt=0;

int motor_pwm_period=6;

void SysTick_Handler(void){

	if(delay_cnt>0){
		delay_cnt--;
	}
}

void delay_ms(uint16_t delay){
	delay_cnt=delay;
	while(delay_cnt){

	}
}

void config(){


	//data bus
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);


	//config for alternation pin(must be previously set it before AF mode of LED)
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4);


	//led config
	LED.GPIO_Mode=GPIO_Mode_AF; //GPIO alternate function mode
	LED.GPIO_OType=GPIO_OType_PP;
	LED.GPIO_Pin=GPIO_Pin_12  ;
	LED.GPIO_PuPd=GPIO_PuPd_NOPULL;
	LED.GPIO_Speed=0x03;
    GPIO_Init(GPIOD,&LED);


	SysTick_Config(SystemCoreClock/1000);// 1ms de bir systick_handler interuptuna girer.


	// time base config
	TIMBaseStruct.TIM_ClockDivision=TIM_CKD_DIV4;
	TIMBaseStruct.TIM_RepetitionCounter=0; //tekrar etme sayýsý(+1 olduðu için 0 yazýnca 1 kere tekrar ediyor)
	TIMBaseStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIMBaseStruct.TIM_Period=99;      // týmer ýn 1 saniye çalýþmasý için yapýyoruz.
	TIMBaseStruct.TIM_Prescaler=4199; // týmer ýn 1 saniye çalýþmasý için yapýyoruz.
	TIM_TimeBaseInit(TIM4,&TIMBaseStruct);

	TIM_Cmd(TIM4,ENABLE); // timer 4 aktif


	//pwm config(devamý sonsuz while döngüsü içinde)
	TIM_PWM.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_PWM.TIM_OutputState=TIM_OutputState_Enable;
	TIM_PWM.TIM_OCPolarity=TIM_OCPolarity_High;



}



int main(void)
{
 config();

  while (1)
  {

      int motor_pwm_period=6;

      while(motor_pwm_period<90){

    	//PD12
    	TIM_PWM.TIM_Pulse=motor_pwm_period;
        TIM_OC1Init(TIM4,&TIM_PWM);
   	    TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable);

   	    delay_ms(500);

   	    motor_pwm_period+=10;
	  }


      while(motor_pwm_period>10){

         //PD12
         TIM_PWM.TIM_Pulse=motor_pwm_period;
         TIM_OC1Init(TIM4,&TIM_PWM);
         TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable);

         delay_ms(500);

         motor_pwm_period = motor_pwm_period -10;
       }

  }
}











void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}


uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}













