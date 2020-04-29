
A javascript network simulator for the [disaster.radio](https://disaster.radio) routing protocol.

![](screenshot.png?raw=true)

This simulator comes in three parts,
* `router` - a full port of the disaster.radio firmware that can be run inside of a Linux system
* `simulator` - a node js script that creates a virtual network of disaster radio routers
* `visualizer` - a browser-based "visual simulator" that provides a visual representation of the simulated network

## Compile the firmware

First install dependencies for compiling the C++ firmware that is used by the simulator,

```
sudo apt update
sudo apt install build-essential libwebsocketpp-dev libboost_dev
```

Next, get the latest LoRaLayer2 library by running `fetch_deps.sh`,  
```
cd routers
./fetch_deps.sh
```

Then compile the firmware with,
```
make firmware
```

## Test the firmware

Start a single disaster.radio node by running,
```
./firmware
```
Connect to your virtual node by creating a PTY using socat, like so
```
socat PTY,link=./tty/N1,raw,echo=0 -
```
where `N1` corresponds to the ID of the node you wish to connect to.

## Running the simulator

Once the firmware has been compiled and test, you can run the simulator.

```
cd ..
npm install
./simulator.js
```

You can now play around with the network's configuration by modifying the options in `simulator.js`.   

The router firmware can be modified through the `routers/firmware.c` file, you'll need recompile it before re-running the simulator.

The default behavior is for the nodes to learn about their neighbors and for ~100s and then one node, chosen at random, may begin routing packets to other nodes.

If you'd like to know more about the default protocol being used by disaster.radio nodes, read [our wiki](https://github.com/sudomesh/disaster-radio/wiki/Protocol).

# Visual simulator
First install javascript dependencies, if you have not already,
```
npm install
```
Then, build the script,
```
npm run build
```

And, finally, start the server,
```
npm start
```
Be sure to also start `simulator.js` if you haven't already (see above), and open a browser to http://localhost:8000.

You can develop the server using,
```
npm run watch
```
# ToDo
* expand visual interface (e.g. choose which nodes send/receive packets, inspect metrics and routing tables)
* fix various bugs, https://github.com/sudomesh/disaster-radio-simulator/issues

# License and copyright
* Copyright 2020 Sudo Mesh
* javascript simulator is licensed AGPLv3
* `routers/*` is dual-licensed under both GPLv3 and AGPLv3
