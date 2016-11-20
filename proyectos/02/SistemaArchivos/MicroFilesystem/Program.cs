using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MicroFilesystem
{
    class Program
    {
        static void Main(string[] args)
        {
            Filesystem mfs = new Filesystem();
            mfs.run();
        }
    }
}
