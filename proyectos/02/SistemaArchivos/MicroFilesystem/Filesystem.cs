using System;
using System.Collections.Generic;
using System.IO;
using System.IO.Compression;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MicroFilesystem
{
    class Filesystem
    {
        private string projectPath = Environment.CurrentDirectory;
        private string filesystemPath;
        private string userInput;
        private List<string> history;
        private List<string> commands;

        public Filesystem()
        {
            int startIndex = projectPath.IndexOf(@"MicroFilesystem");
            filesystemPath = projectPath.Remove(startIndex);

            if(File.Exists(filesystemPath + "FileSystem.zip"))
            {
                Console.WriteLine(filesystemPath);
                Console.WriteLine("El archivo FileSystem.zip existe!");
                Console.ReadKey();
            }
            else
            {
                Console.WriteLine("No se encontró FileSystem.zip.");
                Console.WriteLine("PRESIONA ENTER PARA TERMINAR EL PROGRAMA");
                Console.ReadKey();
                Environment.Exit(-1);
            }
           
            commands = new List<string>();
            InitializeCommands();
        }

        public void run()
        {

        }

        private void InitializeCommands()
        {
            commands.Add("createfile");     //  Permite crear archivos nuevos
            commands.Add("createdir");      //  Permite crear subdirectorios nuevos
            commands.Add("read");           //  Leer contenido de archivos
            commands.Add("writeto");        //  Escribir en archivos
            commands.Add("list");           //  Listar subdirectorios y archivos
            commands.Add("help");           //  Imprime lista de comandos válidos
            commands.Add("history");        //  Historial de comandos ingresados
            commands.Add("remove");         //  Eliminar archivos o subdirectorios
            commands.Add("exit");           //  Salir del programa
        }
    }
}
