build_dir              = ./build
src_dir                = ./src
dependencies_dir       = ./dependencies
graphics_dir           = $(dependencies_dir)/raylib
graphics_lib_dir       = $(graphics_dir)/lib
graphics_include_dir   = $(graphics_dir)/include
compile_graphics_flags = -lGL -lm -lpthread -ldl -lrt -lX11
graphics_command       = $(graphics_lib_dir)/libraylib.a -I$(graphics_include_dir) -L$(graphics_lib_dir) $(compile_graphics_flags) 

project_name           = game
cxx_compiler           = g++
cxx_version            = -std=c++17
cxx_flags              = $(cxx_version) -Wall -Werror -pedantic

main_build_target      = $(build_dir)/$(project_name) 

$(main_build_target): | $(build_dir) 
	$(cxx_compiler) $(cxx_flags) -o $(build_dir)/$(project_name) $(src_dir)/main.cpp $(graphics_command)


$(build_dir):
	mkdir -p $(build_dir)

clean:
	rm -rf $(build_dir)

run: $(main_build_target)
	./$(main_build_target)
