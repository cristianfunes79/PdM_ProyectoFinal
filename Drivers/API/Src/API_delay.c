#include "API_delay.h"
#include "stm32f4xx_hal.h"  		/* <- HAL include */

/* Macros ----------------------------------------------------------------------------------*/
#define MAX_DELAY_MS 60000 // 1 minuto maximo

/* Private functions -----------------------------------------------------------------------*/
static void ErrorHandler(void)
{
	while(1);
}

/* Public functions ------------------------------------------------------------------------*/

/*
 * @brief 	Inicializa la duracion del retardo especificado y setea la flag running en flase
 * @param 	delay: estructura que contiene el retardo
 * @param	duration: duracion del retardo en ms
 * @retval 	None
 */
void delayInit(delay_t* delay, tick_t duration)
{
	/* Validacion de parametros */
	if (delay == NULL) ErrorHandler();
	if (duration > MAX_DELAY_MS) ErrorHandler();
	/*--------------------------*/

	delay->running = false;
	delay->duration = duration;
}

/*
 * @brief 	Verifica si se cumplio el retardo.
 * @param 	delay: estructura que contiene el retardo en ms
 * @retval 	true si se cumplio el retardo. false si no se cumplio el retardo.
 *
 */
bool_t delayRead(delay_t* delay)
{
	/* Validacion de parametros */
	if (delay == NULL) ErrorHandler();
	/*--------------------------*/

	bool_t delayDone = false;

	if (!delay->running)
	{
		delay->startTime = HAL_GetTick();
		delay->running = true;
	}
	else
	{
		if (HAL_GetTick() - delay->startTime >= delay->duration)
		{
			delayDone = true;
			delay->running = false;
		}
	}

	return delayDone;
}

/*
 * @brief Setea la duracion de un retardo existente.
 * @param 	delay: estructura que contiene el retardo
 * @param	duration: duracion del retardo en ms
 * @retval	None
 */
void delayWrite(delay_t* delay, tick_t duration)
{
	/* Validacion de parametros */
	if (delay == NULL) ErrorHandler();
	if (duration > MAX_DELAY_MS) ErrorHandler();
	/*--------------------------*/

	delay->duration = duration;
}

/*
 * @brief 	Genera un retardo bloqueante en milisegundos.
 * @param 	delay: retardo en milisegundos.
 * @retval	None
 */
void delayBlocking_ms(uint16_t delay)
{
	HAL_Delay(delay);
}
