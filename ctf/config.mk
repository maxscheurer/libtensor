DEFAULT_COMPONENTS = ctf

BLAS        = -llapack -lblas
LIBS        = $(BLAS) 
CXX         = mpicxx
WARN_FLAGS  = #-Drestrict = -Wall 
OPT_FLAGS   = -g -O3
CXXFLAGS    = -fopenmp $(OPT_FLAGS) $(WARN_FLAGS) 
DEFS        = -D__STDC_LIMIT_MACROS
LDFLAGS     = 
INCLUDES    = 
AR          = ar -crs
DEPFLAGS    = -MT $@ -MD -MP -MF $(DEPDIR)/$(notdir $*).Po

#uncomment below to enable performance profiling
#DEFS      := $(DEFS) -DPROFILE

#uncomment below to enable CTF debugging and status output
#DEFS      := $(DEFS) -DDEBUG=1

#SCALAPACK only necessary for pgemm tests and benchmarks 
#LIBS      := $(LIBS) -L$(HOME)/work/scalapack-2.0.2/lib -lscalapack -lgfortran
#DEFS      := $(DEFS) -DUSE_SCALAPACK

