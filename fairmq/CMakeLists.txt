################################################################################
# Copyright (C) 2012-2018 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

####################
# external plugins #
####################
if(BUILD_DDS_PLUGIN)
  add_subdirectory(plugins/DDS)
endif()


############################
# preprocessor definitions #
############################
if(BUILD_NANOMSG_TRANSPORT)
  add_definitions(-DBUILD_NANOMSG_TRANSPORT)
endif()
if(BUILD_OFI_TRANSPORT)
  add_definitions(-DBUILD_OFI_TRANSPORT)
endif()


##################
# subdirectories #
##################
# add_subdirectory(shmem/prototype)
if(BUILD_OFI_TRANSPORT)
  add_subdirectory(ofi)
endif()


##########################
# libFairMQ header files #
##########################
set(FAIRMQ_HEADER_FILES
    DeviceRunner.h
    EventManager.h
    FairMQChannel.h
    FairMQDevice.h
    FairMQLogger.h
    FairMQMessage.h
    FairMQParts.h
    FairMQPoller.h
    FairMQUnmanagedRegion.h
    FairMQSocket.h
    FairMQStateMachine.h
    FairMQTransportFactory.h
    Tools.h
    Transports.h
    devices/FairMQBenchmarkSampler.h
    devices/FairMQMerger.h
    devices/FairMQMultiplier.h
    devices/FairMQProxy.h
    devices/FairMQSink.h
    devices/FairMQSplitter.h
    options/FairMQParser.h
    options/FairMQProgOptions.h
    options/FairMQSuboptParser.h
    options/FairProgOptions.h
    options/FairProgOptionsHelper.h
    Plugin.h
    PluginManager.h
    PluginServices.h
    plugins/Builtin.h
    plugins/Control.h
    runFairMQDevice.h
    StateMachine.h
    shmem/FairMQMessageSHM.h
    shmem/FairMQPollerSHM.h
    shmem/FairMQUnmanagedRegionSHM.h
    shmem/FairMQSocketSHM.h
    shmem/FairMQTransportFactorySHM.h
    shmem/Common.h
    shmem/Manager.h
    shmem/Monitor.h
    shmem/Region.h
    tools/CppSTL.h
    tools/Network.h
    tools/Process.h
    tools/Strings.h
    tools/Unique.h
    tools/Version.h
    zeromq/FairMQMessageZMQ.h
    zeromq/FairMQPollerZMQ.h
    zeromq/FairMQUnmanagedRegionZMQ.h
    zeromq/FairMQSocketZMQ.h
    zeromq/FairMQTransportFactoryZMQ.h
)

if(BUILD_NANOMSG_TRANSPORT)
    set(FAIRMQ_HEADER_FILES ${FAIRMQ_HEADER_FILES}
        nanomsg/FairMQMessageNN.h
        nanomsg/FairMQPollerNN.h
        nanomsg/FairMQUnmanagedRegionNN.h
        nanomsg/FairMQSocketNN.h
        nanomsg/FairMQTransportFactoryNN.h
    )
endif()

if(BUILD_OFI_TRANSPORT)
    set(FAIRMQ_HEADER_FILES ${FAIRMQ_HEADER_FILES}
        ofi/Context.h
        ofi/Message.h
        ofi/Poller.h
        ofi/Socket.h
        ofi/TransportFactory.h
    )
endif()

##########################
# libFairMQ source files #
##########################
set(FAIRMQ_SOURCE_FILES
    DeviceRunner.cxx
    FairMQChannel.cxx
    FairMQDevice.cxx
    FairMQLogger.cxx
    FairMQMessage.cxx
    FairMQPoller.cxx
    FairMQSocket.cxx
    FairMQStateMachine.cxx
    FairMQTransportFactory.cxx
    devices/FairMQBenchmarkSampler.cxx
    devices/FairMQMerger.cxx
    devices/FairMQMultiplier.cxx
    devices/FairMQProxy.cxx
    # devices/FairMQSink.cxx
    devices/FairMQSplitter.cxx
    options/FairMQParser.cxx
    options/FairMQProgOptions.cxx
    options/FairMQSuboptParser.cxx
    options/FairProgOptions.cxx
    Plugin.cxx
    PluginManager.cxx
    PluginServices.cxx
    plugins/Control.cxx
    StateMachine.cxx
    shmem/FairMQMessageSHM.cxx
    shmem/FairMQPollerSHM.cxx
    shmem/FairMQUnmanagedRegionSHM.cxx
    shmem/FairMQSocketSHM.cxx
    shmem/FairMQTransportFactorySHM.cxx
    shmem/Manager.cxx
    shmem/Monitor.cxx
    shmem/Region.cxx
    zeromq/FairMQMessageZMQ.cxx
    zeromq/FairMQPollerZMQ.cxx
    zeromq/FairMQUnmanagedRegionZMQ.cxx
    zeromq/FairMQSocketZMQ.cxx
    zeromq/FairMQTransportFactoryZMQ.cxx
)

if(BUILD_NANOMSG_TRANSPORT)
    set(FAIRMQ_SOURCE_FILES ${FAIRMQ_SOURCE_FILES}
        nanomsg/FairMQMessageNN.cxx
        nanomsg/FairMQPollerNN.cxx
        nanomsg/FairMQUnmanagedRegionNN.cxx
        nanomsg/FairMQSocketNN.cxx
        nanomsg/FairMQTransportFactoryNN.cxx
    )
endif()

if(BUILD_OFI_TRANSPORT)
    set(FAIRMQ_SOURCE_FILES ${FAIRMQ_SOURCE_FILES}
        ofi/Context.cxx
        ofi/Message.cxx
        ofi/Poller.cxx
        ofi/Socket.cxx
        ofi/TransportFactory.cxx
    )
endif()


###################
# configure files #
###################
configure_file(${CMAKE_SOURCE_DIR}/fairmq/run/startMQBenchmark.sh.in ${CMAKE_BINARY_DIR}/bin/startMQBenchmark.sh)
configure_file(${CMAKE_SOURCE_DIR}/fairmq/run/benchmark.json ${CMAKE_BINARY_DIR}/bin/config/benchmark.json)
configure_file(${CMAKE_SOURCE_DIR}/fairmq/options/startConfigExample.sh.in
               ${CMAKE_BINARY_DIR}/bin/startConfigExample.sh)


#################################
# define libFairMQ build target #
#################################
add_library(FairMQ SHARED
  ${FAIRMQ_SOURCE_FILES}
  ${FAIRMQ_HEADER_FILES} # for IDE integration
)

#######################
# include directories #
#######################
target_include_directories(FairMQ
    PUBLIC # consumers inherit public include directories
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}>
    $<INSTALL_INTERFACE:include/fairmq>
    $<INSTALL_INTERFACE:include>
)

##################
# link libraries #
##################
if(BUILD_NANOMSG_TRANSPORT)
  set(NANOMSG_DEPS nanomsg msgpackc)
endif()
if(BUILD_OFI_TRANSPORT)
  set(OFI_DEPS OFI::libfabric protobuf::libprotobuf $<TARGET_OBJECTS:OfiTransport>)
endif()
target_link_libraries(FairMQ
    INTERFACE # only consumers link against interface dependencies

    PUBLIC # libFairMQ AND consumers of libFairMQ link aginst public dependencies
    dl
    Boost::boost
    Boost::program_options
    Boost::thread
    Boost::system
    Boost::filesystem
    Boost::regex
    Boost::date_time
    Boost::signals
    FairLogger::FairLogger

    PRIVATE # only libFairMQ links against private dependencies
    libzmq
    ${NANOMSG_DEPS}
    ${OFI_DEPS}
)
set_target_properties(FairMQ PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}"
)

###############
# executables #
###############

add_executable(bsampler run/runBenchmarkSampler.cxx)
target_link_libraries(bsampler FairMQ)

add_executable(merger run/runMerger.cxx)
target_link_libraries(merger FairMQ)

add_executable(multiplier run/runMultiplier.cxx)
target_link_libraries(multiplier FairMQ)

add_executable(proxy run/runProxy.cxx)
target_link_libraries(proxy FairMQ)

add_executable(sink run/runSink.cxx)
target_link_libraries(sink FairMQ)

add_executable(splitter run/runSplitter.cxx)
target_link_libraries(splitter FairMQ)

add_executable(runConfigExample options/runConfigEx.cxx)
target_link_libraries(runConfigExample FairMQ)

add_executable(shmmonitor shmem/runMonitor.cxx)
target_link_libraries(shmmonitor FairMQ)

add_executable(uuidGen run/runUuidGenerator.cxx)
target_link_libraries(uuidGen FairMQ)

###########
# install #
###########
install(
    TARGETS # FairMQFull, tests are not installed
    FairMQ
    bsampler
    merger
    multiplier
    proxy
    sink
    splitter
    shmmonitor
    uuidGen

    EXPORT ${PROJECT_EXPORT_SET}
    LIBRARY DESTINATION ${PROJECT_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${PROJECT_INSTALL_BINDIR}
)

# preserve relative path and prepend fairmq
foreach(HEADER ${FAIRMQ_HEADER_FILES})
    get_filename_component(_path ${HEADER} DIRECTORY)
    file(TO_CMAKE_PATH ${PROJECT_INSTALL_INCDIR}/${_path} _destination)
    install(FILES ${HEADER}
        DESTINATION ${_destination}
    )
endforeach()
