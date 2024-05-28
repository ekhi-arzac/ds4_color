#include <errno.h>
#include <fcntl.h>
#include <linux/hidraw.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <time.h>
#include <unistd.h>

// Define the path to your DualShock 4 controller's hidraw device
#define HIDRAW_DEVICE "/dev/hidrawX"
#define SLEEP_DURATION 100 // 10 milliseconds

typedef struct {
  unsigned char r;
  unsigned char g;
  unsigned char b;
} color_t;

int set_light_bar_color(int fd, color_t color) {
  unsigned char buf[32];
  memset(buf, 0, sizeof(buf));

  buf[0] = 0x05;    // Report ID for setting LED color on DS4
  buf[1] = 0xFF;    // Flags (0xFF to apply all settings)
  buf[6] = color.r; // Red value
  buf[7] = color.g; // Green value
  buf[8] = color.b; // Blue value

  if (write(fd, buf, sizeof(buf)) != sizeof(buf)) {
    perror("Failed to write to hidraw device");
    return errno;
  }

  return 0;
}

color_t hsv_to_rgb(float h, float s, float v) {
  float r, g, b;
  int i = (int)(h * 6);
  float f = h * 6 - i;
  float p = v * (1 - s);
  float q = v * (1 - f * s);
  float t = v * (1 - (1 - f) * s);

  switch (i % 6) {
  case 0:
    r = v;
    g = t;
    b = p;
    break;
  case 1:
    r = q;
    g = v;
    b = p;
    break;
  case 2:
    r = p;
    g = v;
    b = t;
    break;
  case 3:
    r = p;
    g = q;
    b = v;
    break;
  case 4:
    r = t;
    g = p;
    b = v;
    break;
  case 5:
    r = v;
    g = p;
    b = q;
    break;
  }

  color_t color = {(unsigned char)(r * 255), (unsigned char)(g * 255),
                   (unsigned char)(b * 255)};
  return color;
}

void sleep_ms(int milliseconds) {
  struct timespec req, rem;
  req.tv_sec = milliseconds / 1000;
  req.tv_nsec = (milliseconds % 1000) * 1000000L;
  nanosleep(&req, &rem);
}

int main() {
  int fd;
  float hue = 0.0;

  fd = open(HIDRAW_DEVICE, O_RDWR | O_NONBLOCK);
  if (fd < 0) {
    perror("Failed to open hidraw device");
    return errno;
  }

  while (1) {
    color_t color = hsv_to_rgb(hue, 1.0, 1.0);
    if (set_light_bar_color(fd, color) != 0) {
      fprintf(stderr, "Failed to set light bar color\n");
      close(fd);
      return 1;
    }

    hue += 0.01;
    if (hue >= 1.0) {
      hue = 0.0;
    }

    sleep_ms(SLEEP_DURATION);
  }

  close(fd);
  return 0;
}
