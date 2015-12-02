#!/bin/bash

gcc \
	interpreter.c \
	core/core_script.c \
	core/core.c core/syntax_analysis.c \
	core/core_aux/core_aux_regex.c \
	core/core_aux/core_aux_str.c \
	core/core_variables.c \
	-lpcre \
	-omaverick
