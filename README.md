# 2025_sim

```
mkdir -p ros2_ws/src
cd ros2_ws/src
```

```
git clone https://github.com/motii8128/2025_sim.git
```


```
cd ..
colcon build --symlink-install
```

```
. install/setup.bash
```

```
ros2 launch gz_world_launcher sim.launch.xml
```
