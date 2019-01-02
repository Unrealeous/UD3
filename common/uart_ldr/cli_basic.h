#ifndef CLI_BASIC_H
#define CLI_BASIC_H

#include <stdint.h>

#define PARAM_SIZE(param) sizeof(param) / sizeof(parameter_entry)

#define SIZEP(x) ((char*)(&(x) + 1) - (char*)&(x))
#define ADD_PARAM(para_type,text, value_var, type) {para_type,text, &value_var, SIZEP(value_var), type},
#define ADD_COMMAND(command, command_func, help_text) {command, command_func, help_text},
#define TYPE_UNSIGNED   0
#define TYPE_SIGNED     1
#define TYPE_FLOAT      2
#define TYPE_CHAR       3
#define TYPE_STRING     4

#define PARAM_DEFAULT   0
#define PARAM_CONFIG    1

#define ROW_SIZE 16
#define DATASET_BYTES 5

#define CYDEV_EEPROM_ROW_SIZE 0x00000010u
#define CY_EEPROM_SIZEOF_ROW        (CYDEV_EEPROM_ROW_SIZE)

#define CYDEV_EE_SIZE 0x00000800u
#define CY_EEPROM_SIZE              (CYDEV_EE_SIZE)

#define SERIAL 0
#define USB 1
#define ETH 2
#define NONE 3

   
typedef struct parameter_entry_struct parameter_entry;
struct parameter_entry_struct {
    const uint8_t parameter_type;
	const char *name;
	void *value;
	const uint8_t size;
	const uint8_t type;
};

void EEPROM_read_conf(parameter_entry * params, uint8_t param_size, uint16_t eeprom_offset ,uint8_t port);

uint32_t djb_hash(const char* cp);

#endif