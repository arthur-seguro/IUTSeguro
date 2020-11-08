#include "myalloc-bloc-entete-0.h"
#include <stdio.h>


#define ENTETE_SIZE (ALIGN(sizeof(bloc_entete)))

void blocinfo(void* ptr)
{
 bloc_entete* bloc_total= (bloc_entete*) ((char*)ptr - ENTETE_SIZE);
 printf("pointeur bloc %p \n, pointeur donnees %p \n, taille totale: %d, \nbloc libre ?: %d\n",
	bloc_total,
	ptr,
	bloc_total->taille,
	bloc_total->suivant_ptr,
	bloc_total->precedent_ptr);
}
