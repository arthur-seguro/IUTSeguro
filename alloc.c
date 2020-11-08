#include "myalloc-bloc-entete-0.h"



#define ENTETE_SIZE (ALIGN(sizeof(struct bloc_entete)))


void* myalloc(size_t t){

	/*char* ptr = debut;
	int ptr2;
	struct bloc_entete* bloc;
	int taille = sizeof(t);

	while(ptr!= sbrk(0)){
		bloc = (struct bloc_entete*) ptr;
		if(bloc->libre == 1){
			if(bloc->taille > taille){
				bloc->libre = 0;
				return ptr + ENTETE_SIZE;
			}
		}
		ptr2 =((int) ptr + (int) bloc->taille +  (int) ENTETE_SIZE);
		ptr = (char*) ptr2;	
	}*/
	void* res = sbrk(ALIGN(t+sizeof(struct bloc_entete)));
	struct bloc_entete entt;
	entt.taille = sizeof(t);
	entt.libre = 0;
	res = (char *) res;
	res += sizeof(entt);	
	res = (void*) res;
	return res;
}

void myfree(void* ptr ){
	char* ptr2;
	ptr2 = (char*) ptr - ENTETE_SIZE;
	bloc_entete* bloc = (bloc_entete*) ptr2;
	bloc->libre = 1; 
}
