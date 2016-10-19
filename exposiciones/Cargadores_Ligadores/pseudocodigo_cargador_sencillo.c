/*http://xikotenkaltsb.blogspot.mx/2011/04/41-cargadores-y-ligadores.html*/

/***definir la estructura del registro de encabezado ***/
struct enc_ejec{
	unsigned int dir_ini;
	/* las otras partes del encabezado del archivo ejecutable */
};

/***prototipos para las funciones usadas por el cargador***/
struct enc_ejec leer_enc( FILE *);
char leer_byte ( FILE *);

/***--------el cargador ---------***/
char *carga (File *arch_ejec);
{
	struct enc_ejec encabezado ;
	char *dire_byte;

	/* leer encabezado del archivo */*
	encabezado = leer_enc(arch_ejec);
	
	/*copiar a la memoria los segmentos de texto y datos */
	dir_byte = DIR_CARGA;
	
	while(!eof(arch_ejec)){
		dir_byte = leer (arch_ejec);
		dir_byte = dir_byte+1 ;
	}
	return ((char*) encabezado.dir_ini);
}
