#	Specification of build process of TinyRender under Linux

#------------------------BUILD VARIABLES-----------------------------
#	Directories, containing headers
INCLUDE_DIR = ../Include/
#	Output directory which will contain output compiled file
OUTPUT_DIR = ../Bin/

SOURCES = EngineManager.cpp Geometry.cpp Main.cpp Model.cpp \
	  Shaders.cpp TGAImage.cpp 

HEADERS = EngineManager.h Geometry.h Line.h Model.h Shaders.h \
	  TGAImage.h Triangle.h

#------------------------BUILD_RULES---------------------------------
TinyRenderBuilding : $(addprefix $(INCLUDE_DIR), $(HEADERS)) $(SOURCES)
	mkdir $(OUTPUT_DIR)
	g++ -std=c++14 -o $(OUTPUT_DIR)TinyRender.out -I$(INCLUDE_DIR) $(SOURCES)
