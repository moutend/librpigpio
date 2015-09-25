#ifndef RPIGPIO_H
#define RPIGPIO_H

#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>

#define BLOCK_SIZE           (4 * 1024)
#define PERIPHERAL_BASE_ADDR 0x3F000000
#define GPIO_BASE_ADDR       (PERIPHERAL_BASE_ADDR + 0x00200000)

typedef struct {
  unsigned long         gpio_base_addr;
  int                   memory_fd;
  void                  *map;
  volatile unsigned int *addr;
} rpi_gpio;

int SetupGPIO(rpi_gpio *gpio);
int ClearGPIO(rpi_gpio *gpio);
int unmapGPIO(rpi_gpio *gpio);
int   mapGPIO(rpi_gpio *gpio);
int BlinkLED(rpi_gpio *gpio);

#endif
