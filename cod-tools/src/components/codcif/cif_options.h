/*---------------------------------------------------------------------------*\
**$Author: andrius $
**$Date: 2017-04-12 13:39:05 +0300 (Wed, 12 Apr 2017) $ 
**$Revision: 5195 $
**$URL: svn://www.crystallography.net/cod-tools/branches/experiment/andrius-codcif-CRUD-API/src/components/codcif/cif_options.h $
\*---------------------------------------------------------------------------*/

#ifndef __CIF_OPTIONS_H
#define __CIF_OPTIONS_H

typedef enum cif_option_t {
    DO_NOT_UNPREFIX_TEXT = 1,
    DO_NOT_UNFOLD_TEXT   = 2,
    FIX_ERRORS           = 4,
    FIX_DUPLICATE_TAGS_WITH_SAME_VALUES  = 8,
    FIX_DUPLICATE_TAGS_WITH_EMPTY_VALUES = 16,
    FIX_DATA_HEADER      = 32,
    FIX_DATABLOCK_NAMES  = 64,
    FIX_STRING_QUOTES    = 128,
    CO_SUPPRESS_MESSAGES = 256,
    CO_DO_NOT_REPORT_LONG_LINES = 512,
    CO_COUNT_LINES_FROM_2 = 1024,
} cif_option_t;

cif_option_t cif_option_default();
cif_option_t cif_option_set( cif_option_t options, cif_option_t opt );
cif_option_t cif_option_set_fix_errors( cif_option_t );
cif_option_t cif_option_set_do_not_unprefix_text( cif_option_t copt );
cif_option_t cif_option_set_do_not_unfold_text( cif_option_t copt );
cif_option_t
cif_option_set_fix_duplicate_tags_with_same_values( cif_option_t copt );
cif_option_t
cif_option_set_fix_duplicate_tags_with_empty_values( cif_option_t copt );
cif_option_t cif_option_set_fix_data_header( cif_option_t copt );
cif_option_t cif_option_set_fix_datablock_names( cif_option_t copt );
cif_option_t cif_option_set_fix_string_quotes( cif_option_t copt );
cif_option_t cif_option_suppress_messages( cif_option_t copt );
cif_option_t cif_option_count_lines_from_2( cif_option_t copt );

#endif
