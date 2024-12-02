build_dir               = ./build
src_dir                 = ./src
terminal_module_dir     = $(src_dir)/terminal
dependencies_dir        = ./dependencies
entt_dir                = $(dependencies_dir)/entt-3.14.0/single_include/entt/
graphics_dir            = $(dependencies_dir)/raylib
graphics_lib_dir        = $(graphics_dir)/lib
graphics_include_dir    = $(graphics_dir)/include
compile_graphics_flags  = -lGL -lm -lpthread -ldl -lrt -lX11
graphics_command        = $(graphics_lib_dir)/libraylib.a -I$(graphics_include_dir) -L$(graphics_lib_dir) $(compile_graphics_flags)
entt_command            = -I$(entt_dir)

##
## Compiling the Terminal static library...
##
terminal_build_command          = $(cxx_compiler) -c -o $(build_dir)/terminal.o $(terminal_module_dir)/terminal.cpp -I$(graphics_include_dir)
terminal_build_library_command  = ar rcs $(build_dir)/terminal.a $(build_dir)/terminal.o
terminal_module_compile_command = $(build_dir)/terminal.a -I$(terminal_module_dir)

project_name            = game
cxx_compiler            = g++
cxx_version             = -std=c++17
cxx_flags               = $(cxx_version) -Wall -Werror -pedantic

main_build_target       = $(build_dir)/$(project_name)

$(main_build_target): | $(build_dir)
	$(terminal_build_command)
	$(terminal_build_library_command)
	$(cxx_compiler) $(cxx_flags) -o $(build_dir)/$(project_name) $(src_dir)/main.cpp $(terminal_module_compile_command) $(graphics_command) $(entt_command)

$(build_dir):
	mkdir -p $(build_dir)

clean:
	rm -rf $(build_dir)

run: $(main_build_target)
	./$(main_build_target)

