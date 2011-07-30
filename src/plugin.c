#include <Python.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <dlfcn.h>
#include <glib.h>
#include <gtk/gtk.h>
#include <geanyplugin.h>
#include "plugin.h"


GeanyPlugin		*geany_plugin;
GeanyData		*geany_data;
GeanyFunctions	*geany_functions;


PLUGIN_VERSION_CHECK(200)

PLUGIN_SET_INFO(_("GeanyPy"),
				_("Python plugins support"),
				"1.0",
				"Matthew Brush <mbrush@codebrainz.ca>");


static void
GeanyPy_start_interpreter(const gchar *path_to_add)
{
    gchar *init_code;


	if (dlopen(GEANYPY_PYTHON_LIBRARY, RTLD_LAZY | RTLD_GLOBAL) == NULL)
    {
        g_warning("Unable to pre-load Python library.");
        return;
    }

    Py_Initialize();

    PyRun_SimpleString("import os,sys");
    init_code = g_strdup_printf(
        "sys.path.append('%s'.replace('~', os.path.expanduser('~')))",
        path_to_add);
    PyRun_SimpleString(init_code);
    g_free(init_code);
    init_geany_dialogs();
    init_geany_filetype();
    init_geany_document();
    PyRun_SimpleString("import geany");
}

static void
GeanyPy_stop_interpreter(void)
{
    if (Py_IsInitialized())
        Py_Finalize();
}


static void
GeanyPy_start_console(void)
{
    if (Py_IsInitialized())
        PyRun_SimpleString("geany.show_console()");
}


static void
on_geany_startup_complete(GObject unused, gpointer user_data)
{
    GeanyPy_start_console();
}


void plugin_init(GeanyData *data)
{
	GeanyPy_start_interpreter(GEANYPY_PYTHON_DIR);

    plugin_signal_connect(geany_plugin, NULL, "geany-startup-complete",
        TRUE, G_CALLBACK(on_geany_startup_complete), NULL);
}


void plugin_cleanup(void)
{
	GeanyPy_stop_interpreter();
}