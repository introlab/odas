ODAS ![Analytics](https://ga-beacon.appspot.com/UA-27707792-4/github-main?pixel) 
=======

ODAS stands for Open embeddeD Audition System. This is a library dedicated to perform sound source localization, tracking, separation and post-filtering. ODAS is coded entirely in C, for more portability, and is optimized to run easily on low-cost embedded hardware. ODAS is free and open source.

[![ODAS Demonstration](https://img.youtube.com/vi/n7y2rLAnd5I/0.jpg)](https://youtu.be/n7y2rLAnd5I)

# Getting started

## Installation

### Prerequesites

The new ODAS version only requires the external library FFTW:

```
sudo apt-get install libfftw3-dev
```

### Installing

Clone the project:

```
git clone https://github.com/introlab/odas.git
```

Create a folder to build the project:

```
cd odas
mkdir build
cd build
```

Run CMake (in the build directory):

```
cmake ../
```

Compile the project:

```
make
```

## Configuration

Each microphone array has a different geometry, and this needs to be configured. Moreover, additional parameters need to be specified to ensure the system will process the signals from a microphone array properly. A tutorial is being written and will be available soon to explain what are the important steps to follow to configure your system. Some prewritten configuration files (in JSON format) are also available to work with existing hardware.

## Sockets

ODAS works as a server with many sockets to get inputs and outputs. The ports from and to which data are read are defined in a socket file (in JSON format).

## Running

### Read the content of a file, and return track sources results to a file

You must define the port that will receive the RAW audio. Typically you would use a RAW file format, with sample in signed 16-bits format, little endian, and the number of channels that corresponds to the number of microphones. Here, suppose the chosen port is 5001, and say the RAW file is `myAudio.raw`.

You must define the port that will send the tracked source results. The results is formatted in JSON. Here, suppose the chosen port is 6002, and the results will be stored in `tracked.json`.

All other ununed ports are set to 0.

Suppose you are using a UMA8 microphone array from MiniDSP, you can use the following configuration file:

```
settings/config/minidsp/uma8.json
```

Now the following socket file defines the ports used in this example:

```
settings/socket/sst.json
```

Then you can launch odas:

```
bin/core -c settings/config/minidsp/uma8.json -s settings/socket/sst.json 
```

You should see something like this:

```
 ODAS (Open embeddeD Audition System)

 Author:      Francois Grondin
 Email:       fgrondin@mit.edu
 Website:     odas.io
 Version:     3.0

 Initializing settings.... [Done]
 Initializing configs..... [Done]
 Terminating settings..... [Done]
 Initializing objects..... [Done]
 Terminating configs...... [Done]
 Processing in progress... 
```

The system is now awaiting for RAW data to process.
Open a new terminal, and type the following command:

```
cat myAudio.raw | netcat localhost 5001
```

This will send the RAW data to ODAS via the port 5001.

Now open another terminal, and type the following command:

```
socketcat -p 6002 > tracked.json
```

This will output the result in the `tracked.json` file. Once the whole RAW file is processed, the sockets should close, and ODAS terminate.

### Read from a sound card, and return track sources results to terminal

Suppose you are still using UMA8 microphone array from MiniDSP. We use the same configuration and socket JSON files as in the previous example.

This sound card provides us with 8 channels, though only the first 7 are connected to microphones (the last one is left silence). Moreover, the sample format is provided in signed 32-bit little endian, while ODAS expects 16-bit little endians. To solve this formatting and channels mapping issue, let's use some tools provided by ODAS, that are the `formatter` and the `mapper`.

You first launch odas:

```
bin/core -c settings/config/minidsp/uma8.json -s settings/socket/sst.json 
```

Then you launch the another terminal that will receive the results:

```
bin/socketcat -p 6002
```

Finally, you pipeline the audio stream from arecord to ODAS, going through the tools:

```
arecord --device=hw:1,0 --channels=8 --rate=48000 --format=S32_LE --file-type=raw | bin/mapper -i 8 -o "0-6" -b s32le | bin/formatter -i s32le -o s16le | netcat localhost 5001
```

You should see the tracking results appear live in the last terminal.