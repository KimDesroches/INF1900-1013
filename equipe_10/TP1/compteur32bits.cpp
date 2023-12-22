/*
 * Nom: compteur 32 bits
 * Copyright (C) 2005 Matthew Khouzam
 * License http://www.gnu.org/copyleft/gpl.html GNU/GPL
 * Description: Ceci est un exemple simple de programme 
 * Version: 1.1
 * 
 * Version 1.2 par Jérôme Collin, août 2023
 * 
 */


#include <avr/io.h> 

int main()
{
  // Les 4 ports sont en mode sortie
  DDRA = 0xFF; 
  DDRB = 0xFF; 
  DDRC = 0xFF; 
  DDRD = 0xFF; 
  
  // c'est un compteur de 32 bits d'où le type unsigned long
  unsigned long compteur = 0; 

  while (true) 
  {   
    // Le port D prend les bits de 0 a 7 du compteur
    // autrement dit, l'octet de poids le plus faible.
    PORTD = compteur;       
                         
    // Le port C prend les bits de 8 à 15 du compteur 
    // en faisant un decallage de 8 bits.
    PORTC = compteur >> 8;  

    // Le port B prend les bits de 16 à 23 du compteur
    // en faisant un decallage de 16 bits.
    PORTB = compteur >> 16; 

    // Le port B prend les bits de 24 à 31 du compteur
    // en faisant un decallage de 24 bits.
    PORTA = compteur >> 24;
    
    // si le compteur est à 0xFFFF, il revient à 0 naturellement
    compteur++; 
  }
  
  return 0; 
}

