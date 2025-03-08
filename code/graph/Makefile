CFLAGS		= -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include/ -g
LIBS		= /usr/lib64/libglib-2.0.so -lgtest
CC			= g++

all: ttx

%.o:%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

ttx:unit_test_kahn.o graph.o graph_bfscan.o graph_dfscan.o graph_prim.o graph_kruskal.o graph_shortest_path.o
	$(CC) -o $@ $^ $(LIBS)  
