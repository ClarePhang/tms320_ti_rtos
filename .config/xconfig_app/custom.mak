## THIS IS A GENERATED FILE -- DO NOT EDIT
.configuro: .libraries,28L linker.cmd package/cfg/app_p28L.o28L

# To simplify configuro usage in makefiles:
#     o create a generic linker command file name 
#     o set modification times of compiler.opt* files to be greater than
#       or equal to the generated config header
#
linker.cmd: package/cfg/app_p28L.xdl
	$(SED) 's"^\"\(package/cfg/app_p28Lcfg.cmd\)\"$""\"C:/Documents and Settings/salnikov/workspace_v6_1/tms320_ti_rtos/.config/xconfig_app/\1\""' package/cfg/app_p28L.xdl > $@
	-$(SETDATE) -r:max package/cfg/app_p28L.h compiler.opt compiler.opt.defs
