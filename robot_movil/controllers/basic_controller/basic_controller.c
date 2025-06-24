#include <webots/robot.h>
#include <webots/lidar.h>
#include <webots/gps.h>
#include <stdio.h>

#define TIME_STEP 32

int main() {
  wb_robot_init();

  // Obtener dispositivos
  WbDeviceTag lidar = wb_robot_get_device("lidar");
  wb_lidar_enable(lidar, TIME_STEP);
  int lidar_width = wb_lidar_get_horizontal_resolution(lidar);
  printf("LIDAR resolution: %d\n", lidar_width);

  WbDeviceTag gps = wb_robot_get_device("gps");
  wb_gps_enable(gps, TIME_STEP);

  // Loop de simulación
  while (wb_robot_step(TIME_STEP) != -1) {
    // Leer posición
    const double *position = wb_gps_get_values(gps);
    printf("GPS: [X: %.2f, Y: %.2f, Z: %.2f]\n", position[0], position[1], position[2]);

    // Leer distancias del LIDAR
    const float *lidar_values = wb_lidar_get_range_image(lidar);
    printf("LIDAR sample [0]: %.2f m | sample [mid]: %.2f m | sample [end]: %.2f m\n",
           lidar_values[0],
           lidar_values[lidar_width / 2],
           lidar_values[lidar_width - 1]);

    printf("----------------------\n");
  }

  wb_robot_cleanup();
  return 0;
}
