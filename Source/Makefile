SOURCES = EngineManager.cpp Geometry.cpp Main.cpp Model.cpp \
	  Shaders.cpp TGAImage.cpp 

INCLUDE_DIR = ../Include/

HEADERS = EngineManager.h Geometry.h Line.h Model.h Shaders.h \
	  TGAImage.h Triangle.h

TinyRender.out : $(addprefix $(INCLUDE_DIR), $(HEADERS)) $(SOURCES)
	g++ -std=c++14 -I$(INCLUDE_DIR) $(SOURCES)
