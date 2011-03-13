CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )
CMAKE_POLICY( SET CMP0015 NEW )

#include directories
SET( IRRLICHT_INCLUDE_DIR "../irrlicht/include" PATH )
SET( BULLET_INCLUDE_DIR "../bullet/src" PATH )
SET( LUA_INCLUDE_DIR "../lua/src" PATH )
SET( BOOST_INCLUDE_DIR "../boost" PATH )

#linker directories
SET( IRRLICHT_LIB_DIR "../irrlicht/lib/Linux" PATH )
SET( BULLET_LIB_DIR "../bullet/lib" PATH )
SET( LUA_LIB_DIR "../boost/lib" PATH )
SET( BOOST_LIB_DIR "../lua/src" PATH )

INCLUDE_DIRECTORIES( ${IRRLICHT_INCLUDE_DIR} ${BULLET_INCLUDE_DIR} ${LUA_INCLUDE_DIR} ${BOOST_INCLUDE_DIR} )
LINK_DIRECTORIES( ${IRRLICHT_LIB_DIR} ${BULLET_LIB_DIR} ${LUA_LIB_DIR} ${BOOST_LIB_DIR} )

PROJECT( PulsarEngine )

ADD_LIBRARY( PulsarEngine STATIC
### Engine
src/PulsarEngine/IObject.cpp
src/PulsarEngine/PulsarEngine.cpp
src/PulsarEngine/ConfigStorage.cpp
src/PulsarEngine/ValueFactory.cpp
### Entities
src/PulsarEngine/Entities/Entity.cpp
src/PulsarEngine/Entities/GraphicalEntity.cpp
src/PulsarEngine/Entities/DynamicEntity.cpp
src/PulsarEngine/Entities/SensorEntity.cpp
src/PulsarEngine/Entities/GhostSensorEntity.cpp
### ToolKits
src/PulsarEngine/ToolKits/CameraToolKit.cpp
src/PulsarEngine/ToolKits/ConstraintToolKit.cpp
src/PulsarEngine/ToolKits/EntityToolKit.cpp
src/PulsarEngine/ToolKits/PulsarEventReceiver.cpp
src/PulsarEngine/ToolKits/ScriptToolKit.cpp
)

TARGET_LINK_LIBRARIES( PulsarEngine 
Irrlicht
GL
Xrandr
lua
#BulletSoftBody
BulletDynamics
BulletCollision
LinearMath
#boost_filesystem
boost_system 
)

ADD_CUSTOM_COMMAND( TARGET spacegame POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E make_directory ../lib
	COMMAND ${CMAKE_COMMAND} -E copy ../build/libPulsarEngine.so ../lib/libPulsarEngine.so )

#MultiBouncer settings

LINK_DIRECTORIES( "../wiiuse/src/release-" )
INCLUDE_DIRECTORIES( "../wiiuse/src" )

ADD_EXECUTABLE( MultiBouncer
src/main.cpp
src/MultiBouncer/MultiBouncerGame.cpp
src/MultiBouncer/bouncers/SmallFastTestBouncer.cpp
)

TARGET_LINK_LIBRARIES( MultiBouncer wiiuse PulsarEngine boost_filesystem )