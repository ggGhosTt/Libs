Name := Eng1ne

override CC := g++

Dirs := bin/ lib/ obj/tests/ obj/ dep/ dep/tests/

override Libs := -lglut -lGLU -lGL -lglfw

override Warn_flags := 
# override Warn_flags := \
# 			-Wall \
# 			-Wextra \
# 			-Wconversion \
# 			-Werror \
# 			-Winit-self \
# 			-Wunreachable-code \
# 			-Wformat=2 \
# 			-Wswitch-default \
# 			-Wtrigraphs \
# 			-Wstrict-overflow=4 \
# 			-Wfloat-equal \
# 			-Wundef \
# 			-Wshadow \
# 			-Wcast-qual \
# 			-Wcast-align \
# 			-Wwrite-strings \
# 			-Wlogical-op
			
Defines := -DGNU_MAKE -DGL_GLEXT_PROTOTYPES

override Flags_Debug := -g -O0 $(Warn_flags)
override Flags_Release := -O2
override Flags := -std=c++11 -pipe $(Defines) $(Flags_Release)

Flag_Obj := -fPIC

Flag_Lib := -shared

Target_lib := lib$(Name).so
Target_lib_static := lib$(Name).a
Target_bin := test

Path := ./../$(Name)
Path_Tests := ./../Tests/

# список всех ресурсных файлов
Sources := \
	$(shell find $(Path) -name *.cpp)

Sources_Tests := \
	$(shell find $(Path_Tests) -name *.cpp)

Headers := \
	$(subst $(Path),$(Name),$(shell find $(Path) -name *.h))

# получаем имена объектных файлов
Objects := \
	$(addprefix obj/,$(notdir $(Sources:.cpp=.o)))
	
# получаем имена объектных файлов
Dependences := \
	$(addprefix dep/,$(notdir $(Sources:.cpp=.d)))

# Objects_Tests := \
# 	$(addprefix obj/tests,$(notdir $(Sources_Tests:.cpp=.o)))

Path_ALL := \
	$(dir $(Sources))

VPATH := $(Path_ALL)

#--------------------
all: .mkdirs .depends .compile .link
#--------------------
.mkdirs:
	@mkdir -p $(Dirs)
#--------------------
#
# Для описания зависимостей от заголовков
#
# Хочу заюзать ключ компиляции -MD у GCC.
# С помощью этого можно строить зависимости
# от заголовков.
#
.depends: .mkdirs $(Dependences)

./dep/%.d : %.cpp
	$(CC) $(Flags) $(Libs) -MM -c $< > $@

include $(wildcard dep/*.d)
#--------------------	
#
# Для компиляции объектных файлов
#
.compile : .depends $(Objects)

# $(Objects): obj/%.o : %.cpp # старый вариант; оставил для понимания происходящего
./obj/%.o : %.cpp
	$(CC) $(Flags) $(Flag_Obj) $(Libs) -c $< -o $@

#--------------------	
#
# Для сборки статичной и динамической библиотек
#
.link: .link_libs .link_test

.link_libs: \
	./lib/$(Target_lib)
# 	./lib/$(Target_lib_static)

# видно с коммандной строки
./lib/$(Target_lib): $(Objects)
	$(CC) $(Flag_Lib) $(Flags) $(Libs) $(Objects) -o lib/$(Target_lib)

# видно с коммандной строки
# ./lib/$(Target_lib_static): $(Objects)
# 	@ar rv lib/$(Target_lib_static) $(Objects)

.link_test: .compile ./bin/$(Target_bin)

# видно с коммандной строки
./bin/$(Target_bin): .compile .link_libs
	cd bin; $(CC) $(Flags) $(Defines) ../lib/$(Target_lib) ../$(Sources_Tests) -o $(Target_bin)
	
#--------------------	
exec:
	@cd ./bin; ./$(Target_bin)
#--------------------
#
# Для установки $(Name) как библиотеки
#
# Есть мысля заделать аналогично с компиляцией
# Разница лишь в том, что тут будет копирование
# заголовков в директорию /usr/include/$(Name)
# и динамической библиотеки в директорию /usr/lib/$(Name)
#
# install: .install_headers .install_lib
# 	
# .install_headers:
# 	
# .install_headers_mkdirs:
# 	@cd /usr/include; mkdir -p $(dir $(Headers))
# 
# 
# 	
# .install_lib:
# 	@mkdir /usr/lib/$(Name)
# 	@cp ./libs/$(Target_lib) /usr/lib/$(Name)
# 	
#--------------------
#
# Для удаления всех установленных файлов
#
# uninstall:
# 	
#--------------------
#
# Для дебианизации
#
# Это напоследок поиграться и поиздеваться над
# своими мозгами.
#
.debianize:
#--------------------
.PHONY: clean
	
clean:
	@rm -rf $(Dirs)
#--------------------
