#ifndef consFile
#define consFile

    #define nbrSquareMat 8
    #define vert 1
    #define blanc -1
    #define VIDE 3 
    #define PLEIN -3
    #define UNDEFINED 4
    #define droite 5
    #define gauche 6
    #define blanc_gauche 9   
    #define blanc_droite 10
    #define vert_gauche 11 
    #define vert_droite 12  

    typedef struct Positions Positions; 
    struct Positions {
        int x; 
        int y;
    };
    typedef struct matrixJType matrixJType; 
    struct matrixJType {
        int state; // VIDE ou PLEIN
        int couleur; // blanc ou vert
    };


#endif
