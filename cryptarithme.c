/* Projet cryptarithme
Félix LANDREAU
7/1/24 */

#include<stdio.h>
#include<string.h>
#include<stdbool.h>



typedef struct lettre {
    char nom ;
    int val ;
}lettre ;

void afficherSTexte(char* l1, char* l2, char* total);
bool nouvelleLettre(char l, lettre* tl, int n);
int valeur(char l , lettre* lettres, int iLettres);
int puissance(int nb , int exp);
bool additionCorrecte(char* l1,int tl1, char* l2, int tl2, char* total, int ttotal, lettre* lettres, int iLettres);
void afficherSChiffres(char* l1, int tl1, char* l2, int tl2, char* total, int ttotal, lettre* lettres, int iLettres);
void test(char* l1, int tl1, char* l2, int tl2, char* total, int ttotal, lettre* lettres, int iLettres, int indexLettres ) ;


int main (){
    int nblettres = 0 ;
    int tl1 ;
    int tl2 ;
    int ttotal ;

    lettre lettres[10] ;
    int iLettres ;
    char l1[10] ;
    char l2[10] ;
    char total[10] ;
    printf("Ligne 1 : combien de lettres ? ");
    scanf("%d", &tl1);
    printf("Ligne 1 : ") ;
    scanf("%s", &l1);
    printf("Ligne 2 : combien de lettres ? ");
    scanf("%d", &tl2);
    printf("Ligne 2 : ") ;
    scanf("%s", &l2);
    printf("Total : combien de lettres ? ");
    scanf("%d", &ttotal);
    printf("Total : ") ;
    scanf("%s", &total);

    for (int i = tl1-1; i>=0 ; i-- ){
        if(nouvelleLettre(l1[i], lettres, 10)){
            lettres[iLettres].nom =l1[i] ;
            iLettres ++ ;
        }
    }
    for (int i = tl2-1; i>=0 ; i-- ){
        if(nouvelleLettre(l2[i], lettres, 10)){
            lettres[iLettres].nom =l2[i] ;
            iLettres ++ ;
        }
    }
    for (int i = ttotal-1; i>=0 ; i-- ){
        if(nouvelleLettre(total[i], lettres, 10)){
            lettres[iLettres].nom =total[i] ;
            iLettres ++ ;
        }
    }

    afficherSTexte(l1, l2, total);


    printf("iLettres = %d\n", iLettres);
    printf("lettres : ");
    for (int i = 0; i<iLettres ; i++){
        printf("%c", lettres[i].nom);
    }
    printf("\n");

    test(l1, tl1, l2, tl2, total, ttotal, lettres, iLettres, 0);
}


void afficherSTexte(char* l1,char*  l2, char* total){
    //Entrées : lignes sous forme char*
    //Sortie : affiche l'addition. Ne retourne rien
    printf("  %s\n",l1);
    printf("+ %s\n",l2);
    printf("----------\n");
    printf("= %s\n",total);
}

void afficherSChiffres(char* l1, int tl1, char* l2, int tl2, char* total, int ttotal, lettre* lettres, int iLettres){
    // Entrées : lignes, lettres et leur valeur, nombre de lettres
    // Sorties : affichage de la somme avec les chiffres à la place des lettres 
    printf("  ");
    for(int i = 0; i<tl1; i++){
        printf("%d", valeur(l1[i], lettres,  iLettres ));
    }
    printf("\n");
    printf("+ ");
    for(int i = 0; i<tl2; i++){
        printf("%d", valeur(l2[i],  lettres,  iLettres ));
    }
    printf("\n");
    printf("--------\n");
    printf("= ");
    for(int i = 0; i<ttotal; i++){
        printf("%d", valeur(total[i], lettres, iLettres ));
    }
    printf("\n");
}

bool nouvelleLettre(char l, lettre* tl, int n){
    // renvoie false si l est dans tl, true sinon
    for (int i = 0 ; i<n ; i++){
        if (l == tl[i].nom) {
            return false ;
        }
    }
    return true ;
}

bool additionCorrecte(char* l1,int tl1, char* l2, int tl2, char* total, int ttotal, lettre* lettres, int iLettres){
    int sl1 = 0 ;
    for (int i=0 ; i < tl1 ; i++){
        sl1 += valeur(l1[i], lettres, iLettres)*puissance(10, tl1-i-1) ;
    }
    int sl2 = 0 ;
    for (int i=0 ; i < tl2 ; i++){
        sl2 += valeur(l2[i], lettres, iLettres)*puissance(10, tl2-i-1) ;
    }
    int stotal = 0 ;
    for (int i=0 ; i < ttotal ; i++){
        stotal += valeur(total[i], lettres, iLettres)*puissance(10, ttotal-i-1 ) ;
    }
    bool correct = sl1 + sl2 == stotal ;
    return (correct) ;
}


int valeur(char l , lettre* lettres, int iLettres){
    for (int i = 0 ; i<iLettres ; i++){
        if ( l == lettres[i].nom){
            return (lettres[i].val) ;
        }
    }
}
int puissance(int nb , int exp){
    int s = 1 ;
    for(int i = 0; i<exp ; i++){
        s*=nb ;
    }
    return (s) ;
}

void test(char* l1, int tl1, char* l2, int tl2, char* total, int ttotal, lettre* lettres, int iLettres, int indexLettres ){
    //printf("indexLettres = %d\n", indexLettres);
    if (indexLettres == iLettres){
        if (additionCorrecte(l1, tl1, l2, tl2, total, ttotal, lettres, iLettres)){
            printf ("Une solution :\n");
            afficherSChiffres(l1, tl1, l2, tl2, total, ttotal, lettres, iLettres);
        }
    }
    else {
        bool correct ;
        for( int j = 0; j<10 ; j++){
            lettres[indexLettres].val = j ;
            correct = true ;
            for(int i = 0 ; i<indexLettres ; i++ ){
                for ( int j = i+1; j < indexLettres ; j++ ){
                    if (lettres[i].val==lettres[j].val){
                        correct = false ;
                    }
                }
            }
            if(correct) {
                test(l1, tl1, l2, tl2, total, ttotal, lettres,iLettres, indexLettres+1 );
            }
        }
    }
}