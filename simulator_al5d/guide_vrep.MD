# AL5D-LYNX SIMULATOR

V-rep based simulator for robotic arm AL5D-LYNX

1. Access v-rep website: http://www.coppeliarobotics.com/. PRO EDU and PLAYER versions are available for free!
2. Access youtube channel: https://www.youtube.com/watch?v=QQ3M55bXjQw

## RUNNING V-REP 
1. Open Terminal
2. Go to VREP installation folder
3. Execute vrep.sh: 

`user@host$ ./vrep.sh`

## USING REMOTE API

1. To enable the remote API on the server side (i.e. on V-REP's side), make sure the remote API plugin was successfully loaded at V-REP start-up (you can inspect the terminal for information related to plugin loading) .

2. Go to Main Script of your scene. In the funcion *sysCall_init()*, call *simRemoteApi.start(19999)*. The socket port is 19999 in this case.

```
function sysCall_init()
    sim.handleSimulationStart()
    sim.openModule(sim.handle_all)
    sim.handleGraph(sim.handle_all_except_explicit,0)
    simRemoteApi.start(19999)
end
```
3. Comment any code of the model in the function *sysCall_actuation()*.
4. Create a file main.cpp and import the remote api file.
```

extern "C" {
  #include "remoteApi/extApi.h"
}

```
5. To use the remote API functionality in your C/C++ application, just include following C-language files in your project:

- extApi.h 

- extApi.c 

- extApiPlatform.h (contains platform specific code)

- extApiPlatform.c (contains platform specific code)

Above files are located in V-REP's installation directory, under programming/remoteApi. 

6. To enable the remote API on the client side (i.e. your application), call **simxStart**.

```
//Example
int clientID=simxStart((simxChar*)serverIP.c_str(),serverPort,true,true,3000,5);

```
![This page](http://www.coppeliarobotics.com/helpFiles/en/remoteApiFunctions.htm) This page lists and describes all supported C/C++ remote API functions
