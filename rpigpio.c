#include "rpigpio.h"

int SetupGPIO(rpi_gpio *gpio) {
  int is_mapped;

  gpio->gpio_base_addr = GPIO_BASE_ADDR;

  is_mapped = mapGPIO(gpio);

  if(is_mapped) {
    return is_mapped;
  }

  return 0;
}
int BlinkLED(rpi_gpio *gpio) {
  int n = 5;

  *(gpio->addr + 2)  = 0x00000200;

  while(n) {
    *(gpio->addr + 7)  = 0x00800000;
    usleep(500000);
    *(gpio->addr + 10) = 0x00800000;
    usleep(500000);

    n -= 1;
  }

  return 0;
}

int ClearGPIO(rpi_gpio *gpio) {
  *(gpio->addr + 10) = 0x00800000;
  *(gpio->addr + 2)  = 0x00000000;

  unmapGPIO(gpio);

  return 0;
}

int mapGPIO(rpi_gpio *gpio) {
  gpio->memory_fd = open("/dev/mem", O_RDWR|O_SYNC);

  if(gpio->memory_fd < 0) {
    perror("Failed to open /dev/mem\n");
    return 1;
  }

  gpio->map = mmap(
    NULL,
    BLOCK_SIZE,
    PROT_READ|PROT_WRITE,
    MAP_SHARED,
    gpio->memory_fd,
    gpio->gpio_base_addr
  );

  if(gpio->map == MAP_FAILED) {
    perror("mmap");
    return 1;
  }

  gpio->addr = (volatile unsigned int *)gpio->map;

  return 0;
}

int unmapGPIO(rpi_gpio *gpio) {
  munmap(gpio->map, BLOCK_SIZE);
  close(gpio->memory_fd);

  return 0;
}
