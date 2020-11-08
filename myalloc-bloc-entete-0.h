#include <stdlib.h>
#include <unistd.h>

#define ALIGNMENT 8
#define ALIGN(size) (((size) + (ALIGNMENT-1)) & ~(ALIGNMENT-1))

/*typedef struct bloc_entete
{
 size_t taille; //taille du bloc utilisateur
 unsigned short libre : 1 ; //drapeau de 1 bit qui indique si le bloc est libre ou utilise: 1 libre, 0 utilise.
} bloc_entete ;*/

typedef struct bloc_entete
{
    size_t taille; //taille du bloc utilisateurstruct 
    struct bloc_entete* suivant_ptr ;// pointeur sur le blocsuivant dans la listestruct 
    struct bloc_entete* precedent_ptr ;// pointeur sur le blocprecedent dans la liste
} bloc_entete ;
