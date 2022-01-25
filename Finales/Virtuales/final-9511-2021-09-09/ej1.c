#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define RC5_FIXED_BITS_VAL 0x03
#define RC5_FIXED_BITS_SHIFT 12

#define RC5_BTN_FLAG_MSK 0x01
#define RC5_BTN_FLAG_SHIFT 11

#define RC5_ADDR_MSK 0x1F
#define RC5_ADDR_SHIFT 6

#define RC5_CMD_MSK 0x3F

uint16_t rc5_empaquetar(bool toggle, uint8_t direccion, uint8_t comando) {
	return RC5_FIXED_BITS_VAL << RC5_FIXED_BITS_SHIFT | toggle << RC5_BTN_FLAG_SHIFT | (direccion & RC5_ADDR_MSK) << RC5_ADDR_SHIFT | (comando & RC5_CMD_MSK);
}

bool rc5_desempaquetar(uint16_t paquete, bool *toggle, uint8_t *direccion, uint8_t *comando) {

	if ((paquete >> RC5_FIXED_BITS_SHIFT) != RC5_FIXED_BITS_VAL)
		return false;

	*toggle = (paquete >> RC5_BTN_FLAG_SHIFT) & RC5_BTN_FLAG_MSK;
	*direccion = (paquete >> RC5_ADDR_SHIFT) & RC5_ADDR_MSK;
	*comando = paquete & RC5_CMD_MSK;

	return true;
}

int main(void) {
	printf("%x\n", rc5_empaquetar(true, 0x1c, 0x3a));
	assert(rc5_empaquetar(true, 0x1c, 0x3a) == 0x3f3a);

	bool toggle;
	uint8_t direccion;
	uint8_t comando;
	assert(rc5_desempaquetar(0x3f3a, &toggle, &direccion, &comando));
	assert(toggle == true);
	assert(direccion == 0x1c);
	assert(comando == 0x3a);

	// OPCIONAL: pruebas adicionales

	assert(rc5_desempaquetar(0x1f3a, &toggle, &direccion, &comando) == false); // Paquete con header incorrecto (0001 T AAAAA CCCCCC)

	printf("%s: OK\n", __FILE__);
	return 0;
}
