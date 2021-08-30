INCLUDE = -I../../ \

CPPFLAGS = -Wall -fPIC $(INCLUDE) $(DEBUG_DEF) -std=c++11
LIBS = libgrid.a

all : clean $(LIBS)

clean:
	rm -rf *.o *.a

libgrid.a: lbs_hashtable.o lbs_grid.o gengxin.o lbs_bitmap.o SERVER_GRID_LBS_NN_HEAP.o lbs_index.o 
	ar cr $@ $^

.o : .cpp
	g++ $(CPPFLAGS) -c $^
