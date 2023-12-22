MCU=atmega324pa

PROJECTNAME=test

PRJSRC=project.cpp

#______________________Ajout inclusion lib et liaison_________________________
# Inclusions additionnels (ex: -I/path/to/mydir)
INC= -I../lib

# Libraires a lier (ex: -lmylib)
LIBS= -L../lib -lstatic
#_____________________________________________________________________________

# Niveau d'optimization
# Utilisez s (size opt), 1, 2, 3 ou 0 (off)
OPTLEVEL=s

# Programmer ID - Ne pas changer 
# Liste complete des IDs disponible avec avrdude
AVRDUDE_PROGRAMMERID=usbasp


####### variables #######

#compilateur utilise
CC=avr-gcc
#pour copier le contenu d'un fichier objet vers un autre
OBJCOPY=avr-objcopy
#pour permettre le transfert vers le microcontroleur
AVRDUDE=avrdude
#pour supprimer les fichiers lorsque l'on appel make clean
REMOVE=rm -f
# HEXFORMAT -- format pour les fichiers produient .hex
HEXFORMAT=ihex

#________________________Chemin vers dossier lib______________________________
LIB_DIRECTORY = ../lib
#_____________________________________________________________________________

####### Options de compilation #######

# Flags pour le compilateur en C
CFLAGS=-I. -I/usr/include/simavr -MMD $(INC) -g -mmcu=$(MCU) -O$(OPTLEVEL) \
	-std=c++14 -fpack-struct -fshort-enums \
	-funsigned-bitfields -funsigned-char \
	-Wall

# Flag supplémentaire pour retirer le bogue de "array subscript 0 is outside 
# array bounds" sur avr-gcc v12
GCCVERSION := $(shell expr `$(CC) -dumpversion | cut -f1 -d.` \>= 12)
ifeq "$(GCCVERSION)" "1"
    CFLAGS += --param=min-pagesize=0
endif

# Flags pour le compilateur en C++
CXXFLAGS=-fno-exceptions

# Linker pour lier les librairies utilisees
LDFLAGS=-Wl,-Map,$(TRG).map -mmcu=$(MCU)



####### Cible (Target) #######

#Nom des cibles par defaut
TRG=$(PROJECTNAME).elf
HEXROMTRG=$(PROJECTNAME).hex
HEXTRG=$(HEXROMTRG) $(PROJECTNAME).ee.hex



####### Definition de tout les fichiers objets #######

# Cette fonction permet de differencier les fichiers .c
# des fichiers .cpp
# Fichier C
CFILES=$(filter %.c, $(PRJSRC))
# Fichier C++
CPPFILES=$(filter %.cpp, $(PRJSRC))

# Liste de tout les fichiers objet que nous devons creer
OBJDEPS=$(CFILES:.c=.o) \
	$(CPPFILES:.cpp=.o)
	
.PHONY: all install clean

# Make all permet simplement de compiler le projet
#
all: $(TRG) $(HEXROMTRG)

# Implementation de la cible
$(TRG): $(OBJDEPS)
	$(CC) $(LDFLAGS) -o $(TRG) $(OBJDEPS) \
	-lm $(LIBS)

# Production des fichiers object
# De C a objet
%.o: %.c
	$(CC) $(CFLAGS) -c $<
# De C++ a objet
%.o: %.cpp
	$(CC) $(CFLAGS) $(CXXFLAGS) -c $<

# Verification des dependances (header dependencies)
-include *.d

# Production des fichiers hex a partir des fichiers elf
%.hex: %.elf
	$(OBJCOPY) -j .text -j .data -O $(HEXFORMAT) $< $@

# Make install permet de compiler le projet puis
# d'ecrire le programme en memoire flash dans votre
# microcontroleur. Celui-ci doit etre branche par cable USB
install: $(HEXROMTRG)
	$(AVRDUDE) -c $(AVRDUDE_PROGRAMMERID) \
	-p $(MCU) -P -e -U flash:w:$(HEXROMTRG)

# Make clean permet d'effacer tout les fichiers generes
# lors de la compilation
clean:
	$(REMOVE) $(TRG) $(TRG).map $(OBJDEPS) $(HEXTRG) *.d *elf.map

#_________________Ajout regle pour effacer la librarie aussi___________________
clean_all:	
	$(REMOVE) $(TRG) $(TRG).map $(OBJDEPS) $(HEXTRG) *.d *elf.map
	$(MAKE) -C $(LIB_DIRECTORY) clean

#___________________Ajout regle pour produire la librarie______________________
lib:
	$(MAKE) -C $(LIB_DIRECTORY)

# _____________________________Ajout regle debug_______________________________
debug: CXXFLAGS += -DDEBUG -g
debug: CCFLAGS += -DDEBUG -g
debug: $(TRG) $(HEXROMTRG)