/*escriu a la posicio indicada per la pagina page i el byte y 
el text de s*/
void writeTxt(byte page, byte y, char * s);


/*escriu el temps faltant per acabar el cafe*/
void updateGLCD();

/*dibuixa a la GLCD els dos botons d'augmentar i disminuir l'aigua*/
void creacio_botons();

/*escriu a la GLCD el percentatge d'aigua que es vol fer servir 
per fer el cafe*/
void escriure_percentatge();


/*dibuixa a la GLCD la barra que indica la quantitat d'aigua i 
crida la funcio escriure_percentatge*/
void creacio_barra();


/*dibuixa a la GLCD la tassa de cafe*/
void creacio_tassa();


/*dibuixa a la GLCD el surtidor de cafe i la part superior 
de la cafetera*/
void creacio_surtidor();

/*dibuixa a la GLCD la majoria del contorn de la cafetera que no 
s'ha dibuixat amb altre funcions*/
void contorn();

/*crida totes les funcions per dibuixar la cafetera en el seu estat inicial*/
void estatinicial();

/*fa l'animacio del boto que augmenta la quantitat d'aigua quan es clica*/
void animacio_augmentar();

/*fa l'animacio del boto que disminueix la quantitat d'aigua quan es clica*/
void animacio_disminuir();

/*quan es clica el boto d'augmentar, augmenta el valor que es mostra en el tant 
per cent, el valor del temps que es trigara a fer el cafe, actualitza la barra i 
crida la funcio animacio_augmentar*/
void augmentar();

/*quan es clica el boto de disminuir, disminueix el valor que es mostra en el tant 
per cent, el valor del temps que es trigara a fer el cafe, actualitza la barra i 
crida la funcio animacio_disminuir*/
void disminuir();

/*actualitza el valor del temps que queda per acabar de fer el cafe que es
mostra per pantalla */
void actualitzacio();

/*fa l'animacio del cafe per pantalla mentres s'esta fent*/
void animacio_cafe();

/*activa el timer, canvia el valor del tant per cent que es veia per pantalla
pel del temps que queda per acabar de fer el cafe i crida la funcio animacio_cafe*/
void cafe();

/*fa l'animacio del cafe per pantalla quan ja s'ha acabat*/
void animacio_acabat();

/*para el timer, reinicia els valors a l'estat inicial i com es mostrava la cafetera
i crida la funcio animacio_acabat*/
void acaba();

