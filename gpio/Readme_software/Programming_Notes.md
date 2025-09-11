# Porgamming Notes

## Description

Document any coding or programming tip, mistake, or technique 
I learn in `gpio` project.

## Pointer Arithmetic

In `void GPIO_Interrupt_Priority(uint8_t IRQNumber, uint8_t IRQ_Priority)`:

be aware of pointer arithmetic when setting up the priority in `NVIC_IPRy` register:

1. `NVIC_IPR_BASE_ADD` is the base addresse, it is a pointer

2. To move to a specific memory location (so a specific `NVIC_IPR_y` register, one of the 60 register): `NVIC_IPR_BASE_ADD + 4*ipr_y`:

    - we add `4*ipr_y` to move to another `IPRy` register
    - `ipr_y` is of 8 bits, so we multiply by 4 to get a width of 32 bits
  
3. When setting the bits and using `*` operator, make sure to place the `*` using `()`, and not like this:

<pre>*NVIC_IPR_BASE_ADD + 4*ipr_y</pre>