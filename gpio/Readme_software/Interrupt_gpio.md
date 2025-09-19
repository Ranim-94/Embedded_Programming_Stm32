# STM32F407G GPIO Interrupts Analysis

## Table of Contents

- [STM32F407G GPIO Interrupts Analysis](#stm32f407g-gpio-interrupts-analysis)
  - [Table of Contents](#table-of-contents)
  - [Overview](#overview)
    - [Code](#code)
  - [1. Hardware and Software Setup](#1-hardware-and-software-setup)
  - [2. Event Flow: What Happens When You Press the Button](#2-event-flow-what-happens-when-you-press-the-button)
  - [3. Role of Each Peripheral](#3-role-of-each-peripheral)
  - [4. Software Responsibilities](#4-software-responsibilities)
  - [5. Hardware Responsibilities](#5-hardware-responsibilities)
  - [6. Key Points](#6-key-points)
  - [7. Example Code Snippet](#7-example-code-snippet)
  - [8. Summary Table](#8-summary-table)
  - [9. References](#9-references)

## Overview
This document explains the flow and hardware interaction when using GPIO interrupts on the STM32F407G microcontroller, using PA0 as a button input and PD12 as an LED output. It covers the roles of EXTI, NVIC, and the EXTI->PR register, and clarifies the software and hardware responsibilities.

### Code

See [`main_interrupt_gpio.c`](../Src/main_interrupt_gpio.c) under [`gpio` project](../).

---

## 1. Hardware and Software Setup
- **PA0**: Configured as input (button)
- **PD12**: Configured as output (LED)
- **EXTI Line 0**: Configured to detect falling edge on PA0
- **NVIC**: Configured in `main()` to enable EXTI0 interrupt

---

## 2. Event Flow: What Happens When You Press the Button

```
[Button PA0 pressed]
    |
    v
[EXTI Line 0 detects edge]
    |
    v
[EXTI->PR pending bit set by hardware]
    |
    v
[NVIC receives IRQ request from EXTI]
    |
    v
[EXTI0_IRQHandler called by NVIC]
    |
    v
[GPIO_IRQ_Handle(0) clears EXTI->PR]
    |
    v
[User code runs (e.g., toggle LED PD12)]
```

---

## 3. Role of Each Peripheral

- **EXTI (External Interrupt/Event Controller):**
  - Detects the configured edge (falling/rising) on PA0.
  - Sets the corresponding pending bit in `EXTI->PR` automatically (hardware action).

- **EXTI->PR (Pending Register):**
  - Each bit corresponds to a line (e.g., bit 0 for PA0).
  - When set, indicates an interrupt is pending for that line.
  - Must be cleared in software (by writing 1 to the bit) after handling the interrupt.

- **NVIC (Nested Vectored Interrupt Controller):**
  - Receives the IRQ request from EXTI when the pending bit is set.
  - Calls the appropriate interrupt handler (e.g., `EXTI0_IRQHandler`).
  - You enable/configure this in your `main()` function.

---

## 4. Software Responsibilities
- Configure GPIO, EXTI, and NVIC in `main()`.
- In the interrupt handler, check and clear the EXTI->PR pending bit for the pin.
- Run user code (e.g., toggle LED) in the handler.

---

## 5. Hardware Responsibilities
- Detect the edge on the input pin.
- Set the EXTI->PR pending bit automatically.
- Send the IRQ request to NVIC.

---

## 6. Key Points
- The EXTI->PR pending bit is set by hardware when the event occurs.
- Your code must clear the pending bit after handling the interrupt.
- NVIC only calls your handler if you have enabled the interrupt in software.
- The actual IRQ signaling and pending bit setting are handled by hardware.

---

## 7. Example Code Snippet
```c
void EXTI0_IRQHandler(void) {
    GPIO_IRQ_Handle(0); // Handle interrupt for pin 0
    // User code: toggle LED, etc.
}

void GPIO_IRQ_Handle(uint8_t pin_nb) {
    if (EXTI->PR & (1 << pin_nb)) {
        EXTI->PR |= (1 << pin_nb); // Clear pending bit
    }
}
```

---

## 8. Summary Table
| Step                | Who Does It? | Description                                 |
|---------------------|--------------|---------------------------------------------|
| Edge detected       | Hardware     | EXTI detects edge on PA0                    |
| Set EXTI->PR        | Hardware     | Pending bit set for EXTI line 0             |
| IRQ to NVIC         | Hardware     | EXTI signals NVIC to handle interrupt       |
| Handler called      | Hardware     | NVIC calls `EXTI0_IRQHandler()`                 |
| Clear EXTI->PR      | Software     | Your code clears pending bit in handler     |
| User action         | Software     | Your code toggles LED, etc.                 |

---

## 9. References
- STM32F407 Reference Manual
- STM32F4 Datasheet
