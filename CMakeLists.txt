CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )
CMAKE_POLICY( SET CMP0015 NEW )

INCLUDE_DIRECTORIES( ../irrlicht/include ../bullet/src ../boost ../lua/src )
LINK_DIRECTORIES( ../../irrlicht/lib/Linux ../../bullet/lib ../../boost/lib ../../lua/src )

PROJECT( PulsarEngine )

ADD_LIBRARY( PulsarEngine
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