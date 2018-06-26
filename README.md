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

## Running

### Read the content of a file, and return track sources results to a file

You must define the port that will receive the RAW audio. Typically you would use a RAW file format, with sample in signed 16-bits format, little endian, and the number of channels that corresponds to the number of microphones. Here, suppose the chosen port is 5000, and say the RAW file is `myAudio.raw`.

You must define the port that will send the tracked source results. The results is formatted in JSON. Here, suppose the chosen port is 6000, and the results will be stored in `tracked.json`.

You get the following section of code in the configuration file (let's call it `myConfig.json`):

```
    ...

    "socket":
    {

        "raw": 5000,
        "targets": 0,
        
        "pots": 0,
        "tracks": 6000,
        "seps": 0,
        "pfs": 0

    },

    ...

```

Then you can launch odas:

```
bin/core -c myConfig.json
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
cat myAudio.raw | netcat localhost 5000
```

This will send the RAW data to ODAS via the port 5000.

Now open another terminal, and type the following command:

```
netcat localhost 6000 > tracked.json
```

This will output the result in the `tracked.json` file. Once the whole RAW file is processed, the sockets should close, and ODAS terminate.