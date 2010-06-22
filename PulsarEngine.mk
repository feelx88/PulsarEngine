##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=PulsarEngine
ConfigurationName      :=Debug
IntermediateDirectory  :=./Build
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "/home/feelx/devel/Project0012"
ProjectPath            := "/home/feelx/devel/Project0012"
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Felix Müller
Date                   :=22.06.2010
CodeLitePath           :="/home/feelx/.codelite"
LinkerName             :=g++
ArchiveTool            :=ar rcus
SharedObjectLinkerName :=g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
CompilerName           :=g++
C_CompilerName         :=gcc
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
MakeDirCommand         :=mkdir -p
CmpOptions             := -g -W $(Preprocessors)
LinkOptions            :=  
IncludePath            :=  "$(IncludeSwitch)." "$(IncludeSwitch)." "$(IncludeSwitch)../irrlicht/include" "$(IncludeSwitch)../bullet/src" "$(IncludeSwitch)../lua/src" 
RcIncludePath          :=
Libs                   :=$(LibrarySwitch)Irrlicht $(LibrarySwitch)GL $(LibrarySwitch)Xrandr $(LibrarySwitch)lua $(LibrarySwitch)BulletSoftBody $(LibrarySwitch)BulletDynamics $(LibrarySwitch)BulletCollision $(LibrarySwitch)LinearMath $(LibrarySwitch)boost_filesystem $(LibrarySwitch)boost_system 
LibPath                := "$(LibraryPathSwitch)." "$(LibraryPathSwitch)../bullet/lib" "$(LibraryPathSwitch)../irrlicht/lib/Linux" "$(LibraryPathSwitch)../lua/lib" "$(LibraryPathSwitch)../boost/lib" 


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects=$(IntermediateDirectory)/main$(ObjectSuffix) $(IntermediateDirectory)/ContactPointStorage$(ObjectSuffix) $(IntermediateDirectory)/ConfigStorage$(ObjectSuffix) $(IntermediateDirectory)/ValueFactory$(ObjectSuffix) $(IntermediateDirectory)/PulsarEngine$(ObjectSuffix) $(IntermediateDirectory)/IObject$(ObjectSuffix) $(IntermediateDirectory)/ConstraintToolKit$(ObjectSuffix) $(IntermediateDirectory)/DynamicEntity$(ObjectSuffix) $(IntermediateDirectory)/Entity$(ObjectSuffix) $(IntermediateDirectory)/GhostSensorEntity$(ObjectSuffix) \
	$(IntermediateDirectory)/GraphicalEntity$(ObjectSuffix) $(IntermediateDirectory)/SensorEntity$(ObjectSuffix) $(IntermediateDirectory)/CameraToolKit$(ObjectSuffix) $(IntermediateDirectory)/EntityToolKit$(ObjectSuffix) $(IntermediateDirectory)/ScriptToolKit$(ObjectSuffix) $(IntermediateDirectory)/PulsarEventReceiver$(ObjectSuffix) 

##
## Main Build Targets 
##
all: $(OutputFile)

$(OutputFile): makeDirStep $(Objects)
	@$(MakeDirCommand) $(@D)
	$(LinkerName) $(OutputSwitch)$(OutputFile) $(Objects) $(LibPath) $(Libs) $(LinkOptions)

makeDirStep:
	@test -d ./Build || $(MakeDirCommand) ./Build

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/feelx/devel/Project0012/main.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/main$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main$(DependSuffix): main.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/main$(ObjectSuffix) -MF$(IntermediateDirectory)/main$(DependSuffix) -MM "/home/feelx/devel/Project0012/main.cpp"

$(IntermediateDirectory)/main$(PreprocessSuffix): main.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main$(PreprocessSuffix) "/home/feelx/devel/Project0012/main.cpp"

$(IntermediateDirectory)/ContactPointStorage$(ObjectSuffix): ContactPointStorage.cpp $(IntermediateDirectory)/ContactPointStorage$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/feelx/devel/Project0012/ContactPointStorage.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/ContactPointStorage$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ContactPointStorage$(DependSuffix): ContactPointStorage.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/ContactPointStorage$(ObjectSuffix) -MF$(IntermediateDirectory)/ContactPointStorage$(DependSuffix) -MM "/home/feelx/devel/Project0012/ContactPointStorage.cpp"

$(IntermediateDirectory)/ContactPointStorage$(PreprocessSuffix): ContactPointStorage.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ContactPointStorage$(PreprocessSuffix) "/home/feelx/devel/Project0012/ContactPointStorage.cpp"

$(IntermediateDirectory)/ConfigStorage$(ObjectSuffix): ConfigStorage.cpp $(IntermediateDirectory)/ConfigStorage$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/feelx/devel/Project0012/ConfigStorage.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/ConfigStorage$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ConfigStorage$(DependSuffix): ConfigStorage.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/ConfigStorage$(ObjectSuffix) -MF$(IntermediateDirectory)/ConfigStorage$(DependSuffix) -MM "/home/feelx/devel/Project0012/ConfigStorage.cpp"

$(IntermediateDirectory)/ConfigStorage$(PreprocessSuffix): ConfigStorage.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ConfigStorage$(PreprocessSuffix) "/home/feelx/devel/Project0012/ConfigStorage.cpp"

$(IntermediateDirectory)/ValueFactory$(ObjectSuffix): ValueFactory.cpp $(IntermediateDirectory)/ValueFactory$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/feelx/devel/Project0012/ValueFactory.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/ValueFactory$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ValueFactory$(DependSuffix): ValueFactory.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/ValueFactory$(ObjectSuffix) -MF$(IntermediateDirectory)/ValueFactory$(DependSuffix) -MM "/home/feelx/devel/Project0012/ValueFactory.cpp"

$(IntermediateDirectory)/ValueFactory$(PreprocessSuffix): ValueFactory.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ValueFactory$(PreprocessSuffix) "/home/feelx/devel/Project0012/ValueFactory.cpp"

$(IntermediateDirectory)/PulsarEngine$(ObjectSuffix): PulsarEngine.cpp $(IntermediateDirectory)/PulsarEngine$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/feelx/devel/Project0012/PulsarEngine.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/PulsarEngine$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/PulsarEngine$(DependSuffix): PulsarEngine.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/PulsarEngine$(ObjectSuffix) -MF$(IntermediateDirectory)/PulsarEngine$(DependSuffix) -MM "/home/feelx/devel/Project0012/PulsarEngine.cpp"

$(IntermediateDirectory)/PulsarEngine$(PreprocessSuffix): PulsarEngine.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/PulsarEngine$(PreprocessSuffix) "/home/feelx/devel/Project0012/PulsarEngine.cpp"

$(IntermediateDirectory)/IObject$(ObjectSuffix): IObject.cpp $(IntermediateDirectory)/IObject$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/feelx/devel/Project0012/IObject.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/IObject$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/IObject$(DependSuffix): IObject.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/IObject$(ObjectSuffix) -MF$(IntermediateDirectory)/IObject$(DependSuffix) -MM "/home/feelx/devel/Project0012/IObject.cpp"

$(IntermediateDirectory)/IObject$(PreprocessSuffix): IObject.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/IObject$(PreprocessSuffix) "/home/feelx/devel/Project0012/IObject.cpp"

$(IntermediateDirectory)/ConstraintToolKit$(ObjectSuffix): ConstraintToolKit.cpp $(IntermediateDirectory)/ConstraintToolKit$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/feelx/devel/Project0012/ConstraintToolKit.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/ConstraintToolKit$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ConstraintToolKit$(DependSuffix): ConstraintToolKit.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/ConstraintToolKit$(ObjectSuffix) -MF$(IntermediateDirectory)/ConstraintToolKit$(DependSuffix) -MM "/home/feelx/devel/Project0012/ConstraintToolKit.cpp"

$(IntermediateDirectory)/ConstraintToolKit$(PreprocessSuffix): ConstraintToolKit.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ConstraintToolKit$(PreprocessSuffix) "/home/feelx/devel/Project0012/ConstraintToolKit.cpp"

$(IntermediateDirectory)/DynamicEntity$(ObjectSuffix): DynamicEntity.cpp $(IntermediateDirectory)/DynamicEntity$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/feelx/devel/Project0012/DynamicEntity.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/DynamicEntity$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/DynamicEntity$(DependSuffix): DynamicEntity.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/DynamicEntity$(ObjectSuffix) -MF$(IntermediateDirectory)/DynamicEntity$(DependSuffix) -MM "/home/feelx/devel/Project0012/DynamicEntity.cpp"

$(IntermediateDirectory)/DynamicEntity$(PreprocessSuffix): DynamicEntity.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/DynamicEntity$(PreprocessSuffix) "/home/feelx/devel/Project0012/DynamicEntity.cpp"

$(IntermediateDirectory)/Entity$(ObjectSuffix): Entity.cpp $(IntermediateDirectory)/Entity$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/feelx/devel/Project0012/Entity.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Entity$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Entity$(DependSuffix): Entity.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Entity$(ObjectSuffix) -MF$(IntermediateDirectory)/Entity$(DependSuffix) -MM "/home/feelx/devel/Project0012/Entity.cpp"

$(IntermediateDirectory)/Entity$(PreprocessSuffix): Entity.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Entity$(PreprocessSuffix) "/home/feelx/devel/Project0012/Entity.cpp"

$(IntermediateDirectory)/GhostSensorEntity$(ObjectSuffix): GhostSensorEntity.cpp $(IntermediateDirectory)/GhostSensorEntity$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/feelx/devel/Project0012/GhostSensorEntity.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/GhostSensorEntity$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/GhostSensorEntity$(DependSuffix): GhostSensorEntity.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/GhostSensorEntity$(ObjectSuffix) -MF$(IntermediateDirectory)/GhostSensorEntity$(DependSuffix) -MM "/home/feelx/devel/Project0012/GhostSensorEntity.cpp"

$(IntermediateDirectory)/GhostSensorEntity$(PreprocessSuffix): GhostSensorEntity.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/GhostSensorEntity$(PreprocessSuffix) "/home/feelx/devel/Project0012/GhostSensorEntity.cpp"

$(IntermediateDirectory)/GraphicalEntity$(ObjectSuffix): GraphicalEntity.cpp $(IntermediateDirectory)/GraphicalEntity$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/feelx/devel/Project0012/GraphicalEntity.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/GraphicalEntity$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/GraphicalEntity$(DependSuffix): GraphicalEntity.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/GraphicalEntity$(ObjectSuffix) -MF$(IntermediateDirectory)/GraphicalEntity$(DependSuffix) -MM "/home/feelx/devel/Project0012/GraphicalEntity.cpp"

$(IntermediateDirectory)/GraphicalEntity$(PreprocessSuffix): GraphicalEntity.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/GraphicalEntity$(PreprocessSuffix) "/home/feelx/devel/Project0012/GraphicalEntity.cpp"

$(IntermediateDirectory)/SensorEntity$(ObjectSuffix): SensorEntity.cpp $(IntermediateDirectory)/SensorEntity$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/feelx/devel/Project0012/SensorEntity.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/SensorEntity$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SensorEntity$(DependSuffix): SensorEntity.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/SensorEntity$(ObjectSuffix) -MF$(IntermediateDirectory)/SensorEntity$(DependSuffix) -MM "/home/feelx/devel/Project0012/SensorEntity.cpp"

$(IntermediateDirectory)/SensorEntity$(PreprocessSuffix): SensorEntity.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/SensorEntity$(PreprocessSuffix) "/home/feelx/devel/Project0012/SensorEntity.cpp"

$(IntermediateDirectory)/CameraToolKit$(ObjectSuffix): CameraToolKit.cpp $(IntermediateDirectory)/CameraToolKit$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/feelx/devel/Project0012/CameraToolKit.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/CameraToolKit$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CameraToolKit$(DependSuffix): CameraToolKit.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/CameraToolKit$(ObjectSuffix) -MF$(IntermediateDirectory)/CameraToolKit$(DependSuffix) -MM "/home/feelx/devel/Project0012/CameraToolKit.cpp"

$(IntermediateDirectory)/CameraToolKit$(PreprocessSuffix): CameraToolKit.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CameraToolKit$(PreprocessSuffix) "/home/feelx/devel/Project0012/CameraToolKit.cpp"

$(IntermediateDirectory)/EntityToolKit$(ObjectSuffix): EntityToolKit.cpp $(IntermediateDirectory)/EntityToolKit$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/feelx/devel/Project0012/EntityToolKit.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/EntityToolKit$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/EntityToolKit$(DependSuffix): EntityToolKit.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/EntityToolKit$(ObjectSuffix) -MF$(IntermediateDirectory)/EntityToolKit$(DependSuffix) -MM "/home/feelx/devel/Project0012/EntityToolKit.cpp"

$(IntermediateDirectory)/EntityToolKit$(PreprocessSuffix): EntityToolKit.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/EntityToolKit$(PreprocessSuffix) "/home/feelx/devel/Project0012/EntityToolKit.cpp"

$(IntermediateDirectory)/ScriptToolKit$(ObjectSuffix): ScriptToolKit.cpp $(IntermediateDirectory)/ScriptToolKit$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/feelx/devel/Project0012/ScriptToolKit.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/ScriptToolKit$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ScriptToolKit$(DependSuffix): ScriptToolKit.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/ScriptToolKit$(ObjectSuffix) -MF$(IntermediateDirectory)/ScriptToolKit$(DependSuffix) -MM "/home/feelx/devel/Project0012/ScriptToolKit.cpp"

$(IntermediateDirectory)/ScriptToolKit$(PreprocessSuffix): ScriptToolKit.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ScriptToolKit$(PreprocessSuffix) "/home/feelx/devel/Project0012/ScriptToolKit.cpp"

$(IntermediateDirectory)/PulsarEventReceiver$(ObjectSuffix): PulsarEventReceiver.cpp $(IntermediateDirectory)/PulsarEventReceiver$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/feelx/devel/Project0012/PulsarEventReceiver.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/PulsarEventReceiver$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/PulsarEventReceiver$(DependSuffix): PulsarEventReceiver.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/PulsarEventReceiver$(ObjectSuffix) -MF$(IntermediateDirectory)/PulsarEventReceiver$(DependSuffix) -MM "/home/feelx/devel/Project0012/PulsarEventReceiver.cpp"

$(IntermediateDirectory)/PulsarEventReceiver$(PreprocessSuffix): PulsarEventReceiver.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/PulsarEventReceiver$(PreprocessSuffix) "/home/feelx/devel/Project0012/PulsarEventReceiver.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/main$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/main$(DependSuffix)
	$(RM) $(IntermediateDirectory)/main$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/ContactPointStorage$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/ContactPointStorage$(DependSuffix)
	$(RM) $(IntermediateDirectory)/ContactPointStorage$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/ConfigStorage$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/ConfigStorage$(DependSuffix)
	$(RM) $(IntermediateDirectory)/ConfigStorage$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/ValueFactory$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/ValueFactory$(DependSuffix)
	$(RM) $(IntermediateDirectory)/ValueFactory$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/PulsarEngine$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/PulsarEngine$(DependSuffix)
	$(RM) $(IntermediateDirectory)/PulsarEngine$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/IObject$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/IObject$(DependSuffix)
	$(RM) $(IntermediateDirectory)/IObject$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/ConstraintToolKit$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/ConstraintToolKit$(DependSuffix)
	$(RM) $(IntermediateDirectory)/ConstraintToolKit$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/DynamicEntity$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/DynamicEntity$(DependSuffix)
	$(RM) $(IntermediateDirectory)/DynamicEntity$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Entity$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Entity$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Entity$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/GhostSensorEntity$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/GhostSensorEntity$(DependSuffix)
	$(RM) $(IntermediateDirectory)/GhostSensorEntity$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/GraphicalEntity$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/GraphicalEntity$(DependSuffix)
	$(RM) $(IntermediateDirectory)/GraphicalEntity$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/SensorEntity$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/SensorEntity$(DependSuffix)
	$(RM) $(IntermediateDirectory)/SensorEntity$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/CameraToolKit$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/CameraToolKit$(DependSuffix)
	$(RM) $(IntermediateDirectory)/CameraToolKit$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/EntityToolKit$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/EntityToolKit$(DependSuffix)
	$(RM) $(IntermediateDirectory)/EntityToolKit$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/ScriptToolKit$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/ScriptToolKit$(DependSuffix)
	$(RM) $(IntermediateDirectory)/ScriptToolKit$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/PulsarEventReceiver$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/PulsarEventReceiver$(DependSuffix)
	$(RM) $(IntermediateDirectory)/PulsarEventReceiver$(PreprocessSuffix)
	$(RM) $(OutputFile)


