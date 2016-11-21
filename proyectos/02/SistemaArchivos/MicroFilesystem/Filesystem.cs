using System;
using System.Collections.Generic;
using System.Diagnostics;
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
                ZipFile.ExtractToDirectory(filesystemPath + "FileSystem.zip", filesystemPath + "FileSystem");
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
                    case "clear":
                        if(input.Length == 1)
                        {
                            Console.Clear();
                        }
                        else
                        {
                            Console.WriteLine("Este comando no acepta parámetros.");
                        }
                        break; 
                    case "createfile":
                        if(input.Length >= 2)
                        {
                            CreateFile(input);
                        }
                        else
                        {
                            Console.WriteLine("Este comando requiere especificar el nombre del archivo a crear.");
                        }
                        break;
                    case "read":
                        Console.WriteLine("read");
                        break;
                    case "edit":
                        if (input.Length >= 2)
                        {
                            Edit(input);
                        }
                        else
                        {
                            Console.WriteLine("Este comando requiere especificar el nombre del archivo a editar.");
                        }
                        break;
                    case "list":
                        if (input.Length == 1)
                        {
                            List();
                        }
                        else
                        {
                            Console.WriteLine("Este comando no acepta parámetros.");
                        }
                        break;
                    case "help":
                        if(input.Length == 1)
                        {
                            Help();
                        }
                        else
                        {
                            Console.WriteLine("Este comando no acepta parámetros.");
                        }
                        break;
                    case "history":
                        if (input.Length == 1)
                        {
                            History();
                        }
                        else
                        {
                            Console.WriteLine("Este comando no acepta parámetros.");
                        }
                        break;
                    case "remove":
                        Console.WriteLine("remove");
                        break;
                    case "exit":
                        if(input.Length == 1)
                        {
                            Exit();
                        }
                        else
                        {
                            Console.WriteLine("Este comando no acepta parámetros.");
                        }
                        break;
                    case "":
                        break;
                    default:
                        Console.WriteLine("Comando no válido. Ingresa 'help' para ver una lista de los comandos disponibles.");
                        break;
                }

            }
            while (userInput != "exit");
        }

        public void CreateFile(string[] input)
        {
            string filename = "";
            for (int i = 1; i < input.Length; i++) 
            {
                //  Al primer caracter no se le agrega un espacio
                if(i == 1)
                {
                    filename += input[i];
                }
                //  Si al archivo se le agrega una extensión.
                else if(input[i].StartsWith("."))
                {
                    filename += input[i];
                }
                //  Si el archivo no contiene extensión
                else
                {
                    filename += " " + input[i];
                }
            }

            if (filename.Length > 15)
            {
                Console.WriteLine("El límite de nombre de un archivo son 15 caracteres (incluyendo espacios y extensión).");
                return;
            }

            if(File.Exists(filesystemPath + @"FileSystem\" + filename))
            {
                Console.WriteLine("Ya existe un archivo con este nombre.");
                return;
            }
            else
            {
                try
                {
                    var file = File.Create(filesystemPath + @"FileSystem\" + filename);
                    file.Close();
                }
                catch(Exception)
                {
                    Console.WriteLine("No se pudo crear el archivo. Vuelve a intentarlo más tarde.");
                }
            }
        }

        public void Read()
        {

        }

        public void Edit(string[] input)
        {
            string filename = "";
            for (int i = 1; i < input.Length; i++)
            {
                //  Al primer caracter no se le agrega un espacio
                if (i == 1)
                {
                    filename += input[i];
                }
                //  Si al archivo se le agrega una extensión.
                else if (input[i].StartsWith("."))
                {
                    filename += input[i];
                }
                //  Si el archivo no contiene extensión
                else
                {
                    filename += " " + input[i];
                }
            }

            //  Si el archivo a editar no existe.
            if(!File.Exists(filesystemPath + @"FileSystem\" + filename))
            {
                Console.WriteLine("El archivo no existe.");
                return;
            }
            else
            {
                //  Invoca al bloc de notas de Windows para permitir la escritura en el archivo.
                Process notepad = new Process();
                notepad.StartInfo = new ProcessStartInfo(@"notepad.exe", (filesystemPath + @"FileSystem\" + filename));

                Console.WriteLine("La ejecución del programa continuará una vez que el bloc de notas se haya cerrado.");
                notepad.Start();
                notepad.WaitForExit();
                Console.WriteLine("Resumiendo la ejecución del programa...");
            }
        }

        public void List()
        {
            var fileList = Directory.EnumerateFiles(filesystemPath + @"FileSystem\");

            if(fileList.Count() == 0)
            {
                Console.WriteLine("No hay archivos creados.");
            }
            else
            {
                Console.WriteLine("Archivos:");
                foreach (var entry in fileList)
                {
                    Console.WriteLine("\t>> {0}", entry.Substring(entry.LastIndexOf(@"\") + 1));
                }
            }
        }

        public void Help()
        {
            Console.WriteLine("***************************************************************************************");
            Console.WriteLine("*****{0,36}AYUDA{0,36}*****", "");
            Console.WriteLine("***************************************************************************************");

            Console.WriteLine("> createfile [nombre_archivo]");
            Console.WriteLine("\tPermite crear un archivo especificando su nombre (no más de 15 caracteres).\n");

            Console.WriteLine("> clear");
            Console.WriteLine("\tLimpia la pantalla.\n");

            Console.WriteLine("> read [nombre_archivo]");
            Console.WriteLine("\tDespliega todo el contenido de un archivo en pantalla, si es que existe.\n");

            Console.WriteLine("> edit [nombre_archivo]");
            Console.WriteLine("\tPermite editar el contenido de un archivo, si es que existe.\n");

            Console.WriteLine("> list");
            Console.WriteLine("\tLista los archivos contenidos dentro del directorio.\n");

            Console.WriteLine("> help");
            Console.WriteLine("\tDespliega una lista de comandos disponibles.\n");

            Console.WriteLine("> history");
            Console.WriteLine("\tMuestra una lista de todos los comandos ingresados.\n");

            Console.WriteLine("> remove [nombre_archivo]");
            Console.WriteLine("\tElimina un archivo (especificando su nombre), si es que existe.\n");

            Console.WriteLine(">> exit");
            Console.WriteLine("\tTermina la ejecución del programa y guarda todos los cambios.\n");

            Console.WriteLine("***************************************************************************************");
        }

        public void History()
        {
            Console.WriteLine("Lista de comandos ingresados: ");
            foreach (var entry in history)
                Console.WriteLine("\t>> " + entry);
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
            commands.Add("edit");           //  Editar un archivo
            commands.Add("list");           //  Listar subdirectorios y archivos
            commands.Add("help");           //  Imprime lista de comandos válidos
            commands.Add("history");        //  Historial de comandos ingresados
            commands.Add("remove");         //  Eliminar archivos o subdirectorios
            commands.Add("exit");           //  Salir del programa
        }
    }
}
