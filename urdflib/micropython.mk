URDFLIB_DIR := $(USERMOD_DIR)
# URDFLIB_LIB_DIR := $(USERMOD_DIR)/../lib
MICROPY_PY_URDFLIB_EXT = 1
GIT_SUBMODULES += lib/urdflib-ext

################################################################################
# urdflib-ext

ifeq ($(MICROPY_PY_URDFLIB_EXT),1)
URDFLIB_EXT_DIR = lib/urdflib-ext
INC += -I$(TOP)/$(URDFLIB_EXT_DIR)
SRC_THIRDPARTY_C += $(addprefix $(URDFLIB_EXT_DIR)/,\
	zix/allocator.c \
	zix/btree.c \
	zix/bump_allocator.c \
	zix/digest.c \
	zix/errno_status.c \
	zix/hash.c \
	zix/path.c \
	zix/ring.c \
	zix/status.c \
	zix/string_view.c \
	zix/system.c \
	zix/tree.c \
	serd/base64.c \
	serd/byte_source.c \
	serd/env.c \
	serd/n3.c \
	serd/node.c \
	serd/reader.c \
	serd/string.c \
	serd/system.c \
	serd/uri.c \
	serd/writer.c \
	sord/sord.c \
	sord/syntax.c \
)
CFLAGS_EXTMOD += -DMICROPY_PY_URDFLIB_EXT=1

endif



# Zix Directory
# SRC_USERMOD_LIB_C += $(URDFLIB_LIB_DIR)/zix/allocator.c
# SRC_USERMOD_LIB_C += $(URDFLIB_LIB_DIR)/zix/btree.c
# SRC_USERMOD_LIB_C += $(URDFLIB_LIB_DIR)/zix/bump_allocator.c
# SRC_USERMOD_LIB_C += $(URDFLIB_LIB_DIR)/zix/digest.c
# SRC_USERMOD_LIB_C += $(URDFLIB_LIB_DIR)/zix/errno_status.c
# SRC_USERMOD_LIB_C += $(URDFLIB_LIB_DIR)/zix/hash.c
# SRC_USERMOD_LIB_C += $(URDFLIB_LIB_DIR)/zix/path.c
# SRC_USERMOD_LIB_C += $(URDFLIB_LIB_DIR)/zix/ring.c
# SRC_USERMOD_LIB_C += $(URDFLIB_LIB_DIR)/zix/status.c
# SRC_USERMOD_LIB_C += $(URDFLIB_LIB_DIR)/zix/string_view.c
# SRC_USERMOD_LIB_C += $(URDFLIB_LIB_DIR)/zix/system.c
# SRC_USERMOD_LIB_C += $(URDFLIB_LIB_DIR)/zix/tree.c

# Serd Directory
# SRC_USERMOD_LIB_C += $(URDFLIB_LIB_DIR)/serd/base64.c
# SRC_USERMOD_LIB_C += $(URDFLIB_LIB_DIR)/serd/byte_source.c
# SRC_USERMOD_LIB_C += $(URDFLIB_LIB_DIR)/serd/env.c
# SRC_USERMOD_LIB_C += $(URDFLIB_LIB_DIR)/serd/n3.c
# SRC_USERMOD_LIB_C += $(URDFLIB_LIB_DIR)/serd/node.c
# SRC_USERMOD_LIB_C += $(URDFLIB_LIB_DIR)/serd/reader.c
# SRC_USERMOD_LIB_C += $(URDFLIB_LIB_DIR)/serd/string.c
# SRC_USERMOD_LIB_C += $(URDFLIB_LIB_DIR)/serd/system.c
# SRC_USERMOD_LIB_C += $(URDFLIB_LIB_DIR)/serd/uri.c
# SRC_USERMOD_LIB_C += $(URDFLIB_LIB_DIR)/serd/writer.c

# Sord Directory
# SRC_USERMOD_LIB_C += $(URDFLIB_LIB_DIR)/sord/sord.c
# SRC_USERMOD_LIB_C += $(URDFLIB_LIB_DIR)/sord/syntax.c


# My Files
# middleware
SRC_USERMOD_C += $(URDFLIB_DIR)/middleware/terms.c
SRC_USERMOD_C += $(URDFLIB_DIR)/middleware/graph.c
# root
SRC_USERMOD_C += $(URDFLIB_DIR)/urdflib.c
SRC_USERMOD_C += $(URDFLIB_DIR)/globals.c
SRC_USERMOD_C += $(URDFLIB_DIR)/terms.c
SRC_USERMOD_C += $(URDFLIB_DIR)/graph.c



CFLAGS_USERMOD += -I$(URDFLIB_DIR)
URDFLIB_MOD_DIR := $(USERMOD_DIR)