/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "lwip.h"
#include "usb_host.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "httpd.h"
#include "bum_player.h"
#include "accelerometer_handler.h"
#include <string.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define PLAYER_NAME "Jean"
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

I2S_HandleTypeDef hi2s3;

UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */

event e;

#define TIM2_MS 10
#define BUMPER_DT_MS 100

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_I2S3_Init(void);
static void MX_USART3_UART_Init(void);
void MX_USB_HOST_Process(void);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

int8_t buffer[2] = {0};

#define ABS(x) (x < 0) ? (-x) : x

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  int8_t xval, yval = 0x00;

  xval = buffer[0];
  yval = buffer[1];

  set_accelerometer_values(buffer);

  if (ABS(xval) > 0)
  {
    HAL_GPIO_TogglePin(GPIOD, LD5_Pin);
  }

  if (ABS(yval) > 0)
  {
    HAL_GPIO_TogglePin(GPIOD, LD4_Pin);
  }

  // Restart receiving data on USART3
  HAL_UART_Receive_IT(&huart3, buffer, 2);
}

// int _write(int file, char *ptr, int len)
// {
//   HAL_UART_Transmit(&huart6, (uint8_t *)ptr, len, 1000);
//   return len;
// }

// void pwm_angle_to_registers(int angle)
// {
//   if (angle < -90)
//     angle = -90;
//   else if (angle > 90)
//     angle = 90;

//   // 100 counts / ms
//   // -90 --> 0.75 ms
//   //  90 --> 2.25 ms
//   // 100 * (0.75 + 1,5/180 * (angle + 90))

//   int pulse = 75 + (150 * (angle + 90)) / 180;
//   int period = pulse + 2000;

//   // Besoin de stopper le timer ? De reset ? d'attendre la fin d'un cycle ?
//   // Non : shadow registers
//   __HAL_TIM_SET_AUTORELOAD(&htim9, (period - 1));
//   __HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_1, (pulse - 1));
// }

void bumper_signal_error(int x)
{
  HAL_GPIO_WritePin(LD3_GPIO_Port, LD5_Pin, 1); // RED

  char buff[20];
  sprintf(buff, "ERROR %d<br/>", x);

  bum_log(buff);
}

void bumper_signal_debug(int x)
{
  HAL_GPIO_TogglePin(LD6_GPIO_Port, LD6_Pin); // BLUE
}

BumperProtocolPlayer bum_player;

#define JSON_ORDERS_SIZE 500
char json_orders[JSON_ORDERS_SIZE + 1];

int bumper_game_step(uint8_t step, uint8_t param)
{
  int len = strlen(json_orders);
  if (len > JSON_ORDERS_SIZE - 50)
    return 0;

  char msg[40];
  msg[0] = 0;
  switch (step)
  {
  case BUM_STEP_REGISTERED:
    switch (param)
    {
    case 0: // internal error
      strcpy(msg, "Internal Error");
      break;
    case 1: // OK
      strcpy(msg, "OK registered as ");
      strcat(msg, bum_player.name);
      break;
    case 2: // OK but already registered
      strcpy(msg, "OK already as ");
      strcat(msg, bum_player.name);
      break;
    case 3: // NO, too many players
      strcpy(msg, "Too many players");
      break;
    case 4: // NO, game already started
      strcpy(msg, "Too late");
      break;
    default:
      strcpy(msg, "param ???");
      break;
    }
    break;

  case BUM_STEP_START:
    strcpy(msg, "Playing as ");
    strcat(msg, bum_player.name);
    break;
    break;

  case BUM_STEP_RESULT:
    break;

  case BUM_STEP_END:
    sprintf(msg, "Game Over");
    break;

  default:
    strcpy(msg, "step ???");
    break;
  }

  if (msg[0])
  {
    sprintf(json_orders + len, "{\"display\":[{\"id\":\"step\",\"x\":200,\"y\":-5,\"content\":\"%s\"}]},", msg);
  }

  return 1;
}

int bumper_game_new_player(uint8_t id, const char *name, uint32_t color)
{
  int len = strlen(json_orders);
  if (len > JSON_ORDERS_SIZE - 50)
    return 0;
  sprintf(json_orders + len, "{\"new_player\":[{\"i\":%d,\"name\":\"%s\",\"color\": \"#%06X\"}]},", (unsigned int)id, name, (unsigned int)color);
  return 1;
}

int bumper_game_player_move(uint8_t id, uint16_t x, uint16_t y, uint16_t s)
{
  int len = strlen(json_orders);
  if (len > JSON_ORDERS_SIZE - 50)
    return 0;
  sprintf(json_orders + len, "{\"move\":[{\"i\":%d,\"x\":%d,\"y\":%d,\"a\":%d,\"s\":%d}]},", (unsigned int)id, (unsigned int)x, (unsigned int)y, 0, (unsigned int)s);
  return 1;
}

int bumper_game_print(const char *msg)
{
  int len = strlen(json_orders);
  if (len > JSON_ORDERS_SIZE - 50)
    return 0;
  sprintf(json_orders + len, "{\"display\":[{\"id\":\"score\",\"x\":10,\"y\":-5,\"content\":\"%s\"}]},", msg);
  return 1;
}

void bumper_init_player()
{
  bum_player.game_step = bumper_game_step;
  bum_player.game_new_player = bumper_game_new_player;
  bum_player.game_player_move = bumper_game_player_move;
  bum_player.game_print = bumper_game_print;

  bum_player.error = bumper_signal_error;
  bum_player.debug = bumper_signal_debug;

  bum_init_player(&bum_player);
}

WebInterface wi;

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_I2S3_Init();
  MX_LWIP_Init();
  MX_USB_HOST_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */

  strcpy(bum_player.name, PLAYER_NAME);

  // web_interface_init(&wi);

  // MX_LWIP_Init_(0);

  // HAL_TIM_Base_Start_IT(&htim2);

  // event_init(&e);

  // Start receiving data on USART3
  HAL_UART_Receive_IT(&huart3, &buffer, 2);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  // HAL_DAC_Start(&hdac, DAC_CHANNEL_1);

  // Start AD conversion
  // HAL_ADC_Start(&hadc1);

  // Start timer 9
  // HAL_TIM_Base_Start(&htim9);
  // Start PWM on channel 1, timer 9
  // HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_1);
  httpd_init();

  // bumper_init_player();

  // strcpy(json_orders, "{\"L\":[");

  while (1)
  {
    /* USER CODE END WHILE */
    MX_USB_HOST_Process();

    /* USER CODE BEGIN 3 */

    MX_LWIP_Process();

    // bum_process_player();

    // Execute buttons pushed in web interface
    //   if (event_check(&wi.evt))
    //   {
    //     if (wi.button_register_player)
    //     {
    //       wi.button_register_player = 0;
    //       bum_game_register(bum_player.name);
    //     }

    //     if (wi.button_acc)
    //     {
    //       wi.button_acc = 0;
    //       bum_game_acceleration(wi.acc_x, wi.acc_y, 0);
    //     }
    //   }

    //   if (event_check(&e)) // If the event has been triggered
    //   {
    //     bum_process(TIM2_MS);

    //     static int N_BUMPER_DT_MS = 0;
    //     N_BUMPER_DT_MS += TIM2_MS;
    //     if (N_BUMPER_DT_MS >= BUMPER_DT_MS)
    //     {
    //       N_BUMPER_DT_MS = 0;
    //     }

    //     static int N500 = 0;
    //     N500 += TIM2_MS;
    //     if (N500 >= 500)
    //     {
    //       N500 = 0;
    //       HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin); // ORANGE
    //     }
    //   }
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_I2S;
  PeriphClkInitStruct.PLLI2S.PLLI2SN = 192;
  PeriphClkInitStruct.PLLI2S.PLLI2SR = 2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */
}

/**
  * @brief I2S3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2S3_Init(void)
{

  /* USER CODE BEGIN I2S3_Init 0 */

  /* USER CODE END I2S3_Init 0 */

  /* USER CODE BEGIN I2S3_Init 1 */

  /* USER CODE END I2S3_Init 1 */
  hi2s3.Instance = SPI3;
  hi2s3.Init.Mode = I2S_MODE_MASTER_TX;
  hi2s3.Init.Standard = I2S_STANDARD_PHILIPS;
  hi2s3.Init.DataFormat = I2S_DATAFORMAT_16B;
  hi2s3.Init.MCLKOutput = I2S_MCLKOUTPUT_ENABLE;
  hi2s3.Init.AudioFreq = I2S_AUDIOFREQ_96K;
  hi2s3.Init.CPOL = I2S_CPOL_LOW;
  hi2s3.Init.ClockSource = I2S_CLOCK_PLL;
  hi2s3.Init.FullDuplexMode = I2S_FULLDUPLEXMODE_DISABLE;
  if (HAL_I2S_Init(&hi2s3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2S3_Init 2 */

  /* USER CODE END I2S3_Init 2 */
}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(CS_I2C_SPI_GPIO_Port, CS_I2C_SPI_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(OTG_FS_PowerSwitchOn_GPIO_Port, OTG_FS_PowerSwitchOn_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, LD4_Pin | LD3_Pin | LD5_Pin | LD6_Pin | Audio_RST_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : CS_I2C_SPI_Pin */
  GPIO_InitStruct.Pin = CS_I2C_SPI_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(CS_I2C_SPI_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : OTG_FS_PowerSwitchOn_Pin */
  GPIO_InitStruct.Pin = OTG_FS_PowerSwitchOn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(OTG_FS_PowerSwitchOn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PDM_OUT_Pin */
  GPIO_InitStruct.Pin = PDM_OUT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
  HAL_GPIO_Init(PDM_OUT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : SPI1_SCK_Pin SPI1_MISO_Pin */
  GPIO_InitStruct.Pin = SPI1_SCK_Pin | SPI1_MISO_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : BOOT1_Pin */
  GPIO_InitStruct.Pin = BOOT1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(BOOT1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : CLK_IN_Pin */
  GPIO_InitStruct.Pin = CLK_IN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
  HAL_GPIO_Init(CLK_IN_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LD4_Pin LD3_Pin LD5_Pin LD6_Pin
                           Audio_RST_Pin */
  GPIO_InitStruct.Pin = LD4_Pin | LD3_Pin | LD5_Pin | LD6_Pin | Audio_RST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pin : OTG_FS_OverCurrent_Pin */
  GPIO_InitStruct.Pin = OTG_FS_OverCurrent_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(OTG_FS_OverCurrent_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : MEMS_INT2_Pin */
  GPIO_InitStruct.Pin = MEMS_INT2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(MEMS_INT2_GPIO_Port, &GPIO_InitStruct);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
