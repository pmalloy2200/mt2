# Makefile for Midterm 2 project

CC = clang
GRAPH = gnuplot
CFLAGS = -Wall -O0 -g
LFLAGS = -O0 -g
LIBS = -lm -lgsl
OBJECTS = white-dwarf.o white-dwarf-eqs.o white-dwarf-iterate.o 
EXECS = white-dwarf white-dwarf-iterate 
PNGS = rho_vs_r.png m_vs_r.png
LOGS = mass rhovsr
FUNS = 

rho_vs_r.png: rho_vs_r.gpl rhovsr
	$(GRAPH) rho_vs_r.gpl

m_vs_r.png: m_vs_r.gpl mass
	$(GRAPH) m_vs_r.gpl
    
mass: white-dwarf-iterate
	./white-dwarf-iterate > mass
        	
rhovsr: white-dwarf
	./white-dwarf > rhovsr

white-dwarf-iterate: white-dwarf-iterate.o white-dwarf-eqs.o
	${CC} $(LFLAGS) $(LIBS) -o $@ $^
	
white-dwarf: white-dwarf.o white-dwarf-eqs.o
	${CC} $(LFLAGS) $(LIBS) -o $@ $^

$(SOURCES): $(FUNS)

clean:
	rm -f $(OBJECTS)
	rm -f $(EXECS)

veryclean: clean
	rm -f $(PNGS)
	rm -f $(LOGS)
	

