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

assets_dir              = $(src_dir)/assets/
assets_stamp            = $(build_dir)/assets.stamp
copy_assets_command     = cp -R $(assets_dir) $(build_dir)

project_name            = game
cxx_compiler            = g++
cxx_version             = -std=c++17
cxx_flags               = $(cxx_version) -Wall -Werror -pedantic

sources                 = $(wildcard $(src_dir)/*.cpp)
objects                 = $(patsubst $(src_dir)/%.cpp, $(build_dir)/%.o, $(sources))
terminal_object         = $(build_dir)/terminal.o
terminal_library        = $(build_dir)/terminal.a
main_build_target       = $(build_dir)/$(project_name)

all: $(main_build_target)

$(main_build_target): $(objects) $(terminal_library) $(assets_stamp) | $(build_dir)
	$(cxx_compiler) $(cxx_flags) -o $@ $^ $(graphics_command) $(entt_command) -I$(terminal_module_dir)

$(build_dir)/%.o: $(src_dir)/%.cpp | $(build_dir)
	$(cxx_compiler) $(cxx_flags) -c -o $@ $< -I$(graphics_include_dir) $(entt_command) -I$(terminal_module_dir) 

$(terminal_object): $(terminal_module_dir)/terminal.cpp | $(build_dir)
	$(cxx_compiler) $(cxx_flags) -c -o $@ $< -I$(graphics_include_dir)

$(terminal_library): $(terminal_object)
	ar rcs $@ $<

$(build_dir):
	mkdir -p $@

$(assets_stamp): $(shell find $(assets_dir) -type f)
	@echo "Copying updated assets to $(build_dir)..."
	$(copy_assets_command)
	@touch $@

clean:
	rm -rf $(build_dir)

run: $(main_build_target)
	./$(main_build_target)

