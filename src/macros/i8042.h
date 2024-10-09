#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

#include <lcom/lcf.h>


//Definir a irq line do teclado a 1, pq timer é o 0
#define KBD_IRQ_LINE 1

//Definir hook_id para o keyboard
#define KBD_HOOK_ID BIT(1)

#define KBD_OUT_BUF 0x60
#define KBD_IN_BUF 0x64
#define ESC_KEY 0x81

//Definir macros para os bits mais importantes do status code
#define STATUS_CODE_OBF BIT(0)
#define STATUS_CODE_IBF BIT(1)
#define STATUS_CODE_AUX BIT(5)
#define STATUS_CODE_TIMEOUT BIT(6)
#define STATUS_CODE_PARITY BIT(7)

//Macros para as portas de escrita e leitura do command byte
#define READ_CMD_BYTE_PORT 0x20
#define WRITE_CMD_BYTE_PORT 0x60

#define COOLDOWN 20000
#define TENTATIVAS 5

//Definir a irq line do rato a 12
#define MOUSE_IRQ_LINE 12

//Definir hook_id para o mouse
#define MOUSE_HOOK_ID BIT(2)

#define ACKNOLEDGMENT_BYTE 0xFA
#define ENABLE_MOUSE 0xA8
#define DISABLE_MOUSE 0xA7
#define WRITE_BYTE_TO_MOUSE 0xD4

//Comandos para o rato
#define FIRST_BYTE          BIT(3)
#define MOUSE_RESET 0xFF
#define MOUSE_RESEND 0xFE
#define MOUSE_SET_DEFAULTS 0xF6
#define MOUSE_DISABLE_DATA_REPORTING 0xF5
#define MOUSE_ENABLE_DATA_REPORTING 0xF4
#define MOUSE_SAMPLE_RATE 0xF3
#define SET_MOUSE_REMOTE_MODE 0xF0
#define SET_MOUSE_STREAM_MODE 0xEA
#define READ_DATA 0xEB
#define STATUS_REQUEST 0xE9

//Resultados do Ackoledgment Byte, este deve ser colocado no OUT_BUT do KBD 0x60
#define ACK 0xFA
#define NACK 0xFE
#define ERROR 0xFC

#endif

