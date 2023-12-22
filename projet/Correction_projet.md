# Polytechnique Montréal

Département de génie informatique et génie logiciel

INF1900: Projet initial de système embarqué

# Grille de correction des programmes:

Identification:
+ Travail    : Projet final
+ Section #  : 1
+ Équipe #   : 1013
+ Correcteur : Ghali Chraibi

# LISIBILITÉ
## En-têtes en début de programme   

| Pénalité par erreur                          | -1.5       |
| -------------------------------------------- | ---------- |
| Noms des auteurs                             |            |
| Description du programme                     |            |
| Identifications matérielles (Broches I/O)    |            |
| Table des états ou autres s'il y a lieu      |            |
| __Résultat partiel__                         | __(1/1.5)__ |

- Votre fichier principal `MainAlgo.cpp` ne contient pas de description matérielle exhaustive. Cependant, je retire qu'une partie de la pénalité par erreur car votre README.md couvre suffisamment la description du programme et chaque fichier de votre librairie contient une identification matérielle exhaustive. (-0.5)

## Identificateurs significatifs (Autodocumentation)

| Points importants                            | Poids      |
| -------------------------------------------- | ---------- |
| Absence de *chiffres magiques*               | (0/0.5)     |
| Noms de variables décrivent l'intention      | (0.1/0.5)     |
| Noms de fonctions décrivent l'intention      | (0.5/0.5)     |
| __Résultat partiel__                         | __(0.6/1.5)__ |

- Plusieurs chiffres magiques : `Game.cpp` (43, 45, 191),  `Music.cpp` (8, 14), `Navigation.cpp` (43, 47, 51, 55), etc. (-0.5)

- Les noms des paramètres de fonctions doivent être en `camelCase`: `RED_DELAY`, `DELAY_A`, etc. (-0.1)
- Les noms des enum class doivent être en PascalCase: `selectionState`, `directions` (-0.1)
- Quelques variablers ont des noms non significatifs: `interrupt`, `selection` et `validation` (-0.2)

- Bons choix de noms de fonctions!
- 
## Commentaires pertinents

Bonnes raisons d'un commentaire
 + Explication d'un algorithme 
 + Procédure peu évidente (ou *hack*)
 + Référence d'extraits de code copiés d'Internet
 + Détail du POURQUOI d'un extrait de code

| Pénalité par erreur                          | -0.5       |
| -------------------------------------------- | ---------- |
| __Résultat partiel__                         | __(1/1.0)__ |


## Indentation   

| Points importants                            | Poids      |
| -------------------------------------------- | ---------- |
| Indentation structurée                       | (/0.5)     |
| Indentation uniforme dans le programme       | (/0.5)     |
| __Résultat partiel__                         | __(0.5/1.0)__ |

- La structure n'est pas uniforme: parfois 4 espaces, parfois 2 indentations. (-0.5)

# MODULARITÉ ET COMPRÉHENSION
## Fonctions bien définies

| Pénalité par erreur                          | -0.5       |
| -------------------------------------------- | ---------- |
| Responsabilité unique d'une fonction         |            |
| Maximum de 4 paramètres                      |            |
| Absence de code dupliqué                     |            |
| etc                                          |            |
| __Résultat partiel__                         | __(0.5/1.0)__ |

- Plusieurs fonctions manquent de modularité. Il faudrait les séparer en plusieurs fonctions plus petites afin de faciliter la compréhension du code. (Ex: `processMovement`, `executeState`) (-0.5)

## Bonne application des concepts de programmation et systèmes embarqués

| Pénalité par erreur                          | -1.0       |
| -------------------------------------------- | ---------- |
| Utilisation appropriée des registres         |            |
| Machine à états codée clairement             |            |
| Délais et minuteries utilisés judicieusement |            |
| PWM bien établi                              |            |
| Scrutation et interruptions bien utilisées   |            |
| etc                                          |            |
| __Résultat partiel__                         | __(4/4.0)__ |

- Bonne utilisation des registres et des minuteries. Bravo!

# FONCTIONNALITÉS
## Git

| Points importants                            | Poids      |
| -------------------------------------------- | ---------- |
| Fichiers aux bons endroits                   | (/1.5)     |
| Absence de fichiers inutiles                 | (/1.5)     |
| __Résultat partiel__                         | __(3/3.0)__ |


## Compilation    

| Points importants                            | Poids      |
| -------------------------------------------- | ---------- |
| Absence de messages d'erreurs de compilation | (/1.5)     |
| Absence de messages d'attention (*warning*)  | (/0.5)     |
| __Résultat partiel__                         | __(2/2.0)__ |
   

## Évaluation boîte noire  

| Points importants                            | Poids      |
| -------------------------------------------- | ---------- |
| Cas normal de fonctionnement                 | (/2.5)     |
| Cas limites observables                      | (/2.5)     |
| __Résultat partiel__                         | __(5/5.0)__ |

# Résultat

__Total des points: 17.6/20__

# Commentaires du correcteur:

Votre projet montre une bonne application des concepts de programmation et des systèmes embarqués. Cependant, pour améliorer la qualité de votre code, je suggère de prêter une attention plus soutenue aux identificateurs : réduisez les chiffres magiques et choisissez des noms de variables plus descriptifs. Faites aussi plus attention à la modularité de vos fonctions. Vous avez bien géré l'organisation générale du projet. Un excellent travail d'ensemble ! 

Passez de belles fêtes et bonne chance pour vos futurs projets. 🌟

# Basé sur le commit suivant
```
commit cb5e91b1d8735e8f1b91dd5d2ec40370b33eca12
Author: ghfal <ghfal>
Date:   Mon Dec 4 20:32:11 2023 -0500

    REMISE FINALE, MERCI
```

# Fichiers indésirables pertinents
Aucun

# Tous les fichiers indésirables
```
tp/tp9/exec/writing/progmem.out
```

# Sorties de `make` dans les sous-répertoires

## Sortie de `make` dans `projet/lib`
```
avr-gcc -I. -I/usr/include/simavr -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c Button.cpp
avr-gcc -I. -I/usr/include/simavr -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c Corner.cpp
avr-gcc -I. -I/usr/include/simavr -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c Debug.cpp
avr-gcc -I. -I/usr/include/simavr -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c Delay.cpp
avr-gcc -I. -I/usr/include/simavr -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c Game.cpp
avr-gcc -I. -I/usr/include/simavr -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c Led.cpp
avr-gcc -I. -I/usr/include/simavr -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c LineFollower.cpp
avr-gcc -I. -I/usr/include/simavr -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c Music.cpp
avr-gcc -I. -I/usr/include/simavr -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c Navigation.cpp
avr-gcc -I. -I/usr/include/simavr -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c Node.cpp
avr-gcc -I. -I/usr/include/simavr -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c Robot.cpp
avr-gcc -I. -I/usr/include/simavr -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c Rs232.cpp
avr-gcc -I. -I/usr/include/simavr -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c Timer.cpp
avr-gcc -I. -I/usr/include/simavr -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c Trajectory.cpp
avr-gcc -I. -I/usr/include/simavr -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c can.cpp
avr-gcc -I. -I/usr/include/simavr -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c customprocs.cpp
avr-gcc -I. -I/usr/include/simavr -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c lcm_so1602dtr_m.cpp
avr-gcc -I. -I/usr/include/simavr -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c lcm_so1602dtr_m_fw.cpp
avr-gcc -I. -I/usr/include/simavr -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c memoire24.cpp
avr-ar -crs libstatic.a  Button.o Corner.o Debug.o Delay.o Game.o Led.o LineFollower.o Music.o Navigation.o Node.o Robot.o Rs232.o Timer.o Trajectory.o can.o customprocs.o lcm_so1602dtr_m.o lcm_so1602dtr_m_fw.o memoire24.o

```

## Sortie de `make` dans `projet/app`
```
avr-gcc -I. -I/usr/include/simavr -MMD -I../lib -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c MainAlgo.cpp
avr-gcc -Wl,-Map,test.elf.map -mmcu=atmega324pa -o test.elf  MainAlgo.o \
	-lm -L../lib -lstatic
/usr/local/opt/avr-binutils/bin/avr-ld: cannot find -lstatic: No such file or directory
collect2: error: ld returned 1 exit status
make: *** [test.elf] Error 1

```
