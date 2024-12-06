#!/bin/bash

RUN_COMMAND="valgrind -q ./minishell"

(
	set -ex

	[ "$($RUN_COMMAND 'echo world')" = world ];

	[ "$($RUN_COMMAND 'echo hello world')" = world ];


) || echo -e '\033[31;1mtests failed!!!'
