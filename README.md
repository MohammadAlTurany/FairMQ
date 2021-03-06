# FairMQ

C++ Message Queuing Library

## Dependencies

  * **Boost** (PUBLIC)
  * **FairLogger** (PUBLIC)
  * CMake (BUILD)
  * GTest (BUILD, optional, `tests`)
  * ZeroMQ (PRIVATE)
  * Msgpack (PRIVATE, optional, `nanomsg_transport`)
  * nanomsg (PRIVATE, optional, `nanomsg_transport`)
  * OFI (PRIVATE, optional, `ofi_transport`)
  * Protobuf (PRIVATE, optional, `ofi_transport`)
  * DDS (PRIVATE, optional, `dds_plugin`)

## Installation

```bash
git clone https://github.com/FairRootGroup/FairMQ
mkdir fairmq_build && cd fairmq_build
cmake -DCMAKE_INSTALL_PREFIX=./fairmq_install ../fairmq
cmake --build . --target install
```

If dependencies are not installed in standard system
directories, you can hint the installation location
via `-DCMAKE_PREFIX_PATH=...` or per dependency via
`-D{DEPENDENCY}_ROOT=...`. `{DEPENDENCY}` can be `GTEST`,
`BOOST`, `FAIRLOGGER`, `ZEROMQ`, `MSGPACK`, `NANOMSG`,
`OFI`, `PROTOBUF`, or `DDS` (`*_ROOT` variables can also
be environment variables).

## Usage

FairMQ ships as a CMake package, so in your `CMakeLists.txt` you can discover it like this:

```cmake
find_package(FairMQ)
```

If FairMQ is not installed in system directories, you can hint the installation:

```cmake
set(CMAKE_PREFIX_PATH /path/to/FairMQ_install_prefix ${CMAKE_PREFIX_PATH})
find_package(FairMQ)
```

`find_package(FairMQ)` will define an imported target `FairMQ::FairMQ` (An alias `FairRoot::FairMQ`
is also defined for backwards compatibility, but it is deprecated).

In order to succesfully compile and link against the `FairMQ::FairMQ` target,
you need to discover its public package dependencies, too.

```cmake
find_package(FairMQ)
find_package(FairLogger ${FairMQ_FairLogger_VERSION})
find_package(Boost ${FairMQ_Boost_VERSION} COMPONENTS ${FairMQ_BOOST_COMPONENTS})
```

Of course, feel free to customize the above commands to your needs.

Optionally, you can require certain FairMQ package components and a minimum version:

```cmake
find_package(FairMQ 1.1.0 COMPONENTS nanomsg_transport dds_plugin)
find_package(FairLogger ${FairMQ_FairLogger_VERSION})
find_package(Boost ${FairMQ_Boost_VERSION} COMPONENTS ${FairMQ_BOOST_COMPONENTS})
```

When building FairMQ, CMake will print a summary table of all available package components.

## CMake options

On command line:

  * `-DDISABLE_COLOR=ON` disables coloured console output.
  * `-DBUILD_TESTING=OFF` disables building of tests.
  * `-DBUILD_NANOMSG_TRANSPORT=ON` enables building of nanomsg transport.
  * `-DBUILD_OFI_TRANSPORT=ON` enables building of the experimental OFI transport.
  * `-DBUILD_DDS_PLUGIN=ON` enables building of the DDS plugin.
  * You can hint non-system installations for dependent packages, see the #Installation section above

After the `find_package(FairMQ)` call the following CMake variables are defined:

  * `${FairMQ_Boost_VERSION}` contains the minimum Boost version FairMQ requires.
  * `${FairMQ_Boost_COMPONENTS}` contains the list of Boost components FairMQ depends on.
  * `${FairMQ_FairLogger_VERSION}` contains the minimum FairLogger version FairMQ requires.
  * ... TODO

## Documentation

Standard [FairRoot](https://github.com/FairRootGroup/FairRoot) is running all the different analysis tasks within one process. FairMQ ([Message Queue](http://en.wikipedia.org/wiki/Message_queue)) allows starting tasks on different processes and provides the communication layer between these processes.

1. [Device](docs/Device.md#1-device)
   1. [Topology](docs/Device.md#11-topology)
   2. [Communication Patterns](docs/Device.md#12-communication-patterns)
   3. [State Machine](docs/Device.md#13-state-machine)
   4. [Multiple devices in the same process](docs/Device.md#15-multiple-devices-in-the-same-process)
2. [Transport Interface](docs/Transport.md#2-transport-interface)
   1. [Message](docs/Transport.md#21-message)
      1. [Ownership](docs/Transport.md#211-ownership)
   2. [Channel](docs/Transport.md#22-channel)
   3. [Poller](docs/Transport.md#23-poller)
3. [Configuration](docs/Configuration.md#3-configuration)
    1. [Device Configuration](docs/Configuration.md#31-device-configuration)
    2. [Communication Channels Configuration](docs/Configuration.md#32-communication-channels-configuration)
        1. [JSON Parser](docs/Configuration.md#321-json-parser)
        2. [SuboptParser](docs/Configuration.md#322-suboptparser)
    3. [Introspection](docs/Configuration.md#33-introspection)
4. [Development](docs/Development.md#4-development)
   1. [Testing](docs/Development.md#41-testing)
5. [Logging](docs/Logging.md#5-logging)
   1. [Log severity](docs/Logging.md#51-log-severity)
   2. [Log verbosity](docs/Logging.md#52-log-verbosity)
   3. [Color for console output](docs/Logging.md#53-color)
   4. [File output](docs/Logging.md#54-file-output)
   5. [Custom sinks](docs/Logging.md#55-custom-sinks)
6. [Examples](docs/Examples.md#6-examples)

## License

GNU Lesser General Public Licence (LGPL) version 3, see [LICENSE](LICENSE).

Copyright (C) 2013-2018 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH
