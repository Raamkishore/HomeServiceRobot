# HomeServiceRobot

## Building workspace

Create a workspace named "catkin_ws".

```
mkdir ~/catkin_ws
```

Clone this repository anywhere and move the "src" directory to the catkin_ws directory.

```
git clone https://github.com/Raamkishore/HomeServiceRobot
```

Get into the src directory.

```
cd ~/catkin_ws/src
```

Use the below command inside the src directory.

```
catkin_init_workspace
```

Go to the catkin_ws directory and build the workspace. (You can directly use the below commands after the previous command)

```
cd ..
catkin_make
```

## Running the project

Follow the below commands to run the project.

```
cd /src/scripts
chmod +x home_service.sh
./ home_service.sh
```

You can see that a robot is moving towards a marker (pickup location), waits for some time to simulate a pickup, the marker is hidden so as to show that the robot has picked up the package and the robot starts moving towards the drop location where the package has to be dropped. Once the robot reaches the drop location, the marker will be shown to simulate that the robot has dropped the package.

This is a best use case for robots to be deployed in places like warehouses and industries where the objects have to be moved frequently.
