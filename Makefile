OBJS	= Elements/Element_em.cpp.o \
	  JS_Access/JS_Man_em.cpp.o

OUT	= libDOMscripten.a
CXX	= em++
CC      = emcc
BUILD_CXX_FLAGS	 = -Wall -std=c++17 -g -fexceptions
BULID_CC_FLAGS   =
LINK_OPTS	 =

all: $(OBJS)
	#$(CXX) -g $(OBJS) -o $(OUT) $(LINK_OPTS)
	emar rcs $(OUT) $(OBJS)


%.cpp.o: %.cpp
	$(CXX) $< $(BUILD_CXX_FLAGS) $(LINK_OPTS) -g -c -o $@

%.c.o: %.c
	$(CXX) $< $(BUILD_CXX_FLAGS) $(LINK_OPTS) -g -c -o $@

clean:
	rm -f $(OBJS) $(OUT)

em:
	em++ letterConvert.cpp Score.cpp emscripten.cpp -o em_build/VLUtil.js -std=c++17 -s WASM=1 -s EXPORTED_RUNTIME_METHODS=ccall,cwrap -s ASSERTIONS=1
