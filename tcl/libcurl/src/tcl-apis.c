#include <tcl.h>
#include <string.h>
#include "scurl.h"

static int CurlCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]) {
	char * url;
	Tcl_Obj *result;
	if (objc < 2) {
		Tcl_WrongNumArgs(interp, 1, objv, "need an argument for url");
		return TCL_ERROR;
	}

	url = Tcl_GetString(objv[1]);

	Buffer * buf = get(url);
	if (buf == NULL) {
		result = Tcl_NewStringObj(scurl_err(), scurl_err_l());
		Tcl_SetObjResult(interp, result);
		return TCL_ERROR;
	}
	int length = buf->length;

	result = Tcl_NewStringObj(buf->buf, length);
	Tcl_SetObjResult(interp, result);

	buffer_close(buf);
	return TCL_OK;
}

int Scurl_Init(Tcl_Interp *interp) {
	Tcl_PkgProvide(interp, "scurl", "1.0");

	Tcl_CreateObjCommand(interp, "urlget", CurlCmd,
			(ClientData) NULL, (Tcl_CmdDeleteProc *)NULL);
	return TCL_OK;
}
