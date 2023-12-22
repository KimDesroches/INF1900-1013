# Polytechnique Montréal

Département de génie informatique et génie logiciel

INF1900: Projet initial de système embarqué

# Grille de correction des programmes:

Identification:
+ Travail    : Mise en commun du code et formation de librairies
+ Section #  : 1
+ Équipe #   : 1013
+ Correcteur : Charles De Lafontaine

# CODE

| Points importants                                        | Poids       |
| -------------------------------------------------------- | ----------- |
| La qualités et le choix de vos portions de code choisies | (4.4/5.0)      |
| La qualités de vos modifications aux Makefiles           | (4/5.0)      |
| __Résultat partiel__                                     | __(8.4/10.0)__ |

# RAPPORT

| Points importants                                                           | Poids      |
| --------------------------------------------------------------------------- | ---------- |
| Explications cohérentes par rapport au code retenu pour former la librairie | (1.4/2.0)     |
| Explications cohérentes par rapport aux Makefiles modifiés                  | (1.4/2.0)     |
| Explications claires avec un bon niveau de détails                          | (1.4/2.0)     |
| Bon français                                                                | (0.75/1.0)     |
| __Résultat partiel__                                                        | __(4.95/7.0)__ |

# GÉNÉRALITÉS
## Bonne soumission de l'ensemble du code et du rapport selon le format demandé 

| Pénalité par erreur      | -0.5       |
| ------------------------ | ---------- |
| compilation sans erreurs |            |
| etc                      |            |
| __Résultat partiel__     | __(3/3.0)__ |


# Résultat

__Total des points: 16.35/20__

# Commentaires du correcteur:

## >>> RAPPORT <<< 

- ＤÉＴＡＩＬＳ:      7️⃣/🔟
- 🇫​​🇴​​🇷​​🇲​​🇦​​🇹​:       ✅
- 𝔽ℝ𝔸ℕℂ𝔸𝕀𝕊 (𝕊𝕋ℝ𝕀ℂ𝕋): ❌, revoir ATMega244pa

## >>> MAKEFILES <<< 

- Makefile commun:         ❌
- Makefiles synthétisés:   ❌

## >>> COMPILATION <<< 

- Compilation automatique par le grader:  ✅
- Aucun *warning*:                        ✅
- Aucune *error*:                         ✅
- Aucun fichiers indésirables:            ✅

## >>> CODE <<< 

- Attention à la nomenclature de vos noms de fichiers, ceux-ci devraient être en PascalCase.
- Vous auriez dû (pu) inclure un header pour Project.cpp afin d'y définir importations, constantes, etc. et faciliter la lecture de votre implémentation, à faire attention pour la remise de votre projet final.
- Toujours préférer l'insertion d'une ligne vide à la fin de tous vos fichiers.
- Button.cpp:       ✅
- Button.h:         ✅, vous pourriez inclure un header 'includes', pour rôle d'inclure l'entièreté des fichiers de votre librairie, afin de réduire l'importation à une seule ligne, et ce, pour tous vos fichiers d'implémentation.
- Debug.cpp:        ✅
- Debug.h:          ✅, préférez une boucle while au lieu d'une boucle do...while.
- Delay.cpp:        je ne comprends pas l'utilité et le lien avec le nom de votre implémentation; il s'agit d'un hack ici qui n'est pas du tout portable, en plus de l'ambiguité causée par delay_X d'AVR. Attention aux variables magiques.
- Delay.h: attention au mixin #pragma once avec #ifndef. Choisissez simplement l'un, ou l'autre, pas les deux au sein de votre implémentation (ayant les deux la même tâche selon votre approche).
- Led.cpp:          ✅
- Led.h:            ✅
- Navigation.cpp:   ✅, sauf votre /100.
- Navigation.h:     ✅
- RS232.cpp:        revoir la nomenclature de vos noms de fichiers (PascalCase -> Rs232), revoir variables magiques.
- RS232.h:          ✅
- Timer.cpp:        attention aux variables magiques.
- Timer.h:          ✅

💧 Watermark: 🄲🄳🄻, 𝟤𝟦/𝟣𝟣/𝟤𝟥 ✅

# Basé sur le commit suivant
```
commit a509059142e8fb1306f3beb7d200c06af75e85a4
Author: ghfal <ghfal>
Date:   Tue Oct 31 16:29:01 2023 -0400

    pdf
```

# Fichiers indésirables pertinents
Aucun

# Tous les fichiers indésirables
Aucun

# Sorties de `make` dans les sous-répertoires

## Sortie de `make` dans `tp/tp7/lib`
```
make : on entre dans le répertoire « /home/gigl/Bureau/WS/inf1900-grader/correction_tp7/1013/tp/tp7/lib »
avr-gcc -I. -I/usr/include/simavr -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c button.cpp
avr-gcc -I. -I/usr/include/simavr -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c can.cpp
avr-gcc -I. -I/usr/include/simavr -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c debug.cpp
avr-gcc -I. -I/usr/include/simavr -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c delay.cpp
avr-gcc -I. -I/usr/include/simavr -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c led.cpp
avr-gcc -I. -I/usr/include/simavr -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c memoire_24.cpp
avr-gcc -I. -I/usr/include/simavr -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c navigation.cpp
avr-gcc -I. -I/usr/include/simavr -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c RS232.cpp
avr-gcc -I. -I/usr/include/simavr -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c Timer.cpp
avr-ar -crs libstatic.a  button.o can.o debug.o delay.o led.o memoire_24.o navigation.o RS232.o Timer.o
make : on quitte le répertoire « /home/gigl/Bureau/WS/inf1900-grader/correction_tp7/1013/tp/tp7/lib »

```

## Sortie de `make` dans `tp/tp7/exec`
```
make : on entre dans le répertoire « /home/gigl/Bureau/WS/inf1900-grader/correction_tp7/1013/tp/tp7/exec »
avr-gcc -I. -I/usr/include/simavr -MMD -I../lib -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -fno-exceptions -c project.cpp
avr-gcc -Wl,-Map,test.elf.map -mmcu=atmega324pa -o test.elf  project.o \
-lm -L../lib -lstatic
avr-objcopy -j .text -j .data -O ihex test.elf test.hex
make : on quitte le répertoire « /home/gigl/Bureau/WS/inf1900-grader/correction_tp7/1013/tp/tp7/exec »

```
