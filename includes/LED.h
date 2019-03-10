#ifndef __LED_H_
#define __LED_H_
const uint64_t symbol[] PROGMEM = {

    0x1800183860663c00,

    0x10387cfefeee4400,

    0x060e0c0808281800,

    0x10307efe7e301000,

    0x1018fcfefc181000,
    
    /*add start from 5*/
    0x08080808ff080808

};



const uint64_t numbers[] PROGMEM = {

    /* 8     =>      1   row */

    0x3c66666e76663c00, /* 0 */

    0x7e1818181c181800,	/* 1 */

    0x7e060c3060663c00,	/* 2 */

    0x3c66603860663c00,	/* 3 */

    0x30307e3234383000, /* 4 */

    0x3c6660603e067e00, /* 5 */

    0x3c66663e06663c00, /* 6 */

    0x1818183030667e00, /* 7 */

    0x3c66663c66663c00, /* 8 */

    0x3c66607c66663c00, /* 9 */

};



const uint64_t Atoz[] PROGMEM = {

    0x6666667e66663c00, /* A */

    0x3e66663e66663e00,	/* B */

    0x3c66060606663c00,

    0x3e66666666663e00,

    0x7e06063e06067e00,

    0x0606063e06067e00,

    0x3c66760606663c00,

    0x6666667e66666600,

    0x3c18181818183c00,

    0x1c36363030307800,

    0x66361e0e1e366600,

    0x7e06060606060600,

    0xc6c6c6d6feeec600,

    0xc6c6e6f6decec600,

    0x3c66666666663c00,

    0x06063e6666663e00,

    0x603c766666663c00,

    0x66361e3e66663e00,

    0x3c66603c06663c00,

    0x18181818185a7e00,

    0x7c66666666666600,

    0x183c666666666600,

    0xc6eefed6c6c6c600,

    0xc6c66c386cc6c600,

    0x1818183c66666600,

    0x7e060c1830607e00,

    0x0000000000000000,

    0x7c667c603c000000,

    0x3e66663e06060600,

    0x3c6606663c000000,

    0x7c66667c60606000,

    0x3c067e663c000000,

    0x0c0c3e0c0c6c3800,

    0x3c607c66667c0000,

    0x6666663e06060600,

    0x3c18181800180000,

    0x1c36363030003000,

    0x66361e3666060600,

    0x1818181818181800,

    0xd6d6feeec6000000,

    0x6666667e3e000000,

    0x3c6666663c000000,

    0x06063e66663e0000,

    0xf0b03c36363c0000,

    0x060666663e000000,

    0x3e403c027c000000,

    0x1818187e18180000,

    0x7c66666666000000,

    0x183c666600000000,

    0x7cd6d6d6c6000000,

    0x663c183c66000000,

    0x3c607c6666000000, /* y */

    0x3c0c18303c000000  /* z */

};



uint64_t pgm_read_64( void *ptr )

{

    uint64_t result;

    memcpy_P( &result, ptr, sizeof(uint64_t) );

    return result;

}
/*****LED_end****/
#endif