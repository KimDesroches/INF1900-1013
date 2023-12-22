## Objectif
L'objectif du robot était d'effectuer, de manière autonome, différents trajets sur une carte. 

## Carte
La carte représente un parcours composé de plusieurs segments de poids différents. 
Il y a 28 points qui se retrouvent sur le plan et il est possible de les identifier à l'aide de coordonnées. 
En effet, les lignes sont numérotées de 1 à 4 et les colonnes de 1 à 7. Ces coordonnées permettent d’identifier les points du robot (destinations pour les trajets qu'effectue le robot). 

Lors  des épreuves, le robot doit toujours se déplacer en suivant le ruban. Il ne peut pas s'aventurer hors de la route. 

## Mode
Le robot doit aussi  effectuer 2 modes soit Identifier le coin et Effectuer un trajet. Le choix du mode se fait via l’appui de différents boutons sur le breadbord (robot).

### 1. Identifer le coin :
Le robot a pour objectif de déterminer sur quel coin il a été placé et dans quelle orientation il se trouve. Une fois le coin déterminé, il doit afficher sur l’écran LCD les coordonnées du point (lignes et colonnes) son orientation initiale (soit Nord, Sud, Ouest, Est).
Pour ce faire, il devra circuler sur la carte.

### 2. Effectuer le trajet :
3. Le robot doit se rendre au point entré par l’utilisateur en utilisant le trajet le plus court.
4.  La valeur de chaque segment noir a un poids de 1. Les segments jaune ont un poids de 2 et les segments rouge, un poids de 5.

Lors du trajet, un poteau sera placé sur un des points du trajet. Le robot devra alors identifier l’obstacle et changer sa direction afin d’effectuer un nouveau trajet pour se rendre à sa destination finale. 
Le nouveau trajet devra aussi tenir compte du poids de chaque segment. Un total de trois trajets doivent être effectués et l’emplacement de l’obstacle va changer à chaque fois.
