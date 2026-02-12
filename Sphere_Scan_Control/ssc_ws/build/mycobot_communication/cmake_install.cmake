# Install script for directory: /home/jhs/Desktop/Git/MyCobot280_ROS_Study/Sphere_Scan_Control/ssc_ws/src/mycobot_communication

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/jhs/Desktop/Git/MyCobot280_ROS_Study/Sphere_Scan_Control/ssc_ws/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/mycobot_communication/msg" TYPE FILE FILES
    "/home/jhs/Desktop/Git/MyCobot280_ROS_Study/Sphere_Scan_Control/ssc_ws/src/mycobot_communication/msg/MycobotAngles.msg"
    "/home/jhs/Desktop/Git/MyCobot280_ROS_Study/Sphere_Scan_Control/ssc_ws/src/mycobot_communication/msg/MycobotCoords.msg"
    "/home/jhs/Desktop/Git/MyCobot280_ROS_Study/Sphere_Scan_Control/ssc_ws/src/mycobot_communication/msg/MycobotSetAngles.msg"
    "/home/jhs/Desktop/Git/MyCobot280_ROS_Study/Sphere_Scan_Control/ssc_ws/src/mycobot_communication/msg/MycobotSetCoords.msg"
    "/home/jhs/Desktop/Git/MyCobot280_ROS_Study/Sphere_Scan_Control/ssc_ws/src/mycobot_communication/msg/MycobotGripperStatus.msg"
    "/home/jhs/Desktop/Git/MyCobot280_ROS_Study/Sphere_Scan_Control/ssc_ws/src/mycobot_communication/msg/MycobotPumpStatus.msg"
    "/home/jhs/Desktop/Git/MyCobot280_ROS_Study/Sphere_Scan_Control/ssc_ws/src/mycobot_communication/msg/MycobotSetEndType.msg"
    "/home/jhs/Desktop/Git/MyCobot280_ROS_Study/Sphere_Scan_Control/ssc_ws/src/mycobot_communication/msg/MycobotSetFreshMode.msg"
    "/home/jhs/Desktop/Git/MyCobot280_ROS_Study/Sphere_Scan_Control/ssc_ws/src/mycobot_communication/msg/MycobotSetToolReference.msg"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/mycobot_communication/srv" TYPE FILE FILES
    "/home/jhs/Desktop/Git/MyCobot280_ROS_Study/Sphere_Scan_Control/ssc_ws/src/mycobot_communication/srv/GetAngles.srv"
    "/home/jhs/Desktop/Git/MyCobot280_ROS_Study/Sphere_Scan_Control/ssc_ws/src/mycobot_communication/srv/SetAngles.srv"
    "/home/jhs/Desktop/Git/MyCobot280_ROS_Study/Sphere_Scan_Control/ssc_ws/src/mycobot_communication/srv/GetCoords.srv"
    "/home/jhs/Desktop/Git/MyCobot280_ROS_Study/Sphere_Scan_Control/ssc_ws/src/mycobot_communication/srv/SetCoords.srv"
    "/home/jhs/Desktop/Git/MyCobot280_ROS_Study/Sphere_Scan_Control/ssc_ws/src/mycobot_communication/srv/GripperStatus.srv"
    "/home/jhs/Desktop/Git/MyCobot280_ROS_Study/Sphere_Scan_Control/ssc_ws/src/mycobot_communication/srv/PumpStatus.srv"
    "/home/jhs/Desktop/Git/MyCobot280_ROS_Study/Sphere_Scan_Control/ssc_ws/src/mycobot_communication/srv/SetEndType.srv"
    "/home/jhs/Desktop/Git/MyCobot280_ROS_Study/Sphere_Scan_Control/ssc_ws/src/mycobot_communication/srv/SetFreshMode.srv"
    "/home/jhs/Desktop/Git/MyCobot280_ROS_Study/Sphere_Scan_Control/ssc_ws/src/mycobot_communication/srv/SetToolReference.srv"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/mycobot_communication/cmake" TYPE FILE FILES "/home/jhs/Desktop/Git/MyCobot280_ROS_Study/Sphere_Scan_Control/ssc_ws/build/mycobot_communication/catkin_generated/installspace/mycobot_communication-msg-paths.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/home/jhs/Desktop/Git/MyCobot280_ROS_Study/Sphere_Scan_Control/ssc_ws/devel/include/mycobot_communication")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/roseus/ros" TYPE DIRECTORY FILES "/home/jhs/Desktop/Git/MyCobot280_ROS_Study/Sphere_Scan_Control/ssc_ws/devel/share/roseus/ros/mycobot_communication")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/common-lisp/ros" TYPE DIRECTORY FILES "/home/jhs/Desktop/Git/MyCobot280_ROS_Study/Sphere_Scan_Control/ssc_ws/devel/share/common-lisp/ros/mycobot_communication")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/gennodejs/ros" TYPE DIRECTORY FILES "/home/jhs/Desktop/Git/MyCobot280_ROS_Study/Sphere_Scan_Control/ssc_ws/devel/share/gennodejs/ros/mycobot_communication")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  execute_process(COMMAND "/usr/bin/python3" -m compileall "/home/jhs/Desktop/Git/MyCobot280_ROS_Study/Sphere_Scan_Control/ssc_ws/devel/lib/python3/dist-packages/mycobot_communication")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python3/dist-packages" TYPE DIRECTORY FILES "/home/jhs/Desktop/Git/MyCobot280_ROS_Study/Sphere_Scan_Control/ssc_ws/devel/lib/python3/dist-packages/mycobot_communication")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/jhs/Desktop/Git/MyCobot280_ROS_Study/Sphere_Scan_Control/ssc_ws/build/mycobot_communication/catkin_generated/installspace/mycobot_communication.pc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/mycobot_communication/cmake" TYPE FILE FILES "/home/jhs/Desktop/Git/MyCobot280_ROS_Study/Sphere_Scan_Control/ssc_ws/build/mycobot_communication/catkin_generated/installspace/mycobot_communication-msg-extras.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/mycobot_communication/cmake" TYPE FILE FILES
    "/home/jhs/Desktop/Git/MyCobot280_ROS_Study/Sphere_Scan_Control/ssc_ws/build/mycobot_communication/catkin_generated/installspace/mycobot_communicationConfig.cmake"
    "/home/jhs/Desktop/Git/MyCobot280_ROS_Study/Sphere_Scan_Control/ssc_ws/build/mycobot_communication/catkin_generated/installspace/mycobot_communicationConfig-version.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/mycobot_communication" TYPE FILE FILES "/home/jhs/Desktop/Git/MyCobot280_ROS_Study/Sphere_Scan_Control/ssc_ws/src/mycobot_communication/package.xml")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/mycobot_communication" TYPE PROGRAM FILES "/home/jhs/Desktop/Git/MyCobot280_ROS_Study/Sphere_Scan_Control/ssc_ws/build/mycobot_communication/catkin_generated/installspace/mycobot_services.py")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/mycobot_communication" TYPE PROGRAM FILES "/home/jhs/Desktop/Git/MyCobot280_ROS_Study/Sphere_Scan_Control/ssc_ws/build/mycobot_communication/catkin_generated/installspace/mycobot_topics.py")
endif()

