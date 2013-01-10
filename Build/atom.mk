LOCAL_PATH := $(call my-dir)

# Not with bionic
ifneq ("$(TARGET_LIBC)","bionic")

include $(CLEAR_VARS)

LOCAL_MODULE := libNetwork
LOCAL_DESCRIPTION := ardrone3 SDK Network Control Library

LOCAL_LIBRARIES := libSAL
LOCAL_EXPORT_LDLIBS := -lnetwork
# User define command to be launch before configure step.
# Generates files used by configure
define LOCAL_AUTOTOOLS_CMD_POST_UNPACK
	$(Q) cd $(PRIVATE_SRC_DIR) && ./bootstrap
endef

# User define command to be launch after dirclean
# Remove every files generated by bootstrap
define LOCAL_AUTOTOOLS_CMD_POST_DIRCLEAN
	$(Q) cd $(PRIVATE_SRC_DIR) && ./cleanup
endef

include $(BUILD_AUTOTOOLS)

endif
