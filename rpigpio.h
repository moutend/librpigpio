#ifndef RPIGPIO_H
#define RPIGPIO_H

#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>

#define PERIPHERALS_BASE 0x3F000000
#define GPIO_BASE        (PERIPHERALS_BASE + 0x00200000)
#define BLOCK_SIZE       (4 * 1024)

struct bcm2835_peripheral {
  unsigned long         addr_p;
  int                   mem_fd;
  void                  *map;
  volatile unsigned int *addr;
};

int UnmapPeripherals(struct bcm2835_peripheral *p);
int MapPeripherals(struct bcm2835_peripheral *p);
int BlinkLED(void);

#endif
