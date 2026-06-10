_This project has been created as part of the 42 curriculum by ide-abre, jde-carv._

# Description

Cub3d is a game that renders a first-person perspective 3D maze using ray-casting. The technique involves calculating the distance between the player and a segment of a wall within their field of view, along with the player's angle and direction.

Each segment is called a ray. With every ray calculated, it is possible to render an image proportional to the player's distance and angle, creating a 3D effect.

# Instructions

Cub3d depends on the MiniLibX library to run. Since the subject does not specify how the library should be imported, we have shipped it as a `.tgz` file inside the `minilibx` folder to simplify setup.

```bash
cd minilibx
tar -xvf minilibx-linux.tgz
make
```

In the root folder, to compile the game:
```bash
make
```

To run:
```bash
./cub3d <map>
```

The map file must have a `.cub` extension and follow the pattern described in the subject.

# Resources
* [Pikuma's course on Raycasting Engine Programming with C](https://pikuma.com/courses/raycasting-engine-tutorial-algorithm-javascript)
* [MiniLibX documentation](https://harm-smits.github.io/42docs/libs/minilibx)