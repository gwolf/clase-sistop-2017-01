using System;
using System.Collections.Generic;
using System.IO;
using System.IO.Compression;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
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
                //ZipFile.ExtractToDirectory(filesystemPath + "FileSystem.zip", filesystemPath + "FileSystem");
            }
            else
            {
                Console.WriteLine("No se encontró FileSystem.zip.");
                Console.Write("PRESIONA ENTER PARA TERMINAR EL PROGRAMA");
                Console.ReadKey();
                Environment.Exit(-1);
            }
           
            commands = new List<string>();
            history = new List<string>();
            InitializeCommands();
        }

        public void run()
        {
            do
            {
                Console.Write("mfs> ");
                userInput = Console.ReadLine();
                string[] input = Regex.Replace(userInput.Trim(' '), @"\s+", " ").Split(' ');

                if(commands.Contains(input[0]))
                {
                    history.Add(input[0]);
                }

                switch(input[0])
                {
                    /* case "test":
                        Console.WriteLine("[{0}]", userInput);
                        foreach (string c in input)
                        {
                            Console.WriteLine("\t >>[{0}]", c);
                        }
                        break;*/ 
                    case "createfile":
                        Console.WriteLine("createfile");
                        break;
                    case "read":
                        Console.WriteLine("read");
                        break;
                    case "writeto":
                        Console.WriteLine("writeto");
                        break;
                    case "list":
                        Console.WriteLine("list");
                        break;
                    case "help":
                        Console.WriteLine("help");
                        break;
                    case "history":
                        Console.WriteLine("history llamada");
                        break;
                    case "remove":
                        Console.WriteLine("remove");
                        break;
                    case "exit":
                        Console.WriteLine("EXIT");
                        break;
                    case "":
                        break;
                    default:
                        Console.WriteLine("\tIngresa un comando válido.");
                        break;
                }

            }
            while (userInput != "exit");

            /*do
            {
                Console.Write(RutaActual + "> ");
                EntradaDelTeclado = Console.ReadLine();
                string[] entrada = EntradaDelTeclado.Split(' ');

                if (comandosValidos.Contains(entrada[0].ToLower()))
                    historial.Add(entrada[0].ToLower());

                switch (entrada[0].ToLower())
                {
                    case "dir":
                        if (entrada.Length == 1)
                            Dir();
                        else
                            Dir(entrada);
                        break;
                    case "cd":
                        try
                        {
                            Cd(entrada);
                        }
                        catch (NotEnoughParametersException nepe)
                        {
                            Console.WriteLine("\tError: " + nepe.Message);
                        }
                        break;
                    case "touch":
                        try
                        {
                            Touch(entrada);
                        }
                        catch (NotEnoughParametersException nepe)
                        {
                            Console.WriteLine("\tError: " + nepe.Message);
                        }
                        catch (FileAlreadyExistsException faee)
                        {
                            Console.WriteLine("\tError: " + faee.Message);
                        }
                        break;
                    case "move":
                        try
                        {
                            Move(entrada);
                        }
                        catch (NotEnoughParametersException nepe)
                        {
                            Console.WriteLine("\tError: " + nepe.Message);
                        }
                        break;
                    case "cls":
                        Cls();
                        break;
                    case "history":
                        History();
                        break;
                    case "exit":
                        Exit(5);
                        break;
                    default:
                        Console.WriteLine("\tIngresa un comando válido");
                        break;
                }
            }
            while (EntradaDelTeclado.ToLower() != "exit"); */

            /*Console.WriteLine("El archivo zip original se eliminará...");
            Console.ReadKey();
            File.Delete(filesystemPath + "FileSystem.zip");
            Console.WriteLine("El archivo zip nuevo se está generando...");
            Console.ReadKey();
            ZipFile.CreateFromDirectory(filesystemPath + "FileSystem", filesystemPath + "FileSystem.zip");
            Console.WriteLine("El archivo temporal está a punto de destruirse...");
            Console.ReadKey();
            Directory.Delete(filesystemPath + "FileSystem", true);*/
        }

        public void CreateFile()
        {

        }

        public void Clear()
        {

        }

        public void Read()
        {

        }

        public void WriteTo()
        {

        }

        public void List()
        {

        }

        public void Help()
        {

        }

        public void History()
        {

        }

        public void Remove()
        {

        }

        public void Exit()
        {
            //  El archivo zip utilizado originalmente se borra.
            File.Delete(filesystemPath + "FileSystem.zip");
            
            //  Se crea un nuevo archivo ZIP a partir de los datos modificados en tiempo de ejecución.
            ZipFile.CreateFromDirectory(filesystemPath + "FileSystem", filesystemPath + "FileSystem.zip");
            
            //  Se elimina el directorio temporal utilizado en tiempo de ejecución.
            Directory.Delete(filesystemPath + "FileSystem", true);

            Environment.Exit(0);
        }

        private void InitializeCommands()
        {
            commands.Add("createfile");     //  Permite crear archivos nuevos
            commands.Add("clear");          //  Limpiar la pantalla
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
