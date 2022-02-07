#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>

#define PC_MASK 0xFFFFFF
#define PC_SHIFT 2
#define ARM1_PC_IS_IN_RANGE(x) (x <= PC_MASK)

uint32_t psr_pc_get(uint32_t *psr) {
    return (*psr >> PC_SHIFT) & PC_MASK;
}

// static void print_bin(uint32_t x) {
//     for (int i = 31; i >= 0; i--) {
//         fprintf(stderr,"%d", (x >> i) & 1);
//         if (i % 4 == 0)
//             fprintf(stderr," ");
//     }
//     fprintf(stderr,"\n");
// }

void psr_pc_set(uint32_t *psr, uint32_t pc) {
    *psr = (*psr & ~(PC_MASK << PC_SHIFT)) | (pc << PC_SHIFT);
}

bool psr_pc_sumar(uint32_t *psr, int d) {
    const uint32_t pc = psr_pc_get(psr);
    if (ARM1_PC_IS_IN_RANGE(pc + d)) {
        psr_pc_set(psr, pc + d);
        return true;
    }
    return false;
}

int main(void) {
    uint32_t psr = 0x99999999;             // 1001 1001 1001 1001 1001 1001 1001 1001
    assert(psr_pc_get(&psr) == 0x666666);  //           0110 0110 0110 0110 0110 0110

    psr_pc_set(&psr, 42);
    assert(psr_pc_get(&psr) == 42);
    bool r;
    r = psr_pc_sumar(&psr, -16);
    assert(r);
    assert(psr_pc_get(&psr) == 26);
    r = psr_pc_sumar(&psr, -30);
    assert(!r);
    assert(psr_pc_get(&psr) == 26);

    // OPCIONAL: escribir pruebas adicionales

    printf("%s: OK\n", __FILE__);
    return 0;
}
