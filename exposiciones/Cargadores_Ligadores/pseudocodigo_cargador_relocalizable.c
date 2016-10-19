/*http://xikotenkaltsb.blogspot.mx/2011/04/41-cargadores-y-ligadores.html*/

Struct enc_ejc{
	Unsigned int dir_ini;
	Unsigned int tamaño_texto, tamaño_datos, tamaño_bss;
	/*otros campos del registro de encabezado*/
};

/***prototipo para las funciones usadas por el cargador***/
struct enc_ejec leer_enc( FILE *);
char leer_byte(FILE*);
char*obtener_memoria(unsigned int);
void establecer_correspondencia(char*unsigned int);

/***el cargador***/
unsigned int*carga (FILE*arch_ejec)
{
	struct enc_ejec encabezado;
	char *dir-byte, *dir_carga;
	unsigned int tamaño_prog;

	encabezado = leer_enc(arch_ejec);
	
	/*determinar el tamaño del programa y asignar el espacio*/
	/*La dirección inicial es una dirección 1ógica y no una dirección física.*/
	tamaño_prog = encabezado.tamaño_texto + encabezado.tamaño_datos + encabezado.tamaño_bss;
	dir_carga = obtener_memoria (tamaño_prg);

	/*copiar los segmentos de texto y datos*/
	dir_byte = dir_carga;
	while(!eof(arch_ejec){
		*dir_byte = leer_byte(arch_ejec);
		dir_byte = dir_byte+1;
	}

	/*establecer la correspondencia de direcciones*/
	establecer_correspondencia(dir_carga,tamaño_prog);

	return ((char*)encabezado.dir_ini);
}
