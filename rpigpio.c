#include "rpigpio.h"

int BlinkLED() {
  int n = 5;
  struct bcm2835_peripheral gpio = {GPIO_BASE};

  if(MapPeripherals(&gpio)) {
    return 1;
  }

  /* Init GPIO23 */
  *(gpio.addr + 2)  = 0x00000200;

  while(n) {
    *(gpio.addr + 7)  = 0x00800000;
    usleep(500000);
    *(gpio.addr + 10) = 0x00800000;
    usleep(500000);

    n -= 1;
  }

  /* cleanup */
  *(gpio.addr + 10) = 0x00800000;
  *(gpio.addr + 2)  = 0x00000000;

  UnmapPeripherals(&gpio);
  printf("ok\n");

  return 0;
}

int MapPeripherals(struct bcm2835_peripheral *p) {
  p->mem_fd = open("/dev/mem", O_RDWR|O_SYNC);

  if(p->mem_fd < 0) {
    printf("Failed to open /dev/mem, try checking permissions.\n");
    return 1;
  }

  p->map = mmap(
    NULL,
    BLOCK_SIZE,
    PROT_READ|PROT_WRITE,
    MAP_SHARED,
    p->mem_fd,
    p->addr_p
  );

  if(p->map == MAP_FAILED) {
    perror("mmap");
    return 1;
  }

  p->addr = (volatile unsigned int *)p->map;

  return 0;
}

int UnmapPeripherals(struct bcm2835_peripheral *p) {
  munmap(p->map, BLOCK_SIZE);
  close(p->mem_fd);

  return 0;
}
