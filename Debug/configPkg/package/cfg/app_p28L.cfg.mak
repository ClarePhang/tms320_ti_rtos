# invoke SourceDir generated makefile for app.p28L
app.p28L: .libraries,app.p28L
.libraries,app.p28L: package/cfg/app_p28L.xdl
	$(MAKE) -f C:\Users\lamazavr\workspace_v6_0\tms320_ti_rtos/src/makefile.libs

clean::
	$(MAKE) -f C:\Users\lamazavr\workspace_v6_0\tms320_ti_rtos/src/makefile.libs clean

