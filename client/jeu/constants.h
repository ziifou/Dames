#ifndef consFile
#define consFile

    #define SQUARE_NUMBERS 8
    #define blanc -1
    #define vert 1
    #define VIDE 3 
    #define UNDEFINED 4
    #define PLEIN -3


    typedef struct matrixJType matrixJType; 
    struct matrixJType {
        int state; // VIDE ou PLEIN
        int couleur; // blanc ou vert
    };

    typedef struct Positions Positions; 
    struct Positions {
        int x; 
        int y;
    };

#endif
