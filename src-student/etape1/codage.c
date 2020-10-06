#include "../commun/td3.h"


extern Handler HANDLER_TABLE[PALETTE_SIZE];
extern char ALPHABET_PALETTE[PALETTE_SIZE];
extern char* NOM_FICHIERS[PALETTE_SIZE];

//choix de la palette a utiliser
char* palette_courante = ALPHABET_PALETTE;

char minuscule(char c) {
	if (c <= 'Z' && c >= 'A')
		return c + 32;
	return c;
}

void ecrire_position(int fd, int position) {
	char *res = malloc(8 * sizeof(char));
	char nb[8];
	int index = 0;

	sprintf(nb, "%d", position);
	for (; index < 8 - strlen(nb); index++)
		res[index] = '0';
	for (int i = 0; i < strlen(nb); i++, index++)
		res[index] = nb[i];
	printf("%s", res);
	write(fd, res, 8);
}

void codage(int in) {

	int position = 0;
	char c;
	int index_caractere;
	char *nom_fichier;
	int out;

	while (read(in, &c, 1) != 0) {
		c = minuscule(c);
		index_caractere = get_index_for_char(c);
		nom_fichier = NOM_FICHIERS[index_caractere];        	
		out = open(nom_fichier, O_CREAT | O_WRONLY);
		ecrire_position(out, position);
		close(out);
		position++;
	}
}


void decodage(int out)
{


}

int main() {
	
	int fd = open("message.txt", O_RDONLY);
	
	codage(fd);
}
		
