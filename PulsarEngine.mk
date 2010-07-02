##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## MultiBouncerDebug
ProjectName            :=PulsarEngine
ConfigurationName      :=MultiBouncerDebug
IntermediateDirectory  :=./obj
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "/home/feelx/devel/Project0012"
ProjectPath            := "/home/feelx/devel/Project0012"
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Felix Müller
Date                   :=02.07.2010
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
Objects=$(IntermediateDirectory)/MultiBouncer_MultiBouncerGame$(ObjectSuffix) $(IntermediateDirectory)/ToolKits_ConstraintToolKit$(ObjectSuffix) $(IntermediateDirectory)/ToolKits_ScriptToolKit$(ObjectSuffix) $(IntermediateDirectory)/ToolKits_EntityToolKit$(ObjectSuffix) $(IntermediateDirectory)/ToolKits_CameraToolKit$(ObjectSuffix) $(IntermediateDirectory)/ToolKits_PulsarEventReceiver$(ObjectSuffix) $(IntermediateDirectory)/Entities_SensorEntity$(ObjectSuffix) $(IntermediateDirectory)/Entities_GhostSensorEntity$(ObjectSuffix) $(IntermediateDirectory)/Entities_DynamicEntity$(ObjectSuffix) $(IntermediateDirectory)/Entities_GraphicalEntity$(ObjectSuffix) \
	$(IntermediateDirectory)/Entities_Entity$(ObjectSuffix) $(IntermediateDirectory)/PulsarEngine_ConfigStorage$(ObjectSuffix) $(IntermediateDirectory)/PulsarEngine_ContactPointStorage$(ObjectSuffix) $(IntermediateDirectory)/PulsarEngine_IObject$(ObjectSuffix) $(IntermediateDirectory)/PulsarEngine_ValueFactory$(ObjectSuffix) $(IntermediateDirectory)/PulsarEngine_PulsarEngine$(ObjectSuffix) $(IntermediateDirectory)/src_main$(ObjectSuffix) 

##
## Main Build Targets 
##
all: $(OutputFile)

$(OutputFile): makeDirStep $(Objects)
	@$(MakeDirCommand) $(@D)
	$(LinkerName) $(OutputSwitch)$(OutputFile) $(Objects) $(LibPath) $(Libs) $(LinkOptions)
	@echo Executing Post Build commands ...
	mv $(IntermediateDirectory)/$(ProjectName) src/MultiBouncer/$(ProjectName)
	@echo Done

makeDirStep:
	@test -d ./obj || $(MakeDirCommand) ./obj

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/MultiBouncer_MultiBouncerGame$(ObjectSuffix): src/MultiBouncer/MultiBouncerGame.cpp $(IntermediateDirectory)/MultiBouncer_MultiBouncerGame$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/feelx/devel/Project0012/src/MultiBouncer/MultiBouncerGame.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/MultiBouncer_MultiBouncerGame$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/MultiBouncer_MultiBouncerGame$(DependSuffix): src/MultiBouncer/MultiBouncerGame.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/MultiBouncer_MultiBouncerGame$(ObjectSuffix) -MF$(IntermediateDirectory)/MultiBouncer_MultiBouncerGame$(DependSuffix) -MM "/home/feelx/devel/Project0012/src/MultiBouncer/MultiBouncerGame.cpp"

$(IntermediateDirectory)/MultiBouncer_MultiBouncerGame$(PreprocessSuffix): src/MultiBouncer/MultiBouncerGame.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/MultiBouncer_MultiBouncerGame$(PreprocessSuffix) "/home/feelx/devel/Project0012/src/MultiBouncer/MultiBouncerGame.cpp"

$(IntermediateDirectory)/ToolKits_ConstraintToolKit$(ObjectSuffix): src/PulsarEngine/ToolKits/ConstraintToolKit.cpp $(IntermediateDirectory)/ToolKits_ConstraintToolKit$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/feelx/devel/Project0012/src/PulsarEngine/ToolKits/ConstraintToolKit.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/ToolKits_ConstraintToolKit$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ToolKits_ConstraintToolKit$(DependSuffix): src/PulsarEngine/ToolKits/ConstraintToolKit.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/ToolKits_ConstraintToolKit$(ObjectSuffix) -MF$(IntermediateDirectory)/ToolKits_ConstraintToolKit$(DependSuffix) -MM "/home/feelx/devel/Project0012/src/PulsarEngine/ToolKits/ConstraintToolKit.cpp"

$(IntermediateDirectory)/ToolKits_ConstraintToolKit$(PreprocessSuffix): src/PulsarEngine/ToolKits/ConstraintToolKit.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ToolKits_ConstraintToolKit$(PreprocessSuffix) "/home/feelx/devel/Project0012/src/PulsarEngine/ToolKits/ConstraintToolKit.cpp"

$(IntermediateDirectory)/ToolKits_ScriptToolKit$(ObjectSuffix): src/PulsarEngine/ToolKits/ScriptToolKit.cpp $(IntermediateDirectory)/ToolKits_ScriptToolKit$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/feelx/devel/Project0012/src/PulsarEngine/ToolKits/ScriptToolKit.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/ToolKits_ScriptToolKit$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ToolKits_ScriptToolKit$(DependSuffix): src/PulsarEngine/ToolKits/ScriptToolKit.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/ToolKits_ScriptToolKit$(ObjectSuffix) -MF$(IntermediateDirectory)/ToolKits_ScriptToolKit$(DependSuffix) -MM "/home/feelx/devel/Project0012/src/PulsarEngine/ToolKits/ScriptToolKit.cpp"

$(IntermediateDirectory)/ToolKits_ScriptToolKit$(PreprocessSuffix): src/PulsarEngine/ToolKits/ScriptToolKit.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ToolKits_ScriptToolKit$(PreprocessSuffix) "/home/feelx/devel/Project0012/src/PulsarEngine/ToolKits/ScriptToolKit.cpp"

$(IntermediateDirectory)/ToolKits_EntityToolKit$(ObjectSuffix): src/PulsarEngine/ToolKits/EntityToolKit.cpp $(IntermediateDirectory)/ToolKits_EntityToolKit$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/feelx/devel/Project0012/src/PulsarEngine/ToolKits/EntityToolKit.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/ToolKits_EntityToolKit$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ToolKits_EntityToolKit$(DependSuffix): src/PulsarEngine/ToolKits/EntityToolKit.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/ToolKits_EntityToolKit$(ObjectSuffix) -MF$(IntermediateDirectory)/ToolKits_EntityToolKit$(DependSuffix) -MM "/home/feelx/devel/Project0012/src/PulsarEngine/ToolKits/EntityToolKit.cpp"

$(IntermediateDirectory)/ToolKits_EntityToolKit$(PreprocessSuffix): src/PulsarEngine/ToolKits/EntityToolKit.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ToolKits_EntityToolKit$(PreprocessSuffix) "/home/feelx/devel/Project0012/src/PulsarEngine/ToolKits/EntityToolKit.cpp"

$(IntermediateDirectory)/ToolKits_CameraToolKit$(ObjectSuffix): src/PulsarEngine/ToolKits/CameraToolKit.cpp $(IntermediateDirectory)/ToolKits_CameraToolKit$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/feelx/devel/Project0012/src/PulsarEngine/ToolKits/CameraToolKit.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/ToolKits_CameraToolKit$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ToolKits_CameraToolKit$(DependSuffix): src/PulsarEngine/ToolKits/CameraToolKit.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/ToolKits_CameraToolKit$(ObjectSuffix) -MF$(IntermediateDirectory)/ToolKits_CameraToolKit$(DependSuffix) -MM "/home/feelx/devel/Project0012/src/PulsarEngine/ToolKits/CameraToolKit.cpp"

$(IntermediateDirectory)/ToolKits_CameraToolKit$(PreprocessSuffix): src/PulsarEngine/ToolKits/CameraToolKit.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ToolKits_CameraToolKit$(PreprocessSuffix) "/home/feelx/devel/Project0012/src/PulsarEngine/ToolKits/CameraToolKit.cpp"

$(IntermediateDirectory)/ToolKits_PulsarEventReceiver$(ObjectSuffix): src/PulsarEngine/ToolKits/PulsarEventReceiver.cpp $(IntermediateDirectory)/ToolKits_PulsarEventReceiver$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/feelx/devel/Project0012/src/PulsarEngine/ToolKits/PulsarEventReceiver.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/ToolKits_PulsarEventReceiver$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ToolKits_PulsarEventReceiver$(DependSuffix): src/PulsarEngine/ToolKits/PulsarEventReceiver.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/ToolKits_PulsarEventReceiver$(ObjectSuffix) -MF$(IntermediateDirectory)/ToolKits_PulsarEventReceiver$(DependSuffix) -MM "/home/feelx/devel/Project0012/src/PulsarEngine/ToolKits/PulsarEventReceiver.cpp"

$(IntermediateDirectory)/ToolKits_PulsarEventReceiver$(PreprocessSuffix): src/PulsarEngine/ToolKits/PulsarEventReceiver.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ToolKits_PulsarEventReceiver$(PreprocessSuffix) "/home/feelx/devel/Project0012/src/PulsarEngine/ToolKits/PulsarEventReceiver.cpp"

$(IntermediateDirectory)/Entities_SensorEntity$(ObjectSuffix): src/PulsarEngine/Entities/SensorEntity.cpp $(IntermediateDirectory)/Entities_SensorEntity$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/feelx/devel/Project0012/src/PulsarEngine/Entities/SensorEntity.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Entities_SensorEntity$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Entities_SensorEntity$(DependSuffix): src/PulsarEngine/Entities/SensorEntity.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Entities_SensorEntity$(ObjectSuffix) -MF$(IntermediateDirectory)/Entities_SensorEntity$(DependSuffix) -MM "/home/feelx/devel/Project0012/src/PulsarEngine/Entities/SensorEntity.cpp"

$(IntermediateDirectory)/Entities_SensorEntity$(PreprocessSuffix): src/PulsarEngine/Entities/SensorEntity.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Entities_SensorEntity$(PreprocessSuffix) "/home/feelx/devel/Project0012/src/PulsarEngine/Entities/SensorEntity.cpp"

$(IntermediateDirectory)/Entities_GhostSensorEntity$(ObjectSuffix): src/PulsarEngine/Entities/GhostSensorEntity.cpp $(IntermediateDirectory)/Entities_GhostSensorEntity$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/feelx/devel/Project0012/src/PulsarEngine/Entities/GhostSensorEntity.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Entities_GhostSensorEntity$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Entities_GhostSensorEntity$(DependSuffix): src/PulsarEngine/Entities/GhostSensorEntity.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Entities_GhostSensorEntity$(ObjectSuffix) -MF$(IntermediateDirectory)/Entities_GhostSensorEntity$(DependSuffix) -MM "/home/feelx/devel/Project0012/src/PulsarEngine/Entities/GhostSensorEntity.cpp"

$(IntermediateDirectory)/Entities_GhostSensorEntity$(PreprocessSuffix): src/PulsarEngine/Entities/GhostSensorEntity.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Entities_GhostSensorEntity$(PreprocessSuffix) "/home/feelx/devel/Project0012/src/PulsarEngine/Entities/GhostSensorEntity.cpp"

$(IntermediateDirectory)/Entities_DynamicEntity$(ObjectSuffix): src/PulsarEngine/Entities/DynamicEntity.cpp $(IntermediateDirectory)/Entities_DynamicEntity$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/feelx/devel/Project0012/src/PulsarEngine/Entities/DynamicEntity.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Entities_DynamicEntity$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Entities_DynamicEntity$(DependSuffix): src/PulsarEngine/Entities/DynamicEntity.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Entities_DynamicEntity$(ObjectSuffix) -MF$(IntermediateDirectory)/Entities_DynamicEntity$(DependSuffix) -MM "/home/feelx/devel/Project0012/src/PulsarEngine/Entities/DynamicEntity.cpp"

$(IntermediateDirectory)/Entities_DynamicEntity$(PreprocessSuffix): src/PulsarEngine/Entities/DynamicEntity.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Entities_DynamicEntity$(PreprocessSuffix) "/home/feelx/devel/Project0012/src/PulsarEngine/Entities/DynamicEntity.cpp"

$(IntermediateDirectory)/Entities_GraphicalEntity$(ObjectSuffix): src/PulsarEngine/Entities/GraphicalEntity.cpp $(IntermediateDirectory)/Entities_GraphicalEntity$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/feelx/devel/Project0012/src/PulsarEngine/Entities/GraphicalEntity.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Entities_GraphicalEntity$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Entities_GraphicalEntity$(DependSuffix): src/PulsarEngine/Entities/GraphicalEntity.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Entities_GraphicalEntity$(ObjectSuffix) -MF$(IntermediateDirectory)/Entities_GraphicalEntity$(DependSuffix) -MM "/home/feelx/devel/Project0012/src/PulsarEngine/Entities/GraphicalEntity.cpp"

$(IntermediateDirectory)/Entities_GraphicalEntity$(PreprocessSuffix): src/PulsarEngine/Entities/GraphicalEntity.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Entities_GraphicalEntity$(PreprocessSuffix) "/home/feelx/devel/Project0012/src/PulsarEngine/Entities/GraphicalEntity.cpp"

$(IntermediateDirectory)/Entities_Entity$(ObjectSuffix): src/PulsarEngine/Entities/Entity.cpp $(IntermediateDirectory)/Entities_Entity$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/feelx/devel/Project0012/src/PulsarEngine/Entities/Entity.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Entities_Entity$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Entities_Entity$(DependSuffix): src/PulsarEngine/Entities/Entity.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Entities_Entity$(ObjectSuffix) -MF$(IntermediateDirectory)/Entities_Entity$(DependSuffix) -MM "/home/feelx/devel/Project0012/src/PulsarEngine/Entities/Entity.cpp"

$(IntermediateDirectory)/Entities_Entity$(PreprocessSuffix): src/PulsarEngine/Entities/Entity.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Entities_Entity$(PreprocessSuffix) "/home/feelx/devel/Project0012/src/PulsarEngine/Entities/Entity.cpp"

$(IntermediateDirectory)/PulsarEngine_ConfigStorage$(ObjectSuffix): src/PulsarEngine/ConfigStorage.cpp $(IntermediateDirectory)/PulsarEngine_ConfigStorage$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/feelx/devel/Project0012/src/PulsarEngine/ConfigStorage.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/PulsarEngine_ConfigStorage$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/PulsarEngine_ConfigStorage$(DependSuffix): src/PulsarEngine/ConfigStorage.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/PulsarEngine_ConfigStorage$(ObjectSuffix) -MF$(IntermediateDirectory)/PulsarEngine_ConfigStorage$(DependSuffix) -MM "/home/feelx/devel/Project0012/src/PulsarEngine/ConfigStorage.cpp"

$(IntermediateDirectory)/PulsarEngine_ConfigStorage$(PreprocessSuffix): src/PulsarEngine/ConfigStorage.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/PulsarEngine_ConfigStorage$(PreprocessSuffix) "/home/feelx/devel/Project0012/src/PulsarEngine/ConfigStorage.cpp"

$(IntermediateDirectory)/PulsarEngine_ContactPointStorage$(ObjectSuffix): src/PulsarEngine/ContactPointStorage.cpp $(IntermediateDirectory)/PulsarEngine_ContactPointStorage$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/feelx/devel/Project0012/src/PulsarEngine/ContactPointStorage.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/PulsarEngine_ContactPointStorage$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/PulsarEngine_ContactPointStorage$(DependSuffix): src/PulsarEngine/ContactPointStorage.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/PulsarEngine_ContactPointStorage$(ObjectSuffix) -MF$(IntermediateDirectory)/PulsarEngine_ContactPointStorage$(DependSuffix) -MM "/home/feelx/devel/Project0012/src/PulsarEngine/ContactPointStorage.cpp"

$(IntermediateDirectory)/PulsarEngine_ContactPointStorage$(PreprocessSuffix): src/PulsarEngine/ContactPointStorage.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/PulsarEngine_ContactPointStorage$(PreprocessSuffix) "/home/feelx/devel/Project0012/src/PulsarEngine/ContactPointStorage.cpp"

$(IntermediateDirectory)/PulsarEngine_IObject$(ObjectSuffix): src/PulsarEngine/IObject.cpp $(IntermediateDirectory)/PulsarEngine_IObject$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/feelx/devel/Project0012/src/PulsarEngine/IObject.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/PulsarEngine_IObject$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/PulsarEngine_IObject$(DependSuffix): src/PulsarEngine/IObject.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/PulsarEngine_IObject$(ObjectSuffix) -MF$(IntermediateDirectory)/PulsarEngine_IObject$(DependSuffix) -MM "/home/feelx/devel/Project0012/src/PulsarEngine/IObject.cpp"

$(IntermediateDirectory)/PulsarEngine_IObject$(PreprocessSuffix): src/PulsarEngine/IObject.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/PulsarEngine_IObject$(PreprocessSuffix) "/home/feelx/devel/Project0012/src/PulsarEngine/IObject.cpp"

$(IntermediateDirectory)/PulsarEngine_ValueFactory$(ObjectSuffix): src/PulsarEngine/ValueFactory.cpp $(IntermediateDirectory)/PulsarEngine_ValueFactory$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/feelx/devel/Project0012/src/PulsarEngine/ValueFactory.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/PulsarEngine_ValueFactory$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/PulsarEngine_ValueFactory$(DependSuffix): src/PulsarEngine/ValueFactory.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/PulsarEngine_ValueFactory$(ObjectSuffix) -MF$(IntermediateDirectory)/PulsarEngine_ValueFactory$(DependSuffix) -MM "/home/feelx/devel/Project0012/src/PulsarEngine/ValueFactory.cpp"

$(IntermediateDirectory)/PulsarEngine_ValueFactory$(PreprocessSuffix): src/PulsarEngine/ValueFactory.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/PulsarEngine_ValueFactory$(PreprocessSuffix) "/home/feelx/devel/Project0012/src/PulsarEngine/ValueFactory.cpp"

$(IntermediateDirectory)/PulsarEngine_PulsarEngine$(ObjectSuffix): src/PulsarEngine/PulsarEngine.cpp $(IntermediateDirectory)/PulsarEngine_PulsarEngine$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/feelx/devel/Project0012/src/PulsarEngine/PulsarEngine.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/PulsarEngine_PulsarEngine$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/PulsarEngine_PulsarEngine$(DependSuffix): src/PulsarEngine/PulsarEngine.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/PulsarEngine_PulsarEngine$(ObjectSuffix) -MF$(IntermediateDirectory)/PulsarEngine_PulsarEngine$(DependSuffix) -MM "/home/feelx/devel/Project0012/src/PulsarEngine/PulsarEngine.cpp"

$(IntermediateDirectory)/PulsarEngine_PulsarEngine$(PreprocessSuffix): src/PulsarEngine/PulsarEngine.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/PulsarEngine_PulsarEngine$(PreprocessSuffix) "/home/feelx/devel/Project0012/src/PulsarEngine/PulsarEngine.cpp"

$(IntermediateDirectory)/src_main$(ObjectSuffix): src/main.cpp $(IntermediateDirectory)/src_main$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/feelx/devel/Project0012/src/main.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_main$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_main$(DependSuffix): src/main.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/src_main$(ObjectSuffix) -MF$(IntermediateDirectory)/src_main$(DependSuffix) -MM "/home/feelx/devel/Project0012/src/main.cpp"

$(IntermediateDirectory)/src_main$(PreprocessSuffix): src/main.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_main$(PreprocessSuffix) "/home/feelx/devel/Project0012/src/main.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/MultiBouncer_MultiBouncerGame$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/MultiBouncer_MultiBouncerGame$(DependSuffix)
	$(RM) $(IntermediateDirectory)/MultiBouncer_MultiBouncerGame$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/ToolKits_ConstraintToolKit$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/ToolKits_ConstraintToolKit$(DependSuffix)
	$(RM) $(IntermediateDirectory)/ToolKits_ConstraintToolKit$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/ToolKits_ScriptToolKit$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/ToolKits_ScriptToolKit$(DependSuffix)
	$(RM) $(IntermediateDirectory)/ToolKits_ScriptToolKit$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/ToolKits_EntityToolKit$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/ToolKits_EntityToolKit$(DependSuffix)
	$(RM) $(IntermediateDirectory)/ToolKits_EntityToolKit$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/ToolKits_CameraToolKit$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/ToolKits_CameraToolKit$(DependSuffix)
	$(RM) $(IntermediateDirectory)/ToolKits_CameraToolKit$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/ToolKits_PulsarEventReceiver$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/ToolKits_PulsarEventReceiver$(DependSuffix)
	$(RM) $(IntermediateDirectory)/ToolKits_PulsarEventReceiver$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Entities_SensorEntity$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Entities_SensorEntity$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Entities_SensorEntity$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Entities_GhostSensorEntity$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Entities_GhostSensorEntity$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Entities_GhostSensorEntity$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Entities_DynamicEntity$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Entities_DynamicEntity$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Entities_DynamicEntity$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Entities_GraphicalEntity$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Entities_GraphicalEntity$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Entities_GraphicalEntity$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Entities_Entity$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Entities_Entity$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Entities_Entity$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/PulsarEngine_ConfigStorage$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/PulsarEngine_ConfigStorage$(DependSuffix)
	$(RM) $(IntermediateDirectory)/PulsarEngine_ConfigStorage$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/PulsarEngine_ContactPointStorage$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/PulsarEngine_ContactPointStorage$(DependSuffix)
	$(RM) $(IntermediateDirectory)/PulsarEngine_ContactPointStorage$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/PulsarEngine_IObject$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/PulsarEngine_IObject$(DependSuffix)
	$(RM) $(IntermediateDirectory)/PulsarEngine_IObject$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/PulsarEngine_ValueFactory$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/PulsarEngine_ValueFactory$(DependSuffix)
	$(RM) $(IntermediateDirectory)/PulsarEngine_ValueFactory$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/PulsarEngine_PulsarEngine$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/PulsarEngine_PulsarEngine$(DependSuffix)
	$(RM) $(IntermediateDirectory)/PulsarEngine_PulsarEngine$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/src_main$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_main$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_main$(PreprocessSuffix)
	$(RM) $(OutputFile)


