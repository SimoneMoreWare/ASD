/*
    parametro matrice tridimensionale D^2 X R X C

    funzione flatten alloca una nuova matrice bidimensionale di dimensione (DXR) X (DXC)
    ricopia i contenuti della matrice ricevuta con uno schema preciso
    ritorna la matrice
*/

int **flatten(int D,int R,int C,int ***mat3d){
    int **mat2d;
    int n_righe = D*R;
    int n_colonne = D*C;
    int i,j,k;
    int di=0,dj=0;
    
    mat2d = (int **) malloc(n_righe*sizeof(int *));
    for(i=0;i<n_righe;i++) mat2d[i] = (int *) malloc(n_colonne*sizeof(int));
    
    for(k=0;k<D*D;k++){
        for(i=0;i<R;i++){
            for(j=0;j<C;j++){
                mat2d[i+di][j+dj] = mat3d[i][j][k];
            }
        }
       
        di=di+c 
	if (di>=(D*C)) { di=0; dj=dj+R; }
    }
    
    return mat2d;
}
