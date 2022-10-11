/*
 * API_debounce.c
 *
 *  Created on: Sep 13, 2022
 *      Author: Cristian Funes
 */
#include "API_debounce.h"
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */

/* Private macros ------------------------------------------------------------------------ */
#define DELAY_DEBOUNCING_MS 40  // Retardo en ms para pasar al proximo led en la secuencia

/* Private definitions ------------------------------------------------------------------- */
typedef enum
{
	BUTTON_UP,
	BUTTON_FALLING,
	BUTTON_DOWN,
	BUTTON_RAISING
} debounceState_t;

/* Private variables --------------------------------------------------------------------- */
static debounceState_t debounceStateCurrent;
static delay_t delayDebouncing;
static bool_t fallingEdge;

/* Private functions ------------------------------------------------------------------------ */
static void Error_Handler(void);

static void buttonPressed(void)
{
	fallingEdge = true;
}


/* Public functions ------------------------------------------------------------------------ */

/*
 * @brief 	Lee una variable interna del modulo API_debounce y
 * 			retorna el valor de la misma
 * @params 	None
 * @retval	true or false, dependiendo el valor de la variable leida
 */
bool_t readKey(void)
{
	bool_t state = fallingEdge;
	if (fallingEdge) fallingEdge = false;
	return state;
}

/*
 * @brief Inicializa la maquina de estados
 * @params None
 * @retval None
 */
void debounceFSM_init(void)
{
	debounceStateCurrent = BUTTON_UP;
	delayInit(&delayDebouncing, DELAY_DEBOUNCING_MS);
}

/*
 * @brief Actualiza la maquina de estados al estado siguiente
 * @params None
 * @retval None
 */
void debounceFSM_update(void)
{
	switch(debounceStateCurrent)
	{
		case BUTTON_UP:
			if (BSP_PB_GetState(BUTTON_USER)) debounceStateCurrent = BUTTON_FALLING;
			break;
		case BUTTON_FALLING:
			if (delayRead(&delayDebouncing))
			{
				if (BSP_PB_GetState(BUTTON_USER))
				{
					debounceStateCurrent = BUTTON_DOWN;
					buttonPressed();
				}
				else
				{
					debounceStateCurrent = BUTTON_UP;
				}
			}
			break;
		case BUTTON_DOWN:
			if (!BSP_PB_GetState(BUTTON_USER)) debounceStateCurrent = BUTTON_RAISING;
			break;
		case BUTTON_RAISING:
			if (delayRead(&delayDebouncing))
			{
				if (!BSP_PB_GetState(BUTTON_USER))
				{
					debounceStateCurrent = BUTTON_UP;
				}
				else
				{
					debounceStateCurrent = BUTTON_DOWN;
				}
			}
			break;
		default:
			Error_Handler();
			break;
	}
}

static void Error_Handler(void)
{
	while(1);
}

