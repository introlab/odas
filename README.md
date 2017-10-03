# ODAS

ODAS stands for Open embeddeD Audition System. This is a library dedicated to perform sound source localization, tracking, separation and post-filtering. ODAS is coded entirely in C, for more portability, and is optimized to run easily on low-cost embedded hardware. ODAS is free and open source.

## Prerequisites

You will need CMake, GCC and the following external libraries:

FFTW:

```
sudo apt-get install libfftw3-dev
```

LibConfig:

```
sudo apt-get install libconfig-dev
```

ALSA:

```
sudo apt-get install libasound2-dev
```

## Installing

Clone the project:

```
git clone https://github.com/introlab/odas.git --branch=dev
```

Create a folder to build the project:

```
mkdir build
cd build
```

Run CMake:

```
cmake ../
```

Compile the project:

```
make
```

## Using ODAS with existing microphone arrays

### ReSpeaker

Connect the soundcard via USB to the computer. Then type the following command to see where is located the ReSpeaker:

```
arecord -l
```

You should get something like this:

```
**** List of CAPTURE Hardware Devices ****
card 1: MID [HDA Intel MID], device 0: ALC662 rev1 Analog [ALC662 rev1 Analog]
  Subdevices: 1/1
  Subdevice #0: subdevice #0
card 1: MID [HDA Intel MID], device 2: ALC662 rev1 Alt Analog [ALC662 rev1 Alt Analog]
  Subdevices: 1/1
  Subdevice #0: subdevice #0
card 3: Array [ReSpeaker Microphone Array], device 0: USB Audio [USB Audio]
  Subdevices: 1/1
  Subdevice #0: subdevice #0
```

In this case, the soundcard ID is 3, and the device ID is 0. Open the file config/respeaker.cfg, and set in the section "raw" the soundcard ID and device ID:

```
interface: {
    type = "soundcard";
    card = 3;
    device = 0;
}
```

To run ODAS with ReSpeaker, and type in the following command:

```
bin/odascore -c config/respeaker.cfg
```

You should get the following output:

```
{
    "timeStamp": 623,
    "src": [
        { "id": 5, "x": 0.661, "y": 0.343, "z": 0.667 },
        { "id": 0, "x": 0.000, "y": 0.000, "z": 0.000 },
        { "id": 0, "x": 0.000, "y": 0.000, "z": 0.000 },
        { "id": 0, "x": 0.000, "y": 0.000, "z": 0.000 }
    ]
}
```

The timeStamp is a unique ID in time to identify each frame. The tracked sources ID correspond to 0 if there is no tracked source, or something else (in this example 5) when a source is tracked. The xyz directional coordinates are then given for the tracked source. In this case, four tracked sources are displayed (1 active, 3 free spots where ID=0) because the system is configured to track up to four sources simultaneously.

### XMOS xCore Array Microphone

Connect the soundcard via USB to the computer. Then type the following command to see where is located the XMOS xCore Array Microphone:

```
arecord -l
```

You should get something like this:

```
**** List of CAPTURE Hardware Devices ****
card 1: MID [HDA Intel MID], device 0: ALC662 rev1 Analog [ALC662 rev1 Analog]
  Subdevices: 1/1
  Subdevice #0: subdevice #0
card 1: MID [HDA Intel MID], device 2: ALC662 rev1 Alt Analog [ALC662 rev1 Alt Analog]
  Subdevices: 1/1
  Subdevice #0: subdevice #0
card 3: UAC20 [XMOS Microphone Array UAC2.0], device 0: USB Audio [USB Audio]
  Subdevices: 1/1
  Subdevice #0: subdevice #0
```

In this case, the soundcard ID is 3, and the device ID is 0. Open the file config/xmos.cfg, and set in the section "raw" the soundcard ID and device ID:

```
interface: {
    type = "soundcard";
    card = 3;
    device = 0;
}
```

To run ODAS with XMOS, and type in the following command:

```
bin/odascore -c config/xmos.cfg
```

You should get the following output:

```
{
    "timeStamp": 623,
    "src": [
        { "id": 5, "x": 0.661, "y": 0.343, "z": 0.667 },
        { "id": 0, "x": 0.000, "y": 0.000, "z": 0.000 },
        { "id": 0, "x": 0.000, "y": 0.000, "z": 0.000 },
        { "id": 0, "x": 0.000, "y": 0.000, "z": 0.000 }
    ]
}
```

The timeStamp is a unique ID in time to identify each frame. The tracked sources ID correspond to 0 if there is no tracked source, or something else (in this example 5) when a source is tracked. The xyz directional coordinates are then given for the tracked source. In this case, four tracked sources are displayed (1 active, 3 free spots where ID=0) because the system is configured to track up to four sources simultaneously.