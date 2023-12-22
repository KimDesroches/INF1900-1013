
MCU=atmega324pa

# _____________________________Changement nom_________________________________
PROJECTNAME=libstatic
#_____________________________________________________________________________


# _____________________________Fichiers sources_______________________________
PRJSRC= $(wildcard *.cpp)
#_____________________________________________________________________________


# Inclusions additionnels (ex: -I/path/to/mydir)
INC=

# Libraires a lier (ex: -lmylib)
LIBS=

# Niveau d'optimization
# Utilisez s (size opt), 1, 2, 3 ou 0 (off)
OPTLEVEL=s

# Programmer ID - Ne pas changer 
# Liste complete des IDs disponible avec avrdude
AVRDUDE_PROGRAMMERID=usbasp

####### variables #######

#compilateur utilise
CC=avr-gcc

# _______________________________Ajout ar____________________________________
AR=avr-ar
#_____________________________________________________________________________


#pour copier le contenu d'un fichier objet vers un autre
OBJCOPY=avr-objcopy
#pour permettre le transfert vers le microcontroleur
AVRDUDE=avrdude
#pour supprimer les fichiers lorsque l'on appel make clean
REMOVE=rm -f


####### Options de compilation #######

# Flags pour le compilateur en C
CFLAGS=-I. -I/usr/include/simavr -MMD $(INC) -g -mmcu=$(MCU) -O$(OPTLEVEL) \
	-std=c++14 -fpack-struct -fshort-enums \
	-funsigned-bitfields -funsigned-char \
	-Wall

# Flags pour le compilateur en C++
CXXFLAGS=-fno-exceptions

# Linker pour lier les librairies utilisees
LDFLAGS=-Wl,-Map,$(TRG).map -mmcu=$(MCU)


####### Cible (Target) #######

# ____________________________Changer extension______________________________
TRG=$(PROJECTNAME).a
#_____________________________________________________________________________

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


####### Creation des commandes du Makefile ####### 

# Creation des cibles Phony (Phony Target)
# En plus de la commande make qui permet de compiler
# votre projet, vous pouvez utilisez les commandes
# make all, make install et make clean
.PHONY: all install clean

# Make all permet simplement de compiler le projet
#
all: $(TRG)

# _________________________Modification cible________________________________
$(TRG): $(OBJDEPS)
	$(AR) -crs $(TRG) $(OBJDEPS)
#_____________________________________________________________________________

# Production des fichiers object
# De C a objet
%.o: %.c
	$(CC) $(CFLAGS) -c $<
# De C++ a objet
%.o: %.cpp
	$(CC) $(CFLAGS) $(CXXFLAGS) -c $<

# Verification des dependances (header dependencies)
-include *.d

# Make clean permet d'effacer tout les fichiers generes
# lors de la compilation
clean:
	$(REMOVE) $(TRG) $(TRG).map $(OBJDEPS) *.d