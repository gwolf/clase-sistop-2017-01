require 'rfusefs'

class HelloDir
  def contents(path)
      fn = File.join(@base,path)
  Dir.entries(fn).map { |file|
  file = file.sub(/^#{fn}\/?/,'')
  if ['..','.'].include?(file)
    nil
  else
    file
  end
  }.compact.sort
  end
  def file?(path)
    path == '/hello.txt'
  end
  def read_file(path)
	"Hello, World!\n"    
  end
end

hellodir = HelloDir.new
FuseFS.set_root( hellodir )

# Mount under a directory given on the command line.
FuseFS.mount_under ARGV.shift
FuseFS.run
