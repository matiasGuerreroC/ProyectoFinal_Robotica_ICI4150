# ProyectoFinal_Robotica_ICI4150
Repositorio para el desarrollo y documentación del proyecto final del curso Robótica y Sistemas Autónomos (ICI4150) de la PUCV, semestre 2025-01.

Integrantes del grupo: 
- Cesár Cristobal Anabalón Navarrete
- Ulysses Edward Barreto Horn
- Felipe Jesus Andres Bravo Romo
- Matias Ignacio Guerrero Castillo
- Fabiana Andrea Piña Vera

### Instrucciones para ejecutar el simulador en Webots

1. **Abrir el proyecto en Webots**

   * Abre Webots y carga el archivo del mundo:

     ```
     worlds/proyecto.wbt
     ```

2. **Compilar el controlador**

   * En Webots, asegúrate de que el robot esté usando el controlador `controlador` ubicado en:

     ```
     controllers/controlador/controlador.c
     ```

3. **Ejecutar la simulación**

   * Haz clic en el botón de **Play (▶️)** para comenzar la simulación.
   * El robot iniciará el movimiento, detectará obstáculos con LIDAR y sensores, construirá un mapa y planificará una ruta usando el algoritmo **A\***.

4. **Requisitos y dependencias**

   * Webots versión 2023 o superior.
   * No se requieren librerías externas: todo el controlador está implementado en **C** utilizando las API de Webots.

5. **Estructura del proyecto**

   ```
   ProyectoFinal_Robotica_ICI4150/
   ├── controllers/
   │   └── controlador/         ← Código C del robot
   │       └── controlador.c
   ├── worlds/
   │   └── proyecto.wbt        ← Mundo principal del proyecto
   └── README.md               ← Instrucciones y detalles del proyecto
   ```
