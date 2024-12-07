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

project_name            = game
cxx_compiler            = g++
cxx_version             = -std=c++17
cxx_flags               = $(cxx_version) -Wall -Werror -pedantic

# Generar una lista de objetos basados en los archivos fuente
sources                 = $(wildcard $(src_dir)/*.cpp)
objects                 = $(patsubst $(src_dir)/%.cpp, $(build_dir)/%.o, $(sources))
terminal_object         = $(build_dir)/terminal.o
terminal_library        = $(build_dir)/terminal.a
main_build_target       = $(build_dir)/$(project_name)

# Regla principal
all: $(main_build_target)

# Regla para el ejecutable principal
$(main_build_target): $(objects) $(terminal_library) | $(build_dir)
	$(cxx_compiler) $(cxx_flags) -o $@ $^ $(graphics_command) $(entt_command) -I$(terminal_module_dir)

# Regla para compilar cada archivo fuente
$(build_dir)/%.o: $(src_dir)/%.cpp | $(build_dir)
	$(cxx_compiler) $(cxx_flags) -c -o $@ $< -I$(graphics_include_dir) $(entt_command) -I$(terminal_module_dir) 

# Compilar el módulo terminal
$(terminal_object): $(terminal_module_dir)/terminal.cpp | $(build_dir)
	$(cxx_compiler) $(cxx_flags) -c -o $@ $< -I$(graphics_include_dir)

$(terminal_library): $(terminal_object)
	ar rcs $@ $<

# Crear el directorio build
$(build_dir):
	mkdir -p $@

# Limpiar la compilación
clean:
	rm -rf $(build_dir)

# Ejecutar el programa
run: $(main_build_target)
	./$(main_build_target)

