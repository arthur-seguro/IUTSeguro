#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>  
#include "myalloc-bloc-entete-0.h"

#define TAILLE_MAX 1024
#define ENTETE_SIZE (ALIGN(sizeof(struct bloc_entete)))
#define ALIGNMENT 8
#define ALIGN(size) (((size) + (ALIGNMENT-1)) & ~(ALIGNMENT-1))
//void* myalloc1(size_t);
//void* myalloc2(size_t);
//void myfree(void*);
void* myalloc3(size_t);
void myfree2(void*);
extern void blocinfo(void*);
void* debut;

int main(int argc, char* argv[]){
  
    debut = sbrk(0);
    void* a = myalloc3(10);
    printf("%p\n",a);
    void * b = myalloc3(12);
    printf("%p\n",b);
    // See if its free or not 
    bloc_entete* block = (bloc_entete*)((char*)a-ENTETE_SIZE);
    printf("__________%d________%d________\n",block->precedent_ptr, block->suivant_ptr);
    myfree2(a);
    printf("__________%d________%d________\n",block->precedent_ptr, block->suivant_ptr);
    void *d = myalloc3(5);
    printf("%p\n",d);
    printf("%p\n",a);
    printf("__________%d________%d________\n",block->precedent_ptr, block->suivant_ptr);
}

void* myalloc3(size_t t){
  bloc_entete* ptr = (bloc_entete*)debut;
  bloc_entete* ptrchange ; 
  bloc_entete* ptrchange2 ;

    //parcours de liste pour le recyclage 
    while ((void*) ptr != sbrk(0))
    {
      printf("montrer : suivant :%d precedent : %d\n", ptr->suivant_ptr,ptr->precedent_ptr);
      if(ptr->taille >= ALIGN(t)){
        ptrchange = ptr->suivant_ptr;
        ptrchange2 = ptr->precedent_ptr;
        if (ptr->suivant_ptr != NULL)
          ptrchange->precedent_ptr = ptrchange2;
        else
          ptrchange2->suivant_ptr = NULL;
        if(ptr->precedent_ptr!=NULL)
          ptrchange2->suivant_ptr = ptrchange;
        else
          ptrchange->precedent_ptr = NULL;

        return (void*) ptr + ENTETE_SIZE;
        
      }
      if(ptr->suivant_ptr == NULL)
        break;
      else
        ptr = ptr->suivant_ptr;
    }

    //creation d'un nouveau bloc
    void* res = sbrk(ALIGN(t) + ENTETE_SIZE);
    bloc_entete* entt = (bloc_entete*) res;
    entt->taille = ALIGN(t);
    entt->suivant_ptr = NULL;
    entt->precedent_ptr = NULL;
    res = (char *) res;
    res += ENTETE_SIZE;	
    res = (void*) res;
    return res;
}

void myfree2(void* ptr ){
  bloc_entete* ptrcourant = (bloc_entete*) debut;
  bloc_entete* ptrchange = (bloc_entete*) ptr;
  int test = 1;

  while (test == 1){
    if (ptrcourant->precedent_ptr == NULL)
    {
      ptrcourant->precedent_ptr = ptrchange;
      ptrchange->suivant_ptr = ptrcourant;
      test = 0;
    }
    ptrcourant = ptrcourant->precedent_ptr;
  }
}



/*void* myalloc2(size_t t){

	bloc_entete* ptr = (bloc_entete*)debut;
	char* ptr2;

	while((void*) ptr != sbrk(0)){
    ptr2 = (char*)ptr;
		if(ptr->libre == 1){
			if(ptr->taille >= ALIGN(t)){
				ptr->libre = 0;
				return (void*) ptr2 + ENTETE_SIZE;
			}
		}
		ptr = (bloc_entete*) ptr2 + ENTETE_SIZE + ptr->taille;	
	}

  return myalloc1(t);
	
  
}

void* myalloc1(size_t t){
  void* res = sbrk(ALIGN(t) + ENTETE_SIZE);

	struct bloc_entete* entt = (bloc_entete*) res;
	entt->taille = ALIGN(t);
	entt->libre = 0;
	res = (char *) res;
	res += ENTETE_SIZE;	
	res = (void*) res;
	return res;
}

void myfree(void* ptr ){
	char* ptr2;
	ptr2 = (char*) ptr - ENTETE_SIZE;
	bloc_entete* bloc = (bloc_entete*) ptr2;
	bloc->libre = 1; 
}*/
