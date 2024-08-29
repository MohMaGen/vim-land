name := vim-land
target ?= linux

target-base-dir = target/

ifeq ($(target), linux)
	compiler := /usr/bin/gcc
	target-dir := $(target-base-dir)linux/
	platform-os := LINUX
else
	target-dir := $(target-base-dir)windows/
	compiler := x86_64-w64-mingw32-gcc
	platform-os := WINDOWS
endif

target-libs-dir := $(target-dir)libs/
target-objs-dir := $(target-dir)objs/
public-incl-dir := inc/

debug-run: debug
	$(target-dir)$(name)-debug

debug: prepare-dirs include-shaders raylib $(name)-debug
	@echo "build debug for <$(target)>:"

prepare-dirs:
	@echo "prepare dirs:"
	mkdir -p target/linux/objs
	mkdir -p target/windows/objs
	mkdir -p target/linux/libs
	mkdir -p target/windows/libs
	mkdir -p target/linux/xmpls
	mkdir -p target/windows/xmpls

raylib:
	@echo "build raylib"
	@make -C ./raylib/src clean
	@make CC=$(compiler) -C ./raylib/src PLATFORM=PLATFORM_DESKTOP PLATFORM_OS=$(platform-os)
	@mv ./raylib/src/libraylib* $(target-libs-dir)



src-dir := src/
core-dir := $(src-dir)core/
private-incl-dir := $(core-dir)

sources := $(wildcard $(core-dir)*.c)
objects := $(patsubst $(core-dir)%.c, $(target-objs-dir)%.o, $(sources))

xmpls-srcs := $(wildcard $(src-dir)xmpl-*.c)
xmpls-objs := $(patsubst $(src-dir)%.c, $(target-objs-dir)%.o, $(xmpls-srcs))
xmpls-exes := $(patsubst $(target-objs-dir)%.o, $(target-dir)%, $(xmpls-objs))

main-src := $(src-dir)main.c
main-obj := $(target-objs-dir)main.o
main-exe := $(target-dir)$(name)-debug

compiler-flags := -Wall -Werror -g3 -ggdb -v --pedantic -pedantic-errors
libs := -lraylib -lm -lpthread
linker-flags := -I $(private-incl-dir) -I $(public-incl-dir) -L $(target-libs-dir) $(libs)

examples: $(objects) debug $(xmpls-exes)
	@echo "examples builed."

$(xmpls-exes): $(target-dir)%: $(target-objs-dir)%.o
	@echo "link example exe {$@}:"
	@$(compiler) -o $@ $< $(objects) $(compiler-flags) $(linker-flags)

$(xmpls-objs): $(target-objs-dir)%.o: $(src-dir)%.c
	@echo "build example obj {$@}:"
	@$(compiler) -o $@ -c $< $(compiler-flags) $(linker-flags)

$(name)-debug: $(main-obj) $(objects)
	@echo "link $(name)-debug exe {$@}:"
	@$(compiler) -o $(main-exe) $(main-obj) $(objects) $(compiler-flags) $(linker-flags)

$(main-obj): $(main-src)
	@echo "build main object:"
	@$(compiler) -o $(main-obj) -c $(main-src) $(compiler-flags) $(linker-flags)

$(objects): $(target-objs-dir)%.o: $(core-dir)%.c
	@echo "build core object {$@}"
	@$(compiler) -o $@ -c $< $(compiler-flags) $(linker-flags)

commands-srcs := $(patsubst $(core-dir)%.c, compile_commands_%, $(sources))
compile-commands: clear-compile-commands $(commands-srcs) commands_main

clear-compile-commands:
	bash -c "[[ -f ./compile_commands.json ]] && rm ./compile_commands.json || echo a"

$(commands-srcs): compile_commands_%: $(core-dir)%.c
	./scripts/add_obj_to_compile_commands.sh $< "$(compiler) -o $@ -c $< $(compiler-flags) $(linker-flags)"

commands_main:
	./scripts/add_obj_to_compile_commands.sh $(main-src) "$(compiler) -o $(main-obj) -c $(main-src) $(compiler-flags) $(linker-flags)"


shaders-dir := shaders/
shaders-fs := $(wildcard $(shaders-dir)*.frag)
shaders-vs := $(wildcard $(shaders-dir)*.vert)
shaders-names-fs := $(patsubst $(shaders-dir)%.frag, %_fragment_shader, $(shaders-fs))
shaders-names-vs := $(patsubst $(shaders-dir)%.vert, %_vertex_shader, $(shaders-vs))
shaders-srcs = $(core-dir)shaders-srcs.c

include-shaders: clear-shaders $(shaders-names-vs) $(shaders-names-fs)
	@echo "shaders included"

clear-shaders:
	@echo "clear shaders"
	./scripts/clear_shaders-c_file.sh $(shaders-srcs)

$(shaders-names-fs): %_fragment_shader: $(shaders-dir)%.frag
	echo "include shader $@"
	cat $< | ./scripts/format_shader.awk -v name="$@" >> $(shaders-srcs)

$(shaders-names-vs): %_vertex_shader: $(shaders-dir)%.vert
	echo "include shader $@"
	cat $< | ./scripts/format_shader.awk -v name="$@" >> $(shaders-srcs)
