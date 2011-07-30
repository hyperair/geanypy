/*
 * plugin.h
 *
 * Copyright 2011 Matthew Brush <mbrush@codebrainz.ca>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301  USA.
 *
 */

#ifndef PLUGIN_H
#define PLUGIN_H
#ifdef __cplusplus
extern "C" {
#endif


#ifndef GEANYPY_PYTHON_DIR
#define GEANYPY_PYTHON_DIR "/usr/local/share/geany/geanypy/geany"
#endif

#ifndef GEANYPY_PYTHON_LIBRARY
#define GEANYPY_PYTHON_LIBRARY "libpython2.6.so"
#endif


extern GeanyPlugin		*geany_plugin;
extern GeanyData		*geany_data;
extern GeanyFunctions	*geany_functions;


typedef struct
{
	PyObject_HEAD

	GeanyFiletype *ft;

    PyObject *display_name;

} Filetype;


typedef struct
{
	PyObject_HEAD

	GeanyDocument *doc;

} Document;


#ifndef PyMODINIT_FUNC
#define PyMODINIT_FUNC void
#endif

PyMODINIT_FUNC init_geany_document(void);

PyMODINIT_FUNC init_geany_filetype(void);
Filetype *Filetype_create_new_from_geany_filetype(GeanyFiletype *ft);

PyMODINIT_FUNC init_geany_dialogs(void);

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif /* PLUGIN_H */