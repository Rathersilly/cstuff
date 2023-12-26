# TODO: - get this wroking!
#
CXX = 'g++'.freeze
source_files = Rake::FileList['test.cpp', 'setup.cpp']
object_files = source_files.ext('.o')
ldflags = '`sdl2-config --libs` -lXext -lX11 -lm -lSDL2_image'
cflags = '`sdl2-config --cxxflags` -g -ggdb -Wall -std=c++17'
# sh "#{CXX} g++ `sdl2-config --cxxflags` #{cflags} #{ldflags} #{args[:fname]}"

task binary: object_files do
  sh "#{CXX}  #{object_files}  #{ldflags}"
  # sh "g++ #{object_files} -o a.out"
end

rule '.o' => '.cpp' do |task|
  sh "#{CXX} -c #{task.source}  #{cflags}"
end

# task default: :binary
task default: :binary

# heredoc = <<-END
#
# CC = 'g++'
# Sources = "simple_sdl_test.cpp setup.cpp"
#
#   Ldflags = '-L/usr/local/lib -lfltk -lXext -lX11 -lm -lfltk_images'
#
# task :default do
#   sh "g++ #{Sources} `sdl2-config --libs`"
#
#   # sh "g++ `sdl2-config --cflags` `sdl2-config --libs`  #{Sources} #{Ldflags} "
# end
#
# # from command line : $ rake fltk[3, "hello"]
# task :fltk, [:fname] do |t, args|
#
#   source_files = Rake::FileList('foo.cpp')
#   object_files = source_files.ext('.o')
#   ldflags = '-L/usr/local/lib -lfltk -lXext -lX11 -lm -lfltk_images'
#   cflags = '-g -ggdb -Wall -std=c++17'
#   p t
#   p args
#   p args[:fname]
#   sh "#{CXX} g++ `sdl2-config --cxxflags` #{cflags} #{ldflags} #{args[:fname]}"
# end
#
# CXX      = $(shell fltk-config --cxx)
# DEBUG    = -gb
# # CXXFLAGS = $(shell fltk-config --use-gl --use-images --cxxflags ) -I.
# CXXFLAGS = $(shell fltk-config --use-gl --use-images --cxxflags )
# LDFLAGS  = $(shell fltk-config --use-gl --use-images --ldflags )
# LDSTATIC = $(shell fltk-config --use-gl --use-images --ldstaticflags )
# LINK     = $(CXX)
# task :argtest, [:a] do |_t, args|
#   p args
# end
#
# END
