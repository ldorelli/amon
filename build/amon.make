# GNU Make project makefile autogenerated by Premake

ifndef config
  config=debug_native
endif

ifndef verbose
  SILENT = @
endif

.PHONY: clean prebuild prelink

ifeq ($(config),debug_native)
  RESCOMP = windres
  TARGETDIR = .
  TARGET = $(TARGETDIR)/libamon.so
  OBJDIR = obj/native/Debug/amon
  DEFINES +=
  INCLUDES += -I../includes/csys -I../includes/gpu -I../includes/social -I../includes/graph -I../includes/util -I../includes/util/json
  FORCE_INCLUDE +=
  ALL_CPPFLAGS += $(CPPFLAGS) -MMD -MP $(DEFINES) $(INCLUDES)
  ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -Og -fPIC -Wl,--no-as-needed -std=c++1y -fPIC -Wall -g -pthread
  ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CFLAGS)
  ALL_RESFLAGS += $(RESFLAGS) $(DEFINES) $(INCLUDES)
  LIBS += -lpthread
  LDDEPS +=
  ALL_LDFLAGS += $(LDFLAGS) -s -shared -pthread -g
  LINKCMD = $(CXX) -o $(TARGET) $(OBJECTS) $(RESOURCES) $(ALL_LDFLAGS) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
all: $(TARGETDIR) $(OBJDIR) prebuild prelink $(TARGET)
	@:

endif

ifeq ($(config),debug_win32)
  RESCOMP = windres
  TARGETDIR = .
  TARGET = $(TARGETDIR)/libamon.so
  OBJDIR = obj/win32/Debug/amon
  DEFINES +=
  INCLUDES += -I../includes/csys -I../includes/gpu -I../includes/social -I../includes/graph -I../includes/util -I../includes/util/json
  FORCE_INCLUDE +=
  ALL_CPPFLAGS += $(CPPFLAGS) -MMD -MP $(DEFINES) $(INCLUDES)
  ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -Og -fPIC -Wl,--no-as-needed -std=c++1y -fPIC -Wall -g -pthread
  ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CFLAGS)
  ALL_RESFLAGS += $(RESFLAGS) $(DEFINES) $(INCLUDES)
  LIBS += -lpthread
  LDDEPS +=
  ALL_LDFLAGS += $(LDFLAGS) -s -shared -pthread -g
  LINKCMD = $(CXX) -o $(TARGET) $(OBJECTS) $(RESOURCES) $(ALL_LDFLAGS) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
all: $(TARGETDIR) $(OBJDIR) prebuild prelink $(TARGET)
	@:

endif

ifeq ($(config),debug_win64)
  RESCOMP = windres
  TARGETDIR = .
  TARGET = $(TARGETDIR)/libamon.so
  OBJDIR = obj/win64/Debug/amon
  DEFINES +=
  INCLUDES += -I../includes/csys -I../includes/gpu -I../includes/social -I../includes/graph -I../includes/util -I../includes/util/json
  FORCE_INCLUDE +=
  ALL_CPPFLAGS += $(CPPFLAGS) -MMD -MP $(DEFINES) $(INCLUDES)
  ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -Og -fPIC -Wl,--no-as-needed -std=c++1y -fPIC -Wall -g -pthread
  ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CFLAGS)
  ALL_RESFLAGS += $(RESFLAGS) $(DEFINES) $(INCLUDES)
  LIBS += -lpthread
  LDDEPS +=
  ALL_LDFLAGS += $(LDFLAGS) -s -shared -pthread -g
  LINKCMD = $(CXX) -o $(TARGET) $(OBJECTS) $(RESOURCES) $(ALL_LDFLAGS) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
all: $(TARGETDIR) $(OBJDIR) prebuild prelink $(TARGET)
	@:

endif

ifeq ($(config),debug_macos)
  RESCOMP = windres
  TARGETDIR = .
  TARGET = $(TARGETDIR)/libamon.so
  OBJDIR = obj/macos/Debug/amon
  DEFINES +=
  INCLUDES += -I../includes/csys -I../includes/gpu -I../includes/social -I../includes/graph -I../includes/util -I../includes/util/json
  FORCE_INCLUDE +=
  ALL_CPPFLAGS += $(CPPFLAGS) -MMD -MP $(DEFINES) $(INCLUDES)
  ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -Og -fPIC -Wl,--no-as-needed -std=c++1y -fPIC -Wall -g -pthread
  ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CFLAGS)
  ALL_RESFLAGS += $(RESFLAGS) $(DEFINES) $(INCLUDES)
  LIBS += -lpthread
  LDDEPS +=
  ALL_LDFLAGS += $(LDFLAGS) -s -shared -pthread -g
  LINKCMD = $(CXX) -o $(TARGET) $(OBJECTS) $(RESOURCES) $(ALL_LDFLAGS) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
all: $(TARGETDIR) $(OBJDIR) prebuild prelink $(TARGET)
	@:

endif

ifeq ($(config),debug_linux86)
  RESCOMP = windres
  TARGETDIR = .
  TARGET = $(TARGETDIR)/libamon.so
  OBJDIR = obj/linux86/Debug/amon
  DEFINES +=
  INCLUDES += -I../includes/csys -I../includes/gpu -I../includes/social -I../includes/graph -I../includes/util -I../includes/util/json
  FORCE_INCLUDE +=
  ALL_CPPFLAGS += $(CPPFLAGS) -MMD -MP $(DEFINES) $(INCLUDES)
  ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -Og -fPIC -Wl,--no-as-needed -std=c++1y -fPIC -Wall -g -pthread
  ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CFLAGS)
  ALL_RESFLAGS += $(RESFLAGS) $(DEFINES) $(INCLUDES)
  LIBS += -lpthread
  LDDEPS +=
  ALL_LDFLAGS += $(LDFLAGS) -s -shared -pthread -g
  LINKCMD = $(CXX) -o $(TARGET) $(OBJECTS) $(RESOURCES) $(ALL_LDFLAGS) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
all: $(TARGETDIR) $(OBJDIR) prebuild prelink $(TARGET)
	@:

endif

ifeq ($(config),debug_linux64)
  RESCOMP = windres
  TARGETDIR = .
  TARGET = $(TARGETDIR)/libamon.so
  OBJDIR = obj/linux64/Debug/amon
  DEFINES +=
  INCLUDES += -I../includes/csys -I../includes/gpu -I../includes/social -I../includes/graph -I../includes/util -I../includes/util/json
  FORCE_INCLUDE +=
  ALL_CPPFLAGS += $(CPPFLAGS) -MMD -MP $(DEFINES) $(INCLUDES)
  ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -Og -fPIC -Wl,--no-as-needed -std=c++1y -fPIC -Wall -g -pthread
  ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CFLAGS)
  ALL_RESFLAGS += $(RESFLAGS) $(DEFINES) $(INCLUDES)
  LIBS += -lpthread
  LDDEPS +=
  ALL_LDFLAGS += $(LDFLAGS) -s -shared -pthread -g
  LINKCMD = $(CXX) -o $(TARGET) $(OBJECTS) $(RESOURCES) $(ALL_LDFLAGS) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
all: $(TARGETDIR) $(OBJDIR) prebuild prelink $(TARGET)
	@:

endif

ifeq ($(config),release_native)
  RESCOMP = windres
  TARGETDIR = .
  TARGET = $(TARGETDIR)/libamon.so
  OBJDIR = obj/native/Release/amon
  DEFINES +=
  INCLUDES += -I../includes/csys -I../includes/gpu -I../includes/social -I../includes/graph -I../includes/util -I../includes/util/json
  FORCE_INCLUDE +=
  ALL_CPPFLAGS += $(CPPFLAGS) -MMD -MP $(DEFINES) $(INCLUDES)
  ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -O2 -fPIC -Wl,--no-as-needed -std=c++1y -fPIC -Wall -g -pthread
  ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CFLAGS)
  ALL_RESFLAGS += $(RESFLAGS) $(DEFINES) $(INCLUDES)
  LIBS += -lpthread
  LDDEPS +=
  ALL_LDFLAGS += $(LDFLAGS) -s -shared -pthread -g
  LINKCMD = $(CXX) -o $(TARGET) $(OBJECTS) $(RESOURCES) $(ALL_LDFLAGS) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
all: $(TARGETDIR) $(OBJDIR) prebuild prelink $(TARGET)
	@:

endif

ifeq ($(config),release_win32)
  RESCOMP = windres
  TARGETDIR = .
  TARGET = $(TARGETDIR)/libamon.so
  OBJDIR = obj/win32/Release/amon
  DEFINES +=
  INCLUDES += -I../includes/csys -I../includes/gpu -I../includes/social -I../includes/graph -I../includes/util -I../includes/util/json
  FORCE_INCLUDE +=
  ALL_CPPFLAGS += $(CPPFLAGS) -MMD -MP $(DEFINES) $(INCLUDES)
  ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -O2 -fPIC -Wl,--no-as-needed -std=c++1y -fPIC -Wall -g -pthread
  ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CFLAGS)
  ALL_RESFLAGS += $(RESFLAGS) $(DEFINES) $(INCLUDES)
  LIBS += -lpthread
  LDDEPS +=
  ALL_LDFLAGS += $(LDFLAGS) -s -shared -pthread -g
  LINKCMD = $(CXX) -o $(TARGET) $(OBJECTS) $(RESOURCES) $(ALL_LDFLAGS) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
all: $(TARGETDIR) $(OBJDIR) prebuild prelink $(TARGET)
	@:

endif

ifeq ($(config),release_win64)
  RESCOMP = windres
  TARGETDIR = .
  TARGET = $(TARGETDIR)/libamon.so
  OBJDIR = obj/win64/Release/amon
  DEFINES +=
  INCLUDES += -I../includes/csys -I../includes/gpu -I../includes/social -I../includes/graph -I../includes/util -I../includes/util/json
  FORCE_INCLUDE +=
  ALL_CPPFLAGS += $(CPPFLAGS) -MMD -MP $(DEFINES) $(INCLUDES)
  ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -O2 -fPIC -Wl,--no-as-needed -std=c++1y -fPIC -Wall -g -pthread
  ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CFLAGS)
  ALL_RESFLAGS += $(RESFLAGS) $(DEFINES) $(INCLUDES)
  LIBS += -lpthread
  LDDEPS +=
  ALL_LDFLAGS += $(LDFLAGS) -s -shared -pthread -g
  LINKCMD = $(CXX) -o $(TARGET) $(OBJECTS) $(RESOURCES) $(ALL_LDFLAGS) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
all: $(TARGETDIR) $(OBJDIR) prebuild prelink $(TARGET)
	@:

endif

ifeq ($(config),release_macos)
  RESCOMP = windres
  TARGETDIR = .
  TARGET = $(TARGETDIR)/libamon.so
  OBJDIR = obj/macos/Release/amon
  DEFINES +=
  INCLUDES += -I../includes/csys -I../includes/gpu -I../includes/social -I../includes/graph -I../includes/util -I../includes/util/json
  FORCE_INCLUDE +=
  ALL_CPPFLAGS += $(CPPFLAGS) -MMD -MP $(DEFINES) $(INCLUDES)
  ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -O2 -fPIC -Wl,--no-as-needed -std=c++1y -fPIC -Wall -g -pthread
  ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CFLAGS)
  ALL_RESFLAGS += $(RESFLAGS) $(DEFINES) $(INCLUDES)
  LIBS += -lpthread
  LDDEPS +=
  ALL_LDFLAGS += $(LDFLAGS) -s -shared -pthread -g
  LINKCMD = $(CXX) -o $(TARGET) $(OBJECTS) $(RESOURCES) $(ALL_LDFLAGS) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
all: $(TARGETDIR) $(OBJDIR) prebuild prelink $(TARGET)
	@:

endif

ifeq ($(config),release_linux86)
  RESCOMP = windres
  TARGETDIR = .
  TARGET = $(TARGETDIR)/libamon.so
  OBJDIR = obj/linux86/Release/amon
  DEFINES +=
  INCLUDES += -I../includes/csys -I../includes/gpu -I../includes/social -I../includes/graph -I../includes/util -I../includes/util/json
  FORCE_INCLUDE +=
  ALL_CPPFLAGS += $(CPPFLAGS) -MMD -MP $(DEFINES) $(INCLUDES)
  ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -O2 -fPIC -Wl,--no-as-needed -std=c++1y -fPIC -Wall -g -pthread
  ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CFLAGS)
  ALL_RESFLAGS += $(RESFLAGS) $(DEFINES) $(INCLUDES)
  LIBS += -lpthread
  LDDEPS +=
  ALL_LDFLAGS += $(LDFLAGS) -s -shared -pthread -g
  LINKCMD = $(CXX) -o $(TARGET) $(OBJECTS) $(RESOURCES) $(ALL_LDFLAGS) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
all: $(TARGETDIR) $(OBJDIR) prebuild prelink $(TARGET)
	@:

endif

ifeq ($(config),release_linux64)
  RESCOMP = windres
  TARGETDIR = .
  TARGET = $(TARGETDIR)/libamon.so
  OBJDIR = obj/linux64/Release/amon
  DEFINES +=
  INCLUDES += -I../includes/csys -I../includes/gpu -I../includes/social -I../includes/graph -I../includes/util -I../includes/util/json
  FORCE_INCLUDE +=
  ALL_CPPFLAGS += $(CPPFLAGS) -MMD -MP $(DEFINES) $(INCLUDES)
  ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -O2 -fPIC -Wl,--no-as-needed -std=c++1y -fPIC -Wall -g -pthread
  ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CFLAGS)
  ALL_RESFLAGS += $(RESFLAGS) $(DEFINES) $(INCLUDES)
  LIBS += -lpthread
  LDDEPS +=
  ALL_LDFLAGS += $(LDFLAGS) -s -shared -pthread -g
  LINKCMD = $(CXX) -o $(TARGET) $(OBJECTS) $(RESOURCES) $(ALL_LDFLAGS) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
all: $(TARGETDIR) $(OBJDIR) prebuild prelink $(TARGET)
	@:

endif

OBJECTS := \
	$(OBJDIR)/epidemics.o \
	$(OBJDIR)/network_models.o \
	$(OBJDIR)/graph.o \
	$(OBJDIR)/social_networks.o \
	$(OBJDIR)/twitter.o \
	$(OBJDIR)/fenwick.o \
	$(OBJDIR)/json.o \
	$(OBJDIR)/progress_bar.o \

RESOURCES := \

CUSTOMFILES := \

SHELLTYPE := msdos
ifeq (,$(ComSpec)$(COMSPEC))
  SHELLTYPE := posix
endif
ifeq (/bin,$(findstring /bin,$(SHELL)))
  SHELLTYPE := posix
endif

$(TARGET): $(GCH) $(OBJECTS) $(LDDEPS) $(RESOURCES) ${CUSTOMFILES}
	@echo Linking amon
	$(SILENT) $(LINKCMD)
	$(POSTBUILDCMDS)

$(TARGETDIR):
	@echo Creating $(TARGETDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(TARGETDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(TARGETDIR))
endif

$(OBJDIR):
	@echo Creating $(OBJDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(OBJDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(OBJDIR))
endif

clean:
	@echo Cleaning amon
ifeq (posix,$(SHELLTYPE))
	$(SILENT) rm -f  $(TARGET)
	$(SILENT) rm -rf $(OBJDIR)
else
	$(SILENT) if exist $(subst /,\\,$(TARGET)) del $(subst /,\\,$(TARGET))
	$(SILENT) if exist $(subst /,\\,$(OBJDIR)) rmdir /s /q $(subst /,\\,$(OBJDIR))
endif

prebuild:
	$(PREBUILDCMDS)

prelink:
	$(PRELINKCMDS)

ifneq (,$(PCH))
$(OBJECTS): $(GCH) $(PCH)
$(GCH): $(PCH)
	@echo $(notdir $<)
	$(SILENT) $(CXX) -x c++-header $(ALL_CXXFLAGS) -o "$@" -MF "$(@:%.gch=%.d)" -c "$<"
endif

$(OBJDIR)/epidemics.o: ../src/csys/epidemics.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/network_models.o: ../src/csys/network_models.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/graph.o: ../src/graph/graph.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/social_networks.o: ../src/social/social_networks.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/twitter.o: ../src/social/twitter.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/fenwick.o: ../src/util/fenwick.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/json.o: ../src/util/json/json.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/progress_bar.o: ../src/util/progress_bar.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"

-include $(OBJECTS:%.o=%.d)
ifneq (,$(PCH))
  -include $(OBJDIR)/$(notdir $(PCH)).d
endif