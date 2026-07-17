###################################################################
#
# Static library
#
# Builds libemclib.a
#####################################################################

LIB_NAME := libemclib.a
LIB_BUILD := $(ROOT_BUILD)/build
LIB_OBJS := $(addprefix $(LIB_BUILD)/,$(patsubst %.c,%.o,$(LIB_SRCS)))