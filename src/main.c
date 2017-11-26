/**
 ******************************************************************************
 * @file    UART/UART_TwoBoards_ComPolling/Src/main.c
 * @author  MCD Application Team
 * @version V1.2.7
 * @date    17-February-2017
 * @brief   This sample code shows how to use STM32F4xx UART HAL API to transmit
 *          and receive a data buffer with a communication process based on
 *          polling transfer.
 *          The communication is done using 2 Boards.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

UART_HandleTypeDef UartHandle;
signed char Valeurs[4];

/* Buffer used for transmission */

uint8_t setWifiMode[] = "AT+CWMODE=3\r\n";
uint8_t connectRouter[] = "AT+CWJAP=\"Master_SE\",\"U8d_4fW@\"\r\n";
uint8_t connectServer[] = "AT+CIPSTART=\"TCP\",\"192.168.42.145\",975\r\n";
uint8_t ID[] = "59ef-6F70-4bM7\n";
uint8_t reset[] = "AT+RST\r\n";

/* Buffer used for reception */

uint8_t aRxBuffer[RXBUFFERSIZE];

/* Private function prototypes -----------------------------------------------*/

static void SystemClock_Config(void);
static void Error_Handler(void);
static void uart_write(uint8_t* pBuffer);
static void uart_receive();
static void Valeurs_x_y();
static void Start_ESP8266();

int main(void)
{
	/* STM32F4xx HAL library initialization:
       - Configure the Flash prefetch, instruction and Data caches
       - Configure the Systick to generate an interrupt each 1 msec
       - Set NVIC Group Priority to 4
       - Global MSP (MCU Support Package) initialization
	 */
	HAL_Init();

	/* Configure LED3, LED4, LED5 and LED6 */
	BSP_LED_Init(LED3);
	BSP_LED_Init(LED4);
	BSP_LED_Init(LED5);
	BSP_LED_Init(LED6);

	/* Configure the system clock to 168 MHz */
	SystemClock_Config();

	/*##-1- Configure the UART peripheral ######################################*/
	/* Put the USART peripheral in the Asynchronous mode (UART Mode) */
	/* UART1 configured as follow:
      - Word Length = 8 Bits
      - Stop Bit = One Stop bit
      - Parity = None
      - BaudRate = 9600 baud
      - Hardware flow control disabled (RTS and CTS signals) */
	UartHandle.Instance          = USARTx;

	UartHandle.Init.BaudRate     = 9600;
	UartHandle.Init.WordLength   = UART_WORDLENGTH_8B;
	UartHandle.Init.StopBits     = UART_STOPBITS_1;
	UartHandle.Init.Parity       = UART_PARITY_NONE;
	UartHandle.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
	UartHandle.Init.Mode         = UART_MODE_TX_RX;
	UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;

	if(HAL_UART_Init(&UartHandle) != HAL_OK)
	{
		Error_Handler();
	}
	GPIO_InitTypeDef gpio_init;
	gpio_init.Pin=GPIO_PIN_2;
	gpio_init.Mode=GPIO_MODE_INPUT;
	HAL_GPIO_Init(GPIOA,&gpio_init);

	/* Configure KEY Button */
	BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_GPIO);

	/* Wait for USER Button press before starting the Communication */
	while (BSP_PB_GetState(BUTTON_KEY) == RESET)
	{
		/* Toggle LED3 waiting for user to press button */
		BSP_LED_Toggle(LED3);
		HAL_Delay(40);
	}
	/* Wait for USER Button release before starting the Communication */
	while (BSP_PB_GetState(BUTTON_KEY) == SET)
	{
	}

	/* Turn LED3 off */
	BSP_LED_Off(LED3);

	Start_ESP8266();

	while(1)
	{
		Valeurs_x_y();
	}

}

	static void Start_ESP8266()
	{

		uart_write(reset);
		uart_receive();
		while(aRxBuffer[12]!='K'){};
		HAL_Delay(2000);

		uart_write(setWifiMode);
		uart_receive();
		while(aRxBuffer[18]!='K'){}

		uart_write(connectRouter);
		while(aRxBuffer[3]!='K'){
			uart_receive();
		}

		uart_write(connectServer);
		/*while(aRxBuffer[55]!='K'){
		uart_receive();
	}

	uart_write(status);*/
	}

	static void Valeurs_x_y()
	{
		uart_receive();

		if(aRxBuffer[9]=='x')
		{
			if (aRxBuffer[10]=='+')
			{
				Valeurs[0]=aRxBuffer[11];
				BSP_LED_On(LED3);
			}
			if(aRxBuffer[10]=='-')
			{
				Valeurs[2]=aRxBuffer[11];
				BSP_LED_On(LED4);
			}
		}

		if(aRxBuffer[9]=='y')
		{
			if (aRxBuffer[10]=='+')
			{
				Valeurs[1]=aRxBuffer[11];
				BSP_LED_On(LED5);
			}
			if (aRxBuffer[10]=='-')
			{
				Valeurs[3]=aRxBuffer[11];
				BSP_LED_On(LED6);
			}
		}
		if(aRxBuffer[9]=='R')
		{
			BSP_LED_Off(LED3);
			BSP_LED_Off(LED4);
			BSP_LED_Off(LED5);
			BSP_LED_Off(LED6);
		}

	}

	static void uart_write(uint8_t* pBuffer){
		/* The board sends the message and expects to receive it back */

		/*##-2- Start the transmission process #####################################*/
		/* While the UART in reception process, user can transmit data through
	     "aTxBuffer" buffer */

		unsigned char txSize = 0;
		unsigned char caractereActuel = 0;

		do
		{
			caractereActuel =pBuffer[txSize];
			txSize++;
		}
		while(caractereActuel != '\0');

		txSize--;

		if(HAL_UART_Transmit(&UartHandle, pBuffer, txSize, 5000)!= HAL_OK)
		{
			Error_Handler();
		}

	}

	static void uart_receive(){

		HAL_UART_Receive(&UartHandle, (uint8_t *)aRxBuffer, RXBUFFERSIZE, 100);

	}


	/**
	 * @brief  System Clock Configuration
	 *         The system Clock is configured as follow :
	 *            System Clock source            = PLL (HSE)
	 *            SYSCLK(Hz)                     = 168000000
	 *            HCLK(Hz)                       = 168000000
	 *            AHB Prescaler                  = 1
	 *            APB1 Prescaler                 = 4
	 *            APB2 Prescaler                 = 2
	 *            HSE Frequency(Hz)              = 8000000
	 *            PLL_M                          = 8
	 *            PLL_N                          = 336
	 *            PLL_P                          = 2
	 *            PLL_Q                          = 7
	 *            VDD(V)                         = 3.3
	 *            Main regulator output voltage  = Scale1 mode
	 *            Flash Latency(WS)              = 5
	 * @param  None
	 * @retval None
	 */
	static void SystemClock_Config(void)
	{
		RCC_ClkInitTypeDef RCC_ClkInitStruct;
		RCC_OscInitTypeDef RCC_OscInitStruct;

		/* Enable Power Control clock */
		__HAL_RCC_PWR_CLK_ENABLE();

		/* The voltage scaling allows optimizing the power consumption when the device is
     clocked below the maximum system frequency, to update the voltage scaling value 
     regarding system frequency refer to product datasheet.  */
		__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

		/* Enable HSE Oscillator and activate PLL with HSE as source */
		RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
		RCC_OscInitStruct.HSEState = RCC_HSE_ON;
		RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
		RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
		RCC_OscInitStruct.PLL.PLLM = 8;
		RCC_OscInitStruct.PLL.PLLN = 336;
		RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
		RCC_OscInitStruct.PLL.PLLQ = 7;
		if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
		{
			Error_Handler();
		}

		/* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
     clocks dividers */
		RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
		RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
		RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
		RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
		RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
		if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
		{
			Error_Handler();
		}

		/* STM32F405x/407x/415x/417x Revision Z devices: prefetch is supported  */
		if (HAL_GetREVID() == 0x1001)
		{
			/* Enable the Flash prefetch */
			__HAL_FLASH_PREFETCH_BUFFER_ENABLE();
		}
	}

	/**
	 * @brief  UART error callbacks
	 * @param  UartHandle: UART handle
	 * @note   This example shows a simple way to report transfer error, and you can
	 *         add your own implementation.
	 * @retval None
	 */
	void HAL_UART_ErrorCallback(UART_HandleTypeDef *UartHandle)
	{
		/* Turn LED3 on: Transfer error in reception/transmission process */
		BSP_LED_On(LED3);
	}


	/**
	 * @brief  This function is executed in case of error occurrence.
	 * @param  None
	 * @retval None
	 */
	static void Error_Handler(void)
	{
		/* Turn LED5 on */
		BSP_LED_On(LED5);
		while(1)
		{
		}
	}

	/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
