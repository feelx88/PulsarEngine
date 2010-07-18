CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )
CMAKE_POLICY( SET CMP0015 NEW )

#include directories
SET( IRRLICHT_INCLUDE_DIR "../irrlicht/include" )
SET( BULLET_INCLUDE_DIR "../bullet/src" )
SET( LUA_INCLUDE_DIR "../lua/src" )
SET( BOOST_INCLUDE_DIR "../boost" )

#linker directories
SET( IRRLICHT_LIB_DIR "../irrlicht/lib/Linux" )
SET( BULLET_LIB_DIR "../bullet/lib" )
SET( LUA_LIB_DIR "../boost/lib" )
SET( BOOST_LIB_DIR "../lua/src" )

INCLUDE_DIRECTORIES( ${IRRLICHT_INCLUDE_DIR} ${BULLET_INCLUDE_DIR} ${LUA_INCLUDE_DIR} ${BOOST_INCLUDE_DIR} )
LINK_DIRECTORIES(  ${IRRLICHT_LIB_DIR} ${BULLET_LIB_DIR} ${LUA_LIB_DIR} ${BOOST_LIB_DIR} )

PROJECT( PulsarEngine )

ADD_LIBRARY( PulsarEngine SHARED
### Engine
src/PulsarEngine/IObject.cpp
src/PulsarEngine/PulsarEngine.cpp
src/PulsarEngine/ConfigStorage.cpp
src/PulsarEngine/ContactPointStorage.cpp
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

ADD_EXECUTABLE( MultiBouncer
src/main.cpp
src/MultiBouncer/MultiBouncerGame.cpp
)

TARGET_LINK_LIBRARIES( MultiBouncer PulsarEngine )