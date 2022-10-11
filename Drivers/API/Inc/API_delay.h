#ifndef _API_DELAY_H_
#define _API_DELAY_H_

#include <stdbool.h>
#include <stdint.h>

/* Exported types ------------------------------------------------------------*/
typedef uint32_t tick_t;
typedef bool bool_t;

typedef struct
{
	tick_t startTime;
	tick_t duration;
	bool_t running;
} delay_t;

/* Exported functions ------------------------------------------------------- */

/*
 * @brief 	Inicializa la duracion del retardo especificado y setea la flag running en flase
 * @param 	delay: estructura que contiene el retardo
 * @param	duration: duracion del retardo en ms
 * @retval 	None
 */
void delayInit(delay_t* delay, tick_t duration);

/*
 * @brief 	Verifica si se cumplio el retardo.
 * @param 	delay: estructura que contiene el retardo en ms
 * @retval 	true si se cumplio el retardo. false si no se cumplio el retardo.
 *
 */
bool_t delayRead(delay_t* delay);

/*
 * @brief 	Setea la duracion de un retardo existente.
 * @param 	delay: estructura que contiene el retardo
 * @param	duration: duracion del retardo en ms
 * @retval	None
 */
void delayWrite(delay_t* delay, tick_t duration);

/*
 * @brief 	Genera un retardo bloqueante en milisegundos.
 * @param 	delay: retardo en milisegundos.
 * @retval	None
 */
void delayBlocking_ms(uint16_t delay);

#endif
