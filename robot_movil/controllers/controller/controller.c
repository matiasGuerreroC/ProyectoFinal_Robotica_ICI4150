#include <webots/robot.h>
#include <webots/motor.h>
#include <webots/gps.h>
#include <webots/lidar.h>
#include <stdio.h>
#include <math.h>

#define TIME_STEP 32
#define NUM_WHEELS 4
#define MAX_SPEED 6.28

int main() {
  wb_robot_init();

  // Obtener motores
  const char *wheel_names[NUM_WHEELS] = {"wheel1", "wheel2", "wheel3", "wheel4"};
  WbDeviceTag wheels[NUM_WHEELS];
  for (int i = 0; i < NUM_WHEELS; i++) {
    wheels[i] = wb_robot_get_device(wheel_names[i]);
    wb_motor_set_position(wheels[i], INFINITY);
    wb_motor_set_velocity(wheels[i], 0.0);
  }

  // GPS
  WbDeviceTag gps = wb_robot_get_device("gps");
  wb_gps_enable(gps, TIME_STEP);

  // LIDAR
  WbDeviceTag lidar = wb_robot_get_device("lidar");
  wb_lidar_enable(lidar, TIME_STEP);

  int lidar_width = wb_lidar_get_horizontal_resolution(lidar);
  const int front_index = lidar_width / 2;

  // Control
  const double forward_speed = 3.0;
  const double turn_speed = 3.0;
  const double obstacle_threshold = 0.2;

  int turning = 0;
  int turn_steps = 40; // Ajusta si quieres que gire más/menos
  int current_turn = 0;

  while (wb_robot_step(TIME_STEP) != -1) {
    // Leer LIDAR
    const float *lidar_values = wb_lidar_get_range_image(lidar);
    float front_distance = lidar_values[front_index];

    // Leer GPS
    const double *pos = wb_gps_get_values(gps);
    double x = pos[0];
    double z = pos[2];

    printf("GPS: X=%.2f Z=%.2f\n", x, z);
    printf("LIDAR [Front]: %.2f m\n", front_distance);

    // Evitar obstáculo
    if (turning) {
      // Girar derecha
      wb_motor_set_velocity(wheels[0], turn_speed);
      wb_motor_set_velocity(wheels[1], -turn_speed);
      wb_motor_set_velocity(wheels[2], turn_speed);
      wb_motor_set_velocity(wheels[3], -turn_speed);
      current_turn++;

      if (current_turn >= turn_steps) {
        turning = 0;
        current_turn = 0;
      }
    } else if (front_distance < obstacle_threshold) {
      turning = 1; // Comienza a girar
    } else {
      // Avanzar recto
      for (int i = 0; i < NUM_WHEELS; i++) {
        wb_motor_set_velocity(wheels[i], forward_speed);
      }
    }
  }

  wb_robot_cleanup();
  return 0;
}