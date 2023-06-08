URDFLIB_DIR := $(USERMOD_DIR)
URDFLIB_LIB_DIR := $(USERMOD_DIR)/../lib

# Zix Directory
SRC_USERMOD += $(URDFLIB_LIB_DIR)/zix/allocator.c
SRC_USERMOD += $(URDFLIB_LIB_DIR)/zix/btree.c
SRC_USERMOD += $(URDFLIB_LIB_DIR)/zix/bump_allocator.c
SRC_USERMOD += $(URDFLIB_LIB_DIR)/zix/digest.c
SRC_USERMOD += $(URDFLIB_LIB_DIR)/zix/errno_status.c
SRC_USERMOD += $(URDFLIB_LIB_DIR)/zix/hash.c
SRC_USERMOD += $(URDFLIB_LIB_DIR)/zix/path.c
SRC_USERMOD += $(URDFLIB_LIB_DIR)/zix/ring.c
SRC_USERMOD += $(URDFLIB_LIB_DIR)/zix/status.c
SRC_USERMOD += $(URDFLIB_LIB_DIR)/zix/string_view.c
SRC_USERMOD += $(URDFLIB_LIB_DIR)/zix/system.c
SRC_USERMOD += $(URDFLIB_LIB_DIR)/zix/tree.c

# Serd Directory
SRC_USERMOD += $(URDFLIB_LIB_DIR)/serd/base64.c
SRC_USERMOD += $(URDFLIB_LIB_DIR)/serd/byte_source.c
SRC_USERMOD += $(URDFLIB_LIB_DIR)/serd/env.c
SRC_USERMOD += $(URDFLIB_LIB_DIR)/serd/n3.c
SRC_USERMOD += $(URDFLIB_LIB_DIR)/serd/node.c
SRC_USERMOD += $(URDFLIB_LIB_DIR)/serd/reader.c
SRC_USERMOD += $(URDFLIB_LIB_DIR)/serd/string.c
SRC_USERMOD += $(URDFLIB_LIB_DIR)/serd/system.c
SRC_USERMOD += $(URDFLIB_LIB_DIR)/serd/uri.c
SRC_USERMOD += $(URDFLIB_LIB_DIR)/serd/writer.c

# Sord Directory
SRC_USERMOD += $(URDFLIB_LIB_DIR)/sord/sord.c
SRC_USERMOD += $(URDFLIB_LIB_DIR)/sord/syntax.c


# My Files
SRC_USERMOD += $(URDFLIB_DIR)/urdflib.c
SRC_USERMOD += $(URDFLIB_DIR)/graph.c


CFLAGS_USERMOD += -I$(URDFLIB_DIR)
URDFLIB_MOD_DIR := $(USERMOD_DIR)