#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

void Led_GPIO_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct; //定义一个gpio结构体
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //使能时钟（为了节省功耗，时钟默认关）
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP; //设置为上拉推挽输出
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0| GPIO_Pin_1|GPIO_Pin_2; //定义0引脚
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz; //管脚速度
	GPIO_Init(GPIOA, &GPIO_InitStruct); //初始化gpio
	GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_SET);
	GPIO_WriteBit(GPIOA, GPIO_Pin_1, Bit_SET);
	GPIO_WriteBit(GPIOA, GPIO_Pin_2, Bit_SET);
}

void key_GPIO_int(void)
{
	GPIO_InitTypeDef key_GPIO_InitStruct; //定义一个gpio结构体
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); //使能时钟（为了节省功耗，时钟默认关）
	
	key_GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	key_GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5| GPIO_Pin_4; //定义0引脚
	GPIO_Init(GPIOC, &key_GPIO_InitStruct); //初始化gpio
	
	GPIO_InitTypeDef key1_GPIO_InitStruct; //定义一个gpio结构体
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE); //使能时钟（为了节省功耗，时钟默认关）
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);  
	key_GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	key_GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3| GPIO_Pin_4; //定义0引脚
	GPIO_Init(GPIOB, &key1_GPIO_InitStruct); //初始化gpio
}

int main(void)
{
	Led_GPIO_init(); //初始化GPIO
	key_GPIO_int();
	while(1)
	{
		if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_4) == 1)
		{
			GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_RESET);
		}
		else
		{
			GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_SET);
		}
		
		if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_5) == 1)
		{
			GPIO_WriteBit(GPIOA, GPIO_Pin_1, Bit_RESET);
		}
		else
		{
			GPIO_WriteBit(GPIOA, GPIO_Pin_1, Bit_SET);
		}
		
		if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_3) == 1)
		{
			GPIO_WriteBit(GPIOA, GPIO_Pin_2, Bit_RESET);
		}
		else
		{
			GPIO_WriteBit(GPIOA, GPIO_Pin_2, Bit_SET);
		}
		
		if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4) == 1)
		{
			GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_RESET);
			GPIO_WriteBit(GPIOA, GPIO_Pin_1, Bit_RESET);
			GPIO_WriteBit(GPIOA, GPIO_Pin_2, Bit_RESET);
		}
		else
		{
			GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_SET);
			GPIO_WriteBit(GPIOA, GPIO_Pin_1, Bit_SET);
			GPIO_WriteBit(GPIOA, GPIO_Pin_2, Bit_SET);
		}
	}
}


