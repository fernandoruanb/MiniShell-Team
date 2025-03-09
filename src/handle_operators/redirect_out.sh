#!/usr/bin/env bash
cc handle_redirect_out.c check_errno.c translate.c ../../src/execute/4-exec_cmd.c ../../src/0-utils.c ../../libft/libft.a
