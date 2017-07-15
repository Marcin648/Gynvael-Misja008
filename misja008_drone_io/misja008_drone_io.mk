##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=misja008_drone_io
ConfigurationName      :=Debug
WorkspacePath          :=C:/dev/cpp/misja008_drone_io
ProjectPath            :=C:/dev/cpp/misja008_drone_io/misja008_drone_io
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=marcin
Date                   :=15/07/2017
CodeLitePath           :="C:/Program Files/CodeLite"
LinkerName             :=C:/mingw-w64/mingw64/bin/g++.exe
SharedObjectLinkerName :=C:/mingw-w64/mingw64/bin/g++.exe -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=$(PreprocessorSwitch)DEBUG 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="misja008_drone_io.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := 
RcCompilerName         :=C:/mingw-w64/mingw64/bin/windres.exe
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch).\lib\SFML-2.4.2\include 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)sfml-graphics-d $(LibrarySwitch)sfml-window-d $(LibrarySwitch)sfml-system-d $(LibrarySwitch)sfml-network-d 
ArLibs                 :=  "sfml-graphics-d" "sfml-window-d" "sfml-system-d" "sfml-network-d" 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch).\lib\SFML-2.4.2\lib 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := C:/mingw-w64/mingw64/bin/ar.exe rcu
CXX      := C:/mingw-w64/mingw64/bin/g++.exe
CC       := C:/mingw-w64/mingw64/bin/gcc.exe
CXXFLAGS :=  -g -O0 -std=c++14 -Wall -DDEBUG $(Preprocessors)
CFLAGS   :=  -g -O0 -std=c++14 -Wall -DDEBUG $(Preprocessors)
ASFLAGS  := 
AS       := C:/mingw-w64/mingw64/bin/as.exe


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files\CodeLite
Objects0=$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/IOPacket.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

PostBuild:
	@echo Executing Post Build commands ...
	copy .\lib\SFML-2.4.2\bin\* .\Debug
	copy .\res\* .\Debug
	if not exist .\Debug\cache mkdir .\Debug\cache
	if not exist .\Debug\screen mkdir .\Debug\screen
	@echo Done

MakeIntermediateDirs:
	@$(MakeDirCommand) "./Debug"


$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "./Debug"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/dev/cpp/misja008_drone_io/misja008_drone_io/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM main.cpp

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) main.cpp

$(IntermediateDirectory)/IOPacket.cpp$(ObjectSuffix): IOPacket.cpp $(IntermediateDirectory)/IOPacket.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/dev/cpp/misja008_drone_io/misja008_drone_io/IOPacket.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/IOPacket.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/IOPacket.cpp$(DependSuffix): IOPacket.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/IOPacket.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/IOPacket.cpp$(DependSuffix) -MM IOPacket.cpp

$(IntermediateDirectory)/IOPacket.cpp$(PreprocessSuffix): IOPacket.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/IOPacket.cpp$(PreprocessSuffix) IOPacket.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


